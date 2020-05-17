#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

FILE* f_out,* f_in;

struct locality
{
    char terrain[56];
    long int human_quantity;
    double distance;	
};

void medium_1()
{
	/* Вывести в бинарный файл информацию о населенных пунктах, а также среднюю дистанцию
	   между пунктами и почтовыми отделениями. */

	locality* arr;
	int size;
	double medium_distance = 0;

	//количество пунктов не может быть меньше 1;
	do
	{
		cout << "Введите количество населенных пунктов, данные которых вы будете вводить: ";
		cin >> size;
	} while (size < 1);

	arr = new locality[size];

	for (int i = 0; i < size; i++)
	{
		cout << "Введите наименование населенного пункта номер " << i + 1 << ": ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].terrain, 56);
		cout << endl;

		do {
			cout << "Введите кол-во населения: ";
			cin >> arr[i].human_quantity;
			cout << endl;
		} while (arr[i].human_quantity > 25000000);

		do {
			cout << "Введите дистанцию до почтового отделения(в км): ";
			cin >> arr[i].distance;
			cout << endl;
		} while (arr[i].distance > 1000);

		cout << endl;

		medium_distance += arr[i].distance;
	}

	medium_distance /= size;

	//записываем в бин. файл данные, включая среднюю дистанцию;
	ofstream input("medium1_bin_File.bin", ios::binary | ios::out);

	for (int i = 0; i < size; i++)
	{
		input << "Населенный пункт " << i + 1 << ":" << endl;
		input.write((char*)&arr[i], sizeof arr[i]) << endl << endl;
	}

	input << "Средняя дистанция: ";
	input.write((char*)&medium_distance, sizeof medium_distance) << endl << endl;

	//закрываем файл;
	input.close();

	cout << "Данные записаны в файл" << endl << endl;
	
	/*
	Второй вариант записи:
	f_out = fopen("medium1_bin_File.bin", "wb");
	fwrite(arr, sizeof(locality), size, f_out);
	fclose(f_out);
	*/
}

void medium_2()
{
	/* Записать в бинарный файл некоторое кол-во вещественых чисел, считать данные из файла,
	   отрицательные элементы увеличить на среднее арифметическое этих чисел, положительные - уменьшить
	   на это же значение. Вывести в консоли числа до и после изменений. */

	int quantity;
	double middle = 0;

	do
	{
		cout << "Введите количество чисел которые вы будете вводить: ";
		cin >> quantity;
	} while (quantity < 1);

	double* arr = new double[quantity];

	for (int i = 0; i < quantity; i++)
	{
		cout << "Число номер " << i + 1 << ": ";
		cin >> arr[i];
		cout << endl;
	}

	//после записи открываем файл и считываем данные в новый массив;
	f_out = fopen("medium2_numbers_before.bin", "wb");
	fwrite(arr, sizeof(double), quantity, f_out);
	fclose(f_out);
	
	cout << "Цифры перед изменением: ";

	double* new_arr = new double[quantity];
	f_in = fopen("medium2_numbers_before.bin", "rb");
	fread(new_arr, sizeof(double), quantity, f_in);
	fclose(f_in);

	for (int i = 0; i < quantity; i++)
	{
		cout << new_arr[i] << " ";
		middle += new_arr[i];
	}

	middle = middle / quantity;

	//прибавляем либо отнимаем среднее значение;
	for (int i = 0; i < quantity; i++)
	{
		if (new_arr[i] < 0)
		{
			new_arr[i] = new_arr[i] + middle;
		}

		if (new_arr[i] > 0)
		{
			new_arr[i] = new_arr[i] - middle;
		}
	}

	f_out = fopen("medium2_numbers_after.bin", "wb");
	fwrite(new_arr, sizeof(double), quantity, f_out);
	fclose(f_out);

	cout << endl << endl << "Цифры после изменения: ";

	f_in = fopen("medium2_numbers_after.bin", "rb");
	fread(new_arr, sizeof(double), quantity, f_in);
	fclose(f_in);

	//выводим числа после изменения;
	for (int i = 0; i < quantity; i++)
	{
		cout << new_arr[i] << " ";
	}

	cout << endl << endl;
}

struct car
{
	char firm[56];
	int year;
	long long int milage;
	double price;
};

void medium_3()
{
	/* Уменьшить цену автомобиля на 10% если он был выпущен более 10 лет назад,
	   и на 15%, если его пробег составляет более 1000км. */

	car* arr;
	int size, modern_year = 2020;

	//количество машин не может быть меньше 1;
	do
	{
		cout << "Введите количество автомобилей, данные которых вы будете вводить: ";
		cin >> size;
	} while (size < 1);

	arr = new car[size];

	for (int i = 0; i < size; i++)
	{
		cout << "Введите фирму автомобиля номер " << i + 1 << ": ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].firm, 56);
		cout << endl;

		do {
			cout << "Год выпуска: ";
			cin >> arr[i].year;
			cout << endl;
		} while (arr[i].year < 1900 || arr[i].year > 2020);

		do {
			cout << "Введите пробег(в км): ";
			cin >> arr[i].milage;
			cout << endl;
		} while (arr[i].milage < 0);

		do {
			cout << "Введите цену(в $): ";
			cin >> arr[i].price;
			cout << endl;
		} while (arr[i].price < 0);

		cout << endl;
	}

	//после записи открываем файл и считываем данные в новый массив;
	f_out = fopen("medium3_cars_before.bin", "wb");
	fwrite(arr, sizeof(car), size, f_out);
	fclose(f_out);

	car* new_arr = new car[size];

	f_in = fopen("medium3_cars_before.bin", "rb");
	fread(new_arr, sizeof(car), size, f_in);
	fclose(f_in);

	cout << "Данные из файла перед изменением:" << endl << endl;

	for (int i = 0; i < size; i++)
	{
		cout << "Марка автомобиля номер " << i + 1 << ": " << new_arr[i].firm << endl;
		cout << "Год выпуска: " << new_arr[i].year << endl;
		cout << "Пробег: " << new_arr[i].milage << endl;
		cout << "Цена(в $): " << new_arr[i].price << endl << endl;
	}

	for (int i = 0; i < size; i++)
	{
		if (modern_year - new_arr[i].year > 10 && new_arr[i].milage <= 1000)
		{
			new_arr[i].price = new_arr[i].price / 100 * 90;
		}
		if (new_arr[i].milage > 1000)
		{
			new_arr[i].price = new_arr[i].price / 100 * 85;
		}
	}

	f_out = fopen("medium3_cars_after.bin", "wb");
	fwrite(new_arr, sizeof(car), size, f_out);
	fclose(f_out);

	f_in = fopen("medium3_cars_after.bin", "rb");
	fread(new_arr, sizeof(car), size, f_in);
	fclose(f_in);

	cout << "Данные из файла после изменения:" << endl << endl;

	for (int i = 0; i < size; i++)
	{
		cout << "Марка автомобиля номер " << i + 1 << ": " << new_arr[i].firm << endl;
		cout << "Год выпуска: " << new_arr[i].year << endl;
		cout << "Пробег: " << new_arr[i].milage << endl;
		cout << "Цена(в $): " << new_arr[i].price << endl << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "RU");

	int a;
	int count = 0;

	do
	{
		cout << "Введите номер задания(medium_1 - 1, medium_2 - 2, medium_3 - 3): ";

		cin >> a;

		cout << endl;

		if (a == 1)
		{
			medium_1();
			count++;
		}

		if (a == 2)
		{
			medium_2();
			count++;
		}

		if (a == 3)
		{
			medium_3();
			count++;
		}

	} while (count == 0);

	int b;

	do
	{

		count = 0;

		cout << "Продолжить ввод? Да - 1, Нет - 2: ";

		cin >> b;

		cout << endl;

		if (b == 1)
		{
			count++;
			main();
		}

		if (b == 2)
		{
			cout << "Вы решили не продолжать";
			count++;
			break;
		}

	} while (count == 0);
}


