#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

struct Goods
{
	char name[100];
	char shop[100];
	double price;
	double amount;
	char measurement[20];
};

void Create(char* fname);
void Print(char* fname);
void FiltrShop(char* fname);
bool FiltrPrice(char* fname, double min, double max);
void SortShop(char* fname);
void SortPrice(char* fname);

int main()
{
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
	char fname[61];
	char ch;
	double min, max;
	do
	{
		cout << endl;
		cout << "Головне меню:	" << endl;
		cout << "[1] - введення та збереження данних;" << endl;
		cout << "[2] - загрузка та вивід данних;" << endl;
		cout << "[3] - фільтрування по магазинам;" << endl;
		cout << "[4] - фільтрування по цінам;" << endl;
		cout << "[5] - сортуванням по магазинам;" << endl;
		cout << "[6] - сортування по цінам;" << endl << endl;

		cout << "[0] - завершення роботи." << endl << endl;
		cout << "Ваш вибір: "; cin >> ch;
		switch (ch)
		{
		case '0':
			break;
		case '1':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << endl;
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			Create(fname);
			break;
		case '2':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << endl;
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			Print(fname);
			break;
		case '3':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << endl;
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			FiltrShop(fname);
			break;
		case '4':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << endl;
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			cout << endl;
			cout << "Введіть мінімальну ціну(UAH): "; cin.sync(); cin >> min;
			cout << "Введіть максимальну ціну(UAH): "; cin.sync(); cin >> max;
			cout << endl;
			FiltrPrice(fname, min, max);
			break;
		case '5':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			cout << endl;
			SortShop(fname);
			cout << "Файл відсортовано!" << endl;
			Print(fname);
			break;
		case '6':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << endl;
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			SortPrice(fname);
			cout << endl;
			cout << "Файл відсортовано!" << endl;
			Print(fname);
			break;
		default:
			cout << "Помилка вводу! ";
		}
	} while (ch != '0');
	return 0;
}

void Create(char* fname) // створення файлу з введених рядків
{
	ofstream fout(fname, ios::binary); // відкрили файл для запису
	char ch; // відповідь користувача – чи продовжувати введення
	string s; // введений користувачем рядок
	Goods goods;
	do
	{
		cout << "Назва товару: "; cin >> goods.name;
		cout << "Магазин: "; cin >> goods.shop;
		cout << "Ціна(UAH): "; cin >> goods.price;
		cout << "Кількість: "; cin >> goods.amount;
		cout << "Од. вимірювання: "; cin >> goods.measurement;
		if (!fout.write((char*)&goods, sizeof(Goods)))
		{
			cerr << "Помилка запису у файл." << endl;
		}
		cout << "Продовжити? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	cout << endl;
	fout.close();
}

void Print(char* fname) // виведення файлу на екран
{
	ifstream fin(fname, ios::binary); // відкрили файл для зчитування
	if (fin.fail())
	{
		cout << "Помилка відкриття файлу '" << fname << "'!" << endl;
		return;
	}
	cout << endl;
	Goods goods;
	cout << "========================================================================="
		<< endl;
	cout << "|  №  |  Товар  |  Магазин  |  Ціна  |  Кількість  |  Од. вимірювання  |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	int i = 0;
	while (fin.read((char*)&goods, sizeof(Goods)))
	{
		cout << "| " << setw(2) << right << i + 1 << "  "; i++;
		cout << "|   " << setw(6) << left << goods.name
			<< "|   " << setw(6) << left << goods.shop << "  "
			<< "|   " << setw(5) << left << goods.price
			<< setw(4) << "|     " << setw(6) << left << goods.amount << "  "
			<< setw(6) << "|       " << setw(12) << left << goods.measurement << "|";
		cout << endl;
	}
	cout << "========================================================================= "
		<< endl;
	cout << endl;
	cout << endl;
	fin.close();
}

void FiltrShop(char* fname)
{
	ifstream fin(fname, ios::binary);
	if (fin.fail())
	{
		cout << "Помилка відкриття файлу '" << fname << "'!" << endl;
		return;
	}
	cout << endl;
	Goods goods;
	string store;
	int k = 0;
	cout << "Будь ласка, введіть назву магазину: "; cin.sync(); getline(cin, store);
	cout << endl;
	cout << "========================================================================="
		<< endl;
	cout << "|  №  |  Товар  |  Магазин  |  Ціна  |  Кількість  |  Од. вимірювання  |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	int i = 0;
	while (fin.read((char*)&goods, sizeof(Goods)))
	{
		if (goods.shop == store) {
			cout << "| " << setw(2) << right << i + 1 << "  "; i++;
			cout << "|   " << setw(6) << left << goods.name
				<< "|   " << setw(6) << left << goods.shop << "  "
				<< "|   " << setw(5) << left << goods.price
				<< setw(4) << "|     " << setw(6) << left << goods.amount << "  "
				<< setw(6) << "|       " << setw(12) << left << goods.measurement << "|";
			cout << endl;
			k = 1;
		}
	}
	if (k == 0) {
		cout << "Нажаль, цей магазин не було знайдено. Будь ласка, перевірте правильність вводу." << endl;
	}
	cout << "========================================================================= "
		<< endl;
	cout << endl;
	cout << endl;
	fin.close();
}

bool FiltrPrice(char* fname, double min, double max)
{
	ifstream fin(fname, ios::binary);
	if (!fin)
	{
		cout << "Помилка відкриття файлу '" << fname << "'!" << endl;
		return false;
	}
	cout << endl;
	Goods goods;
	int k = 0;
	cout << "========================================================================="
		<< endl;
	cout << "|  №  |  Товар  |  Магазин  |  Ціна  |  Кількість  |  Од. вимірювання  |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	int i = 0;
	while (fin.read((char*)&goods, sizeof(Goods)))
	{
		if (goods.price >= min && goods.price <= max) {
			cout << "| " << setw(2) << right << i + 1 << "  "; i++;
			cout << "|   " << setw(6) << left << goods.name
				<< "|   " << setw(6) << left << goods.shop << "  "
				<< "|   " << setw(5) << left << goods.price
				<< setw(4) << "|     " << setw(6) << left << goods.amount << "  "
				<< setw(6) << "|       " << setw(12) << left << goods.measurement << "|";
			cout << endl;
			k = 1;
		}
	}
	if (k == 0) {
		cout << "Схоже, в цій ціновій категорії нічого не було знайдено. Будь ласка, введіть іншу цінову категорію і повторіть пошук." << endl;
		return false;
	}
	cout << "========================================================================= "
		<< endl;
	cout << endl;
	cout << endl;
	fin.close();
	return true;
}

void SortShop(char* fname) {
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}
	f.seekg(0, ios::end);
	int size = f.tellg();
	size = size / sizeof(Goods);
	f.seekg(0, ios::beg);
	Goods* goods = new Goods[size];
	Goods temp;
	f.read((char*)goods, size * sizeof(Goods));
	f.close();
	for (int i = 0; i < size - 1; i++) { // Сортування бульбашкою
		for (int j = size - 1; j > i; j--) {
			string shopOne = goods[j].shop;
			string shopTwo = goods[j - 1].shop;
			if ((shopOne < shopTwo))
			{
				temp = goods[j];
				goods[j] = goods[j - 1];
				goods[j - 1] = temp;
			}
		}
	}
	f.close();
	ofstream file(fname, ios::binary);
	file.write((char*)goods, size * sizeof(Goods));
	file.close();
}

void SortPrice(char* fname) {
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}
	f.seekg(0, ios::end); 
	int size = f.tellg(); 
	size = size / sizeof(Goods);
	f.seekg(0, ios::beg); 
	Goods* goods = new Goods[size];
	Goods temp;
	f.read((char*)goods, size * sizeof(Goods)); 
	f.close();
	for (int i = 0; i < size - 1; i++) { // Сортування бульбашкою
		for (int j = size - 1; j > i; j--) {
			if ((goods[j].price < goods[j - 1].price))
			{
				temp = goods[j];
				goods[j] = goods[j - 1];
				goods[j - 1] = temp;
			}
		}
	}
	f.close();
	ofstream file(fname, ios::binary);
	file.write((char*)goods, size * sizeof(Goods));
	file.close();
}