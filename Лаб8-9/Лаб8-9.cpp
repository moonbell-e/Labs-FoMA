#include <iostream>
#include <fstream>
#include <Windows.h>
#include <stack>

using namespace std;

ofstream file("Lab8-9.txt");

const int n = 10; //количество вершин графа
int matrix_nodes[n][n] =  //массив смежности графа
{ {0,1,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,1},
{0,0,0,0,0,0,1,1,0,0},
{0,0,0,1,0,0,1,0,0,0},
{1,0,0,0,1,0,0,0,0,0},
{0,1,0,0,0,0,0,0,0,1},
{0,0,1,0,0,1,0,0,0,0},
{1,0,0,0,0,1,0,1,0,0},
{0,1,0,0,0,0,0,1,0,0} };

struct item { //структура элемента
	int data;
	item* next;
	item* prev;
};


class stack_ {
private:
	struct nodes {
		int first;
		int last;
	};
	stack <nodes> steck; //стек для хранения связей
	nodes stack_s; //узел вершины
	int vertex; //вершина, в которую хотим попасть
	stack <int> queue; //очередь
	bool visited[n]; //массив посещенных вершин

public:
	void search_in_depth(int start, int end)
	{
		visited[start] = 1; // посещенная
		for (int i = 0; i < n; i++) 
		{
			if (matrix_nodes[start][i] == 1 and visited[i] == 0) 
			{
			stack_s.first = start; 
			stack_s.last = i;
			steck.push(stack_s); 
			if (start == end) break; 
			search_in_depth(i, end);
			}
		}
	}

	void way_search() {
		int start;
		for (int i = 0; i < n; i++) // исходно все вершины равны 0
			visited[i] = 0;
		cout << "Введите начальную точку (нумерация с 0): ";
		cin >> start;
		cout << "До какой точки рассчитать маршрут(нумерация с 0): ";
		cin >> vertex;
		search_in_depth(start, vertex);
		cout << "Путь: " << endl;
		file << "Путь (через стек): " << endl;
		while (!steck.empty()) // пока стек не пуст
		{
			stack_s = steck.top();
			steck.pop();
			if (stack_s.last == vertex)
			{
				vertex = stack_s.first;
				cout << " <- " << vertex;
				file << " <- " << vertex;
			}
		}
		cout << endl;
		file << endl;
	}
};

class recursion {
private:
	bool visited[n]; //массив пройденных вершин
	int ways[n]; //массив родительских вершин
	int count;
public:
	
	void function(int vertex) {
		for(int i = 0; i < n; i++)
			if (!visited[i] && matrix_nodes[vertex][i] == 1)
			{
				ways[i] = vertex;
				visited[i] = true;
				function(i);
			}
	}

	void search_in_depth() {
		int start;
		for (int i = 0; i < n; i++)
			visited[i] = false;
		cout << "Введите начальную точку (нумерация с 0): ";
		cin >> start;
		visited[start] = true;
		ways[start] = -1;
		function(start);
		int end;
		cout << "До какой точки рассчитать маршрут(нумерация с 0): ";
		cin >> end;
		int dne = end;
		int count = 0;
		do {
			count++;
			dne = ways[dne];
		} while (dne != ways[start]);
		int* rev = new int[count];
		int i = 0;
		rev[i] = end;
		i++;
		do {
			rev[i] = ways[end];
			i++;
			end = ways[end];
		} while (end != start);
		i--;
		cout << "Путь: ";
		file << "Путь (через рекурсию): ";
		while (i >= 0)
		{
			cout << rev[i] << " ";
			file << rev[i] << " ";
			i--;
		}
		cout << endl;
		file << endl;
	}


};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	recursion _recursion;
	stack_ stck;

	stck.way_search();
	
	_recursion.search_in_depth();

	file << "Матрица смежности:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			file << matrix_nodes[i][j] << " ";
		}
		file << endl;
	}
}