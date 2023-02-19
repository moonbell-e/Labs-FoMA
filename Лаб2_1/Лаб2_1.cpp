#include "Header.h"
#include <string.h>
#include <locale>


int _state_menu;
void Menu() {
	cout << "Выберите ввод структуры вручную(12) или чтение с файла(10): " << endl
		<< "(0) Выход из программы" << endl
		<< "(1) Очистка элемента структуры" << endl
		<< "(2) Поиск свободной структуры" << endl
		<< "(3) Ввод элемента с клавиатуры" << endl
		<< "(4) Вывод элементов на монитор" << endl
		<< "(5) Вывод всей структуры на монитор" << endl
		<< "(6) Поиск в массиве структур элемента с заданным значением поля" << endl
		<< "(7) Поиск в массиве структуры с минимальным значением заданного поля" << endl
		<< "(8) Сортировка по возрастанию" << endl
		<< "(9) Сортировка по убыванию" << endl
		<< "(10) Чтение файла" << endl
		<< "(11) Запись в файл" << endl
		<< "(12) Ввод вручную" << endl
		<< "Ваш выбор: ";
	cin >> _state_menu;
}

int main() {
	//русификация консоли
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");

	int amount_of_data = 0;
	string file_name;

	string key_word;
	double key_number;
	float procent, procent_max = 0;
	int j;
	int number_or_not;
	int min, max = 0;
	int equivalent = 0;

	Data* d = new Data[amount_of_data];


	Menu();



	while (_state_menu != 0)
	{
		switch (_state_menu)
		{
		case 1:
			system("cls"); //очистка консоли
			if (amount_of_data != 0) {
				DataClear(d, amount_of_data);
			}
			else
				cout << "Данные пусты!" << endl;

			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 2:
			system("cls"); //очистка консоли
			if (amount_of_data != 0) {
				FindFreeData(d, amount_of_data);
			}
			else
				cout << "Данные пусты!" << endl;

			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 3:
			system("cls"); //очистка консоли
			if (amount_of_data != 0) {
				DataAdd(d, amount_of_data);
				amount_of_data++;
			}
			else
				cout << "Данные пусты!" << endl;

			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 4:
			system("cls"); //очистка консоли
			if (amount_of_data != 0) {
				PrintStructure(d, amount_of_data);
			}
			else
				cout << "Данные пусты!" << endl;
			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 5:
			system("cls"); //очистка консоли
			if (amount_of_data != 0) {
				PrintData(d, amount_of_data);
			}
			else
				cout << "Данные пусты!" << endl;
			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 6:
			system("cls"); //очистка консоли
			equivalent = 0;
			if (amount_of_data != 0) {
				cout << "Введите 1 для поиска по числовому значению и 2 для поиска по строковому: ";
				cin >> number_or_not;
				switch (number_or_not)
				{
				case 2:
					cin >> key_word;
					for (int i = 0; i < amount_of_data; i++)
					{
						procent = SearchDataString(key_word, d[i]._fio.surname);
						if (procent > procent_max) {
							procent_max = procent;
							j = i;
							cout << "Самое близкое поле: " << j + 1 << " : " << d[j]._fio.surname << endl;
							cout << "Процент совпадения: " << procent_max << "%" << endl;
							break;
						}
					}
					break;
				case 1:
					cin >> key_number;
					for (int i = 0; i < amount_of_data; i++)
					{
						if ((d[i]._bill_number < key_number) && (d[i]._bill_number > max))
							max = d[i]._bill_number;
					}
					min = 100000;
					for (int i = 0; i < amount_of_data; i++)
					{
						if ((d[i]._bill_number > key_number) && (d[i]._bill_number < max))
							min = d[i]._bill_number;
					}
					for (int i = 0; i < amount_of_data; i++)
					{
						if (d[i]._bill_number == key_number)
							equivalent = d[i]._bill_number;
					}
					if (equivalent != 0)
					{
						cout << "Равное значение: " << equivalent << endl;
					}
					else
					{
						cout << "Самое близкое значение: ";

						if (abs(key_number - max) < abs(key_number - min))
							cout << max << endl;
						else
							cout << min << endl;
					}
					break;
				}
			}
			else
				cout << "Данные пусты!" << endl;

			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 7:
			system("cls"); //очистка консоли
			if (amount_of_data != 0) {
				SearchMinData(d, amount_of_data);
			}
			else
				cout << "Данные пусты!" << endl;

			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 8:
			system("cls"); //очистка консоли
			if (amount_of_data != 0) {
				DataSortUp(d, amount_of_data);
			}
			else
				cout << "Данные пусты!" << endl;

			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 9:
			system("cls"); //очистка консоли
			if (amount_of_data != 0) {
				DataSortDown(d, amount_of_data);
			}
			else
				cout << "Данные пусты!" << endl;

			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 10:
			system("cls"); //очистка консоли
			ReadingData(d, amount_of_data, "Input.txt");;

			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 11:
			system("cls"); //очистка консоли

			cout << "Введите название файла: ";
			cin >> file_name;
			if (amount_of_data != 0) {
				SavingData(d, amount_of_data, file_name);
			}
			else
				cout << "Данные пусты!" << endl;

			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		case 12:
			system("cls"); //очистка консоли
			DataEntry(d, amount_of_data);

			system("pause"); //задержка консоли
			system("cls"); //очистка консоли
			Menu();
			break;
		default:
			cout << "Неверно введен номер действия!" << endl;

			system("cls"); //очистка консоли
			Menu();
			break;
		}
	}
}