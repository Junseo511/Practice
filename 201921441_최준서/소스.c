//**************************************************************
//
//		201921441	���ؼ�			11/23 �ۼ�
//		�̵�����������а�		����2 �迭���
//
//		Ư�� �Է°��� ���� �迭���� ���� ������� ����Ѵ�.
//
//**************************************************************

#define _CRT_SECURE_NO_WARNINGS
#define SIZE (sizeof(ary)/sizeof(ary[0]))	//ary ���� ���� ���� üũ
#include <stdio.h>

int ary[] = { 2,8,15,1,8,10,5,19,19,3,5,6,6,2,8,2,12,16,3,8,17,12,5,3,14,13,3,2,17,
	   19,16,8,7,12,19,10,13,8,20,16,15,4,12,3,14,14,5,2,12,14,9,8,5,3,18,
	   18,20,4 };	// ����� �迭 ����
void list_find(int list[], int num, int size);
void list_numof(int* list, int size);
double list_avg(int list[], int size);	// �Լ� ������Ÿ�� ����


int main()
{
	char preinput[81]; // ��ǲ�� ����_01
	char input; // ��ǲ�� ����_02
	do
	{
		printf("============================================================\n");
		printf("	1: Ư�� ������ ����/��ġ ����ϱ�\n");
		printf("	2: ��� ���ڿ� ���� ���� ����ϱ�\n");
		printf("	3: ��հ� ����ϱ�\n");
		printf("	q: ���α׷� ����\n");
		printf("	���ϴ� �޴��� �����Ͻÿ�: ");
		preinput[1] = NULL;
		gets(preinput);		// ��ǲ�� �ޱ�
		input = preinput[0];	// ���� �迭 �߿��� �ϳ��� input�� �ֱ�
		printf("============================================================\n\n");	// �޴� ǥ��
		if (preinput[1] != NULL) {
			rewind(stdin);	// ��ǲ�� �ʱ�ȭ
			printf("	��ȿ���� ���� ���Դϴ�.\n\n");
		}
		else {
			switch (input) {

			case '1':	// Ư�� ���� ����, ��ġ ���ϱ�
			{
				float subnum;
				int num;
				while (1) {	// ������ �ݺ�
					printf("============================================================\n");
					printf("	ã�⸦ ���ϴ� ���ڸ� �Է��Ͻÿ�(1-20) : ");
					scanf("%f", &subnum);
					num = subnum;
					if (num-subnum!=0)
					{
						rewind(stdin);	// ��ǲ�� �ʱ�ȭ
						printf("	1~20 ������ ������ �Է��Ͻÿ�.\n");
						printf("============================================================\n\n");
					}
					else if (num > 20 || num < 1)
					{
						rewind(stdin);	// ��ǲ�� �ʱ�ȭ
						printf("	1~20 ������ ������ �Է��Ͻÿ�.\n");
						printf("============================================================\n\n");
					}
					else
					{
						rewind(stdin);	// ��ǲ�� �ʱ�ȭ
						list_find(ary, num, SIZE);
						printf("============================================================\n\n");
						break;
					}
				}
				break;
			}
			case '2':	// ��� ���� ���� ���ϱ�
			{
				rewind(stdin);	// ��ǲ�� �ʱ�ȭ
				printf("======================================================\n");
				list_numof(ary, SIZE);
				printf("======================================================\n\n");
				break;
			}
			case '3':	// �迭 ���� ��� ���ϱ�
			{
				rewind(stdin);	// ��ǲ�� �ʱ�ȭ
				printf("======================================================\n");
				printf("	��հ��� %f�Դϴ�.\n", list_avg(ary,SIZE));
				printf("======================================================\n\n");
				break;
			}
			case 'q':	// ���α׷� ����
			{
				break;
			}
			default:	// ��ǲ�� ����
				rewind(stdin);	// ��ǲ�� �ʱ�ȭ
				printf("	��ȿ���� ���� ���Դϴ�.\n\n");
				break;
			}
		}
	} while (input != 'q');
	printf("	���α׷��� �����մϴ�.\n\n");
	system("pause");
	return 0;
}

void list_find(int list[], int num, int size)	// Ư�� ���� ����, ��ġ ���ϱ� �Լ�
{
	int numof = 0, j = 0;
	int location[81];
	for (int i = 0;i < size;i++) {
		if (list[i] == num) {
			numof++;
			location[j] = i + 1;
			j++;
		}
	}
	if (numof == 0)
		printf("	���� %d�� �迭�� %d���� �����ϴ�.\n", num, numof);	// Ư�� ���ڰ� �迭�� ������
	else {
		printf("	���� %d�� �迭�� %d�� ������ ", num, numof);	// Ư�� ���� ����
		for (int i = 0;i < j;i++)	// Ư�� ���� ��ġ
			printf(", %d", location[i]);
		printf(" �� ��ġ�� �ֽ��ϴ�.\n");
	}

	return 0;
}

void list_numof(int* list, int size)	// ��� ���� ���� ���ϱ� �Լ�
{
	int num = 0;
	for (int x = 1;x < 20;x++)
	{
		for (int y = 0;y < size;y++) {
			if (x == *(list + y))
				num++;
		}
		printf("%d : %d��\n", x, num);
		num = 0;
	}
}

double list_avg(int list[], int size)	// �迭 ���� ��� ���ϱ� �Լ�
{
	int sum = 0;
	double result = 0;
	for (int i = 0;i < size;i++)
		sum += list[i];
	result = (double)sum / size;
	return result;
}