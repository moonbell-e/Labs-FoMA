#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

int state_menu;
int value, _search;
void Menu()
{
	cout << "Введите операцию, которую хотите воспроизвести: " << endl;
	cout << "(0) Выход из программы" << endl
		<< "(1) Удаление элемента бинарного дерева" << endl
		<< "(2) Добавление элемента бинарного дерева" << endl
		<< "(3) Сохранение в файл" << endl
		<< "(4) Вывод бинарного дерева" << endl
		<< "(5) Поиск элемента бинарного дерева" << endl
		<< "(6) Прямой обход бинарного дерева" << endl;
	cin >> state_menu;
}
int tabs, sw;
struct bin_node {
	int data; //содержание узла
	bin_node* left; //указатель на левый узел
	bin_node* right; //указатель на правый узел
};

struct bin_tree
{
	bin_node node;
	struct bin_node* root; //указатель на корень дерева;
	int count; //количество вершин в дереве
};

struct bin_node* add_node(int x, bin_node*& tree) //функция вставки и создания дерева
{
	if (tree == NULL) { // Если дерева нет, то формируем корень
		tree = new bin_node; // память под узел
		tree->data = x;   // поле данных
		tree->left = NULL;
		tree->right = NULL; // ветви инициализируем пустотой
	}
	else  if (x < tree->data)   // условие добавление левого потомка
		tree->left = add_node(x, tree->left);
	else    // условие добавление правого потомка
		tree->right = add_node(x, tree->right);
	return(tree);
}


void straight_pass(bin_node*& tree) { //прямой обход - рекурсивно от корневого элемента к левым, а затем к правым
	if (!tree) return;
	cout << tree->data << " "; //Отображаем корень дерева
	straight_pass(tree->left); //Рекурсивная функция для левого поддерева
	straight_pass(tree->right); //Рекурсивная функция для правого поддерева
}

void print(bin_node* tree)
{
	if (!tree) return; //если ветки не существует - выводить нечего
	tabs += 5; //счетчик рекурсивно вызванных процедур, считающий отступы для вывода

	print(tree->left); //выводим ветку и ее подветки слева
	for (int i = 0; i < tabs; i++) cout << " "; //затем отступы
	cout << tree->data << endl; //данные этой ветки

	print(tree->right); //данные ветки справа

	tabs -= 5; //после уменьшаем количество отступов
	return;
}

bool search(const bin_node* tree, int data) //рекурсивно ищем данные, пока не находим нужное
{
	if (tree == NULL) {
		cout << "Не найдено! ";
		return false;
	}
	if (tree->data == data) { 
		cout << "Элемент найден в бинарном дереве ";
		return true;
	}
	else
	{
		if (data > tree->data)
			search(tree->right, data);
		else
			search(tree->left, data);
	}
}

bin_node* delete_element(bin_node*& tree, int data)
{
	if (data == tree->data) { //если у удаляемого элемента есть хотя бы один дочерний элемент,
		//то наибольший дочерний становится на место удаляемого элемента

		bin_node* tmp; //возвращаемый элемент
		if (tree->right == NULL) //если правый элемент равен 0
			tmp = tree->left; //возвращаемый файл равен левому элементу
		else { 
			bin_node* ptr = tree->right; //иначе если у элемента есть правый элемент
			if (ptr->left == NULL) {  //если его левый потомок равен 0
				ptr->left == tree->left;
				tmp = ptr; //то удаляем правый элемент дерева, левый становится на его место
			}
			else { //если его левый потомок не равен нулю
				bin_node* pmin = ptr->left;
				while (pmin->left != NULL) { 
					ptr = pmin;

					pmin = ptr->left;
				}
				ptr->left = pmin->right;
				pmin->left = tree->left;
				pmin->right = tree->right;
				tmp = pmin; //то мы удаляем наибольший дочерний элемент
			}
		}
		delete tree; 
		return tmp; 
	}
	else if (data < tree->data) 
		tree->left = delete_element(tree->left, data);
	else
		tree->right = delete_element(tree->right, data);
	return tree;
}

void save_to_file(ofstream& f, bin_node*& temp)
{
	if (temp == NULL) return; //если дерево пустое, возвращаемся
	else
	{
		tabs += 5;

		save_to_file(f, temp->left); //левые значения
		for (int i = 0; i < tabs; i++)  f << " ";
		f << temp->data << endl; //записываем корень

		save_to_file(f, temp->right); //правые значения

		tabs -= 5; //после уменьшаем количество отступов
		return;
	}
}


int main()
{
	ofstream _file("temp.txt");
	setlocale(LC_ALL, "ru");
	struct bin_node* root;
	int num = 0;
	int element;
	root = NULL;
	cout << "Введите любые числа (для выхода введите 2021): " << endl;
	while (num != 2021) {
		cin >> num;
		if (num != 2021) root = add_node(num, root);
	}
	cout << "Бинарное дерево: " << endl;
	print(root);

	Menu();

	while (state_menu != 0)
	{
		switch (state_menu)
		{
		case 1:
			cout << "Введите элемент: ";
			cin >> element;
			delete_element(root, element);
			print(root);
			cout << endl << "Прямой обход: ";
			straight_pass(root);
			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 2:
			cout << "Введите элемент: ";
			cin >> element;
			add_node(element, root);
			print(root);
			cout << endl << "Прямой обход: ";
			straight_pass(root);
			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 3:
			save_to_file(_file, root);
			_file.close();

			cout << "Данные записаны в файл!";
			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 4:
			print(root);

			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 5:
			cout << "Введите элемент: ";
			cin >> _search;
			search(root, _search);

			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 6:
			straight_pass(root);

			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		}
	}
}

