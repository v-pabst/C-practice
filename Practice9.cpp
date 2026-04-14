// Practice9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;

enum type_d { разлом, желоб, хребет };

struct depth {
	int meters;
	int kilometers;
};
struct trench {
	char name[20];
	depth deep;
	char ocean[20];
	type_d type;
};

const char* type_string(type_d type) {
	switch (type) {
	case разлом: return "Разлом";
	case желоб: return "Желоб";
	case хребет: return "Хребет";
	}
}

//Вывод всех данных
void print_trenches(trench trenches[], int size) {
	for (int i = 0; i < size; i++) {
		cout << "\nНазвание:" << trenches[i].name << '\n';
		cout << "Глубина:" << trenches[i].deep.meters << "м(" << trenches[i].deep.kilometers << "км)" << '\n';
		cout << "Океан:" << trenches[i].ocean << '\n';
		cout << "Тип:" << type_string(trenches[i].type) << '\n';
	}
}

//Количество пвадин глубже 7000 метров
int deep_7(trench trenches[], int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (trenches[i].deep.meters > 7000) {
			count++;
		}
	}
	return count;
}

//Сортировка по убыванию по океанам
void sort_ocean(trench trenches[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
				if (strcmp(trenches[j].ocean, trenches[j + 1].ocean) > 0) {
					trench temp = trenches[j];
					trenches[j] = trenches[j + 1];
					trenches[j + 1] = temp;
				}
			}
		}
	}

//Впадины одного типа
void print_type(trench trenches[], int size, type_d type) {
	cout << "Желобные впадины:\n";
	trench temp_trenches[20];
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (trenches[i].type == type) {
			temp_trenches[count] = trenches[i];
			count++;
		}
	}
	sort_ocean(temp_trenches, count);
	for (int i = 0; i < count; i++) {
		cout << "\nНазвание: " << temp_trenches[i].name << '\n';
		cout << "Глубина: " << temp_trenches[i].deep.meters << " м ("
			<< temp_trenches[i].deep.kilometers << " км)\n";
		cout << "Океан: " << temp_trenches[i].ocean << '\n';
		cout << "Тип: " << type_string(temp_trenches[i].type) << '\n';
	}
}

//Три глубочайшие впадины
void deepest_3(trench trenches[], int size) {
	trench sorted[20];
	for (int a = 0; a < size;  a++) {
		sorted[a] = trenches[a];
	}
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (sorted[j].deep.meters < sorted[j + 1].deep.meters) {
				trench temp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = temp;
			}
		}
	}
	cout << "\nТри глубочайшие впадины:\n";
	cout << "Название:" << sorted[0].name << " Тип:" << type_string(sorted[0].type) << '\n';
	cout << "Название:" << sorted[1].name << " Тип:" << type_string(sorted[1].type) << '\n';
	cout << "Название:" << sorted[2].name << " Тип:" << type_string(sorted[2].type) << '\n';
}

//Изменение данных впадины
void edit_trench(trench trenches[], int size, int depth) {
	bool found = false;
	for (int i = 0; i < size; i++) {
		if (trenches[i].deep.meters == depth) {
			found = true;
			cout << "\nНайдена впадина: " << trenches[i].name << '\n';

			cout << "Введите новое название: ";
			cin >> trenches[i].name;
			cin.ignore();

			cout << "Введите новую глубину (метры): ";
			cin >> trenches[i].deep.meters;
			cin.ignore();

			cout << "Введите новую глубину (километры): ";
			cin >> trenches[i].deep.kilometers;
			cin.ignore();

			cout << "Введите океан: ";
			cin.getline(trenches[i].ocean, 20);
			cin.ignore();

			int type_choice;
			cout << "Выберите тип (0-Разломная, 1-Желоб, 2-Хребет): ";
			cin >> type_choice;
			trenches[i].type = static_cast<type_d>(type_choice);
			cin.ignore();

			cout << "Данные обновлены\n";
		}
	}
	if (!found) {
		cout << "Впадина с глубиной " << depth << " м не найдена!\n";
	}
}

//Впадины одного океана
void one_ocean(trench trenches[], int size, const char* ocean, trench result[], int& count) {
	count = 0;
	for (int i = 0; i < size; i++) {
		if (strcmp(trenches[i].ocean, ocean) == 0) {
			result[count] = trenches[i];
			count++;
		}
	}
}

//Оберточная функция
void print_filtered(trench trenches[], int size, const char* ocean) {
	trench filtered[20];
	int filtered_count = 0;
	one_ocean(trenches, size, ocean, filtered, filtered_count);
	print_trenches(filtered, filtered_count);
}

//Работа с файлами
//Чтение глубины впадин из файла
void read_deep(trench trenches[], int size, const char* filename) {
	ifstream fin;
	fin.open(filename);
	char name[20];
	int meters;
	if (!fin.is_open()) {
		cout << "Ошибка!\n";
		return;
	}
	while (fin >> name >> meters) {
		for (int i = 0; i < size; i++) {
			if (strcmp(trenches[i].name, name) == 0) {
				trenches[i].deep.meters = meters;
				trenches[i].deep.kilometers = meters / 1000;
			}
		}
	}
	fin.close();
}

//Запись структуры в бинарный файл
void write_binary(trench trenches[], int size, const char* filename) {
	ofstream out(filename, ios::binary | ios::out);
	for (unsigned i = 0; i < size; i++)
		out.write((char*)&trenches[i], sizeof(trenches[i]));
	out.close();
}

//Чтение структуры из бинарного файла 
void read_binary(trench trenches[], int size, const char* filename){
	fstream in(filename, ios::binary | ios::in);
	for (unsigned i = 0; i < size; i++) {
		in.read((char*)&trenches[i], sizeof(trenches[i]));
	}
	in.close();
	for (unsigned i = 0; i < size; i++) {
		cout << '\n' << trenches[i].name << "\n";
		cout << trenches[i].deep.meters << "\n";
		cout << trenches[i].ocean << "\n";
		cout << trenches[i].type << "\n";
	}

}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");
	struct trench trenches[21];
	trenches[0] = { "Тонга", { 10882, 10 }, "Тихий", разлом };
	trenches[1] = { "Марианская", { 11002, 11 }, "Тихий", разлом };
	trenches[2] = { "Курило-Камчатская", { 3489, 3 }, "Северный Ледовитый", желоб };
	trenches[3] = { "Кавказская", { 7892, 7 }, "Атлантический", хребет };
	trenches[4] = { "Кайманская", { 10120, 10 }, "Тихий", хребет };
	trenches[5] = { "Пуэрто-Риканская", { 6290, 6 }, "Индийский", желоб };
	trenches[6] = { "Японская", { 4621, 4 }, "Тихий", разлом };
	trenches[7] = { "Южная", { 8015, 8 }, "Северный Ледовитый", желоб };
	trenches[8] = { "Арабская", { 9949, 9 }, "Индийский", разлом };
	trenches[9] = { "Марокканская", { 5318, 5 }, "Индийский", разлом };
	trenches[10] = { "Романская", { 8639, 8 }, "Тихий", хребет };
	trenches[11] = { "Новая Британская", { 7381, 7 }, "Тихий", хребет };
	trenches[12] = { "Джаванская", { 1082, 1 }, "с", желоб };
	trenches[13] = { "Гватемальская", { 2289, 2 }, "Тихий", разлом };
	trenches[14] = { "Чиллийская", { 4706, 4 }, "Северный Ледовитый", разлом };
	trenches[15] = { "Цейман", { 5001, 5 }, "Северный Ледовитый", желоб };
	trenches[16] = { "Руйкуй", { 8421, 8 }, "Атлантический", желоб };
	trenches[17] = { "Китайская", { 6578, 6 }, "Тихий", разлом };
	trenches[18] = { "Картская", { 1198, 1 }, "Индийский", хребет };
	trenches[19] = { "Буэрто", { 6382, 6 }, "Атлантический", разлом };

	//Вывод 20 впадин
	print_trenches(trenches, 20);

	//Вывод впадин глубже 7000 метров
	cout << "\nКоличество впадин глубже 7000 метров: " << deep_7(trenches, 20) << '\n';
	
	//Вывод типов 3 глубочайших впадин
	deepest_3(trenches, 20);
	cout << '\n';

	//Вывод желобных впадин, отсортированных по океанам
	print_type(trenches, 20, желоб);

	//Изменение данных впадины по глубине
	int edit_depth;
	cout << "\nВведите глубину впадины для редактирования: ";
	cin >> edit_depth;
	edit_trench(trenches, 20, edit_depth);

	//Вывод впадин одного океана
	char one_ocean[20];
	cout << "\nВведите название океана: ";
	cin.getline(one_ocean, 20);
	print_filtered(trenches, 20, one_ocean);

	//Работа с файлами
	//Чтение глубин из файла
	read_deep(trenches, 20, "deep.txt");
	print_trenches(trenches, 20);

	//Запись структуры в бинарный файл
	write_binary(trenches, 20, "trenches.bin");

	//Чтение структуры из бинарного файла
	read_binary(trenches, 20, "trenches.bin");
}
