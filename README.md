# C++
Практика C++
#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cstdio>

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
		std::cout << "Название:" << trenches[i].name << '\n';
		std::cout << "Глубина:" << trenches[i].deep.meters << "м(" << trenches[i].deep.kilometers << "км)" << '\n';
		std::cout << "Океан:" << trenches[i].ocean << '\n';
		std::cout << "Тип:" << type_string(trenches[i].type) << '\n';
		std::cout << '\n';
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
	trench type_trench[20];
	int type_count = 0;
	for (int a = 0; a < size; a++) {
		if (trenches[a].type == желоб) {
			type_trench[type_count] = trenches[a];
			type_count++;
		}
		for (int i = 0; i < type_count; i++) {
			for (int j = type_count - 1; j >= i; j--) {
				if (strcmp(type_trench[j - 1].ocean, type_trench[j].ocean) < 0) {
					trench temp = type_trench[j];
					type_trench[j] = type_trench[j - 1];
					type_trench[j - 1] = temp;
				}
			}
		}
	}
}

//void display_trenches(trench trenches[], int size) {
//	for (int i = 0; i < size; i++) {
//		trench type_trench[20];
//
//		std::cout << "Название: " << trenches[i].name << '\n';
//		std::cout << "Глубина: " << trenches[i].deep.meters << " м ("
//			<< trenches[i].deep.kilometers << " км)" << '\n';
//		std::cout << "Океан: " << trenches[i].ocean << '\n';
//		std::cout << "Тип: " << type_string(trenches[i].type) << '\n';
//		std::cout << '\n';
//	}
//}

//Вывод типов трёх глубочайших впадин
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
	std::cout << "Три глубочайшие впадины:\n";
	std::cout << "Название:" << sorted[0].name << " Тип:" << type_string(sorted[0].type) << '\n';
	std::cout << "Название:" << sorted[1].name << " Тип:" << type_string(sorted[1].type) << '\n';
	std::cout << "Название:" << sorted[2].name << " Тип:" << type_string(sorted[2].type) << '\n';
}

//Вывод впадин одного океана
void one_ocean(trench trenches[], int size, const char* ocean, trench result[], int& result_count) {
	result_count = 0;
	for (int i = 0; i < size; i++) {
		if (strcmp(trenches[i].ocean, ocean) == 0) {
			result[result_count] = trenches[i];
			result_count++;
		}
	}
}

void print_filtered(trench trenches[], int size, const char* ocean) {
	trench filtered[20];
	int filtered_count = 0;
	one_ocean(trenches, size, ocean, filtered, filtered_count);
	print_trenches(filtered, filtered_count);
}

int main()
{
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
	trenches[12] = { "Джаванская", { 1082, 1 }, "Северный Ледовитый", желоб };
	trenches[13] = { "Гватемальская", { 2289, 2 }, "Тихий", разлом };
	trenches[14] = { "Чиллийская", { 4706, 4 }, "Северный Ледовитый", разлом };
	trenches[15] = { "Цейман", { 5001, 5 }, "Северный Ледовитый", желоб };
	trenches[16] = { "Руйкуй", { 8421, 8 }, "Атлантический", желоб };
	trenches[17] = { "Китайская", { 6578, 6 }, "Тихий", разлом };
	trenches[18] = { "Картская", { 1198, 1 }, "Индийский", хребет };
	trenches[19] = { "Буэрто", { 6382, 6 }, "Атлантический", разлом };

	print_trenches(trenches, 20);
	//std::cout << "Количество впадин глубже 7 метров: " << deep_7(trenches, 20) << '\n';
	/*print_trenches(sort_ocean(trenches, 20), 20);*/
	deepest_3(trenches, 20);
	char oneocean[20];
	std::cout << "Введите название океана\n";
	std::cin >> oneocean;
	print_filtered(trenches, 20, oneocean);
	}
}

