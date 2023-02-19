#include <iostream>
#include <limits.h>
#include <fstream>
#include <Windows.h>


using namespace std;
const int infinity = INT_MAX;


int main() {
	SetConsoleCP(1251); //русификация консоли
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	int n, first_v, last_v, temp, min_index, min, weight; //количество вершин, начальная и конечная вершины
	ifstream _file("Lab6.txt"); 
	ofstream file("Lab61.txt");
	cout << "Введите количество вершин: ";
	cin >> n;
	cout << "Введите начальную вершину: ";
	cin >> first_v;
	cout << "Введите конечную вершину: ";
	cin >> last_v;



	int** matrix_nodes = new int* [n]; //инициализация матрицы связей (массива)
	int* min_distance = new int[n]; //инициализация массива кратчайших расстояний
	int* visited = new int[n]; //инициализация массива посещенных вершин

	for (int i = 0; i < n; i++) //необходимо выделить память для чтения с файла
		matrix_nodes[i] = new int[n];

	//чтение матрицы с файла
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			_file >> matrix_nodes[i][j];
		}
	}
	_file.close();

	//вывод матрицы связей
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << matrix_nodes[i][j];
			cout << " "; //пробел между числами
		}
		cout << endl; //переход на новую строку
	}
	//инициализация вершин и расстояний
	for (int i = 0; i < n; i++)
	{
		min_distance[i] = infinity;
		visited[i] = 1;
	}
	min_distance[first_v - 1] = 0;

	//шаг алгоритма
	do {
		min_index = infinity;
		min = infinity;
		for (int i = 0; i < n; i++)
		{ //если вершину еще не обошли и вес меньше min
			if ((visited[i] == 1 && (min_distance[i] < min)))
			{ //переписываем значения
				min = min_distance[i];
				min_index = i;
			}
		}
		//добавляем найденный минимальный вес к текущему весу вершины и сравниваем с текущим мин. весом вершины
		if (min_index != infinity)
		{
			for (int i = 0; i < n; i++)
			{
				if (matrix_nodes[min_index][i] > 0)
				{
					temp = min + matrix_nodes[min_index][i];
					if (temp < min_distance[i])
					{
						min_distance[i] = temp;
					}
				}
			}
			visited[min_index] = 0;
		}
	} while (min_index < infinity);

	visited[0] = last_v; //начальный элемент - конечная вершина
	int count = 1; //индекс предыдущей вершины
	weight = min_distance[last_v - 1]; //вес конечной вершины
	//восстановление пути
	while (last_v-1 != first_v-1) //пока не дошли до начальной вершины
	{
		for (int i = 0; i < n; i++)
			if (matrix_nodes[i][last_v - 1] != 0) //если есть связь
			{
				temp = weight - matrix_nodes[i][last_v - 1];
				if (temp == min_distance[i])
				{
					weight = temp;
					last_v = i + 1;
					visited[count] = i + 1;
					count++;
				}
			}
	}
	//запись в файл матрицы расстояний
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix_nodes[i][j] != 0)
			{
				file << "Начальная вершина: " << i + 1 << " ";
				file << "Конечная вершина: " << j + 1 << " ";
				file << "Расстояние между вершинами: " << matrix_nodes[i][j] << endl;
			}
		}
		file << endl; //переход на новую строку
	}
	file << "Кратчайшие расстояния до вершин " << endl;
	for (int i = 0; i < n; i++)
		file << min_distance[i] << " ";

	file << endl << "Промежуточные вершины от ";
	if (first_v != 0)
	{
		file << first_v << " до ";
		file << visited[0] << endl;
		for (int i = count - 1; i >= 0; i--)
		{
			file << visited[i] << " ";
		}
	}

}
