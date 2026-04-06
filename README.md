# C++
Практика C++
#include "stdafx.h"
#include <iostream>

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

void print_trenches(trench trenches[], int size) {
	for (int i = 0; i < size; i++) {
		std::cout << "Название:" << trenches[i].name << '\n';
		std::cout << "Глубина:" << trenches[i].deep.meters << "м(" << trenches[i].deep.kilometers << "км)" << '\n';
		std::cout << "Океан:" << trenches[i].ocean << '\n';
		std::cout << "Тип:" << type_string(trenches[i].type) << '\n';
		std::cout << '\n';
	}
}

int deep_7(trench trenches[], int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (trenches[i].deep.meters > 7000) {
			count++;
		}
	}
	return count;
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
	std::cout << "Количество впадин глубже 7 метров: " << deep_7(trenches, 20) << '\n';
}
