#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

//структура Фамилия И.О.
struct Fio {
	string surname,
		name,
		patronymic;
};

//структура даты
struct Date {
	int day,
		month,
		year;
};


//структура данных
struct Data {
	Fio _fio;
	int _bill_number;
	double _bill_amount;
	Date _date;
};

//шаблоны функций
void Copy(Data* (&d_n), Data* (&d_o), int n);
void Copy(Data& d_n, Data& d_o);


void DataEntry(Data* (&d), int& n);
void DataAdd(Data* (&d), int& n);
void DataClear(Data* d, int n);
void FindFreeData(Data* (&d), int& n);
void PrintStructure(Data* d, int n);
void PrintData(Data* d, int n);
float SearchDataString(string S1, string S2);
void SearchMinData(Data* (&d), int& n);
void DataSortUp(Data* d, int n);
void DataSortDown(Data* d, int n);
void ReadingData(Data* (&d), int& n, string file_name);
void SavingData(Data* d, int n, string file_name);

