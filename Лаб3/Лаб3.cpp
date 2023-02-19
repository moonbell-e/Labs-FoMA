#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
struct Data
{
public:
	bool isFree; //пуста ли структура или нет
	string FIO;
	string _bill_number;
	string _bill_amount;
	string _date;
	Data()//инициализация
	{
		_date = " ";
		_bill_number = "";
		_bill_amount = "";
		isFree = true;
		FIO = "";
	}
	Data(string name, string bill_number, string bill_amount, string date)//вызов функции (принятие и забивание в структуру значений)
	{
	isFree = false;
	FIO = name;
	_bill_amount = bill_amount;
	_bill_number = bill_number;
	_date = date;
	}
	void Show()//вывод
	{
		cout << "Фамилия: " << FIO << endl;
		cout << "Номер счета: " << _bill_number << endl;
		cout << "Сумма счета: " << _bill_amount << endl;
		cout << "Дата изменения: " << _date << endl;
		cout << endl;
	}
};

struct Node//инициализация односвязного списка
{
	Data value;//поле данных списка
	Node* next_ptr;//указатель на след элемент
	Node()//инициализация след элемента(первого) нулем
	{
		next_ptr = NULL;
	}
	Node(Data a)//список принимает значение структуры
	{
		value = a;
		next_ptr = NULL;
	}
};

class SimplyLinkedList//класс односвязного списка
{
protected:
	Node* head;
	int size;
public:
	SimplyLinkedList()
	{
		head = NULL;
		size = 0;
	}
	int GetSize() // возвращает размер нашего списка
	{
		return size;
	}
	void AddToEnd(Data Data) //добавляет след элемент в конец в список
	{
		Node* node = new Node(Data);
		Node* current = head;
		for (int i = 0; i < size - 1; i++)//сдвигаем вправо все элементы на один
		{//нулеевой освободится
			current = current->next_ptr;
		}
		node->next_ptr = current->next_ptr;
		current->next_ptr = node;
		size++;
	}
	void AddToBegin(Data Data) // добавление элемента в начало списка
	{//по указателю на след узел передаются данные в список
	// Создаем новый узел для значения
		Node* node = new Node(Data);
		// Новый узел привязывается к старому головному элементу
		node->next_ptr = head;
		// Новый узел сам становится головным элементом
		head = node;
		size++;//добавляется еще один узел
	}
	void DeleteLast() // удаляется последнего введенного узла(структура в ней несколько кусков данных)
	{
	if (size > 1)//удаляет посл элемент и уменьшает размерность
	{	
		head = head->next_ptr;
		size--;
	}
	else if (size == 1)//инициализация первого узла
	{//гловоной элемент становится нулевым и уменьшает размерность до нуля
		head = NULL;
		size--;
	}
	else//значит пуст
	{
		cout << "Список пуст!";
	}
	}
	void DeleteFirst() // удаление узла сначала
	{
		if (size > 1)//если не пустой двигает все элементы по указателю
		{
			Node* current = head;
			for (int i = 0; i < size - 1; i++)
			{
				current = current->next_ptr;
			}
			current = NULL;
			size--;//и уменьшает размерность списка на единицу
		}
		else if (size == 1)
		{
			head = NULL;
			size--;
		}
		else
		{
			cout << "Список пуст!";
		}
	}
	float prox_string(string S1, string S2) //одно сравнивается посимвольно с другим
	{
		int i, x = 0;
		double K, N;
		if (strlen(S1.c_str()) >= strlen(S2.c_str()))//одно сравнивается посимвольно с другим
		{
		for (i = 0; i < strlen(S2.c_str()); i++)//считается кол-во схожих символов
		{
		if (S1[i] == S2[i])
		x++;
		}
		N = x / strlen(S2.c_str()); // доля схожести от всех букв слова из базы
		}
		else {
			for (i = 0; i < strlen(S1.c_str()); i++) {
				if (S1[i] == S2[i])
					x++;
			}
			N = x / strlen(S1.c_str()); // то же, но от слова вводимого
		}
		return (N * 100);// процент совпадения
	}
	void Show() // показать весь список
	{
		Node* current = head;
		for (int i = 0; i < size; i++)
		{
			current->value.Show();
			cout << endl;
			current = current->next_ptr;
		}
	}
	void ShowElement(int index) // показать узел с определенным индексом
	{
		if (index < size && index > 0)
		{
			Node* current = head;//в цикле выводим все данные
			for (int i = 0; i < index; i++)
			{
				current = current->next_ptr;
				current->value.Show();
			}
		}
		else
		{
			cout << "Вы вышли за границы!";
		}
	}
	int FindFIO(string name) // поиск по имени (строковому значению)
	{
		int prx = -1;
		float maxProximity = 0;
		Node* current = head;
		for (int i = 0; i < size; i++)
		{
			float currentProximity = prox_string(name,
				current->value.FIO);//процент сходства и ищется макс проц
			if (currentProximity > maxProximity)
			{
				maxProximity = currentProximity;
				prx = i;
			}
			current = current->next_ptr;
		}
		if (prx == -1)
			cout << "Совпадений не найдено!";
		else
		{
			cout << "Индекс найденной структуры: " << prx << endl;
			return prx;
		}
	}
	int FindBillNumber(string name) //поиск по номеру счета
	{
		int prx = -1;
		float maxProximity = 0;
		Node* current = head;
		for (int i = 0; i < size; i++)
		{
			float currentProximity = prox_string(name,
				current->value._bill_number);//процент сходства и ищется макс проц
			if (currentProximity > maxProximity)
			{
				maxProximity = currentProximity;
				prx = i;
			}
			current = current->next_ptr;
		}
		if (prx == -1)
			cout << "Совпадений не найдено!";
		else
		{
			cout << "Индекс найденной структуры: " << prx << endl;
			return prx;
		}
	}
	int FindBillAmount(string name) //поиск по сумме на счете
	{
		int prx = -1;
		float maxProximity = 0;
		Node* current = head;
		for (int i = 0; i < size; i++)
		{
			float currentProximity = prox_string(name,
				current->value._bill_amount);//процент сходства и ищется макс проц
			if (currentProximity > maxProximity)
			{
				maxProximity = currentProximity;
				prx = i;
			}
			current = current->next_ptr;
		}
		if (prx == -1)
			cout << "Совпадений не найдено!";
		else
		{
			cout << "Индекс найденной структуры: " << prx << endl;
			return prx;
		}
	}
	int FindDate(string name) //поиск по году изменения
	{
		int prx = -1;
		float maxProximity = 0;
		Node* current = head;
		for (int i = 0; i < size; i++)
		{
			float currentProximity = prox_string(name,
				current->value._date);//процент сходства и ищется макс проц
			if (currentProximity > maxProximity)
			{
				maxProximity = currentProximity;
				prx = i;
			}
			current = current->next_ptr;
		}
		if (prx == -1)
			cout << "Совпадений не найдено!";
		else
		{
			cout << "Индекс найденной структуры: " << prx << endl;
			return prx;
		}
	}
	void AddAfter(int index, Data Data) //функция вставки данных после индекса который ввели
	{
		Node* current = head;//функция принимает два аргумента(номер узла и название данных, которые хотим вставить)
		//инициализация указателя на последний эелемент
			for (int i = 0; i < index; i++)
			{//по индексам проходимся и двигается элемент и освобождает место для данных
				current = current->next_ptr;
			}
		Node* newNode = new Node(Data);
		Node* dan = current->next_ptr;//"бас" указатель на данный эелемент
		current->next_ptr = newNode;
		newNode->next_ptr = dan;
		size++;
	}
	void DeleteID(int index) //удаляется узела по введенному индексу
	{
		if (size > 0)//если не пустой узел
		{
			if (index > 0 && index < size - 1)//то двигаем все элементы влево и удаляем последний
			{
			Node * current = head;
			for (int i = 0; i < index - 1; i++)//до предпоследнего эелемента
			{
			current = current->next_ptr;
			}
			current->next_ptr = current->next_ptr->next_ptr;
			size--;
			}
			else if (index == 0)//если захотим удалить начало
			{
				DeleteFirst();
			}
			else
			{
				DeleteLast();
			}
		}
		else
		{
			cout << "Список пуст!";
		}
	}
	void DeleteFindFIO(string name) // удаляет данные с найденным похожим введенным стрингом
	{//стринг имя (сложная функция) задание 8(последнее)
		DeleteID(FindFIO(name));
	}
	void DeleteFindBillNumber(string name) //функция удаления по номеру счета
	{
		DeleteID(FindBillNumber(name));
	}
	void DeleteFindBillAmount(string name) //функция удаления по сумме на счете
	{
		DeleteID(FindBillAmount(name));
	}
	void DeleteFindDate(string name) //функция удаления по году изменения
	{
		DeleteID(FindDate(name));
	}
};

struct DoublyNode //инициализация двусвязного списка
{
	Data value;
	DoublyNode* next_ptr; 
	DoublyNode* next; 
	DoublyNode()
	{
		next_ptr = NULL;
		next = NULL;
	}
	DoublyNode(Data Data)
	{
		next_ptr = NULL;
		next = NULL;
		value = Data;
	}
};
class DoublyLinkedList {//двусвязный список
private:
	DoublyNode* first; //указатель на следующий элемент
	DoublyNode* last; // указатель на предыдущий элемент
	int size; //Количество элементов в списке
public:
	DoublyLinkedList()
	{
		last = NULL;
		first = NULL;
		size = 0;
	}
	int GetSize() //возврат размера
	{
		return size;
	}
	void AddToEnd(Data Data) //добавление элемента в конец списка по последнему указателю последнего узла(двусвязн 2ое задание
			{
			DoublyNode * node = new DoublyNode(Data);
			if (first == NULL)
			{
			first = node;
			}
			node->next = NULL;
			node->next_ptr = last;
			if (last != NULL)
			{
			last->next = node;
			}
			last = node;
			size++;
			}
	void AddToBegin(Data Data) //добавление элемента в начало списка(двусвязного 3 - е задание)
	{
		DoublyNode* newitem = new DoublyNode(Data);
		newitem->next_ptr = NULL;
		if (first == NULL)//тк два указателя. начало списка по индексу , все работает по указателям
		{
		newitem->next = NULL;
		first = newitem;
		last = newitem;
		}
		else
		{
			first->next_ptr = newitem;
			newitem->next = first;
			first = newitem;
		}
		size++;
	}
	void DeleteLast() // удаление последнего эелемента в списке 4-е задание
	{
		if (size >= 1)
		{
			last = last->next_ptr;
			last->next = NULL;
			size--;
		}
		else
		{
			cout << "Список пуст!";
		}
	}
	void DeleteFirst() // удаление первого эелемента в списке 5-е задание
	{
		if (size > 0)//посл указ становится предыдущим а предыдущий указат становится без значения
			{
			first = first->next;
			first->next_ptr = NULL;
			size--;
			}
		else
		{
			cout << "Список пуст!";
		}
	}
	float prox_string(string S1, string S2) //одно сравнивается посимвольно с другим
	{
		int i, x = 0;
		double K, N;
		if (strlen(S1.c_str()) >= strlen(S2.c_str()))//одно сравнивается посимвольно с другим
		{
			for (i = 0; i < strlen(S2.c_str()); i++)//считается кол-во схожих символов
			{
			if (S1[i] == S2[i])
				x++;
			}
			N = x / strlen(S2.c_str()); // доля схожести от всех букв слова из базы
		}
		else {
			for (i = 0; i < strlen(S1.c_str()); i++) {
				if (S1[i] == S2[i])
						x++;
			}
			N = x / strlen(S1.c_str()); // то же, но от слова вводимого
		}
		return (N * 100);// процент совпадения
	}
	void Show() // вывод списка всего
	{
		DoublyNode* current = first;
		for (int i = 0; i < size; i++)
		{
			current->value.Show();
			cout << endl;
			current = current->next;
			}
	}
	void ShowElement(int index) // вывод списка по индексу
		{
			if (index < size || index >= 0)
			{
				DoublyNode* current = first;
				for (int i = 0; i < index; i++)
				{
					current = current->next;
				}
				current->value.Show();
			}
			else
			{
				cout << "Вы вышли за границы!";
			}
	}
	int FindFIO(string name) //(поиск) выводит ближайший индекс узла по стрингу, вызывается сравн_стринг
	{//одинаковый с односвязным
			int prx = -1;
			float maxProximity = -1;
			DoublyNode* current = first;
			for (int i = 0; i < size; i++)//по указателю на след эелемент ищет
			{
				float currentProximity = prox_string(name, current->value.FIO);
				if (currentProximity > maxProximity)
				{
					maxProximity = currentProximity;
					prx = i;
				}
				current = current->next;
			}
			if (prx == -1)
				cout << "Совпадений не найдено!";
			else
			{
				cout << "Индекс найденной структуры: " << prx << endl;
				return prx;
			}
	}
	int FindBillNumber(string name) //поиск по номеру счета
	{
		int prx = -1;
		float maxProximity = -1;
		DoublyNode* current = first;
		for (int i = 0; i < size; i++)//по указателю на след эелемент ищет
		{
			float currentProximity = prox_string(name, current->value._bill_number);
			if (currentProximity > maxProximity)
			{
				maxProximity = currentProximity;
				prx = i;
			}
			current = current->next;
		}
		if (prx == -1)
			cout << "Совпадений не найдено!";
		else
		{
			cout << "Индекс найденной структуры: " << prx << endl;
			return prx;
		}
	}
	int FindBillAmount(string name) //поиск по сумме на счете
	{
		int prx = -1;
		float maxProximity = -1;
		DoublyNode* current = first;
		for (int i = 0; i < size; i++)//по указателю на след эелемент ищет
		{
			float currentProximity = prox_string(name, current->value._bill_amount);
			if (currentProximity > maxProximity)
			{
				maxProximity = currentProximity;
				prx = i;
			}
			current = current->next;
		}
		if (prx == -1)
			cout << "Совпадений не найдено!";
		else
		{
			cout << "Индекс найденной структуры: " << prx << endl;
			return prx;
		}
	}
	int FindDate(string name) //поиск по году изменения
	{
		int prx = -1;
		float maxProximity = -1;
		DoublyNode* current = first;
		for (int i = 0; i < size; i++)//по указателю на след эелемент ищет
		{
			float currentProximity = prox_string(name, current->value._date);
			if (currentProximity > maxProximity)
			{
				maxProximity = currentProximity;
				prx = i;
			}
			current = current->next;
		}
		if (prx == -1)
			cout << "Совпадений не найдено!";
		else
		{
			cout << "Индекс найденной структуры: " << prx << endl;
			return prx;
		}
	}
	void AddAfter(int index, Data Data) //ввод узла после веденного индекса (нужно для след функций)(для 7 - ого задания)
	{//различается по двум указателям
		DoublyNode* current = first;
		for (int i = 0; i < index; i++)
		{//после введенного индекса все значения двигаются вправо, увеличивается размерность списка
			current = current->next;
		}
			DoublyNode* newNode = new DoublyNode(Data);
			DoublyNode* afterCurrent = current->next;
			afterCurrent->next_ptr = newNode;
			current->next = newNode;
			newNode->next_ptr = current;
			newNode->next = afterCurrent;
			size++;
	}
	void DeleteID(int index) //удаление с определ индексом (нужно для 8ого задания)
		{//похож принцип но также по двум указателям
			if (size > 0)
			{
				if (index > 0 && index < size - 1)
				{
					DoublyNode* current = first;
					for (int i = 0; i < index - 1; i++)
					{
						current = current->next;
					}
					current->next = current->next->next;//
					current->next->next_ptr = current;//
					size--;
				}
				else if (index == 0)
				{
					DeleteFirst();
				}
				else
				{
					DeleteLast();
				}
			}
			else
			{
				cout << "Список пуст!";
		}
	}
	void DeleteFindFIO(string name) // удаляет данные с найденным похожим введенным стрингом
	{//стринг имя (сложная функция) задание 8(последнее)
		DeleteID(FindFIO(name));
	}
	void DeleteFindBillNumber(string name) //функция удаления по номеру счета
	{
		DeleteID(FindBillNumber(name));
	}
	void DeleteFindBillAmount(string name) //функция удаления по сумме на счете
	{
		DeleteID(FindBillAmount(name));
	}
	void DeleteFindDate(string name) //функция удаления по году изменения
	{
		DeleteID(FindDate(name));
	}

};

int main()
{
	setlocale(LC_ALL, "RUS");
	int pole;
	int ch; int ch2 = 1; int sw = 0;
	int temp, q, ans = 1;
	string temp2;
	Data str;
	char j = 0;//инт или стринг
	DoublyLinkedList list2;
	SimplyLinkedList list1;
	do
	{
		cout << "Односвязный или двусвязный? (1/2): " << endl;
		cin >> q;
		switch (q)
		{
		case 1:
			do {
				cout << "Выберите номер задания" << endl;
				cout << endl;
				cout << "Для односвязного списка" << endl;
				cout << " 0 - Показать список " << endl;
				cout << " 1 - Добавление элемента в конец списка " << endl;
				cout << " 2 - Добавление элемента в начало списка " << endl;
				cout << " 3 - Удаление конечного элемента списка " << endl;
				cout << " 4 - Удаление начального элемента списка " << endl;
				cout << " 5 - Поиск элемента по заданному значению поля структуры " << endl;
					cout << " 6 - Добавление элемента после найденного " << endl;
				cout << " 7 - Удаление найденного элемента. " << endl;
				cin >> sw;
				switch (sw) {
				case 0:
					list1.Show();
					break;
				case 1:
					cout << " 1 функция - Добавление элемента в конец списка " << endl;
					cout << "Введите фамилию, номер счета, сумму на счете и год изменения " << endl;
					cin >> str.FIO >> str._bill_number >> str._bill_amount >> str._date;
					list1.AddToEnd(str);
					list1.Show();
					break;
				case 2:
					cout << " 2 функция - Добавление элемента в начало списка " << endl;
					cout << "Введите фамилию, номер счета, сумму на счете и год изменения " << endl;
					cin >> str.FIO >> str._bill_number >> str._bill_amount >> str._date;
					list1.AddToBegin(str);
					list1.Show();
					break;
				case 3:
					cout << " 3 функция - Удаление конечного элемента списка "
						<< endl;
					list1.DeleteFirst();
					list1.Show();
					break;
					break;
				case 4:
					cout << " 4 функция - Удаление начального элемента списка "
					<< endl;
					list1.DeleteID(list1.GetSize());
					list1.Show();
					break;
				case 5:
					cout << " 5 функция - Поиск элемента по заданному значению поля структуры " << endl;
					cout << "Выберите поиск по 1 - фамилии, 2 - номеру счета, 3 - сумме на счете, 4 - году изменения: ";
					cin >> pole;
					switch (pole)
					{
					case 1:
						cout << "Введите фамилию: ";
						cin >> temp2;
						list1.FindFIO(temp2);
						break;
					case 2:
						cout << "Введите номер счета: ";
						cin >> temp2;
						list1.FindBillNumber(temp2);
						break;
					case 3:
						cout << "Введите сумму на счете: ";
						cin >> temp2;
						list1.FindBillAmount(temp2);
						break;
					case 4:
						cout << "Введите год изменения: ";
						cin >> temp2;
						list1.FindDate(temp2);
						break;
					default:
						cout << "Вы ввели не тот номер!";
						break;
					}
					cout << endl;
					break;
				case 6:
					cout << " 6 функция - Добавление элемента после найденного " << endl;
					cout << "Вы производили поиск по: 1 - фамилии, 2 - номеру счета, 3 - сумме на счете, 4 - году изменения: ";
					cin >> pole;
					switch (pole)
					{
					case 1:
						cout << "Введите фамилию, номер счета, сумму на счете и год изменения " << endl;
						cin >> str.FIO >> str._bill_number >> str._bill_amount >> str._date;
						list1.AddAfter(list1.FindFIO(temp2), str);
						list1.Show();
						break;
					case 2:
						cout << "Введите фамилию, номер счета, сумму на счете и год изменения " << endl;
						cin >> str.FIO >> str._bill_number >> str._bill_amount >> str._date;
						list1.AddAfter(list1.FindBillNumber(temp2), str);
						list1.Show();
						break;
					case 3:
						cout << "Введите фамилию, номер счета, сумму на счете и год изменения " << endl;
						cin >> str.FIO >> str._bill_number >> str._bill_amount >> str._date;
						list1.AddAfter(list1.FindBillAmount(temp2), str);
						list1.Show();
						break;
					case 4:
						cout << "Введите фамилию, номер счета, сумму на счете и год изменения " << endl;
						cin >> str.FIO >> str._bill_number >> str._bill_amount >> str._date;
						list1.AddAfter(list1.FindDate(temp2), str);
						list1.Show();
						break;
					}
				case 7:
					cout << " 7 функция - Удаление найденного элемента. " <<
						endl;
					cout << "Вы производили поиск по: 1 - фамилии, 2 - номеру счета, 3 - сумме на счете, 4 - году изменения: ";
					cin >> pole;
					switch (pole)
					{
					case 1:
						list1.DeleteFindFIO(temp2);
						list1.Show();
						break;
					case 2:
						list1.DeleteFindBillNumber(temp2);
						list1.Show();
						break;
					case 3:
						list1.DeleteFindBillAmount(temp2);
						list1.Show();
						break;
					case 4:
						list1.DeleteFindDate(temp2);
						list1.Show();
						break;
					}
				}
				cout << " [1] - Продолжить; [0] - Выбрать другой тип" << endl;
				cin >> ch2;
			} while (ch2 != 0);
			break;
		case 2:
			do {
				cout << "Выберите номер задания" << endl;
				cout << endl;
				cout << "Для двухсвязного списка" << endl;
				cout << " 0 - Показать список " << endl;
				cout << " 1 - Добавление элемента в конец списка " << endl;
				cout << " 2 - Добавление элемента в начало списка " << endl;
				cout << " 3 - Удаление конечного элемента списка " << endl;
				cout << " 4 - Удаление начального элемента списка " << endl;
				cout << " 5 - Поиск элемента по заданному значению поля структуры " << endl;
					cout << " 6 - Добавление элемента после найденного " << endl;
				cout << " 7 - Удаление найденного элемента " << endl;
				cin >> sw;
				switch (sw) {
				case 0:
					list2.Show();
					break;
				case 1:
					cout << " 1 функция - Добавление элемента в конец списка " << endl;
					cout << "Введите фамилию, номер счета, сумму на счете и год изменения " << endl;
					cin >> str.FIO >> str._bill_number >> str._bill_amount >> str._date;
					list2.AddToEnd(str);
					list2.Show();
					break;
				case 2:
					cout << " 2 функция - Добавление элемента в начало списка " << endl;
					cout << "Введите фамилию, номер счета, сумму на счете и год изменения " << endl;
					cin >> str.FIO >> str._bill_number >> str._bill_amount >> str._date;
					list2.AddToBegin(str);
					list2.Show();
					break;
				case 3:
					cout << " 3 функция - Удаление конечного элемента списка "
						<< endl;
					list2.DeleteID(list2.GetSize());
					list2.Show();
					break;
				case 4:
					cout << " 4 функция - Удаление начального элемента списка " << endl;
					list2.DeleteFirst();
					list2.Show();
					break;
				case 5:
					cout << " 5 функция - Поиск элемента по заданному значению поля структуры " << endl;
					cout << "Выберите поиск по 1 - фамилии, 2 - номеру счета, 3 - сумме на счете, 4 - году изменения: ";
					cin >> pole;
					switch (pole)
					{
					case 1:
						cout << "Введите фамилию: ";
						cin >> temp2;
						list2.FindFIO(temp2);
						break;
					case 2:
						cout << "Введите номер счета: ";
						cin >> temp2;
						list2.FindBillNumber(temp2);
						break;
					case 3:
						cout << "Введите сумму на счете: ";
						cin >> temp2;
						list2.FindBillAmount(temp2);
						break;
					case 4:
						cout << "Введите год изменения: ";
						cin >> temp2;
						list2.FindDate(temp2);
						break;
					default:
						cout << "Вы ввели не тот номер!";
						break;
					}
					cout << endl;
					break;
				case 6:
					cout << " 6 функция - Добавление элемента после найденного " << endl;
					cout << "Вы производили поиск по: 1 - фамилии, 2 - номеру счета, 3 - сумме на счете, 4 - году изменения: ";
					cin >> pole;
					switch (pole)
					{
					case 1:
						cout << "Введите фамилию, номер счета, сумму на счете и год изменения " << endl;
						cin >> str.FIO >> str._bill_number >> str._bill_amount >> str._date;
						list2.AddAfter(list1.FindFIO(temp2), str);
						list2.Show();
						break;
					case 2:
						cout << "Введите фамилию, номер счета, сумму на счете и год изменения " << endl;
						cin >> str.FIO >> str._bill_number >> str._bill_amount >> str._date;
						list2.AddAfter(list1.FindBillNumber(temp2), str);
						list2.Show();
						break;
					case 3:
						cout << "Введите фамилию, номер счета, сумму на счете и год изменения " << endl;
						cin >> str.FIO >> str._bill_number >> str._bill_amount >> str._date;
						list2.AddAfter(list1.FindBillAmount(temp2), str);
						list2.Show();
						break;
					case 4:
						cout << "Введите фамилию, номер счета, сумму на счете и год изменения " << endl;
						cin >> str.FIO >> str._bill_number >> str._bill_amount >> str._date;
						list2.AddAfter(list1.FindDate(temp2), str);
						list2.Show();
						break;
					}
				case 7:
					cout << " 7 функция - Удаление найденного элемента. " <<
						endl;
					cout << "Вы производили поиск по: 1 - фамилии, 2 - номеру счета, 3 - сумме на счете, 4 - году изменения: ";
					cin >> pole;
					switch (pole)
					{
					case 1:
						list2.DeleteFindFIO(temp2);
						list2.Show();
						break;
					case 2:
						list2.DeleteFindBillNumber(temp2);
						list2.Show();
						break;
					case 3:
						list2.DeleteFindBillAmount(temp2);
						list2.Show();
						break;
					case 4:
						list2.DeleteFindDate(temp2);
						list2.Show();
						break;
					}
				}
				cout << " [1] - Продолжить; [0] - Завершить работу с этим типом"
					<< endl;
				cin >> ch;
			} while (ch != 0);
			break;
		}
		cout << "[1] - Начать заново; [0] - Закончить; ";
		cin >> ans;
	} while (ans != 0);
	cout << endl << "End";
}