#include "Functions.h"


void DataAdd(Data* (&d), int& n)
{
	//��������� ������ ������
	Data* buf;
	buf = new Data[n];

	//��������� ������ � ��������� ������
	Copy(buf, d, n);

	//�������� ����� ������
	n++;
	d = new Data[n];

	//���������� ������
	Copy(d, buf, --n);

	cout << "������� ���: ";
	cin >> d[n]._fio.surname >> d[n]._fio.name >> d[n]._fio.patronymic;

	cout << "������� ����� �����: ";
	cin >> d[n]._bill_number;

	cout << "������� ����� �� �����:  ";
	cin >> d[n]._bill_amount;

	cout << "������� ����: ";
	cin >> d[n]._date.day >> d[n]._date.month >> d[n]._date.year;

	cout << endl << "������ ���������!" << endl;

	delete[]buf;

}

void DataEntry(Data* (&d), int& n)
{
	cout << "������� ���������� ������: ";
	cin >> n;

	//������� ������
	d = new Data[n];

	for (int i = 0; i < n; i++) {
		cout << "������� ���: ";
		cin >> d[i]._fio.surname >> d[i]._fio.name >> d[i]._fio.patronymic;

		cout << "������� ����� �����: ";
		cin >> d[i]._bill_number;

		cout << "������� ����� �� �����:  ";
		cin >> d[i]._bill_amount;

		cout << "������� ����: ";
		cin >> d[i]._date.day >> d[i]._date.month >> d[i]._date.year;

		cout << "____________________________________" << endl;
	}
}

void DataClear(Data* d, int n) {
	int _n;
	cout << "������� ����� �������� (�� 1 �� " << n << "): ";
	cin >> _n;
	_n--; //�������� �� ������� �.�. ������  = 0

	if (_n >= 0 && _n < n) {
		d[_n]._fio.surname = d[_n]._fio.name = d[_n]._fio.patronymic = "0";
		d[_n]._bill_number = 0;
		d[_n]._bill_amount = 0.0;
		d[_n]._date.day = d[_n]._date.month = d[_n]._date.year = 0;
	}
	else {
		cout << "����� ������ �������!";
	}

}

void FindFreeData(Data* (&d), int& n)
{
	for (int i = 0; i < n; i++) {
		if (d[i]._fio.surname == "0") { //����� ���������� �������, �� ���������� ���
			cout << "������� ���� � ��������: " << i + 1 << endl;
			break;
		}
		if (i == n) {
			cout << "��������� ���������" << endl;
		}
	}
}

void PrintStructure(Data* d, int n) {
	int _n;
	cout << "������� ����� �������� (�� 1 �� " << n << "): ";
	cin >> _n;
	_n--; //�������� �� ������� �.�. ������  = 0

	if (_n >= 0 && _n < n) {
		cout << "���: " << d[_n]._fio.surname << " " << d[_n]._fio.name << " " << d[_n]._fio.patronymic << endl;
		cout << "����� �����: " << d[_n]._bill_number << endl;
		cout << "����� �� �����: " << d[_n]._bill_amount << endl;
		cout << "���� ���������: " << d[_n]._date.day << "/" 
			 << d[_n]._date.month << "/" << d[_n]._date.year << endl;
	}
	else {
		cout << "����� ������ �������!";
	}
}

void PrintData(Data* d, int n) {
	for (int i = 0; i < n; i++)
	{
		cout << "���: " << d[i]._fio.surname << " " << d[i]._fio.name << " " << d[i]._fio.patronymic << endl;
		cout << "����� �����: " << d[i]._bill_number << endl;
		cout << "����� �� �����: " << d[i]._bill_amount << endl;
		cout << "���� ���������: " << d[i]._date.day << "/"
			<< d[i]._date.month << "/" << d[i]._date.year << endl;
		cout << "____________________________________" << endl;
	}
}

float SearchDataString(string S1, string S2)
{
	float match = 0;
	double N;
	if (strlen(S1.c_str()) >= strlen(S2.c_str())) 
	{
		for (int i = 0; i < strlen(S2.c_str()); i++)
		{
			if (S1[i] == S2[i])
				match++;
		}
		N = match / strlen(S2.c_str()); //���� �������� �� ���� ���� ����� �� ����
	}
	else {
		for (int i = 0; i < strlen(S1.c_str()); i++) {

			if (S1[i] == S2[i])
				match++;
		}
		N = match / strlen(S2.c_str()); //���� �������� �� ���� ���� ����� �� ����
	}
	return (N * 100); //������� ����������

	
}

void SearchMinData(Data* (&d), int& n)
{
	int column_number = 0;
	int j = 0;

	cout << "�������� ����� ����: 1 - ���, 2 - ����� �����, 3 - ����� �����, 4 - ����: ";
	cin >> column_number;
	switch (column_number)
	{
	case 1:
		for (int i = 1; i < n; i++)
			if (d[j]._fio.surname > d[i]._fio.surname && d[i]._fio.surname != "0")
				j = i;
		for (int i = 1; i < n; i++)
			if (d[j]._fio.name > d[i]._fio.name && d[i]._fio.name != "0")
				j = i;
		for (int i = 1; i < n; i++)
			if (d[j]._fio.patronymic > d[i]._fio.patronymic && d[i]._fio.patronymic != "0")
				j = i;
		break;
	case 2:
		for (int i = 1; i < n; i++)
			if (d[j]._bill_number > d[i]._bill_number && d[i]._bill_number != 0)
				j = i;
		break;
	case 3:
		for (int i = 1; i < n; i++)
			if (d[j]._bill_amount > d[i]._bill_amount && d[i]._bill_amount != 0.0)
				j = i;
		break;
	case 4: 
		for (int i = 1; i < n; i++)
			if (d[j]._date.year > d[i]._date.year && d[i]._date.year != 0)
				j = i;
		break;
	}
	cout << "����� ������������ ����: " << j + 1 << endl;
}

void Copy(Data& d_n, Data& d_o)
{
	d_n._fio.surname = d_o._fio.surname;
	d_n._fio.name = d_o._fio.name;
	d_n._fio.patronymic = d_o._fio.patronymic;

	d_n._bill_number = d_o._bill_number;

	d_n._bill_amount = d_o._bill_amount;

	d_n._date.day = d_o._date.day;
	d_n._date.month = d_o._date.month;
	d_n._date.year = d_o._date.year;


}
void Copy(Data* (&d_n), Data* (&d_o), int n)
{
	for (int i = 0; i < n; i++)
	{
		d_n[i] = d_o[i];
	}
}

void DataSortUp(Data* d, int n)
{
	//��������� ����������
	Data buf;
	
	//���������� ������� ��������
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			//������� ����������
			if (d[i]._fio.surname < d[j]._fio.surname) {
				Copy(buf, d[j]);
				Copy(d[j], d[i]);
				Copy(d[i], buf);
			}
		}
	}
	cout << "������ �������������!" << endl;
}

void DataSortDown(Data* d, int n)
{
	//��������� ����������
	Data buf;

	//���������� ������� ��������
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			//������� ����������
			if (d[i]._fio.surname > d[j]._fio.surname) {
				Copy(buf, d[j]);
				Copy(d[j], d[i]);
				Copy(d[i], buf);
			}
		}
	}
	cout << "������ �������������!" << endl;
}

void ReadingData(Data* (&d), int& n, string file_name)
{
	//������� ����� ��� ������

	ifstream reading(file_name);

	if (reading) {

		reading >> n;

		//������� ������
		d = new Data[n];

		for (int i = 0; i < n; i++) {
			reading >> d[i]._fio.surname;
			reading >> d[i]._fio.name;
			reading >> d[i]._fio.patronymic;

			reading >> d[i]._bill_number;

			reading >> d[i]._bill_amount;

			reading >> d[i]._date.day;
			reading >> d[i]._date.month;
			reading >> d[i]._date.year;
		}
	}
	cout << "������ �������!" << endl;
}

void SavingData(Data* d, int n, string file_name)
{
	//��������� ����� ��� ������
	ofstream record(file_name, ios::out);

	if (record) {
		record << n << endl;

		for (int i = 0; i < n; i++)
		{
			record << d[i]._fio.surname << " ";
			record << d[i]._fio.name << " ";
			record << d[i]._fio.patronymic << endl;

			record << d[i]._bill_number << endl;

			record << d[i]._bill_amount << endl;

			record << d[i]._date.day << " ";
			record << d[i]._date.month << " ";
			if (i < n - 1)
				record << d[i]._date.year << endl;
			else
				record << d[i]._date.year;
		}
	}
	else
		cout << "������ �������� �����" << endl;
	
	record.close();
}