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
void EditFile(char* fname, const char* gname);
void AddGoods(char* fname, const char* gname);
void EditGoods(char* fname);
void DelGoods(char* fname, const char* gname);

int main()
{
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
	char fname[61];
	char gname[61];
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
		cout << "[6] - сортування по цінам;" << endl;
		cout << "[7] - редагування данних" << endl << endl;

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
		case '7':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << endl;
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			cout << endl;
			EditFile(fname, "helper.dat");
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

void EditFile(char* fname, const char* gname) {
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}
	char ch;
	f.seekg(0, ios::end);
	int size = f.tellg();
	size = size / sizeof(Goods);
	f.seekg(0, ios::beg);
	cout << endl;
	cout << "Кількість товарів у списку: " << size << endl << endl;
	cout << "[1] - добавити новий товар" << endl;
	cout << "[2] - редагувати інформацію про товар" << endl;
	cout << "[3] - вилучити товар" << endl << endl;

	cout << "[0] - вихід" << endl << endl;
	cout << "Ваш вибір: "; cin >> ch;
	switch (ch) {
	case '0':
		f.close();
		return;
		break;
	case '1':
		AddGoods(fname, gname);
		break;

	case '2':
		EditGoods(fname);
		break;
	case '3':
		DelGoods(fname, gname);
	default:
		cout << "Помилка вводу! " << endl;
	}

}

void AddGoods(char* fname, const char* gname) {
	ifstream f(fname, ios::binary);
	f.seekg(0, ios::end);
	int size = f.tellg();
	size = size / sizeof(Goods);
	f.seekg(0, ios::beg);
	ofstream g(gname, ios::binary);
	cout << endl;
	Goods goods;
	int k = 0;
	while (k < size) {
		f.read((char*)&goods, sizeof(Goods));
		g.write((char*)&goods, sizeof(Goods));
		k++;
	}
	cout << "Назва товару: "; cin >> goods.name;
	cout << "Магазин: "; cin >> goods.shop;
	cout << "Ціна(UAH): "; cin >> goods.price;
	cout << "Кількість: "; cin >> goods.amount;
	cout << "Од. вимірювання: "; cin >> goods.measurement;
	if (!g.write((char*)&goods, sizeof(Goods)))
	{
		cerr << "Помилка запису у файл." << endl;
	}
	f.close();
	g.close();
	ofstream file(fname, ios::binary);
	ifstream gfile(gname, ios::binary);
	while (gfile.read((char*)&goods, sizeof(Goods))) {
		file.write((char*)&goods, sizeof(Goods));
	}
	file.close();
	gfile.close();
	cout << endl;
	cout << "Товар успішно додано" << endl;
	cout << endl;
}


void EditGoods(char* fname) {
	ifstream f(fname, ios::binary);
	f.seekg(0, ios::end);
	int size = f.tellg();
	size = size / sizeof(Goods);
	f.seekg(0, ios::beg);
	Goods* goods = new Goods[size];
	Goods temp;
	f.read((char*)goods, size * sizeof(Goods));
	int numb;
	cout << "Номер товару для редагування: "; cin >> numb;
	if (numb > size) {
		cout << endl;
		cout << "Схоже ви ввели неправильний номер товару, будь ласка повторіть спробу з правильним номером товару." << endl << endl;
	}
	else {
		cout << endl;
		cout << "Назва товару: "; cin >> goods[numb-1].name;
		cout << "Магазин: "; cin >> goods[numb-1].shop;
		cout << "Ціна(UAH): "; cin >> goods[numb-1].price;
		cout << "Кількість: "; cin >> goods[numb-1].amount;
		cout << "Од. вимірювання: "; cin >> goods[numb-1].measurement;
		cout << endl;
	}
	f.close();
	ofstream file(fname, ios::binary);
	file.write((char*)goods, size * sizeof(Goods));
	cout << endl;
	cout << "Данні про файл успішно змінені." << endl << endl;
	file.close();
}

void DelGoods(char* fname, const char* gname) {
	ifstream f(fname, ios::binary);
	f.seekg(0, ios::end);
	int size = f.tellg();
	size = size / sizeof(Goods);
	f.seekg(0, ios::beg);
	ofstream g(gname, ios::binary);
	cout << endl;
	int numb;
	cout << "Введіть номер товару, який потрібно видалити: "; cin >> numb;
	Goods goods;
	int k = 1;
	while (k <= size) {
		if (k != numb) {
			f.read((char*)&goods, sizeof(Goods));
			g.write((char*)&goods, sizeof(Goods));
		}
		k++;
	}
	f.close();
	g.close();
	ofstream file(fname, ios::binary);
	ifstream gfile(gname, ios::binary);
	while (gfile.read((char*)&goods, sizeof(Goods))) {
		file.write((char*)&goods, sizeof(Goods));
	}
	file.close();
	gfile.close();
	cout << endl;
	cout << "Товар успішно видалено" << endl;
	cout << endl;
}
