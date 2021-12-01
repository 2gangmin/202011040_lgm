#include <stdio.h>
#include <windows.h>
#include <string.h>

#define MAX_ST 50

struct Student
{
	int id;						// �й� 
	char name[20], hakjum;		// �̸�, ���� 
	int db;						
	int unix;
	int java;
	float h_avg;				// ��� 
};

void main_menu();								// ���� �޴� 
void out_menu();								// 2�� ���ý� ������ ��� �޴� 

void in_func(struct Student* st);				// ���� �Է� 
void out_func(struct Student* st);				// ���� ��� 
void out_grade(struct Student* st);				// ����� ��� 
void out_one(struct Student* st);				// ���� ��� 
void out_all(struct Student* st);				// ��ü ��� 
int rank(struct Student* st,int tmp);			// ����� �ű�� �Լ� 
int n_hakjum(struct Student* st, int sum);		// ���� �Լ�  

void modify(struct Student* st);				// ���� �Լ� 
void del(struct Student* st);					// ���� �Լ� 

void save_file(struct Student* st);				// ���Ͽ� �����ϴ� �Լ� 
void load_file(struct Student* st);				// ������ �ҷ����� �Լ� 

int main() 
{
	struct Student st[MAX_ST]; 
	int select, i;
	
	for(i=0; i<MAX_ST; i++)
	{
		st[i].id = -1 ; // id�� -1�� �ʱ�ȭ
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
			printf("���α׷��� �����մϴ�.\n");
			return 0;
		default:
			break;
		}
		system("pause");
	}
	return 0;
}

void main_menu()				// ���� �޴�  
{
	puts("����������������������������������������������������������������������������");
	puts("��        �������� ���α׷�           ��");
	puts("����������������������������������������������������������������������������"); 
	puts("��                                    ��");
	puts("��    1.�� ��   2.�� ��   3.�� ��     ��");
	puts("��                                    ��");
	puts("��    4.�� ��   5.�� ��   6.�ҷ�����  ��");
	puts("��                                    ��");
	puts("��    0.�� ��                         ��");
	puts("��                                    ��");
	puts("����������������������������������������������������������������������������");
	printf(" ��ȣ�� �������ּ��� > ");
}

void out_menu()					// ��� �޴�  
{
	puts("����������������������������������������������������������������������������");
	puts("��         ��� ����                  ��");
	puts("����������������������������������������������������������������������������"); 
	puts("��                                    ��");
	puts("��     1. ����� ���(����)           ��");
	puts("��                                    ��");
	puts("��     2. ���� ���(�й� / �̸�)      ��");
	puts("��                                    ��");
	puts("��     3. ��ü ���                   ��");
	puts("��                                    ��");
	puts("��     0. ���� �޴�                   ��");
	puts("��                                    ��");
	puts("����������������������������������������������������������������������������");
	printf(" ��ȣ�� �������ּ��� > ");
}

void in_func(struct Student* st)			// ���� �޴� 1�� �Լ�  
{
	int i, j;
	int cnt=0;
	puts("��    �� ");
	for(i=0; i<MAX_ST; i++)
	{
		if(st[i].id == -1)	break;
	}

	printf("�й� : ");			scanf("%d", &st[i].id);
	for(j=0; j<MAX_ST; j++)	if(st[i].id == st[j].id)	cnt++;	// �й� �ߺ� üũ
	if(cnt > 1)
	{
		st[i].id = -1;
		puts("�ߺ��� �й��Դϴ�. �ٽ� �Է� �ϼ���");
		return;
	}
	printf("�̸� : ");		scanf("%s", st[i].name);
	fflush(stdin);
	printf("DB ���� : ");	scanf("%d", &st[i].db);
	printf("UNIX ���� : ");	scanf("%d", &st[i].unix);
	printf("JAVA ���� : ");	scanf("%d", &st[i].java);
}

void out_func(struct Student* st)			// ���� �޴� 2�� �Լ� (�ȿ� ��� UI ����) 
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
			puts("���� �޴��� ���ư��ϴ�");
			return;
		default:
			break;
		}
		system("pause");
	}
}

void out_grade(struct Student* st)					// ���� ����. ����� ���� ���  
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
	puts("     ����� ���� ���     ");
	out_all(st);
}

void out_one(struct Student* st)			// ���� ���(�й� or �̸�) �����Ͽ� �й� �̸� ���� �հ� ��� ���� ���� ���. 
{
	int select, i, sum=0, cnt=0;
	int tmpID;
	char tmpName[20];
	printf("���� ��� (1.�й� / 2.�̸�) > ");		scanf("%d", &select);
	if(select == 1)
	{
		printf("�й��� �Է��ϼ��� > ");	scanf("%d", &tmpID);
		printf(" %9s | %8s | %5s | %5s | %5s | %5s | %6s | %4s | %4s | \n", "�й�","�̸�","DB","UNIX","JAVA","�հ�","���","����","����");
		for(i=0; i<MAX_ST; i++)
		{
			if(st[i].id == tmpID)
			{				
				sum = st[i].db + st[i].unix + st[i].java;			// �� 
				
				st[i].h_avg=(float)sum/3;							// ��� 

				if(st[i].h_avg<=100 && st[i].h_avg>=90)				// ���� ����	
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
		puts("�ش� �й��� �����ϴ�");
	}
	else if(select == 2)
	{
		printf("�̸��� �Է��ϼ��� > ");		scanf("%s", tmpName);
		printf(" %9s | %8s | %5s | %5s | %5s | %5s | %6s | %4s | %4s | \n", "�й�","�̸�","DB","UNIX","JAVA","�հ�","���","����","����");
		for(i=0; i<MAX_ST; i++)
		{
			if(strcmp(st[i].name, tmpName) == 0)
			{				
				sum = st[i].db + st[i].unix + st[i].java;			// �� 
				
				st[i].h_avg=(float)sum/3;							// ��� 

				if(st[i].h_avg<=100 && st[i].h_avg>=90)				// ���� ���� 
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
		if(cnt==0)	puts("�ش� �̸��� �����ϴ�");		// �������� ��� 
	}
	else{}

}

void out_all(struct Student* st)			// �Է��� ��� ���� ���. 
{
		
	int i;
	int sum = 0;
		
	printf(" %9s | %8s | %5s | %5s | %5s | %5s | %6s | %4s | %4s | \n", "�й�","�̸�","DB","UNIX","JAVA","�հ�","���","����","����");

	for(i=0; i<MAX_ST; i++)
	{
		if(st[i].id != -1)
		{			
			sum = st[i].db + st[i].unix + st[i].java;			// �� 
			
			st[i].h_avg=(float)sum/3;							// ���  

			if(st[i].h_avg<=100 && st[i].h_avg>=90)				// ���� ����	
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

int rank(struct Student* st,int tmp)		// ��� 
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

void modify(struct Student* st)				// �����ϱ� ���� �Լ� 
{
	int select;
	int i, tmpID;
	char tmpName[20];
	
	puts("    ��    ��    ");
	printf(" select (1.�й� / 2.�̸�) > ");		scanf("%d", &select);
	
	if(select == 1)			// �й�(1��)�� �����Ͽ��ٸ� �Ʒ��� �ڵ� ����. 
	{
		printf("�й��� �Է��ϼ��� > ");	scanf("%d", &tmpID);
		for(i=0; i<MAX_ST; i++)
		{
			if(tmpID == st[i].id)	
			{
				printf("DB ���� : ");	scanf("%d",&st[i].db);
				printf("UNIX ���� : ");	scanf("%d",&st[i].unix);
				printf("JAVA ���� : ");	scanf("%d",&st[i].java);				
				printf(" %d�� ID�� �����Ͱ� �����Ǿ����ϴ�\n", tmpID);
				return;
			}
		}
		printf(" %d�� �й��� �������� �ʽ��ϴ�\n", tmpID);
	}
	else if(select==2)			// �̸�(2��)�� �����Ͽ��ٸ� �Ʒ��� �ڵ� ����. 
	{ 
		printf("�̸��� �Է��ϼ��� > ");		scanf("%s", tmpName);
		for(i=0; i<MAX_ST; i++)
		{
			if(strcmp(st[i].name, tmpName) == 0)
			{
				printf("DB ���� : ");	scanf("%d",&st[i].db);
				printf("UNIX ���� : ");	scanf("%d",&st[i].unix);
				printf("JAVA ���� : ");	scanf("%d",&st[i].java);
				printf(" %s�� �����Ͱ� �����Ǿ����ϴ�\n", tmpName);
				return;
			}
		}
		printf(" %s�� �������� �ʽ��ϴ�\n", tmpName);
	}
	else{}
}

void del(struct Student* st)		// �й� or �̸� �� �����Ͽ� �Է��ߴ� ���� ����  
{	
	int select;
	int i, tmpID;
	char tmpName[20];
	
	puts("     ��    ��     ");
	printf(" select (1.�й� / 2.�̸�) > ");		scanf("%d", &select);
	
	if(select == 1)				// �й� ����. 
	{
		printf("�й��� �Է��ϼ��� > ");	scanf("%d", &tmpID);
		for(i=0; i<MAX_ST; i++)
		{
			if(tmpID == st[i].id)	
			{
				st[i].id = -1;
				printf(" %d�� �й��� �����Ǿ����ϴ�\n", tmpID);
				return;
			}
		}
		printf(" %d�� �й��� �������� �ʽ��ϴ�\n", tmpID);
	}
	else if(select==2)			// �̸� ���� 
	{ 
		printf("�̸��� �Է��ϼ��� > ");		scanf("%s", tmpName);
		for(i=0; i<MAX_ST; i++)
		{
			if(strcmp(st[i].name, tmpName) == 0)
			{
				st[i].id = -1;
				printf(" %s�� �����Ǿ����ϴ�\n", tmpName);
				return;
			}
		}
		printf(" %s�� �������� �ʽ��ϴ�\n", tmpName);
	}
	else{}
}

// ���Ͽ��� �ּ������� �ʿ��� [ �й� , �̸� , ����(3����) ] ���� ����, �ҷ���. 

void save_file(struct Student* st)				// ������ �����ϱ� ���� �Լ�. 
{
	int i, sum=0;
    FILE* f = fopen("��������.txt", "w");
	for(i=0; i<MAX_ST; i++)
	{
		if(st[i].id != -1)
		{
			sum = st[i].db + st[i].unix + st[i].java;
			fprintf(f, " %5d %8s %5d %5d %5d\n",
					st[i].id, st[i].name, st[i].db, st[i].unix, st[i].java);
		}
	}
	puts("���� �Ͽ����ϴ�");

	fclose(f);
}

void load_file(struct Student* st)				// �����ߴ� ������ �ҷ����� �Լ�. 
{
	char select;
	int i;
    FILE* f = fopen("��������.txt", "r");
	if(!f)
	{
		puts("�ش� ������ �������� �ʽ��ϴ�");
		return;
	}
	printf("���� �����͸� ����ðڽ��ϱ�(y/n) > ");				 
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
		puts("�߸� �Է��ϼ̽��ϴ�");
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
	puts("�ε� �Ͽ����ϴ�");
	fclose(f);
}
