#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>
#include<Windows.h>
#include <conio.h>

/*ȫ������*/
#define MAX 30
#define length 1000 //�������
int error;//������

Node* head, * Tail;//ͷ�ڵ�
int type, member, account;//�˻�����(1-��ʦ��0-ѧ��),����, �˻�
char user[MAX] = { 0 }, pass[MAX] = { 0 };//��¼�û�
char* USER[2 * MAX] = { 0 }, * PASS[2 * MAX] = { 0 };//�˻���Ϣ
double avr_c, avr_m, avr_e, avr_a, s_c, s_m, s_e, s_a, s;//ƽ����,����
int ranking_c, ranking_m, ranking_e;//����

/*�������Ͷ���*/
typedef struct {
	int math;
	int english;
	int programming;
}Score;

typedef struct {
	char name[30];
	char id[30];
	Score score[30];
}Student;

typedef struct node {
	Student data;
	struct node* next;
	struct node* prior;
}Node;




/*��������*/
void headview(void);//����ͼ��
SMALL_RECT SizeOfWindow(HANDLE hConsoleOutput);//����
void modeset(int w, int h);//����
void surface(void);//���ڳ�ʼ��
bool login(void);//��¼
int awelcome(void);//����Ա���˵�������ѡ��
int swelcome(void);//ѧ�����˵�������ѡ��
void init_node(void);//��ʼ������
void load(void);//����ɼ�����
void jump(void);//��ת����
void save(void);//����д��
void add_student(void);//��ӳ�Ա
void write(void);//����̨д����Ϣ
Node* search(char id[MAX]);//��������
void print_one(Node* list);//��ӡ�����Ϣ
void  delet(Node** list, char id[MAX]);//ɾ����Ϣ
void put_in_order(Node* phead, int code_data, int code_num);//������
void f_rand(int a[], int* t); //�����
void encrypt(char* location_1, char* code_location); //���ܡ�����ǰ���ı�λ�ã�����λ��
void decode(char* location_2, char* code_location); //���ܡ�After_Encrypt��λ�ã�����λ��
int statistics(void);//����ͳ��
int rank(char id[MAX]);//����
int extreme_value(Node* list, int choice, int code_num);//�༶��ֵͳ��
double average_all(Node* list, int choice, int code_num);//�༶����ͳ��
double average_one(Node* list, int choice);//���˾���ͳ��
double variance_all(Node* phead);//�༶����ָ��
double variance_one(Node* p,int choice);//���˲���ָ��
void report(int code_num);//���ɳɼ�����
void GPA(Node* phead);//GPA
void insert_sort(Node* phead);//��������
int analyze(void);//���ݷ�������
void f_analyze(int change);//���ݷ���ʵ��


int main(void)
{
	//��������
	int choice,change;
	char id[MAX];
	//��̨����
	surface();

	//�����ʼ��
	init_node();
	
	//�û���¼|�˵�ѡ��
	type = login();
	//type = 1;

	while (1)
	{
	if (type)
		choice = awelcome();
	else
		choice = swelcome();


		//����ʵ��
		switch (choice)
		{
		case 0://�ù���Ŀǰ���岻��

			break;
		case 1:
			system("cls");
			headview();
			printf("\n\n\t\t\t\t\t\t������ѧ��:	");
			error=scanf("%s", id);
			print_one(search(id));
			jump();
			break;
		case 2:
			system("cls");
			headview();
			printf("\n\n");
			printf("\t\t\t\t     �q ==============================�����======�r\n");
			printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-��ʦ   ��\n");
			printf("\t\t\t\t     �t ======�����==============================�s\n");
			printf("\n\n");
			add_student();
			jump();
			break;
		case 3:
			system("cls");
			headview();
			printf("\n\n");
			printf("\t\t\t\t     �q ==============================�����======�r\n");
			printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-��ʦ   ��\n");
			printf("\t\t\t\t     �t ======�����==============================�s\n");
			printf("\n\n");
			write();
			jump();
			break;
		case 4:
			system("cls");
			headview();
			printf("\n\n");
			printf("\t\t\t\t     �q ==============================�����======�r\n");
			printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-��ʦ   ��\n");
			printf("\t\t\t\t     �t ======�����==============================�s\n");
			printf("\n\n");
			printf("\n\n\n\t\t\t\t\t\t������ѧ�ţ�");
			error=scanf("%s", id);
			delet(&head, id);
			jump();
			break;
		case 5:
			change=analyze();
			f_analyze(change);
			break;
		case 7:
			system("cls");
			save();
			getchar();
			headview();
			printf("\n\n\n\n\n\n");
			printf("\t\t\t\t\t\t\t����ɹ�\n\n\n\n\n");
			return 0;
			break;
		case 8:
			GPA(head);
			getchar();
			getchar();
			break;
		case 6:
			system("cls");
			headview();
			printf("\n\n");
			printf("\t\t\t\t     �q ==============================�����======�r\n");
			printf("\t\t\t\t     ��     ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ      ��\n");
			printf("\t\t\t\t     �t ======�����==============================�s\n");
			printf("\n\n");
			printf("\n\n\n\t\t\t\t\t\t�����������룺");
			scanf("%s", PASS[account]);
			jump();
			break;
		default:
			printf("\t\t\t\t\t���������룺");
			error=scanf("%d", &choice);
			break;
		}
	}
	//printf("OKKKK");�����յ���֤
	//getchar();
	return 0;
}

//��¼����
bool login(void)
{
	FILE* apas,*spas,*ause,*suse;

	int times=0,j = 0,a=1,choice=10, i = 0;//a����������֤����
	again:system("cls");
	headview();
	printf("\t\t\t\t     �q ==============================�����======�r\n");
	printf("\t\t\t\t     ��      ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ     ��\n");
	printf("\t\t\t\t     �t ======�����==============================�s\n");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t����˻����ͣ�   1����>ѧ�� | 2����>��ʦ\n\n");
	printf("\t\t\t\t\t\t\t���ѡ��");
	scanf("%d", &choice);
	system("cls");
	begain:headview();
	printf("\t\t\t\t     �q ==============================�����======�r\n");
	printf("\t\t\t\t     ��      ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ     ��\n");
	printf("\t\t\t\t     �t ======�����==============================�s\n");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t   �û���:	");
	scanf("%s", user);
	printf("\n\t\t\t\t\t   ����:	");
	scanf("%s",pass);
	//printf("%s\n%s", user, pass);������֤
	switch (choice)
	{
	case 1:
		decode("spass.txt", "a1.txt");
		spas=fopen("spass.txt", "r+");
		if (spas == NULL) 
		{
			printf("Error: read file failure.\n");
			exit(-1);
		}
			for ( i = 0; i < 60; i++)
			{
				PASS[i] = malloc(sizeof(char*));
				if(fscanf(spas, "%s", PASS[i])==EOF)break;
			}
			PASS[i] = NULL;
		fclose(spas);
		encrypt("spass.txt", "a1.txt");
		decode("suser.txt", "a2.txt");
		suse=fopen("suser.txt", "r+");
		if (suse == NULL) 
		{
			printf("Error: read file failure.\n");
			exit(-1);
		}
			for ( i = 0; i < 60; i++)
			{
				USER[i] = malloc(sizeof(char*));
				if (fscanf(suse, "%s", USER[i]) == EOF)break;
			}
			USER[i] = NULL;
		fclose(suse);
		encrypt("suser.txt", "a2.txt");

		//printf("%s\n%s", PASS[1], USER[1]);//�ļ�д����֤
		getchar();
		for ( i = 0; a; i++)
		{
			a *= (!(strcmp(user, USER[i]) == 0 && strcmp(pass, PASS[i]) == 0));//�ж���0��ȫ����1
			if (a == 0)account = i;
		}
			while (a)
			{
				times++;	//����������� times++
				if (times > 3)
				{
					printf("\n\n\n\t\t\t\t�˺Ż�������������ۼƴﵽ%d�Σ�ϵͳ����3���ر�", times);
					Sleep(1000);
					system("cls");
					char shutdown[] = { "ϵͳ����%d���ر�..." };
					for (int i = 0; i < 3; i++)
					{
						printf(shutdown, 3 - i);
						Sleep(1000);
						system("cls");
					}
					exit(0);
				}
				printf("\n\n\n\t\t\t\t�˺Ż������������,�㻹��%d�ε�¼���ᣬ����������µ�¼...", 4 - times);
				getchar();
				system("cls");
				goto begain;
			}
			/*for (int i = 0; i < 30; i++) {

				free(USER[i]);
				free(PASS[i]);
			}*/
			//�ڴ��ͷű���
			return 0;
	case 2:
		decode("apass.txt", "a3.txt");
		apas=fopen( "apass.txt", "r+");
		if (apas == NULL)
		{
			printf("Error: read file failure.\n");
			exit(-1);
		}
		for ( i = 0; i < 60; i++) {
			PASS[i] = malloc(sizeof(char*));
			if (fscanf(apas, "%s", PASS[i]) == EOF)break;
		}
		PASS[i] = NULL;
		fclose(apas);
		encrypt("apass.txt", "a3.txt");
		decode("auser.txt", "a4.txt"); 
		ause=fopen( "auser.txt", "r+");
		if (ause == NULL)
		{
			printf("Error: read file failure.\n");
			exit(-1);
		}
		for ( i = 0; i < 60; i++) {
			USER[i] = malloc(sizeof(char*));
			if (fscanf(ause, "%s", USER[i]) == EOF)break;
		}
		USER[i] = NULL;
		fclose(ause);
		encrypt("auser.txt", "a4.txt");
		for (int i = 0; a; i++)
		{
			a *= (!(strcmp(user, USER[i]) == 0 && strcmp(pass, PASS[i]) == 0));//�ж���0��ȫ����1
			if (a == 0)account = i;
		}			
			while (a)
			{
				times++;	//����������� times++
				if (times > 3)
				{
					printf("\n\n\n\t\t\t\t�˺Ż�������������ۼƴﵽ%d�Σ�ϵͳ����3���ر�", times);
					Sleep(1000);
					system("cls");
					char shutdown[] = { "ϵͳ����%d���ر�..." };
					for (int i = 0; i < 3; i++)
					{
						printf(shutdown, 3 - i);
						Sleep(1000);
						system("cls");
					}
					exit(0);
				}
				printf("\n\n\n\t\t\t\t�˺Ż������������,�㻹��%d�ε�¼���ᣬ����������µ�¼...", 4 - times);
				getchar();
				system("cls");
				goto begain;
			}
			/*for (int i = 0; i < 30; i++) {

				free(USER[i]);
				free(PASS[i]);
			}*/
			//�ڴ��ͷű���
			return 1;
	default:
		printf("\n\n\t\t\t\t\t   �����������˻����ͣ�\n");
		goto again;
	}
	getchar();
}

//����Ա�˵�����
int awelcome(void)
{
	int choice=7;
	system("cls");
	headview();
	printf("\t\t\t\t     �q ==============================�����======�r\n");
	printf("\t\t\t\t     ��      ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ     ��\n");
	printf("\t\t\t\t     �t ======�����==============================�s\n");
	printf("\n");
	printf("\t\t\t\t\t\t\t    MENU\n\n");
	printf("\t\t\t\t\t\t     1����>�鿴ѧ���ɼ�\n\n");
	printf("\t\t\t\t\t\t     2����>����ѧ���ɼ�\n\n");
	printf("\t\t\t\t\t\t     3����>�޸�ѧ���ɼ�\n\n");
	printf("\t\t\t\t\t\t     4����>ɾ��ѧ����Ϣ\n\n");
	printf("\t\t\t\t\t\t     5����>�ɼ����ݷ���\n\n");
	printf("\t\t\t\t\t\t     6����>�˻������޸�\n\n");
	printf("\t\t\t\t\t\t     7����>�˳� �� ����\n\n");
	printf("\t\t\t\t\t\t        ����ָ���ţ�\n");
	printf("\t\t\t\t\t\t              ");
	scanf("%d", &choice);
	return choice;
}

//ѧ���˲˵�����
int swelcome(void)
{
	int change,choice=8;//�޸Ĵ���ָ��
	system("cls");
	headview();
	printf("\t\t\t\t     �q ==============================�����======�r\n");
	printf("\t\t\t\t     ��      ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ     ��\n");
	printf("\t\t\t\t     �t ======�����==============================�s\n");
	printf("\n\n");
	printf("\t\t\t\t\t\t\t   MENU\n\n");
	printf("\t\t\t\t\t\t    1����>�鿴��ĳɼ�\n\n");
	printf("\t\t\t\t\t\t    2����>�ɼ����ݷ���\n\n");
	printf("\t\t\t\t\t\t    3����>�˻������޸�\n\n");
	printf("\t\t\t\t\t\t    4����>  GPA��ѯ\n\n");
	printf("\t\t\t\t\t\t    5����>    �˳�\n\n");
	printf("\t\t\t\t\t\t       ����ָ���ţ�\n");
	printf("\t\t\t\t\t\t             ");
	scanf("%d", &change);
	switch (change)
	{
	case 1:
		system("cls");
		headview();
		print_one(search(user));
		jump();
		break;
	case 2:
		choice = 5;
		break;
	case 3:
		choice = 6;
		break;
	case 4:
		choice = 8;
		break;
	case 5:
		choice = 7;
		break;
	default:
		break;
	}
	return choice;
}

//���ڳ�ʼ��
void surface(void)
{
	SetConsoleTitle("UESTC_1605��ɼ�����ϵͳ");
	system("color 70");
	modeset(1200, 675);
	headview();
	printf("\n\n\t\t\t\t\t����һ�����Ƶ�����ȴӵ���������µĳɼ�ϵͳ��\n");
	printf("\n\n\n\n\n\t\t\t\t\t  ||����Made by -Csy- -Sry- -Xy- -Zzy-||\n");
	int i;
	printf("\n\n\n\n\n\t\t\t\t\t\t");
	char heihei[] = { "��Enter������ѧ���ɼ�ϵͳ..." };
	for (i = 0; i < strlen(heihei); i++)
	{
		printf("%c", heihei[i]);
		Sleep(50);
	}
	getchar();
	system("CLS");
	
}
void headview(void)
{
	printf("\n\n\n");
	printf("\t\t\t\t\t     �q �] % �r                   �q ```�r  \n");
	printf("\t\t\t\t\t     (@^o^@) ѧ���ɼ�����ϵͳ (��:��)\n");
	printf("\t\t\t\t\t     (~):(~)                  (~)v(~) \n");
	printf("\n");
}

//���ڵ���
SMALL_RECT SizeOfWindow(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &info);
	return info.srWindow;
}
void modeset(int w, int h)
{
	//	�˺������ô��ڴ�СΪ w*h
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	SMALL_RECT rect = SizeOfWindow(hOut);
	COORD size = { rect.Right + 1,rect.Bottom + 1 };	//���建������С    
	//COORD size = { w, h };
	SetConsoleScreenBufferSize(hOut, size);
	GetConsoleScreenBufferInfo(hOut, &info);//���ػ�����
	SMALL_RECT rc = { 1,1, w, h };
	SetConsoleWindowInfo(hOut, 1, &rc);
	SetWindowLongPtrA(
		GetConsoleWindow(),
		GWL_STYLE,
		GetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE)
		& ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX 
	);
}

//����ɼ�����
void load(void)
{
	int i = 0;
	Node* list;
	Node* flag;
	FILE* txt;
	decode("std.txt", "a5.txt");
	txt = fopen("std.txt", "r+");
	for (list = head; \
		fscanf(txt, "%s", list->data.name) != EOF; 
		list = list->next, list->prior = flag)//�ж��Ƿ������β��ͬʱ����name
	{
		list->data.score->english = list->data.score->math = list->data.score->programming = 0;
		fscanf(txt, "%s", list->data.id);
		for (i = 0; i < 30; i++)
		{
			fscanf(txt, "%d %d %d", &(list->data.score[i].programming), \
				& (list->data.score[i].math), &(list->data.score[i].english));
		}
		(list->next) = (Node*)malloc(sizeof(Node));
		flag = list;
	}
	fclose(txt);
	encrypt("std.txt", "a5.txt");
	list->next = NULL;
}

//��ʼ������
void init_node(void)
{
	head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	head->prior = NULL;
	load();
}

//��ӡ�ɼ�
void print_one(Node* list)
{
	//list = list->next;���Խڵ�ת��
	int n = 1, i = 0;
	printf("\n\n");
	printf("\n\n");
	printf("\t\t\t\t������%s", list->data.name);
	printf("\t\t\t\tѧ�ţ�%s", list->data.id);
	printf("\n\n");
	printf("\t\t\t\t\t\t    �鿴�ڼ��ο��ԣ�");
	scanf("%d", &n);
	printf("\n\t\t\t\t\t\t  C����\t  ��ѧ\t  Ӣ��\t\n");
	if (n) 
	{
		if (abs(list->data.score[n - 1].programming) >= 10000 && abs(list->data.score[n - 1].english) >= 10000 && abs(list->data.score[n - 1].math) >= 10000)
			list->data.score[n - 1].programming = list->data.score[n - 1].math = list->data.score[n - 1].english = 0;
		printf("\t\t\t\t\t\t  %d\t  %d\t  %d\t\n\n\n\n\n", list->data.score[n - 1].programming, \
			list->data.score[n - 1].math, list->data.score[n - 1].english);
	}
	else
	{
		for (i; i < 30; i++)
		{
			if (abs(list->data.score[n - 1].programming) >= 10000 && abs(list->data.score[n - 1].english) >= 10000 && abs(list->data.score[n - 1].math) >= 10000)
				list->data.score[n - 1].programming = list->data.score[n - 1].math = list->data.score[n - 1].english = 0;
			printf("\t\t\t\t\t\t  %d\t  %d\t  %d\t\n\n\n\n\n", list->data.score[i].programming, \
				list->data.score[i].math, list->data.score[i].english);
			printf("\n");
		}
	}
	getchar();
}

//��ת����
void jump(void)
{
	char temp;
	while (1)
	{
		printf("\n\t\t\t\t\t\t\th-->Home\n");
		printf("\t\t\t\t\t\t\t   ");
		temp = getch();
		switch (temp)
		{
		case 'h':
			save();
			break;
		default:
			printf("\n\t\t\t\t\t\t      ��Чָ��!");
			getch();
			break;
		}
		if(temp=='h')
		break;
	}
}

//���桢д������
void save(void)
{
	Node* list;
	FILE* txt;
	decode("std.txt", "a5.txt");
	txt = fopen("std.txt", "w+");
	for (list = head; list->next; list = list->next)
	{
		fprintf(txt, "%s\t", list->data.name);
		fprintf(txt, "%s\t", list->data.id);
		for (int i = 0; i < 30; i++)
		{
			if((abs(list->data.score[i].programming)>200) && (abs(list->data.score[i].math)>200) && (abs(list->data.score[i].english)>200))
				list->data.score[i].programming = list->data.score[i].math = list->data.score[i].english = 0;
			fprintf(txt, "%d\t%d\t%d\t", list->data.score[i].programming, \
				list->data.score[i].math, list->data.score[i].english);
		}
		fprintf(txt, "\n");
	}
	fclose(txt);
	encrypt("std.txt", "a5.txt");

	if (type)
	{
		decode("apass.txt", "a3.txt");
		txt = fopen("apass.txt", "w+");
		for (int i = 0; PASS[i] ; i++)
		{
			fprintf(txt, "%s\n", PASS[i]);
		}
		fclose(txt);
		encrypt("apass.txt", "a3.txt");
	}
	else
	{
		decode("spass.txt", "a1.txt");
		txt = fopen("spass.txt", "w+");
		for (int i = 0; PASS[i] ; i++)
		{
			fprintf(txt, "%s\n", PASS[i]);
		}
		fclose(txt);
		encrypt("spass.txt", "a1.txt");
	}
}

//��ӳ�Ա
void add_student(void)
{
	Node* list;
	int times;
	list = (Node*)malloc(sizeof(Node));
	list->data.score->english = list->data.score->math = list->data.score->programming = 0;
	//for (list = head; list->next; list = list->next);
	list->next = head;
	head = list;
	printf("\n\n");
		printf("\t\t\t\t\t\t������������");
		scanf("%s", list->data.name);
		printf("\n\t\t\t\t\t\t������ѧ�ţ�");
		scanf("%s", list->data.id);
		printf("\n\t\t\t\t\t\t�ڼ��ο��ԣ�");
		scanf("%d", &times);
		printf("\n\t\t\t\t\t\t���������(C���� ��ѧ Ӣ��)��");
		scanf("%d %d %d", &(list->data.score[times - 1].programming), \
			& (list->data.score[times - 1].math), &(list->data.score[times - 1].english));
}

//����̨д����Ϣ
void write(void)
{
	Node* list;
	char id[MAX];
	printf("\n\n\n\t\t\t\t\t\t������ѧ�ţ�");
	scanf("%s", id);
	list = search(id);
	printf("\n\t\t\t\t\t\t������%s", list->data.name);
	int n1, n2, n3, times;
	printf("\n\n");
	printf("\n\t\t\t\t\t\t    �޸ĵ�����Ϣ����0\n");
	printf("\n\t\t\t\t\t\t    ����ȫ����Ϣ����1\n");
	printf("\n\t\t\t\t\t\t         �����룺");
	scanf("%d", &n1);
	while (1)
	{
		switch (n1)
		{
		case 0:
			while (1)
			{
				system("cls");
				headview();
				printf("\n\n");
				printf("\t\t\t\t     �q ==============================�����======�r\n");
				printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-��ʦ   ��\n");
				printf("\t\t\t\t     �t ======�����==============================�s\n");
				printf("\n\n");
				printf("\t\t\t\t\t\t      0-�޸�����\n\n");
				printf("\t\t\t\t\t\t      1-�޸�ѧ��\n\n");
				printf("\t\t\t\t\t\t      2-�޸�C���Գɼ�\n\n");
				printf("\t\t\t\t\t\t      3-�޸���ѧ�ɼ�\n\n");
				printf("\t\t\t\t\t\t      4-�޸�Ӣ��ɼ�\n\n");
				printf("\t\t\t\t\t\t         �����룺");
				scanf("%d", &n2);
				if (n2 != 0 && n2 != 1)
				{
					system("cls");
					headview();
					printf("\n\n");
					printf("\t\t\t\t     �q ==============================�����======�r\n");
					printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-��ʦ   ��\n");
					printf("\t\t\t\t     �t ======�����==============================�s\n");
					printf("\n\n");
					printf("\n\t\t\t\t\t\t      �޸ĵڼ��γɼ���");
					scanf("%d", &n3);
				}
				switch (n2)
				{
				case 0:
					printf("\n\t\t\t\t\t\t������������");
					scanf("%s", list->data.name);
					break;
				case 1:
					printf("\n\t\t\t\t\t\t������ѧ�ţ�");
					scanf("%s", list->data.id);
					break;
				case 2:
					printf("\n\t\t\t\t\t\t   ������C���Գɼ���");
					scanf("%d", &(list->data.score[n3 - 1].programming));
					break;
				case 3:
					printf("\n\t\t\t\t\t\t   ��������ѧ�ɼ���");
					scanf("%d", &(list->data.score[n3 - 1].math));
					break;
				case 4:
					printf("\n\t\t\t\t\t   ������Ӣ��ɼ���");
					scanf("%d", &(list->data.score[n3 - 1].english));
					break;
				default:
					printf("\n\t\t\t\t\t\t��Чָ��");
					getchar();
					break;
				}
				if (n2 == 0 || n2 == 1 || n2 == 2 || n2 == 3 || n2 == 4)
					break;
			}
			break;
		case 1:
			printf("\n\t\t\t\t\t\t������������");
			scanf("%s", list->data.name);
			printf("\n\t\t\t\t\t\t������ѧ�ţ�");
			scanf("%s", list->data.id);
			printf("\n\t\t\t\t\t\t�ڼ��ο��ԣ�");
			scanf("%d", &times);
			printf("\n\t\t\t\t\t\t���������(C���� ��ѧ Ӣ��)��");
			scanf("%d %d %d", &(list->data.score[times - 1].programming), \
				& (list->data.score[times - 1].math), &(list->data.score[times - 1].english));
			break;
		default:
			printf("\n\t\t\t\t\t\t����������");
			system("pause");
			break;
		}
		if (n1 == 0 || n1 == 1)
			break;
	}
}

//��������
Node* search(char id[MAX])//��֪BUG��ѧ�Ų����ڣ���������β����
{
	Node* list;
	list = head;
	for (; list && strcmp(list->data.id, id); list = list->next);//ID search
	return list;
}

//ɾ������ڵ�
void  delet(Node** list, char id[MAX])				//void�������Լ��ٸ�ֵһ�����������
{
	Node* p = (*list);
	Node* q=NULL; //����ָ��
	if (!strcmp(p->data.id, id)) {		//��һ�����ݾ�����������ʱ���������
		(*list) = (*list)->next;   //ɾ����һ�����
	}
	else {
		for (; p && strcmp(p->data.id, id); q = p, p = p->next);
		if (!p)
			printf("unknown id\n"); else {
			q->next = p->next;    //������ָ��������ɾ���Ľ�㣬ָ����һ��
		}
	}

}

//������
void put_in_order(Node* phead,int code_data, int code_num)
{          //���򣬲����
	int code_order;
	Node* p = phead;
	Node* tail = NULL;
	Student temp;
	//printf("\t\t\t\t\t\t0-->�ɸߵ����������");
	//printf("\t\t\t\t\t\t1-->�ɵ͵����������");
	//printf("\t\t\t\t\t\t      �����룺");
	//scanf("%d", &code_order);
	code_order = 0;
	//printf("\t\t\t\t\t\t0-->����ѧ�ɼ��������");
	//printf("\t\t\t\t\t\t1-->��Ӣ��ɼ��������");
	//printf("\t\t\t\t\t\t2-->��c���Գɼ��������");
	//printf("\t\t\t\t\t\t      �����룺");
	//scanf("%d", &code_data);
	//printf("\t\t\t\t\t\t���밴�ڼ��γɼ�����:");
	//scanf("%d", &code_num);
	code_num--;
	while (1)
	{
		switch (code_order) 
		{
		case 0:
			while (1)
			{
				switch (code_data) 
				{
				case 0:
					while (p != tail)
					{
						while (p->next != tail)
						{
							if (p->data.score[code_num].math < p->next->data.score[code_num].math)
							{
								temp = p->data;
								p->data = p->next->data;
								p->next->data = temp;
							}
							p = p->next;
						}
						tail = p;
						p = phead;
					}break;
				case 1:
					while (p != tail) 
					{
						while (p->next != tail) 
						{
							if (p->data.score[code_num].english < p->next->data.score[code_num].english)
							{
								temp = p->data;
								p->data = p->next->data;
								p->next->data = temp;
							}
							p = p->next;
						}
						tail = p;
						p = phead;
					}break;
				case 2:
					while (p != tail)
					{
						while (p->next != tail) 
						{
							if (p->data.score[code_num].programming < p->next->data.score[code_num].programming) 
							{
								temp = p->data;
								p->data = p->next->data;
								p->next->data = temp;
							}
							p = p->next;
						}
						tail = p;
						p = phead;
					}break;
				default:printf("\t\t\t\t\t\t����������");
				}break;
				if (code_data = 0 || code_data == 1 || code_data == 2)
					break;
			}
			break;
		case 1:
			while (1)
			{
				switch (code_data) 
				{
				case 0://while�е�p->next->next != NULL��Ϊ�˱����ȡ���һ��δ��ʼ����β�ڵ�����䴫������ͷ�ڵ�
					while (p != tail )
					{
						while (p->next != tail && p->next->next != NULL)
						{
							if (p->data.score[code_num].math > p->next->data.score[code_num].math) 
							{
								temp = p->data;
								p->data = p->next->data;
								p->next->data = temp;
							}
							p = p->next;
						}
						tail = p;
						p = phead;
					}break;
				case 1:
					while (p != tail)
					{
						while (p->next != tail && p->next->next != NULL) 
						{
							if (p->data.score[code_num].english > p->next->data.score[code_num].english)
							{
								temp = p->data;
								p->data = p->next->data;
								p->next->data = temp;
							}
							p = p->next;
						}
						tail = p;
						p = phead;
					}break;
				case 2:
					while (p != tail)
					{
						while (p->next != tail && p->next->next != NULL)
						{
							if (p->data.score[code_num].programming > p->next->data.score[code_num].programming) 
							{
								temp = p->data;
								p->data = p->next->data;
								p->next->data = temp;
							}
							p = p->next;
						}
						tail = p;
						p = phead;
					}break;
				default:printf("\t\t\t\t\t\t����������");
						break;
				}
			if (code_data = 0 || code_data == 1 || code_data == 2)
				break;
			}
			break;
		default:printf("\t\t\t\t\t\t����������");
			break;
		}
		if (code_order == 0 || code_order == 1)
			break;
	}
}

//����ĺ������ڽ������������
void f_rand(int a[], int* t) { //�����
	srand((unsigned)time(NULL));
	for (int i = 0; i < length; i = i + 1) {
		a[i] = rand();
		*t = rand() % 400 - 200;
	}
}

//����ĺ������ڼ��ܡ�
void encrypt(char* location_1, char* code_location) { //���ܡ�����ǰ���ı�λ�ã�����λ��
	FILE* before_encrypt, * after_encrypt, * encrypt; //����ǰ��After_Encrypt������
	char* location_2 = "After_Encrypt.txt"; //After_Encrypt���ı�λ��
	int ch;
	int a[length]; //�洢���������
	int t; //�ٴμ���
	f_rand(a, &t);

	before_encrypt = fopen(location_1, "r+");
	if (before_encrypt == NULL) return;
	after_encrypt = fopen(location_2, "w");
	for (int j = 0;; j = j + 1) {
		ch = fgetc(before_encrypt);
		if (ch == EOF) break;
		ch = ch + a[j % length];
		fprintf(after_encrypt, "%d ", ch);
	}
	fclose(before_encrypt);
	fclose(after_encrypt);

	encrypt = fopen(code_location, "w");
	fprintf(encrypt, "%d ", t);
	for (int j = length; j > 0; j = j - 1) {
		fprintf(encrypt, "%d ", a[j - 1] + t);
	}
	fclose(encrypt);
	remove(location_1);
	rename(location_2, location_1);
}

//����ĺ������ڽ��ܡ�
void decode(char* location_2, char* code_location) { //���ܡ�After_Encrypt��λ�ã�����λ��
	FILE* before_decode, * after_decode, * code; //����ǰ��After_Decode������
	char* location_3 = "After_Decode.txt"; //After_Decode��λ��
	int b[length]; //�洢�������������
	int ch;
	int t; //�ٴμ���

	code = fopen(code_location, "r");
	if (code == NULL) return;
	fscanf(code, " %d", &t);
	for (int j = length; j > 0; j = j - 1)
		fscanf(code, " %d", &b[j - 1]);
	fclose(code);

	before_decode = fopen(location_2, "r");
	if (before_decode == NULL) return;
	after_decode = fopen(location_3, "w");
	for (int j = 0; fscanf(before_decode, " %d", &ch) != EOF; j = j + 1) {
		ch = ch - (b[j % length] - t);
		fputc(ch, after_decode);
	}
	fclose(before_decode);
	fclose(after_decode);
	remove(code_location);
	remove(location_2);
	rename(location_3, location_2);
}

//����ͳ��
int statistics(void)
{
	int total=0;
	Node* list;
	list = head;
	for (; list; total++, list = list->next);
	return total-1;
}

//����
int rank(char id[MAX])
{
	Node* list;
	int ranking = 1;
	list = head;
	for (; list && strcmp(list->data.id, id);ranking++, list = list->next);//ID search
	return ranking;
}

//��ֵͳ��
int extreme_value(Node* list, int choice, int code_num)
{
	int extreme = 0 ,mode;
	Node* tail = NULL, *p=list;
	Student temp;
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t  �q ==============================�����======�r\n");
	printf("\t\t\t\t  ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-��ʦ   ��\n");
	printf("\t\t\t\t  �t ======�����==============================�s\n");
	printf("\n\n");
	printf("\n\n");
	printf("\t\t\t\t\t\t 0����>   ��߷�\n\n");
	printf("\t\t\t\t\t\t 1����>   ��ͷ�\n\n");
	printf("\t\t\t\t\t\t    ����ָ���ţ�\n");
	printf("\t\t\t\t\t\t          ");
	scanf("%d", &mode);
	code_num--;
	if (mode == 0)
	{
		do {
			switch (choice)
			{
			case 0://MAX
				while (p != tail)
				{
					while (p->next != tail)
					{
						if (p->data.score[code_num].math < p->next->data.score[code_num].math)
						{
							temp = p->data;
							p->data = p->next->data;
							p->next->data = temp;
						}
						p = p->next;
					}
					tail = p;
					p = list;
				}
				extreme = list->data.score[code_num].math;
				break;
			case 1:
				while (p != tail)
				{
					while (p->next != tail)
					{
						if (p->data.score[code_num].english < p->next->data.score[code_num].english)
						{
							temp = p->data;
							p->data = p->next->data;
							p->next->data = temp;
						}
						p = p->next;
					}
					tail = p;
					p = list;
				}
				extreme = list->data.score[code_num].english;
				break;
			case 2:
				while (p != tail)
				{
					while (p->next != tail)
					{
						if (p->data.score[code_num].programming < p->next->data.score[code_num].programming)
						{
							temp = p->data;
							p->data = p->next->data;
							p->next->data = temp;
						}
						p = p->next;
					}
					tail = p;
					p = list;
				}
				extreme = list->data.score[code_num].programming;
				break;
			default:
				printf("\n\t\t\t\t\t\t      ��Чָ��!");
				getchar();
				break;
			}
		} while (choice != 0 && choice != 1 && choice != 2);
		return extreme;
	}
	else if (mode == 1)//MIN
	{
		for (; list; list = list->next);
		do {
			switch (choice)
			{
			case 0:
				while (p != tail)
				{
					while (p->next != tail)
					{
						if (p->data.score[code_num].math < p->next->data.score[code_num].math)
						{
							temp = p->data;
							p->data = p->next->data;
							p->next->data = temp;
						}
						p = p->next;
					}
					tail = p;
					p = list;
				}
				extreme = list->data.score[code_num].math;
				break;
			case 1:
				while (p != tail)
				{
					while (p->next != tail)
					{
						if (p->data.score[code_num].english < p->next->data.score[code_num].english)
						{
							temp = p->data;
							p->data = p->next->data;
							p->next->data = temp;
						}
						p = p->next;
					}
					tail = p;
					p = list;
				}
				extreme = list->data.score[code_num].english;
				break;
			case 2:
				while (p != tail)
				{
					while (p->next != tail)
					{
						if (p->data.score[code_num].programming < p->next->data.score[code_num].programming)
						{
							temp = p->data;
							p->data = p->next->data;
							p->next->data = temp;
						}
						p = p->next;
					}
					tail = p;
					p = list;
				}
				extreme = list->data.score[code_num].programming;
				break;
			default:
				printf("\n\t\t\t\t\t\t      ��Чָ��!");
				getchar();
				break;
			}
		} while (choice != 0 && choice != 1 && choice != 2);
			return extreme;
	}
	return extreme;
}

//�༶����ͳ��
double average_all(Node* list, int choice, int code_num)//mode==0�ǽ������ڼ���avr,mode==1���������汾���average
{   
	double avr = 0;
	int sum = 0, cnt = 0;
	do {
		switch (choice) 
		{
			case 0:
				for (; list->next; list = list->next)
				{
					if (list->data.score[code_num].math != 0)
					{
						sum += list->data.score[code_num].math;
						cnt++;
					}
				}
				avr = sum / cnt;
				break;
			case 1:
				for (; list->next; list = list->next) 
				{
					if (list->data.score[code_num].english != 0)
					{
						sum += list->data.score[code_num].english;
						cnt++;
					}
				}
				avr = sum / cnt;
				break;
			case 2:
				for (; list->next; list = list->next) 
				{
					if (list->data.score[code_num].programming != 0)
					{
						sum += list->data.score[code_num].programming;
						cnt++;
					}
				}
				avr = sum / cnt;
				break;
			case 3:
				for (; list->next; list = list->next) 
				{
					if ((list->data.score[code_num].math != 0) && (list->data.score[code_num].english != 0) && (list->data.score[code_num].programming != 0))
					{
						sum += (list->data.score[code_num].math + list->data.score[code_num].english + list->data.score[code_num].programming);
						cnt++;
					}
				}
				avr = sum / cnt;
				break;
			default:
				printf("\n\t\t\t\t\t\t      ��Чָ��!");
				getchar();
		}
	} while (choice != 0 && choice != 1 && choice != 2 && choice != 3);
	return avr;
}

//���˾���ͳ��
double average_one(Node* list, int choice)
{
	float sum = 0, avr = 0, cnt = 0;
	do{
		switch (choice)
		{
		case 0:
			for (int i = 0; i < 30; i++)
			{
				if (list->data.score[i].math != 0)
				{
					sum += list->data.score[i].math;
					cnt++;
				}
			}
			avr = sum / cnt;
			break;
		case 1:
			for (int i = 0; i < 30; i++)
			{
				if (list->data.score[i].english != 0)
				{
					sum += list->data.score[i].english;
					cnt++;
				}
			}
			avr = sum / cnt;
			break;
		case 2:
			for (int i = 0; i < 30; i++)
			{
				if (list->data.score[i].programming != 0)
				{
					sum += list->data.score[i].programming;
					cnt++;
				}
			}
			avr = sum / cnt;
			break;
		case 3:
			for (int i = 0; i < 30; i++)
			{
				if ((list->data.score[i].math != 0) && (list->data.score[i].english != 0) && (list->data.score[i].programming != 0))
				{
					sum += (list->data.score[i].math + list->data.score[i].english + list->data.score[i].programming);
					cnt++;
				}
			}
			avr = sum / cnt;
			break;
		default:
			printf("\n\t\t\t\t\t\t      ��Чָ��!");
			getchar();
			break;
		}
	}while (choice != 0 && choice != 1 && choice != 2 && choice != 3);
	return avr;
}

//�༶����ͳ��
double variance_all(Node* phead) 
{
	double temp = 0;
	int cnt = 0,code_num,choice;
	Node* p = phead;
	double sum_variance_all = 0;
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t  �q ==============================�����======�r\n");
	printf("\t\t\t\t  ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-��ʦ   ��\n");
	printf("\t\t\t\t  �t ======�����==============================�s\n");
	printf("\n\n");
	printf("\n\n");
	printf("\t\t\t\t\t\t������ڼ��γɼ��ķ���:");
	scanf("%d", &code_num);
	double avr;
	code_num--;
	do {
		system("cls");
		printf("\n\n");
		printf("\t\t\t\t  �q ==============================�����======�r\n");
		printf("\t\t\t\t  ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-��ʦ   ��\n");
		printf("\t\t\t\t  �t ======�����==============================�s\n");
		printf("\n\n");
		printf("\n\n");
		printf("\t\t\t\t\t\t\tMENU\n\n");
		printf("\t\t\t\t\t\t 0����>��ѧ����ָ��\n\n");
		printf("\t\t\t\t\t\t 1����>Ӣ�ﲨ��ָ��\n\n");
		printf("\t\t\t\t\t\t 2����>C���Բ���ָ��\n\n");
		printf("\t\t\t\t\t\t 3����>�ֲܷ���ָ��\n\n");
		printf("\t\t\t\t\t\t    ����ָ���ţ�\n");
		printf("\t\t\t\t\t\t          ");
		scanf("%d", &choice);
		avr = average_all(phead, choice, code_num);
		//printf("%.2lf", avr);
		switch (choice) 
		{
			case 0:
				for (; p->next; p = p->next) 
				{
					if (p->data.score[code_num].math != 0)
					{
						temp = pow(p->data.score[code_num].math - avr, 2);
						sum_variance_all += temp;
						cnt++;
						//printf("%.2lf\n", temp);
						//printf("%.2lf\n", sum_variance_all);
					}
				}
				s_m = sum_variance_all / cnt;
					return sum_variance_all / cnt;
				break;
			case 1:
				for (; p->next; p = p->next) 
				{
					if (p->data.score[code_num].english != 0)
					{
						temp = pow(p->data.score[code_num].english - avr, 2);
						sum_variance_all += temp;
						cnt++;
					}
				}
				s_e = sum_variance_all / cnt;
					return sum_variance_all / cnt;
				break;
			case 2:
				for (; p->next; p = p->next) 
				{
					if (p->data.score[code_num].programming != 0)
					{
						temp = pow(p->data.score[code_num].programming - avr, 2);
						sum_variance_all += temp;
						cnt++;
					}
				}
				s_c = sum_variance_all / cnt;
					return sum_variance_all / cnt;
				break;
			case 3:
				for (; p->next; p = p->next) 
				{
					if ((p->data.score[code_num].math != 0) && (p->data.score[code_num].english != 0) && (p->data.score[code_num].programming != 0))
					{
						temp = pow(p->data.score[code_num].programming + p->data.score[code_num].math + p->data.score[code_num].english - avr, 2);
						sum_variance_all += temp;
						cnt++;
					}
				}
				s_a = sum_variance_all / cnt;
					return sum_variance_all / cnt;
				break;
			default:
				printf("\n\t\t\t\t\t\t      ��Чָ��!");
				getchar();
				break;
		}
	} while (choice != 0 && choice != 1 && choice != 2 && choice != 3);
	return sum_variance_all / cnt;
}

//ѧ���ɼ�����
double variance_one(Node* p,int choice)
{
	double temp = 0;
	int cnt = 0;
	double sum_variance_all = 0;
	double avr;
	avr = average_one(p, choice);
	do{
		switch (choice)
		{
		case 0:
			for (int i=0; i<30; i++)
			{
				if (p->data.score[i].math != 0)
				{
					temp = pow(p->data.score[i].math - avr, 2);
					sum_variance_all += temp;
					cnt++;
				}
			}
			s_m = sum_variance_all / cnt;
			return sum_variance_all / cnt;
			break;
		case 1:
			for (int i=0; i<30; i++)
			{
				if (p->data.score[i].english != 0)
				{
					temp = pow(p->data.score[i].english - avr, 2);
					sum_variance_all += temp;
					cnt++;
				}
			}
			s_e = sum_variance_all / cnt;
			return sum_variance_all / cnt;
			break;
		case 2:
			for (int i=0; i<30; i++)
			{
				if (p->data.score[i].programming != 0)
				{
					temp = pow(p->data.score[i].programming - avr, 2);
					sum_variance_all += temp;
					cnt++;
				}
			}
			s_c = sum_variance_all / cnt;
			return sum_variance_all / cnt;
			break;
		default:
			printf("\n\t\t\t\t\t\t      ��Чָ��!");
			getchar();
			break;
		}
	} while (choice != 0 && choice != 1 && choice != 2);
	return sum_variance_all / cnt;
}

//���ɳɼ�����
void report(int code_num)
{
	Node* list;
	list = search(user);
	avr_m = average_one(list, 0);
	avr_e = average_one(list, 1);
	avr_c = average_one(list, 2);
	s_m = variance_one(list, 0);
	s_e = variance_one(list, 1);
	s_c = variance_one(list, 2);
	member = statistics();
	//printf("%d\n", member);
	put_in_order(head, 0, code_num);
	ranking_m = rank(user);
	put_in_order(head, 1, code_num);
	ranking_e = rank(user);
	put_in_order(head, 2, code_num);
	ranking_c = rank(user);
	printf("\n\t\t\t\t\t\t   ���ڵ�%d�ο����У�\n", code_num);
	printf("\t\t\t��ѧ�÷�%d���༶������%d,", list->data.score[code_num - 1].math, ranking_m);
	if (((float)ranking_m / (float)member) <= 0.2)
		printf("�������㣬ϣ���������֣�������Ŭ��������������ͻ�ƣ�\n");
	else  if (((float)ranking_m / (float)member) > 0.2 && ((float)ranking_m / (float)member) < 0.6)
		printf("���ֲ���ϣ�����ø��ã���ȡ��һ�ο���������һ��¥��\n");
	else if (((float)ranking_m / (float)member) >= 0.6)
		printf("��̫���룬��Ҫ�ú�����ԭ�򣬲�Ҫ������ɣ�Ҫ�๮�̻���Ŷ��\n");

	printf("\t\t\tӢ��÷�%d���༶������%d,", list->data.score[code_num - 1].english, ranking_e);
	if (((float)ranking_e / (float)member) <= 0.2)
		printf("�������㣬ϣ���������֣�������Ŭ��������������ͻ�ƣ�\n");
	else  if (((float)ranking_e / (float)member) > 0.2 && ((float)ranking_e / (float)member) < 0.6)
		printf("���ֲ���ϣ�����ø��ã���ȡ��һ�ο���������һ��¥��\n");
	else if (((float)ranking_e / (float)member) >= 0.6)
		printf("��̫���룬��Ҫ�ú�����ԭ�򣬲�Ҫ������ɣ�Ҫ�๮�̻���Ŷ��\n");

	printf("\t\t\tC���Ե÷�%d���༶������%d,", list->data.score[code_num - 1].programming, ranking_c);
	if (((float)ranking_c / (float)member) <= 0.2)
		printf("�������㣬ϣ���������֣�������Ŭ��������������ͻ�ƣ�\n");
	else  if (((float)ranking_c / (float)member) > 0.2 && ((float)ranking_c / (float)member) < 0.6)
		printf("���ֲ���ϣ�����ø��ã���ȡ��һ�ο���������һ��¥��\n");
	else if (((float)ranking_c / (float)member) >= 0.6)
		printf("��̫���룬��Ҫ�ú�����ԭ�򣬲�Ҫ������ɣ�Ҫ�๮�̻���Ŷ��\n");

}

//��������
int analyze(void)
{
	int choice,change = 0;
	headview();
	if (!type)
	{
		Node* temp;
		temp = search(user);
		while (1)
		{
			system("cls");
			printf("\n\n");
			printf("\t\t\t\t  �q ==============================�����======�r\n");
			printf("\t\t\t\t  ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-ѧ��   ��\n");
			printf("\t\t\t\t  �t ======�����==============================�s\n");
			printf("\n\n");
			printf("\t\t\t\t������%s", temp->data.name);
			printf("\t\t\t\tѧ�ţ�%s", temp->data.id);
			printf("\n\n");
			printf("\t\t\t\t\t\t\tMENU\n\n");
			printf("\t\t\t\t\t\t 1����>���ƽ���ɼ�\n\n");
			printf("\t\t\t\t\t\t 2����>�ɼ�����ָ��\n\n");
			printf("\t\t\t\t\t\t 3����>��ĳɼ�����\n\n");
			printf("\t\t\t\t\t\t 4����>  ���λ��\n\n");
			printf("\t\t\t\t\t\t    ����ָ���ţ�\n");
			printf("\t\t\t\t\t\t          ");
			scanf("%d", &choice);
			switch (choice)
			{
			case 1:change = 1;
				break;
			case 2:change = 2;
				break;
			case 3:change = 3;
				break;
			case 4:change = 4;
				break;
			default:
				printf("\n\t\t\t\t\t\t      ��Чָ��!");
				getchar();
				break;
			}
			if (choice == 1 || choice == 2 || choice == 3 || choice == 4)
				break;
		}
	}
	else
	{
		while (1)
		{
			system("cls");
			printf("\n\n");
			printf("\t\t\t\t  �q ==============================�����======�r\n");
			printf("\t\t\t\t  ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-��ʦ   ��\n");
			printf("\t\t\t\t  �t ======�����==============================�s\n");
			printf("\n\n");
			printf("\n\n");
			printf("\t\t\t\t\t\t\tMENU\n\n");
			printf("\t\t\t\t\t\t 1����>ȫ��ƽ���ɼ�\n\n");
			printf("\t\t\t\t\t\t 2����>�ɼ�����ָ��\n\n");
			printf("\t\t\t\t\t\t 3����> �����ͷ�\n\n");
			printf("\t\t\t\t\t\t    ����ָ���ţ�\n");
			printf("\t\t\t\t\t\t          ");
			scanf("%d", &choice);
			switch (choice)
			{
			case 1:change = 5;
				break;
			case 2:change = 6;
				break;
			case 3:change = 7;
				break;
			default:
				printf("\t\t\t\t\t\t      ��Чָ��!");
				getchar();
				break;
			}
			if (choice == 1 || choice == 2 || choice == 3 )
				break;
		}
	}
	return change;
}

//���ݷ���ʵ��
void f_analyze(int change)
{
	Node* temp;
	int choice, code_num,r_num,extreme, code_data;
	temp = search(user);
	system("cls");
	printf("\n\n");
	if (type)
	{
		printf("\t\t\t\t     �q ==============================�����======�r\n");
		printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-��ʦ   ��\n");
		printf("\t\t\t\t     �t ======�����==============================�s\n");
		printf("\n\n");
	}
	else
	{
		printf("\t\t\t\t     �q ==============================�����======�r\n");
		printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-ѧ��   ��\n");
		printf("\t\t\t\t     �t ======�����==============================�s\n");
		printf("\n\n");
		printf("\t\t\t\t   ������%s", temp->data.name);
		printf("\t\t\t\t   ѧ�ţ�%s", temp->data.id);
		printf("\n\n");
	}
	while (1)
	{
		switch (change)
		{
		case 1:
			printf("\n\n");
			printf("\t\t\t\t\t\t    0����>��ѧƽ���ɼ�\n\n");
			printf("\t\t\t\t\t\t    1����>Ӣ��ƽ���ɼ�\n\n");
			printf("\t\t\t\t\t\t    2����>C����ƽ���ɼ�\n\n");
			printf("\t\t\t\t\t\t    3����>�ܷ�ƽ���ɼ�\n\n");
			printf("\t\t\t\t\t\t       ����ָ���ţ�\n");
			printf("\t\t\t\t\t\t             ");
			scanf("%d", &choice);
			while (1)
			{
				switch (choice)
				{
				case 0:
					avr_m = average_one(temp, choice);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t     �q ==============================�����======�r\n");
					printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-ѧ��   ��\n");
					printf("\t\t\t\t     �t ======�����==============================�s\n");
					printf("\n\n");
					printf("\t\t\t\t   ������%s", temp->data.name);
					printf("\t\t\t\t   ѧ�ţ�%s", temp->data.id);
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      ��ѧƽ���֣�%.2lf\n\n\n\n\n", avr_m);
					break;
				case 1:
					avr_e = average_one(temp, choice);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t     �q ==============================�����======�r\n");
					printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-ѧ��   ��\n");
					printf("\t\t\t\t     �t ======�����==============================�s\n");
					printf("\n\n");
					printf("\t\t\t\t   ������%s", temp->data.name);
					printf("\t\t\t\t   ѧ�ţ�%s", temp->data.id);
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      C����ƽ���֣�%.2lf\n\n\n\n\n", avr_e);
					break;
				case 2:
					avr_c = average_one(temp, choice);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t     �q ==============================�����======�r\n");
					printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-ѧ��   ��\n");
					printf("\t\t\t\t     �t ======�����==============================�s\n");
					printf("\n\n");
					printf("\t\t\t\t   ������%s", temp->data.name);
					printf("\t\t\t\t   ѧ�ţ�%s", temp->data.id);
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      Ӣ��ƽ���֣�%.2lf\n\n\n\n\n", avr_c);
					break;
				case 3:
					avr_a = average_one(temp, choice);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t     �q ==============================�����======�r\n");
					printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-ѧ��   ��\n");
					printf("\t\t\t\t     �t ======�����==============================�s\n");
					printf("\n\n");
					printf("\t\t\t\t   ������%s", temp->data.name);
					printf("\t\t\t\t   ѧ�ţ�%s", temp->data.id);
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      �ܷ�ƽ���֣�%.2lf\n\n\n\n\n", avr_a);
					break;
				default:
					printf("\n\t\t\t\t\t\t         ��Чָ��!\n");
					getchar();
					break;
				}
				if (choice == 0 || choice == 1 || choice == 2 || choice == 3)
					break;
			}
				break;
		case 2://����ָ��
			system("cls");
			printf("\n\n");
			printf("\t\t\t\t     �q ==============================�����======�r\n");
			printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-ѧ��   ��\n");
			printf("\t\t\t\t     �t ======�����==============================�s\n");
			printf("\n\n");
			printf("\t\t\t\t   ������%s", temp->data.name);
			printf("\t\t\t\t   ѧ�ţ�%s", temp->data.id);
			printf("\n\n");
			printf("\t\t\t\t\t\t\t   MENU\n\n");
			printf("\t\t\t\t\t\t    0����>��ѧ����ָ��\n\n");
			printf("\t\t\t\t\t\t    1����>Ӣ�ﲨ��ָ��\n\n");
			printf("\t\t\t\t\t\t    2����>C���Բ���ָ��\n\n");
			printf("\t\t\t\t\t\t       ����ָ���ţ�\n");
			printf("\t\t\t\t\t\t             ");
			scanf("%d", &choice);
			s = variance_one(search(user),choice);
			printf("\t\t\t\t\t\t       ����ָ����%.2lf\n\n\n\n\n", s);
			break;
		case 3://�ɼ�����
			system("cls");
			printf("\n\n");
			printf("\t\t\t\t     �q ==============================�����======�r\n");
			printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-ѧ��   ��\n");
			printf("\t\t\t\t     �t ======�����==============================�s\n");
			printf("\n\n");
			printf("\t\t\t\t   ������%s", temp->data.name);
			printf("\t\t\t\t   ѧ�ţ�%s", temp->data.id);
			printf("\n\n");
			printf("\n\n\n\n\t\t\t\t\t\t   �������ɵڼ��γɼ�����:");
			scanf("%d", &code_num);
			report(code_num);
			break;
		case 4://λ������
			printf("\t\t\t\t\t\t   0-->����ѧ�ɼ��������\n\n");
			printf("\t\t\t\t\t\t   1-->��Ӣ��ɼ��������\n\n");
			printf("\t\t\t\t\t\t   2-->��c���Գɼ��������\n\n");
			printf("\t\t\t\t\t\t         �����룺");
			scanf("%d", &code_data);
			printf("\n\t\t\t\t\t\t   ���밴�ڼ��γɼ�����:");
			scanf("%d", &code_num);
			put_in_order(head,code_data,code_num);
			r_num = rank(user);
			printf("\n\n\t\t\t\t\t\t       ����������%d\n\n\n\n\n",r_num);
			break;
		case 5:
			printf("\t\t\t\t\t\t    0����>��ѧƽ���ɼ�\n\n");
			printf("\t\t\t\t\t\t    1����>Ӣ��ƽ���ɼ�\n\n");
			printf("\t\t\t\t\t\t    2����>C����ƽ���ɼ�\n\n");
			printf("\t\t\t\t\t\t    3����>�ܷ�ƽ���ɼ�\n\n");
			printf("\t\t\t\t\t\t       ����ָ���ţ�\n");
			printf("\t\t\t\t\t\t             ");
			scanf("%d", &choice);
			printf("\t\t\t\t\t\t   ������ڼ��γɼ���");
			scanf("%d", &code_num);
			code_num--;
			while (1)
			{
				switch (choice)
				{
				case 0:
					avr_m = average_all(head, choice, code_num);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t     �q ==============================�����======�r\n");
					printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-��ʦ   ��\n");
					printf("\t\t\t\t     �t ======�����==============================�s\n");
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      ��ѧƽ���֣�%.2lf\n\n\n\n\n", avr_m);
					break;
				case 1:
					avr_e = average_all(head, choice, code_num);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t     �q ==============================�����======�r\n");
					printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-��ʦ   ��\n");
					printf("\t\t\t\t     �t ======�����==============================�s\n");
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      C����ƽ���֣�%.2lf\n\n\n\n\n", avr_e);
					break;
				case 2:
					avr_c = average_all(head, choice, code_num);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t     �q ==============================�����======�r\n");
					printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-��ʦ   ��\n");
					printf("\t\t\t\t     �t ======�����==============================�s\n");
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      Ӣ��ƽ���֣�%.2lf\n\n\n\n\n", avr_c);
					break;
				case 3:
					avr_a = average_all(head, choice, code_num);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t     �q ==============================�����======�r\n");
					printf("\t\t\t\t     ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-��ʦ   ��\n");
					printf("\t\t\t\t     �t ======�����==============================�s\n");
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      �ܷ�ƽ���֣�%.2lf\n\n\n\n\n", avr_a);
					break;
				default:
					printf("\n\t\t\t\t\t\t         ��Чָ��!");
					getchar();
					break;
				}
				if (choice == 0 || choice == 1 || choice == 2 || choice == 3)
					break;
			}
			break;
		case 6:
			s = variance_all(head);
			printf("\t\t\t\t\t\t    ����ָ����%.2lf\n\n\n\n\n", s);
			break;
		case 7://��ֵ
			system("cls");
			printf("\n\n");
			printf("\t\t\t\t  �q ==============================�����======�r\n");
			printf("\t\t\t\t  ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-��ʦ   ��\n");
			printf("\t\t\t\t  �t ======�����==============================�s\n");
			printf("\n\n");
			printf("\n\n");
			printf("\t\t\t\t\t\t 0����>��ѧ�ɼ���ֵ\n\n");
			printf("\t\t\t\t\t\t 1����>Ӣ��ɼ���ֵ\n\n");
			printf("\t\t\t\t\t\t 2����>C���Գɼ���ֵ\n\n");
			printf("\t\t\t\t\t\t    ����ָ���ţ�\n");
			printf("\t\t\t\t\t\t          ");
			scanf("%d", &choice);
			printf("\t\t\t\t\t\t������ڼ��γɼ���");
			scanf("%d", &code_num);
			extreme = extreme_value(head, choice, code_num);
			printf("\t\t\t\t\t\t            %d\n\n\n\n\n",extreme);
			break;
		default:
			printf("\n\t\t\t\t\t\t      ��Чָ��!");
			getchar();
			break;
		}
		if (change == 7 || change == 1 || change == 2 || change == 3 || change == 4 || change == 5 || change == 6)
			break;
	}
	jump();
}

//GPA
void GPA(Node* phead) 
{
	system("cls");
	headview();
	printf("\n\n");
	printf("\t\t\t\t  �q ==============================�����======�r\n");
	printf("\t\t\t\t  ��   ���ӿƼ���ѧ1605��ѧ���ɼ�����ϵͳ-ѧ��   ��\n");
	printf("\t\t\t\t  �t ======�����==============================�s\n");
	printf("\n\n");
	Node* p;
	int choice;
	float avr;
	p = search(user);
	printf("\t\t\t\t\t\t�����ѯ�ڼ��γɼ�:");
	scanf("%d", &choice);
	/*while (1) {
		for (p = phead; strcmp(p->data.id, user) && p; p = p->next);
		if (p)
			break;
		else {
			printf("\t\t\t\t\t\tѧ�Ų����ڣ�");
				Sleep(1000);
		}
	}*/
	choice--;
	avr = (p->data.score[choice].math + p->data.score[choice].english + p->data.score[choice].programming) / 3;
	if (avr >= 85)
	{
		printf("\n\t\t\t\t\t\t  ��̫���ˣ�����4.0");
	}
	else if (avr >= 60)
	{
		printf("\n\t\t\t\t\t\t  ��ļ���Ϊ��%.1f", 4.0 - (85.0 - avr) * 0.1);
	}
	else
	{
		printf("\n\t\t\t\t\t\t      ��ҿ���");
	}
}

//��������
void insert_sort(Node* phead) {
	Node* p = phead;//�������� 
	Student temp;
	Node* in_order, * out_order, * temp_order;
	for (out_order = p->next; out_order; out_order = out_order->next) {
		for (in_order = out_order->prior; in_order; in_order = in_order->prior) { //Ĭ�ϵ�һ����Ϊ������ 
			if (in_order->data.score[0].math > out_order->data.score[0].math)
				break;
		}   //�ҵ��ֽ�� 
		if (!in_order) {
			in_order = (Node*)malloc(sizeof(Node)); //����Ϊ���������������ֵ����������ֵ����ʱ��������ᵼ������ָ���ָ�룬�����Ҫ�����ڴ�ռ� 
			in_order->next = p;
			p->prior = in_order;
		}
		if (in_order != out_order->prior) {  //���Լ��ٸ��Ӷȣ����������������Сʱֱ�ӽ��� 
			temp = out_order->data;
			for (temp_order = out_order->prior; temp_order != in_order; temp_order = temp_order->prior)
				temp_order->next->data = temp_order->data;//���������ƶ�һλ 
			in_order->next->data = temp; //��ʽ������������ �������� 
		}
		p->prior = NULL;//��Ҫ��ͷ���ָ�ԭ�� 
	}
}