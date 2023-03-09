//**************************************************************
//
//		201921441	최준서			11/23 작성
//		미디어기술콘텐츠학과		과제2 배열사용
//
//		특정 입력값에 따라 배열에서 계산된 결과값을 출력한다.
//
//**************************************************************

#define _CRT_SECURE_NO_WARNINGS
#define SIZE (sizeof(ary)/sizeof(ary[0]))	//ary 안의 숫자 갯수 체크
#include <stdio.h>

int ary[] = { 2,8,15,1,8,10,5,19,19,3,5,6,6,2,8,2,12,16,3,8,17,12,5,3,14,13,3,2,17,
	   19,16,8,7,12,19,10,13,8,20,16,15,4,12,3,14,14,5,2,12,14,9,8,5,3,18,
	   18,20,4 };	// 사용할 배열 정의
void list_find(int list[], int num, int size);
void list_numof(int* list, int size);
double list_avg(int list[], int size);	// 함수 프로토타입 정의


int main()
{
	char preinput[81]; // 인풋값 정의_01
	char input; // 인풋값 정의_02
	do
	{
		printf("============================================================\n");
		printf("	1: 특정 숫자의 개수/위치 출력하기\n");
		printf("	2: 모든 숫자에 대한 개수 출력하기\n");
		printf("	3: 평균값 출력하기\n");
		printf("	q: 프로그램 종료\n");
		printf("	원하는 메뉴를 선택하시오: ");
		preinput[1] = NULL;
		gets(preinput);		// 인풋값 받기
		input = preinput[0];	// 받은 배열 중에서 하나만 input에 넣기
		printf("============================================================\n\n");	// 메뉴 표시
		if (preinput[1] != NULL) {
			rewind(stdin);	// 인풋값 초기화
			printf("	유효하지 않은 값입니다.\n\n");
		}
		else {
			switch (input) {

			case '1':	// 특정 숫자 개수, 위치 구하기
			{
				float subnum;
				int num;
				while (1) {	// 오류시 반복
					printf("============================================================\n");
					printf("	찾기를 원하는 숫자를 입력하시오(1-20) : ");
					scanf("%f", &subnum);
					num = subnum;
					if (num-subnum!=0)
					{
						rewind(stdin);	// 인풋값 초기화
						printf("	1~20 사이의 정수를 입력하시오.\n");
						printf("============================================================\n\n");
					}
					else if (num > 20 || num < 1)
					{
						rewind(stdin);	// 인풋값 초기화
						printf("	1~20 사이의 정수를 입력하시오.\n");
						printf("============================================================\n\n");
					}
					else
					{
						rewind(stdin);	// 인풋값 초기화
						list_find(ary, num, SIZE);
						printf("============================================================\n\n");
						break;
					}
				}
				break;
			}
			case '2':	// 모든 숫자 개수 구하기
			{
				rewind(stdin);	// 인풋값 초기화
				printf("======================================================\n");
				list_numof(ary, SIZE);
				printf("======================================================\n\n");
				break;
			}
			case '3':	// 배열 숫자 평균 구하기
			{
				rewind(stdin);	// 인풋값 초기화
				printf("======================================================\n");
				printf("	평균값은 %f입니다.\n", list_avg(ary,SIZE));
				printf("======================================================\n\n");
				break;
			}
			case 'q':	// 프로그램 종료
			{
				break;
			}
			default:	// 인풋값 에러
				rewind(stdin);	// 인풋값 초기화
				printf("	유효하지 않은 값입니다.\n\n");
				break;
			}
		}
	} while (input != 'q');
	printf("	프로그램을 종료합니다.\n\n");
	system("pause");
	return 0;
}

void list_find(int list[], int num, int size)	// 특정 숫자 개수, 위치 구하기 함수
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
		printf("	숫자 %d는 배열에 %d개로 없습니다.\n", num, numof);	// 특정 숫자가 배열에 없을때
	else {
		printf("	숫자 %d는 배열에 %d개 있으며 ", num, numof);	// 특정 숫자 개수
		for (int i = 0;i < j;i++)	// 특정 숫자 위치
			printf(", %d", location[i]);
		printf(" 번 위치에 있습니다.\n");
	}

	return 0;
}

void list_numof(int* list, int size)	// 모든 숫자 개수 구하기 함수
{
	int num = 0;
	for (int x = 1;x < 20;x++)
	{
		for (int y = 0;y < size;y++) {
			if (x == *(list + y))
				num++;
		}
		printf("%d : %d개\n", x, num);
		num = 0;
	}
}

double list_avg(int list[], int size)	// 배열 숫자 평균 구하기 함수
{
	int sum = 0;
	double result = 0;
	for (int i = 0;i < size;i++)
		sum += list[i];
	result = (double)sum / size;
	return result;
}