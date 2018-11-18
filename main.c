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
	int flag = -1;
	fpin = fopen("test.txt", "r");
	fpout = fopen("resut.txt", "w");
	while (!feof(fpin))
	{
		ptr = fgets(line, MAXLEN, fpin);
		if (ptr == NULL)
			break;
		while (*ptr != '\0')
		{
			if ((*ptr == '_') || (*ptr == '\n')) {
				if (flag == -1) {
					flag = -2; //махинация, если первый проход,
					begin = &*ptr;// чтобы удалить пробелы перед первым словом
				}
				if (flag == 0) {
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
					if (begin != end) {// так как сейчас будет замена
						for (; *begin != '\0'; *begin++, *end++) {//удаление пробелов
							*begin = *end;
						}
					}
					end = NULL;	//обнуление
					begin = NULL;
					flag = 0;
				}
			}
			ptr++;
		}
		flag = -1;
		fputs(line, fpout);
	}
	fclose(fpin);
	fclose(fpout);
}
