//TA_Lab_2_3_2023.c Динамічні масиви структур. Робота з файлами. 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

struct book
{
	char author[20];
	char title[50];
	char publ[15];
	char year[5];
};

int main(void)
{
	//Встановив кодування, підключення Укр. мови
	system("chcp 1251");
	setlocale(LC_CTYPE, "ukr");
	system("cls");

	int i, N;
	printf("Задайте кількість книг: ");
	scanf("%d", &N);
	struct book *Lib = (struct book*)malloc(N*sizeof(struct book)); 
	if (Lib != NULL)
	{
		//Введення данних з консолі
		for (i = 0; i < N; ++i)
		{
			getchar();
			printf("Введіть автора %d книги:", (1 + i));
			gets_s((Lib + i)->author, 20 * sizeof(char));
			printf("Введіть назву %d книги:", (1 + i));
			gets_s((Lib + i)->title, 50 * sizeof(char));
			printf("Введіть видавництво %d книги:", (1 + i));
			gets_s((Lib + i)->publ, 15 * sizeof(char));
			printf("Введіть рік видання %d книги:", (1 + i));
			gets((Lib + i)->year, 5 * sizeof(char));
		}
	}
	else
	{
		printf("Збій виділення динамічної пам'яті");
		exit(1);
	}
	system("cls");
	//Запис отриманих з консолі відомостей у файл
	FILE *outfile;
	outfile = fopen("Lib_Inp.dat", "wb");
	if (outfile == NULL)
	{
		printf("\n Помилка відкриття файлу для запису інформації\n");
		exit(1);
	}
	for (i = 0; i < N; i++)
	{
		fwrite(&Lib[i], sizeof(struct book), 1, outfile);
		if (fwrite == 0)
		{
			printf("Помилка запису даних у файл\n");
			exit(1);
		}
	}
	printf("\n Задані Вами відомості упішно записано у файл.\n");

	fclose(outfile);//Файл закрив
	free(Lib);//Очистив пам'ять

	//Зчитування структури даних з файлу
	FILE *infile;
	infile = fopen("Lib_Inp.dat", "rb");
	if (infile == NULL)
	{
		printf("\n Помилка відкриття файлу для считування інформації\n");
		exit(1);
	}
	Lib = (struct book*)malloc(N*sizeof(struct book));
	if (Lib == NULL)
	{
		printf("Збій виділення динамічної пам'яті");
		exit(1);
	}

	for (i = 0; i < N; i++)
	{
		fread(&Lib[i], sizeof(struct book), 1, infile);
	}
	fclose(infile);//Файл закрив

	printf("\n Ви ввели і записали у файл наступну інформацію:\n");

	//Виведення в консоль  

	printf("  _______________________________________________________________________________ \n");
	printf(" | Автор книги     | Назва книги		 | Видавництво	 | Рік видання   |\n");
	printf(" |_________________|_____________________________|_______________|_______________| \n");
	for (i = 0; i < N; i++)
	{
		printf(" | %-15s | %-24s    | %-13s | %-13s |\n", (Lib + i)->author, (Lib + i)->title, (Lib + i)->publ, (Lib + i)->year);
		printf(" |_________________|_____________________________|_______________|_______________| \n");
	}

	// Сортування структури по полю автор
	int res;
	struct book buuf;

	for (i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if ((res = strcmp((Lib + i)->author, (Lib + j)->author)) < 0)
			{
				buuf = *(Lib + i);
				*(Lib + i) = *(Lib + j);
				*(Lib + j) = buuf;
			}
		}
	}

	//Запис відсортованих данних у файл
	FILE *outrezfile;
	outrezfile = fopen("Lib_Rez.dat", "wb");

	if (outrezfile == NULL)
	{
		printf("\n Помилка відкриття файлу для запису інформації\n");
		exit(1);
	}

	for (i = 0; i < N; i++)
	{
		fwrite(&Lib[i], sizeof(struct book), 1, outrezfile);
		if (fwrite == 0)
		{
			printf("Помилка запису даних у файл !\n");
			exit(1);
		}
	}
	printf("\n Відсортовані відомості упішно записано у файл.\n");

	printf("\n У файл записано наступну відсортовану інформацію:\n");
	//Виведення в консоль  
	printf("  _______________________________________________________________________________ \n");
	printf(" | Автор книги     | Назва книги		 | Видавництво	 | Рік видання   |\n");
	printf(" |_________________|_____________________________|_______________|_______________| \n");
	for (i = 0; i < N; i++)
	{
		printf(" | %-15s | %-24s    | %-13s | %-13s |\n", (Lib + i)->author, (Lib + i)->title, (Lib + i)->publ, (Lib + i)->year);
		printf(" |_________________|_____________________________|_______________|_______________| \n");
	}
	fclose(outrezfile);

	//Виведення в текстовий файл
	FILE *rezfile;
	rezfile = fopen("Lib_Rez.txt", "wt");
	if (rezfile == NULL)
	{
		printf("\n Помилка відкриття файлу для запису інформації\n");
		exit(1);
	}
	fprintf(rezfile,"  _______________________________________________________________________________ \n");
	fprintf(rezfile," | Автор книги     | Назва книги		 | Видавництво	 | Рік видання   |\n");
	fprintf(rezfile," |_________________|_____________________________|_______________|_______________| \n");
	for (i = 0; i < N; i++)
	{
		fprintf(rezfile, " | %-15s | %-24s    | %-13s | %-13s |\n", (Lib + i)->author, (Lib + i)->title, (Lib + i)->publ, (Lib + i)->year);
		fprintf(rezfile, " |_________________|_____________________________|_______________|_______________| \n");
	}

	fclose(rezfile);
	free(Lib);

	getchar();
	return 0;
}
