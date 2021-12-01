#include <stdio.h>
#include <windows.h>
#include <string.h>

#define MAX_ST 50

struct Student
{
	int id;						// 학번 
	char name[20], hakjum;		// 이름, 학점 
	int db;						
	int unix;
	int java;
	float h_avg;				// 평균 
};

void main_menu();								// 메인 메뉴 
void out_menu();								// 2번 선택시 나오는 출력 메뉴 

void in_func(struct Student* st);				// 정보 입력 
void out_func(struct Student* st);				// 정보 출력 
void out_grade(struct Student* st);				// 등수별 출력 
void out_one(struct Student* st);				// 개별 출력 
void out_all(struct Student* st);				// 전체 출력 
int rank(struct Student* st,int tmp);			// 등수를 매기는 함수 
int n_hakjum(struct Student* st, int sum);		// 학점 함수  

void modify(struct Student* st);				// 수정 함수 
void del(struct Student* st);					// 삭제 함수 

void save_file(struct Student* st);				// 파일에 저장하는 함수 
void load_file(struct Student* st);				// 파일을 불러오는 함수 

int main() 
{
	struct Student st[MAX_ST]; 
	int select, i;
	
	for(i=0; i<MAX_ST; i++)
	{
		st[i].id = -1 ; // id를 -1로 초기화
	}
	
	while(1)
	{
		system("cls");
		main_menu();
		fflush(stdin);
		scanf("%d", &select);
		system("cls");

		switch(select)
		{
		case 1:
			in_func(st);
			break;
		case 2:
			out_func(st);
			break;
		case 3:
			modify(st);
			break;
		case 4:
		    del(st);
			break;
		case 5:
			save_file(st);
			break;
		case 6:
			load_file(st);
			break;
		case 0:
			printf("프로그램을 종료합니다.\n");
			return 0;
		default:
			break;
		}
		system("pause");
	}
	return 0;
}

void main_menu()				// 메인 메뉴  
{
	puts("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	puts("┃        성적관리 프로그램           ┃");
	puts("┠━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┨"); 
	puts("┃                                    ┃");
	puts("┃    1.입 력   2.출 력   3.수 정     ┃");
	puts("┃                                    ┃");
	puts("┃    4.삭 제   5.저 장   6.불러오기  ┃");
	puts("┃                                    ┃");
	puts("┃    0.종 료                         ┃");
	puts("┃                                    ┃");
	puts("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	printf(" 번호를 선택해주세요 > ");
}

void out_menu()					// 출력 메뉴  
{
	puts("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	puts("┃         출력 선택                  ┃");
	puts("┠━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┨"); 
	puts("┃                                    ┃");
	puts("┃     1. 등수별 출력(정렬)           ┃");
	puts("┃                                    ┃");
	puts("┃     2. 개별 출력(학번 / 이름)      ┃");
	puts("┃                                    ┃");
	puts("┃     3. 전체 출력                   ┃");
	puts("┃                                    ┃");
	puts("┃     0. 메인 메뉴                   ┃");
	puts("┃                                    ┃");
	puts("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	printf(" 번호를 선택해주세요 > ");
}

void in_func(struct Student* st)			// 메인 메뉴 1번 함수  
{
	int i, j;
	int cnt=0;
	puts("입    력 ");
	for(i=0; i<MAX_ST; i++)
	{
		if(st[i].id == -1)	break;
	}

	printf("학번 : ");			scanf("%d", &st[i].id);
	for(j=0; j<MAX_ST; j++)	if(st[i].id == st[j].id)	cnt++;	// 학번 중복 체크
	if(cnt > 1)
	{
		st[i].id = -1;
		puts("중복된 학번입니다. 다시 입력 하세요");
		return;
	}
	printf("이름 : ");		scanf("%s", st[i].name);
	fflush(stdin);
	printf("DB 성적 : ");	scanf("%d", &st[i].db);
	printf("UNIX 성적 : ");	scanf("%d", &st[i].unix);
	printf("JAVA 성적 : ");	scanf("%d", &st[i].java);
}

void out_func(struct Student* st)			// 메인 메뉴 2번 함수 (안에 출력 UI 내용) 
{
	int select;

	while(1)
	{
		system("cls");
		out_menu();
		fflush(stdin);
		scanf("%d", &select);
		system("cls");
		switch(select)
		{
		case 1:
			out_grade(st);
			break;
		case 2:
			out_one(st);
			break;
		case 3:
			out_all(st);
			break;
		case 0:
			puts("메인 메뉴로 돌아갑니다");
			return;
		default:
			break;
		}
		system("pause");
	}
}

void out_grade(struct Student* st)					// 점수 총합. 등수에 따른 출력  
{
	struct Student tmpSt; 
	int i, j;
	for(i=0; i<MAX_ST-1; i++)
	{
		for(j=i+1; j<MAX_ST; j++)
		{
			if(st[i].db+st[i].unix+st[i].java < st[j].db+st[j].unix+st[j].java)
			{
				tmpSt = st[i];
				st[i] = st[j];
				st[j] = tmpSt;
			}
		}
	}
	puts("     등수에 따른 출력     ");
	out_all(st);
}

void out_one(struct Student* st)			// 개별 출력(학번 or 이름) 선택하여 학번 이름 과목 합계 평균 학점 순위 출력. 
{
	int select, i, sum=0, cnt=0;
	int tmpID;
	char tmpName[20];
	printf("개별 출력 (1.학번 / 2.이름) > ");		scanf("%d", &select);
	if(select == 1)
	{
		printf("학번을 입력하세요 > ");	scanf("%d", &tmpID);
		printf(" %9s | %8s | %5s | %5s | %5s | %5s | %6s | %4s | %4s | \n", "학번","이름","DB","UNIX","JAVA","합계","평균","학점","순위");
		for(i=0; i<MAX_ST; i++)
		{
			if(st[i].id == tmpID)
			{				
				sum = st[i].db + st[i].unix + st[i].java;			// 합 
				
				st[i].h_avg=(float)sum/3;							// 평균 

				if(st[i].h_avg<=100 && st[i].h_avg>=90)				// 학점 구분	
					st[i].hakjum = 'A'; 
				if(st[i].h_avg<90 && st[i].h_avg>=80)		
					st[i].hakjum = 'B'; 	
				if(st[i].h_avg<80 && st[i].h_avg>=70)
					st[i].hakjum = 'C'; 	
				if(st[i].h_avg<70 && st[i].h_avg>=60)		
					st[i].hakjum = 'D'; 	 
				if(st[i].h_avg<60 && st[i].h_avg>0)		
					st[i].hakjum = 'F';
					
				printf(" %9d | %8s | %5d | %5d | %5d | %5d | %6.2f | %4c | %4d | \n",
						st[i].id, st[i].name, st[i].db, st[i].unix, st[i].java, sum, st[i].h_avg, st[i].hakjum ,rank(st, i));
				return;
			}
		}
		puts("해당 학번이 없습니다");
	}
	else if(select == 2)
	{
		printf("이름을 입력하세요 > ");		scanf("%s", tmpName);
		printf(" %9s | %8s | %5s | %5s | %5s | %5s | %6s | %4s | %4s | \n", "학번","이름","DB","UNIX","JAVA","합계","평균","학점","순위");
		for(i=0; i<MAX_ST; i++)
		{
			if(strcmp(st[i].name, tmpName) == 0)
			{				
				sum = st[i].db + st[i].unix + st[i].java;			// 합 
				
				st[i].h_avg=(float)sum/3;							// 평균 

				if(st[i].h_avg<=100 && st[i].h_avg>=90)				// 학점 구분 
					st[i].hakjum = 'A'; 
				if(st[i].h_avg<90 && st[i].h_avg>=80)		
					st[i].hakjum = 'B'; 	
				if(st[i].h_avg<80 && st[i].h_avg>=70)
					st[i].hakjum = 'C'; 	
				if(st[i].h_avg<70 && st[i].h_avg>=60)		
					st[i].hakjum = 'D'; 	 
				if(st[i].h_avg<60 && st[i].h_avg>0)		
					st[i].hakjum = 'F';
					
				printf(" %9d | %8s | %5d | %5d | %5d | %5d | %6.2f | %4c | %4d | \n",
						st[i].id, st[i].name, st[i].db, st[i].unix, st[i].java, sum, st[i].h_avg, st[i].hakjum, rank(st, i));	
				cnt++;
			}
		}
		if(cnt==0)	puts("해당 이름이 없습니다");		// 동명이인 출력 
	}
	else{}

}

void out_all(struct Student* st)			// 입력한 모든 정보 출력. 
{
		
	int i;
	int sum = 0;
		
	printf(" %9s | %8s | %5s | %5s | %5s | %5s | %6s | %4s | %4s | \n", "학번","이름","DB","UNIX","JAVA","합계","평균","학점","순위");

	for(i=0; i<MAX_ST; i++)
	{
		if(st[i].id != -1)
		{			
			sum = st[i].db + st[i].unix + st[i].java;			// 합 
			
			st[i].h_avg=(float)sum/3;							// 평균  

			if(st[i].h_avg<=100 && st[i].h_avg>=90)				// 학점 구분	
				st[i].hakjum = 'A'; 
			if(st[i].h_avg<90 && st[i].h_avg>=80)		
				st[i].hakjum = 'B'; 	
			if(st[i].h_avg<80 && st[i].h_avg>=70)
				st[i].hakjum = 'C'; 	
			if(st[i].h_avg<70 && st[i].h_avg>=60)		
				st[i].hakjum = 'D'; 	 
			if(st[i].h_avg<60 && st[i].h_avg>0)		
				st[i].hakjum = 'F';
				
			printf(" %9d | %8s | %5d | %5d | %5d | %5d | %6.2f | %4c | %4d | \n",
					st[i].id, st[i].name, st[i].db, st[i].unix, st[i].java, sum, st[i].h_avg, st[i].hakjum, rank(st, i));
		}
	}
}

int rank(struct Student* st,int tmp)		// 등수 
{
	int rank=1;
	int i;
	float avg_tmp, avg;	

	avg_tmp = (float)(st[tmp].db + st[tmp].unix + st[tmp].java) / 3;	
	for(i=0; i<MAX_ST; i++)
	{
		if(st[i].id != -1)
		{
			avg = (float)(st[i].db + st[i].unix + st[i].java) / 3;		
			if(avg_tmp < avg)	rank++;				
		}
	}
	return rank;
}

void modify(struct Student* st)				// 수정하기 위한 함수 
{
	int select;
	int i, tmpID;
	char tmpName[20];
	
	puts("    수    정    ");
	printf(" select (1.학번 / 2.이름) > ");		scanf("%d", &select);
	
	if(select == 1)			// 학번(1번)을 선택하였다면 아래의 코드 진행. 
	{
		printf("학번을 입력하세요 > ");	scanf("%d", &tmpID);
		for(i=0; i<MAX_ST; i++)
		{
			if(tmpID == st[i].id)	
			{
				printf("DB 성적 : ");	scanf("%d",&st[i].db);
				printf("UNIX 성적 : ");	scanf("%d",&st[i].unix);
				printf("JAVA 성적 : ");	scanf("%d",&st[i].java);				
				printf(" %d번 ID의 데이터가 수정되었습니다\n", tmpID);
				return;
			}
		}
		printf(" %d번 학번이 존재하지 않습니다\n", tmpID);
	}
	else if(select==2)			// 이름(2번)을 선택하였다면 아래의 코드 진행. 
	{ 
		printf("이름을 입력하세요 > ");		scanf("%s", tmpName);
		for(i=0; i<MAX_ST; i++)
		{
			if(strcmp(st[i].name, tmpName) == 0)
			{
				printf("DB 성적 : ");	scanf("%d",&st[i].db);
				printf("UNIX 성적 : ");	scanf("%d",&st[i].unix);
				printf("JAVA 성적 : ");	scanf("%d",&st[i].java);
				printf(" %s의 데이터가 수정되었습니다\n", tmpName);
				return;
			}
		}
		printf(" %s가 존재하지 않습니다\n", tmpName);
	}
	else{}
}

void del(struct Student* st)		// 학번 or 이름 을 선택하여 입력했던 정보 삭제  
{	
	int select;
	int i, tmpID;
	char tmpName[20];
	
	puts("     삭    제     ");
	printf(" select (1.학번 / 2.이름) > ");		scanf("%d", &select);
	
	if(select == 1)				// 학번 선택. 
	{
		printf("학번을 입력하세요 > ");	scanf("%d", &tmpID);
		for(i=0; i<MAX_ST; i++)
		{
			if(tmpID == st[i].id)	
			{
				st[i].id = -1;
				printf(" %d번 학번이 삭제되었습니다\n", tmpID);
				return;
			}
		}
		printf(" %d번 학번이 존재하지 않습니다\n", tmpID);
	}
	else if(select==2)			// 이름 선택 
	{ 
		printf("이름을 입력하세요 > ");		scanf("%s", tmpName);
		for(i=0; i<MAX_ST; i++)
		{
			if(strcmp(st[i].name, tmpName) == 0)
			{
				st[i].id = -1;
				printf(" %s가 삭제되었습니다\n", tmpName);
				return;
			}
		}
		printf(" %s가 존재하지 않습니다\n", tmpName);
	}
	else{}
}

// 파일에는 최소한으로 필요한 [ 학번 , 이름 , 점수(3과목) ] 만을 저장, 불러옴. 

void save_file(struct Student* st)				// 파일을 저장하기 위한 함수. 
{
	int i, sum=0;
    FILE* f = fopen("성적관리.txt", "w");
	for(i=0; i<MAX_ST; i++)
	{
		if(st[i].id != -1)
		{
			sum = st[i].db + st[i].unix + st[i].java;
			fprintf(f, " %5d %8s %5d %5d %5d\n",
					st[i].id, st[i].name, st[i].db, st[i].unix, st[i].java);
		}
	}
	puts("저장 하였습니다");

	fclose(f);
}

void load_file(struct Student* st)				// 저장했던 파일을 불러오는 함수. 
{
	char select;
	int i;
    FILE* f = fopen("성적관리.txt", "r");
	if(!f)
	{
		puts("해당 파일이 존재하지 않습니다");
		return;
	}
	printf("이전 데이터를 지우시겠습니까(y/n) > ");				 
	fflush(stdin);
	scanf("%c", &select);

	if(select == 'y' || select == 'Y')
	{
		for(i=0; i<MAX_ST; i++)
		{
			st[i].id = -1;
		}
	}
	else if(select == 'n' || select == 'N')
	{
	}
	else
	{
		puts("잘못 입력하셨습니다");
		return;
	}
	
	for(i=0; i<MAX_ST; i++)
	{
		if(st[i].id == -1)
		{
			fscanf(f, " %d %s %d %d %d\n",
					&(st[i].id), st[i].name, &(st[i].db), &(st[i].unix), &(st[i].java));
		}
	}
	puts("로드 하였습니다");
	fclose(f);
}
