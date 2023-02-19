#include <iostream>
#include <fstream>

using namespace std;

ofstream file("Lab7.txt");

const int n = 10; //количество вершин
int matrix_nodes[n][n] = //массив смежности графа
{ {0,1,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,1},
{0,0,0,0,0,0,1,1,0,0},
{0,0,0,1,0,0,1,0,0,0},
{1,0,0,0,1,0,0,0,0,0},
{0,1,0,0,0,0,0,0,0,1},
{0,0,1,0,0,1,0,0,0,0}, 
{1,0,0,0,0,1,0,1,0,0},
{0,1,0,0,0,0,0,1,0,0}};

bool visited[n]; //массив пройденных вершин
int ways[n]; //массив родительских вершин

struct item { // cтруктура элемента
	int data;
	item* next;
	item* prev;

};

class queue {

private:
	item* first; // адрес первого элемента в списке
	item* last; // адрес последнего элемента в списке
	int count; // количество элементов в списке

public:
	queue() {
		last = NULL;
		first = NULL;
		count = 0;
	}

	void add(int a) { // добавление элемента в конец списка (push_fifo)

		item* newitem = new item; //выделяем память для нового элемена

		newitem->data = a;
		if (first == NULL) {

			first = newitem;

		}
		newitem->next = NULL;
		newitem->prev = last;

		if (last != NULL) {
			last->next = newitem;

		}
		last = newitem;
		count++;

	}

	void del_first() { // удаление элемента из начала очереди (pop_fifo)
		item* place = first;
		if (place != last) { // если элемент первый, но НЕ последний
			place->next->prev = NULL;
			first = place->next;

		}

		else { // если элемент первый и последний
			first = NULL;
			last = NULL;

		}
		delete place;
		count--;

	}

	bool empty() { // возвращает true если очередь пустая и false если нет
		bool empt;

		if (first == NULL) {
			empt = true;
		}
		else empt = false;
		return empt;

	}
	int first_data() //возвращает значение из начала очереди
	{
		return first->data;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	queue Que;
	int start;
	for (int i = 0; i < n; i++) //исходно все вершины равны
	{
		visited[i] = 0;
	}
	cout << "Из какой вершины начинается путь? ";
	cin >> start;
	start;
	Que.add(start); //помещаем в очередь первый элемент
	visited[start] = 1; 
	ways[start] = -1;
	while (!Que.empty()) //пока очередь не пуста
	{
		int unit = Que.first_data();
		Que.del_first();
		for (int i = 0; i < n; i++)
		{
			if ((visited[i] == 0) && (matrix_nodes[unit][i] == 1))
			{
				Que.add(i);
				ways[i] = unit;
				visited[i] = 1;
			}
		}
	}
	int end;
	cout << "До какой точки рассчитать маршрут? ";
	cin >> end;
	end;

	int dne = end;
	int count = 0;
	do {
		count++;
		dne = ways[dne];
	} while (dne != ways[start]);
	int* rev = new int[count]; //выделение памяти для массива пути
	int i = 0;
	rev[i] = end;
	i++;
	do { //будем сортировать массив пути
		rev[i] = ways[end];
		i++;
		end = ways[end];
	} while (end != start); //пока не сравняются начало и конец
	i--;
	cout << "Путь: ";
	while (i >= 0)
	{
		cout << rev[i] << " ";
		i--;
	}

	file << "Матрица смежности:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			file << matrix_nodes[i][j] << " ";
		}
		file << endl;
	}
	file << "Маршрут: " << endl;
	for (int i = count - 1; i >= 0; i--) {
		file << rev[i] << " ";
	}
	file.close();

	cout << '\n';
	system("pause");
	return 0;
}