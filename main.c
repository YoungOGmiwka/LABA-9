#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAXLEN 100
void main(void)
{
	FILE *fpin;
	FILE *fpout;
	char line[MAXLEN]; // строчка из файла
	char *ptr = NULL; // указатель на строчку
	char *begin = NULL;
	char *end = NULL;
	char *tmp;
	int flag = -1;
	fpin = fopen("test.txt", "r");
	fpout = fopen("resut.txt", "w");
	while(ptr = fgets(line, MAXLEN, fpin))
	{
		flag = -1;
		while (*ptr != '\0')
		{
			if ((*ptr == '_')) 
			{
				if (flag == -1)
				{
					flag = -2; //махинация, если первый проход,
					begin = &*ptr;// чтобы удалить пробелы перед первым словом
				}
				if (flag == 0)
				{
					begin = &*ptr; //запоминаем первый пробел
					flag = 1; //флаг означает, что начало уже 
				}		     //найдено для множества пробелов
			}
			else {
				if (flag == -1) flag = 0;
				if (flag == -2) {//махинация, если первый проход
					ptr++;
					flag = 1; //отходим от концепции "первый проход"
				}			 //, переходим к постоянным случаям
				if (flag == 1) {
					ptr--;//шаг назад на '_'
					end = &*ptr;//запоминаем последний пробел
					ptr = &*begin;       //вернем указатель на начальный пробел,
					tmp = begin;
					if (begin != end) {// так как сейчас будет замена
						while (*begin++ = *end++)
							;
					}
					ptr = tmp;
					end = NULL;	//обнуление
					begin = NULL;
					flag = 0;
				}
			}	
			ptr++;
		}
		if (flag == 1) {
			ptr--;//шаг назад на '_'
			end = &*ptr;//запоминаем последний пробел
			ptr = &*begin;       //вернем указатель на начальный пробел,
			tmp = begin;
			if (begin != end) {// так как сейчас будет замена
				while (*begin++ = *end++)
					;
			}
			ptr = tmp;
			end = NULL;	//обнуление
			begin = NULL;
			flag = 0;
		}
		flag = -1;
		fprintf(fpout,"%s",line);
	}
	fclose(fpin);
	fclose(fpout);
}
