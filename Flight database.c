#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct out_date { //структура даты вылета
	int day, month, year;
} out_date;

typedef struct out_time { //структура время вылета
	int hour, min;
} out_time;

typedef struct number { //структура номера билета
	int nomer;
} number;

typedef struct price { //структура прайс билета
	int dollar;
} price;

typedef struct fly { //структура целого полёта
	char point[100]; //куда летишь
	out_date outdate_D;
	out_time outtime_D;
	number number_D;
	price price_D;
} fly;

typedef struct base { //база данных
	fly* field;
	int max, mix;
} base;

void get_base(base* record) { //ввод через консоль 

	printf("Введите пункт назначения для самолёта: ");

	if (record->mix == record->max) {
		record->field = realloc(record->field, 2 * record->max * sizeof(fly));
		record->max *= 2;
	}

	scanf("%s", &record->field[record->mix].point);

	printf("Введите дату вылета (день, месяц, год): ");

	scanf("%d", &record->field[record->mix].outdate_D.day);
	scanf("%d", &record->field[record->mix].outdate_D.month);
	scanf("%d", &record->field[record->mix].outdate_D.year);


	printf("Введите время вылета (часы, минуты): ");

	scanf("%d", &record->field[record->mix].outtime_D.hour);
	scanf("%d", &record->field[record->mix].outtime_D.min);


	printf("Введите номер билета: ");

	scanf("%d", &record->field[record->mix].number_D.nomer);


	printf("Введите цену за билет на одного пассажира: ");

	scanf("%d", &record->field[record->mix].price_D.dollar);


	record->mix += 1;
}

void print_base(base* record) { //что ты там навводил
	for (int i = 0; i < record->mix; i++) {
		printf("%d. ", i + 1);
		printf("%s\n", record->field[i].point);
		printf("Дата вылета: %d.%d.%d\n", record->field[i].outdate_D.day, record->field[i].outdate_D.month, record->field[i].outdate_D.year);
		printf("Время вылета: %d.%d\n", record->field[i].outtime_D.hour, record->field[i].outtime_D.min);
		printf("Номер билета: %d\n", record->field[i].number_D.nomer);
		printf("Цена билета: %d\n", record->field[i].price_D.dollar);
		printf("\n");
	}
}

void print_search(base* record, int i) { //где нужный рейс
	printf("%s\n", record->field[i].point);
	printf("Дата вылета: %d.%d.%d\n", record->field[i].outdate_D.day, record->field[i].outdate_D.month, record->field[i].outdate_D.year);
	printf("Время вылета: %d.%d\n", record->field[i].outtime_D.hour, record->field[i].outtime_D.min);
	printf("Номер билета: %d\n", record->field[i].number_D.nomer);
	printf("Цена билета: %d\n", record->field[i].price_D.dollar);
	printf("\n");
	}

void print_in_file(char* file, base* record) { //запись в файл каракулей
	FILE* data2;
	data2 = fopen(file, "w");
	fprintf(data2, "%d\n", record->mix);
	for (int i = 0; i < record->mix; i++) {
		//fprintf(data, "%d. ", i + 1);
		fprintf(data2, "%s\n", record->field[i].point);
		fprintf(data2, "%d %d %d\n", record->field[i].outdate_D.day, record->field[i].outdate_D.month, record->field[i].outdate_D.year);
		fprintf(data2, "%d %d\n", record->field[i].outtime_D.hour, record->field[i].outtime_D.min);
		fprintf(data2, "%d\n", record->field[i].number_D.nomer);
		fprintf(data2, "%d\n", record->field[i].price_D.dollar);
	}
	fclose(data2);
}

void deletka(char* file, base* record, int z) { //для удаления
	for (int i = z - 1; i < record->mix; i++) {
		int j;
		for (j = 0; record->field[i + 1].point[j] != '\0'; j++) {
			record->field[i].point[j] = record->field[i + 1].point[j];
		}
		record->field[i].point[j] = '\0';
		record->field[i].outdate_D.day = record->field[i + 1].outdate_D.day;
		record->field[i].outdate_D.month = record->field[i + 1].outdate_D.month;
		record->field[i].outdate_D.year = record->field[i + 1].outdate_D.year;
		record->field[i].outtime_D.hour = record->field[i + 1].outtime_D.hour;
		record->field[i].outtime_D.min = record->field[i + 1].outtime_D.min;
		record->field[i].number_D.nomer = record->field[i + 1].number_D.nomer;
		record->field[i].price_D.dollar = record->field[i + 1].price_D.dollar;


	}
	record->mix -= 1;
	print_in_file(file, record);
}

void get_from_file(char* file, base* record) { //получение каракулей из файла
	FILE* data2;
	data2 = fopen(file, "r");

	fscanf(data2, "%d", &record->mix);

	if (record->mix > record->max) {
		record->field = realloc(record->field, 2 * record->max * sizeof(fly));
		record->max *= 2;
	}

	for (int i = 0; i < record->mix; i++) {
		fscanf(data2, "%s", &record->field[i].point);

		fscanf(data2, "%d", &record->field[i].outdate_D.day);
		fscanf(data2, "%d", &record->field[i].outdate_D.month);
		fscanf(data2, "%d", &record->field[i].outdate_D.year);

		fscanf(data2, "%d", &record->field[i].outtime_D.hour);
		fscanf(data2, "%d", &record->field[i].outtime_D.min);

		fscanf(data2, "%d", &record->field[i].number_D.nomer);

		fscanf(data2, "%d", &record->field[i].price_D.dollar);
	}
	fclose(data2);
}

void add_rec(char* file, base* record) { //добавить запись
	get_base(record);
	int z;
	printf("СОХРАНЯЕМ?(0 - нет, любое - да):"); //запрос пользователю о сохранении в файл
	scanf("%d\n", &z);
	if (z != 0) {
		print_in_file(file, record);
	}
}

void edit_rec(char* file, base* record, int number) { // редактировать запись
	int event_in_func = 0;
	int num = number - 1;

	printf("1. %s\n", record->field[num].point);
	printf("2 Дата вылета: %d.%d.%d\n", record->field[num].outdate_D.day, record->field[num].outdate_D.month, record->field[num].outdate_D.year);
	printf("3 Время вылета: %d.%d\n", record->field[num].outtime_D.hour, record->field[num].outtime_D.min);
	printf("4 Номер билета: %d\n", record->field[num].number_D.nomer);
	printf("5 Цена билета: %d\n", record->field[num].price_D.dollar);
	printf("\n");

	printf("Выберите запись для редактирования: ");
	scanf("%d", &event_in_func);

	switch (event_in_func) {
	case 1:
		scanf("%s", &record->field[num].point);
		break;
	case 2:
		scanf("%d", &record->field[num].outdate_D.day);
		scanf("%d", &record->field[num].outdate_D.month);
		scanf("%d", &record->field[num].outdate_D.year);
		break;
	case 3:
		scanf("%d", &record->field[num].outtime_D.hour);
		scanf("%d", &record->field[num].outtime_D.min);
		break;

	case 4:
		scanf("%d", &record->field[num].number_D.nomer);
		break;

	case 5:
		scanf("%d", &record->field[num].price_D.dollar);
		break;
	}

	print_in_file(file, record);
}

void swap_records(base* record, int old, int new) { //обмен
	base new_rec;
	new_rec.mix = 0;
	new_rec.max = 2;
	new_rec.field = malloc(1 * sizeof(fly));

	int j;

	for (j = 0; record->field[old].point[j] != '\0'; j++)
		new_rec.field[0].point[j] = record->field[old].point[j];
	new_rec.field[0].point[j] = '\0';
	new_rec.field[0].outdate_D.day = record->field[old].outdate_D.day;
	new_rec.field[0].outdate_D.month = record->field[old].outdate_D.month;
	new_rec.field[0].outdate_D.year = record->field[old].outdate_D.year;
	new_rec.field[0].outtime_D.hour = record->field[old].outtime_D.min;
	new_rec.field[0].number_D.nomer = record->field[old].number_D.nomer;
	new_rec.field[0].price_D.dollar = record->field[old].price_D.dollar;

	for (j = 0; record->field[new].point[j] != '\0'; j++)
		record->field[old].point[j] = record->field[new].point[j];
	record->field[old].point[j] = '\0';
	record->field[old].outdate_D.day = record->field[new].outdate_D.day;
	record->field[old].outdate_D.month = record->field[new].outdate_D.month;
	record->field[old].outdate_D.year = record->field[new].outdate_D.year;
	record->field[old].outtime_D.hour = record->field[new].outtime_D.hour;
	record->field[old].number_D.nomer = record->field[new].number_D.nomer;
	record->field[old].price_D.dollar = record->field[new].price_D.dollar;

	for (j = 0; new_rec.field[0].point[j] != '\0'; j++)
		record->field[new].point[j] = new_rec.field[0].point[j];
	record->field[new].point[j] = '\0';
	record->field[new].outdate_D.day = new_rec.field[0].outdate_D.day;
	record->field[new].outdate_D.month = new_rec.field[0].outdate_D.month;
	record->field[new].outdate_D.year = new_rec.field[0].outdate_D.year;
	record->field[new].outtime_D.hour = new_rec.field[0].outtime_D.hour;
	record->field[new].number_D.nomer = new_rec.field[0].number_D.nomer;
	record->field[new].price_D.dollar = new_rec.field[0].price_D.dollar;

	free(new_rec.field);
}

void sort(char* file, base* record) { //сортировка по параметрам
	int event_in_func = 0;
	int first_val = 0, second_val = 0;

	printf("Выберите по какому полю производить сортировку: \n");
	printf("1 - По СТРАНЕ прибытия \n");
	printf("2 - По ДАТЕ отлёта\n");
	printf("3 - По ВРЕМЕНИ отлёта \n");
	printf("4 - По НОМЕРУ билета \n");
	printf("5 - По ЦЕНЕ билета \n");
	scanf("%d", &event_in_func);

	switch (event_in_func) {
	case 1:
		for (int i = 0; i < record->mix; i++) {
			for (int j = record->mix - 1; j > i; j--) {
				if (record->field[j - 1].point[0] > record->field[j].point[0])
					swap_records(record, j, j - 1);
			}
		}
		print_in_file(file, record);
		break;
	case 2:
		for (int i = 0; i < record->mix; i++) {
			for (int j = record->mix - 1; j > i; j--) {
				if (record->field[j - 1].outdate_D.month > record->field[j].outdate_D.month)
					swap_records(record, j, j - 1);
			}
		}
		print_in_file(file, record);
		break;
	case 3:
		for (int i = 0; i < record->mix; i++) {
			for (int j = record->mix - 1; j > i; j--) {
				if (record->field[j - 1].outtime_D.hour > record->field[j].outtime_D.hour)
					swap_records(record, j, j - 1);
			}
		}
		print_in_file(file, record);
		break; 
	case 4:
		for (int i = 0; i < record->mix; i++) {
			for (int j = record->mix - 1; j > i; j--) {
				if (record->field[j - 1].number_D.nomer > record->field[j].number_D.nomer)
					swap_records(record, j, j - 1);
			}
		}
		print_in_file(file, record);
		break;

	case 5:
		for (int i = 0; i < record->mix; i++) {
			for (int j = record->mix - 1; j > i; j--) {
				if (record->field[j - 1].price_D.dollar > record->field[j].price_D.dollar)
					swap_records(record, j, j - 1);
			}
		}
		print_in_file(file, record);
		break;
	}
}

void searching(char* file, base* record) { //поиск по параметрам
	int event_in_func = 0;
	char word[50];
	int check = 1, len = 0;
	int day, month, year, hour, min, nomer, dollar;

	printf("Выберите по какому полю осуществить поиск: \n");
	printf("1 - По СТРАНЕ прибытия \n");
	printf("2 - По ДАТЕ отлёта\n");
	printf("3 - По ВРЕМЕНИ отлёта \n");
	printf("4 - По НОМЕРУ билета \n");
	printf("5 - По ЦЕНЕ билета \n");

	scanf("%d", &event_in_func);

	switch (event_in_func) {
	case 1:
		printf("Введите слово, которое нужно найти: ");
		scanf("%s", &word);
		for (int i = 0; i < record->mix; i++) {
			for (int j = strlen(&word); j > len; j--) {
				check = strncmp(&word, &record->field[i].point, j);
				if (check == 0) {
					printf("%d. %s\n", i + 1, record->field[i].point);
					printf("Дата вылета: %d.%d.%d\n", record->field[i].outdate_D.day, record->field[i].outdate_D.month, record->field[i].outdate_D.year);
					printf("Время отлёта: %d.%d.%d\n", record->field[i].outtime_D.hour, record->field[i].outtime_D.min);
					printf("Номер билета: %d.%d.%d\n", record->field[i].number_D.nomer);
					printf("Цена билета: %d.%d.%d\n", record->field[i].price_D.dollar);
					len = j;
					break;
				}
			}
		}
		break;
	case 2:
		printf("Введите дату (месяц, год): ");
		scanf("%d", &month);
		scanf("%d", &year);

		for (int i = 0; i < record->mix; i++) {
			if (month == record->field[i].outdate_D.month && year == record->field[i].outdate_D.year) {
				printf("%d. %s\n", i + 1, record->field[i].point);
				printf("Время отлёта: %d.%d.%d\n", record->field[i].outtime_D.hour, record->field[i].outtime_D.min);
				printf("Номер билета: %d.%d.%d\n", record->field[i].number_D.nomer);
				printf("Цена билета: %d.%d.%d\n", record->field[i].price_D.dollar);
			}
		}
		break;
	case 3:
		printf("Введите время (часы, минуты): ");
		scanf("%d", &hour);
		scanf("%d", &min);

		for (int i = 0; i < record->mix; i++) {
			if (hour == record->field[i].outtime_D.hour && min == record->field[i].outtime_D.min) {
				printf("%d. %s\n", i + 1, record->field[i].point);
				printf("Дата вылета: %d.%d.%d\n", record->field[i].outdate_D.day, record->field[i].outdate_D.month, record->field[i].outdate_D.year);
				printf("Номер билета: %d.%d.%d\n", record->field[i].number_D.nomer);
				printf("Цена билета: %d.%d.%d\n", record->field[i].price_D.dollar);
			}
		}
		break;

	case 4:
		printf("Введите номер билета: ");
		scanf("%d", &nomer);

		for (int i = 0; i < record->mix; i++) {
			if (nomer == record->field[i].number_D.nomer) {
				printf("%d. %s\n", i + 1, record->field[i].point);
				printf("Дата вылета: %d.%d.%d\n", record->field[i].outdate_D.day, record->field[i].outdate_D.month, record->field[i].outdate_D.year);
				printf("Время отлёта: %d.%d.%d\n", record->field[i].outtime_D.hour, record->field[i].outtime_D.min);
				printf("Цена билета: %d.%d.%d\n", record->field[i].price_D.dollar);
			}
		}
		break;
	case 5:
		printf("Введите цену билета: ");
		scanf("%d", &dollar);

		for (int i = 0; i < record->mix; i++) {
			if (dollar == record->field[i].price_D.dollar) {
				printf("%d. %s\n", i + 1, record->field[i].point);
				printf("Дата вылета: %d.%d.%d\n", record->field[i].outdate_D.day, record->field[i].outdate_D.month, record->field[i].outdate_D.year);
				printf("Время отлёта: %d.%d.%d\n", record->field[i].outtime_D.hour, record->field[i].outtime_D.min);
				printf("Номер билета: %d.%d.%d\n", record->field[i].number_D.nomer);
				printf("Цена билета: %d.%d.%d\n", record->field[i].price_D.dollar);
			}
		}
		break;
	}
}

void main() {
	setlocale(LC_ALL, "Russian");
	base record;
	char file_name[] = "data2.txt";
	record.mix = 0;
	record.max = 2;
	record.field = malloc(2 * sizeof(fly));
	int event = 0, num = 0, a = 0, b = 0, event2 = 0;
	printf("---------------------\n");
	printf("1) Просмотреть файл\n");
	printf("2) Внести новый рейс\n");
	printf("3) Удалить рейс\n");
	printf("4) Редактировать рейс\n");
	printf("5) Отсортировать рейсы\n");
	printf("6) Найти рейсы\n");
	printf("7) EXIT\n");
	printf("---------------------\n");
	scanf("%d", &event);

	switch (event) {
	case 1:
		get_from_file(&file_name, &record);
		print_base(&record);
		main();
		break;
		
	case 2:
		get_from_file(&file_name, &record);
		add_rec(&file_name, &record);
		main();
		break;
	case 3:
		printf("Введите номер рейса, который хотите удалить:");
		scanf("%d", &b);
		get_from_file(&file_name, &record);
		deletka(&file_name, &record, b);
		printf("Рейс успешно удалён, у вас на экране изменённая база данных по рейсам:\n");
		print_base(&record);
		main();
		break;
	case 4:
		get_from_file(&file_name, &record);
		print_base(&record);
		printf("Выберите РЕЙС, которую нужно отредактировать: ");
		scanf("%d", &event);
		edit_rec(&file_name, &record, event);
		print_base(&record);
		main();
		break;
	case 5:
		get_from_file(&file_name, &record);
		sort(&file_name, &record);
		print_base(&record);
		main();
		break;
	case 6:
		get_from_file(&file_name, &record);
		searching(&file_name, &record);
		main();
		break;
	case 7:
		break;
	}
}

