#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAXLEN 100
void main(void)
{
	FILE *fpin;
	FILE *fpout;
	char line[MAXLEN]; // ������� �� �����
	char *ptr = NULL; // ��������� �� �������
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
					flag = -2; //���������, ���� ������ ������,
					begin = &*ptr;// ����� ������� ������� ����� ������ ������
				}
				if (flag == 0) {
					begin = &*ptr; //���������� ������ ������
					flag = 1; //���� ��������, ��� ������ ��� 
				}		     //������� ��� ��������� ��������
			}
			else {
				if (flag == -1) flag = 0;
				if (flag == -2) {//���������, ���� ������ ������
					ptr++;
					flag = 1; //������� �� ��������� "������ ������"
				}			 //, ��������� � ���������� �������
				if (flag == 1) {
					ptr--;//��� ����� �� '_'
					end = &*ptr;//���������� ��������� ������
					ptr = &*begin;       //������ ��������� �� ��������� ������,
					if (begin != end) {// ��� ��� ������ ����� ������
						for (; *begin != '\0'; *begin++, *end++) {//�������� ��������
							*begin = *end;
						}
					}
					end = NULL;	//���������
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
