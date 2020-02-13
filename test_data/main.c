#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>
#include<Windows.h>
#include <conio.h>

/*全局数据*/
#define MAX 30
#define length 1000 //密码个数
int error;//报错检测

Node* head, * Tail;//头节点
int type, member, account;//账户类型(1-教师，0-学生),人数, 账户
char user[MAX] = { 0 }, pass[MAX] = { 0 };//登录用户
char* USER[2 * MAX] = { 0 }, * PASS[2 * MAX] = { 0 };//账户信息
double avr_c, avr_m, avr_e, avr_a, s_c, s_m, s_e, s_a, s;//平均分,方差
int ranking_c, ranking_m, ranking_e;//排名

/*变量类型定义*/
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




/*函数声明*/
void headview(void);//顶部图标
SMALL_RECT SizeOfWindow(HANDLE hConsoleOutput);//窗口
void modeset(int w, int h);//窗口
void surface(void);//窗口初始化
bool login(void);//登录
int awelcome(void);//管理员主菜单，返回选项
int swelcome(void);//学生主菜单，返回选项
void init_node(void);//初始化链表
void load(void);//载入成绩数据
void jump(void);//跳转界面
void save(void);//保存写入
void add_student(void);//添加成员
void write(void);//控制台写入信息
Node* search(char id[MAX]);//链表搜索
void print_one(Node* list);//打印输出信息
void  delet(Node** list, char id[MAX]);//删除信息
void put_in_order(Node* phead, int code_data, int code_num);//排序函数
void f_rand(int a[], int* t); //随机数
void encrypt(char* location_1, char* code_location); //加密。加密前的文本位置，密码位置
void decode(char* location_2, char* code_location); //解密。After_Encrypt的位置，密码位置
int statistics(void);//人数统计
int rank(char id[MAX]);//排序
int extreme_value(Node* list, int choice, int code_num);//班级最值统计
double average_all(Node* list, int choice, int code_num);//班级均分统计
double average_one(Node* list, int choice);//个人均分统计
double variance_all(Node* phead);//班级波动指数
double variance_one(Node* p,int choice);//个人波动指数
void report(int code_num);//生成成绩报告
void GPA(Node* phead);//GPA
void insert_sort(Node* phead);//插入排序
int analyze(void);//数据分析界面
void f_analyze(int change);//数据分析实现


int main(void)
{
	//变量定义
	int choice,change;
	char id[MAX];
	//窗台美化
	surface();

	//程序初始化
	init_node();
	
	//用户登录|菜单选择
	type = login();
	//type = 1;

	while (1)
	{
	if (type)
		choice = awelcome();
	else
		choice = swelcome();


		//功能实现
		switch (choice)
		{
		case 0://该功能目前意义不大

			break;
		case 1:
			system("cls");
			headview();
			printf("\n\n\t\t\t\t\t\t请输入学号:	");
			error=scanf("%s", id);
			print_one(search(id));
			jump();
			break;
		case 2:
			system("cls");
			headview();
			printf("\n\n");
			printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
			printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-教师   │\n");
			printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
			printf("\n\n");
			add_student();
			jump();
			break;
		case 3:
			system("cls");
			headview();
			printf("\n\n");
			printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
			printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-教师   │\n");
			printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
			printf("\n\n");
			write();
			jump();
			break;
		case 4:
			system("cls");
			headview();
			printf("\n\n");
			printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
			printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-教师   │\n");
			printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
			printf("\n\n");
			printf("\n\n\n\t\t\t\t\t\t请输入学号：");
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
			printf("\t\t\t\t\t\t\t保存成功\n\n\n\n\n");
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
			printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
			printf("\t\t\t\t     │     电子科技大学1605班学生成绩管理系统      │\n");
			printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
			printf("\n\n");
			printf("\n\n\n\t\t\t\t\t\t请输入新密码：");
			scanf("%s", PASS[account]);
			jump();
			break;
		default:
			printf("\t\t\t\t\t请重新输入：");
			error=scanf("%d", &choice);
			break;
		}
	}
	//printf("OKKKK");运行终点验证
	//getchar();
	return 0;
}

//登录界面
bool login(void)
{
	FILE* apas,*spas,*ause,*suse;

	int times=0,j = 0,a=1,choice=10, i = 0;//a用于依次验证密码
	again:system("cls");
	headview();
	printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
	printf("\t\t\t\t     │      电子科技大学1605班学生成绩管理系统     │\n");
	printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t你的账户类型？   1——>学生 | 2——>教师\n\n");
	printf("\t\t\t\t\t\t\t你的选择：");
	scanf("%d", &choice);
	system("cls");
	begain:headview();
	printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
	printf("\t\t\t\t     │      电子科技大学1605班学生成绩管理系统     │\n");
	printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t   用户名:	");
	scanf("%s", user);
	printf("\n\t\t\t\t\t   密码:	");
	scanf("%s",pass);
	//printf("%s\n%s", user, pass);输入验证
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

		//printf("%s\n%s", PASS[1], USER[1]);//文件写入验证
		getchar();
		for ( i = 0; a; i++)
		{
			a *= (!(strcmp(user, USER[i]) == 0 && strcmp(pass, PASS[i]) == 0));//有对则0，全错则1
			if (a == 0)account = i;
		}
			while (a)
			{
				times++;	//密码输入错误 times++
				if (times > 3)
				{
					printf("\n\n\n\t\t\t\t账号或密码输入错误累计达到%d次，系统将于3秒后关闭", times);
					Sleep(1000);
					system("cls");
					char shutdown[] = { "系统将于%d秒后关闭..." };
					for (int i = 0; i < 3; i++)
					{
						printf(shutdown, 3 - i);
						Sleep(1000);
						system("cls");
					}
					exit(0);
				}
				printf("\n\n\n\t\t\t\t账号或密码输入错误,你还有%d次登录机会，按任意键重新登录...", 4 - times);
				getchar();
				system("cls");
				goto begain;
			}
			/*for (int i = 0; i < 30; i++) {

				free(USER[i]);
				free(PASS[i]);
			}*/
			//内存释放报错
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
			a *= (!(strcmp(user, USER[i]) == 0 && strcmp(pass, PASS[i]) == 0));//有对则0，全错则1
			if (a == 0)account = i;
		}			
			while (a)
			{
				times++;	//密码输入错误 times++
				if (times > 3)
				{
					printf("\n\n\n\t\t\t\t账号或密码输入错误累计达到%d次，系统将于3秒后关闭", times);
					Sleep(1000);
					system("cls");
					char shutdown[] = { "系统将于%d秒后关闭..." };
					for (int i = 0; i < 3; i++)
					{
						printf(shutdown, 3 - i);
						Sleep(1000);
						system("cls");
					}
					exit(0);
				}
				printf("\n\n\n\t\t\t\t账号或密码输入错误,你还有%d次登录机会，按任意键重新登录...", 4 - times);
				getchar();
				system("cls");
				goto begain;
			}
			/*for (int i = 0; i < 30; i++) {

				free(USER[i]);
				free(PASS[i]);
			}*/
			//内存释放报错
			return 1;
	default:
		printf("\n\n\t\t\t\t\t   请重新输入账户类型！\n");
		goto again;
	}
	getchar();
}

//管理员菜单界面
int awelcome(void)
{
	int choice=7;
	system("cls");
	headview();
	printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
	printf("\t\t\t\t     │      电子科技大学1605班学生成绩管理系统     │\n");
	printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
	printf("\n");
	printf("\t\t\t\t\t\t\t    MENU\n\n");
	printf("\t\t\t\t\t\t     1——>查看学生成绩\n\n");
	printf("\t\t\t\t\t\t     2——>新增学生成绩\n\n");
	printf("\t\t\t\t\t\t     3——>修改学生成绩\n\n");
	printf("\t\t\t\t\t\t     4——>删除学生信息\n\n");
	printf("\t\t\t\t\t\t     5——>成绩数据分析\n\n");
	printf("\t\t\t\t\t\t     6——>账户密码修改\n\n");
	printf("\t\t\t\t\t\t     7——>退出 并 保存\n\n");
	printf("\t\t\t\t\t\t        输入指令编号：\n");
	printf("\t\t\t\t\t\t              ");
	scanf("%d", &choice);
	return choice;
}

//学生端菜单界面
int swelcome(void)
{
	int change,choice=8;//修改传出指令
	system("cls");
	headview();
	printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
	printf("\t\t\t\t     │      电子科技大学1605班学生成绩管理系统     │\n");
	printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
	printf("\n\n");
	printf("\t\t\t\t\t\t\t   MENU\n\n");
	printf("\t\t\t\t\t\t    1——>查看你的成绩\n\n");
	printf("\t\t\t\t\t\t    2——>成绩数据分析\n\n");
	printf("\t\t\t\t\t\t    3——>账户密码修改\n\n");
	printf("\t\t\t\t\t\t    4——>  GPA查询\n\n");
	printf("\t\t\t\t\t\t    5——>    退出\n\n");
	printf("\t\t\t\t\t\t       输入指令编号：\n");
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

//窗口初始化
void surface(void)
{
	SetConsoleTitle("UESTC_1605班成绩管理系统");
	system("color 70");
	modeset(1200, 675);
	headview();
	printf("\n\n\t\t\t\t\t这是一个看似单调，却拥有无数创新的成绩系统！\n");
	printf("\n\n\n\n\n\t\t\t\t\t  ||——Made by -Csy- -Sry- -Xy- -Zzy-||\n");
	int i;
	printf("\n\n\n\n\n\t\t\t\t\t\t");
	char heihei[] = { "按Enter键进入学生成绩系统..." };
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
	printf("\t\t\t\t\t     ╭ ⺌ % ╮                   ╭ ```╮  \n");
	printf("\t\t\t\t\t     (@^o^@) 学生成绩管理系统 (⌒:⌒)\n");
	printf("\t\t\t\t\t     (~):(~)                  (~)v(~) \n");
	printf("\n");
}

//窗口调整
SMALL_RECT SizeOfWindow(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &info);
	return info.srWindow;
}
void modeset(int w, int h)
{
	//	此函数设置窗口大小为 w*h
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	SMALL_RECT rect = SizeOfWindow(hOut);
	COORD size = { rect.Right + 1,rect.Bottom + 1 };	//定义缓冲区大小    
	//COORD size = { w, h };
	SetConsoleScreenBufferSize(hOut, size);
	GetConsoleScreenBufferInfo(hOut, &info);//隐藏滑动条
	SMALL_RECT rc = { 1,1, w, h };
	SetConsoleWindowInfo(hOut, 1, &rc);
	SetWindowLongPtrA(
		GetConsoleWindow(),
		GWL_STYLE,
		GetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE)
		& ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX 
	);
}

//载入成绩数据
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
		list = list->next, list->prior = flag)//判断是否读到结尾的同时读入name
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

//初始化链表
void init_node(void)
{
	head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	head->prior = NULL;
	load();
}

//打印成绩
void print_one(Node* list)
{
	//list = list->next;测试节点转换
	int n = 1, i = 0;
	printf("\n\n");
	printf("\n\n");
	printf("\t\t\t\t姓名：%s", list->data.name);
	printf("\t\t\t\t学号：%s", list->data.id);
	printf("\n\n");
	printf("\t\t\t\t\t\t    查看第几次考试：");
	scanf("%d", &n);
	printf("\n\t\t\t\t\t\t  C语言\t  数学\t  英语\t\n");
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

//跳转界面
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
			printf("\n\t\t\t\t\t\t      无效指令!");
			getch();
			break;
		}
		if(temp=='h')
		break;
	}
}

//保存、写入数据
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

//添加成员
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
		printf("\t\t\t\t\t\t请输入姓名：");
		scanf("%s", list->data.name);
		printf("\n\t\t\t\t\t\t请输入学号：");
		scanf("%s", list->data.id);
		printf("\n\t\t\t\t\t\t第几次考试：");
		scanf("%d", &times);
		printf("\n\t\t\t\t\t\t请输入分数(C语言 数学 英语)：");
		scanf("%d %d %d", &(list->data.score[times - 1].programming), \
			& (list->data.score[times - 1].math), &(list->data.score[times - 1].english));
}

//控制台写入信息
void write(void)
{
	Node* list;
	char id[MAX];
	printf("\n\n\n\t\t\t\t\t\t请输入学号：");
	scanf("%s", id);
	list = search(id);
	printf("\n\t\t\t\t\t\t姓名：%s", list->data.name);
	int n1, n2, n3, times;
	printf("\n\n");
	printf("\n\t\t\t\t\t\t    修改单项信息输入0\n");
	printf("\n\t\t\t\t\t\t    填入全部信息输入1\n");
	printf("\n\t\t\t\t\t\t         请输入：");
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
				printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
				printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-教师   │\n");
				printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
				printf("\n\n");
				printf("\t\t\t\t\t\t      0-修改姓名\n\n");
				printf("\t\t\t\t\t\t      1-修改学号\n\n");
				printf("\t\t\t\t\t\t      2-修改C语言成绩\n\n");
				printf("\t\t\t\t\t\t      3-修改数学成绩\n\n");
				printf("\t\t\t\t\t\t      4-修改英语成绩\n\n");
				printf("\t\t\t\t\t\t         请输入：");
				scanf("%d", &n2);
				if (n2 != 0 && n2 != 1)
				{
					system("cls");
					headview();
					printf("\n\n");
					printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-教师   │\n");
					printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\n\t\t\t\t\t\t      修改第几次成绩：");
					scanf("%d", &n3);
				}
				switch (n2)
				{
				case 0:
					printf("\n\t\t\t\t\t\t请输入姓名：");
					scanf("%s", list->data.name);
					break;
				case 1:
					printf("\n\t\t\t\t\t\t请输入学号：");
					scanf("%s", list->data.id);
					break;
				case 2:
					printf("\n\t\t\t\t\t\t   请输入C语言成绩：");
					scanf("%d", &(list->data.score[n3 - 1].programming));
					break;
				case 3:
					printf("\n\t\t\t\t\t\t   请输入数学成绩：");
					scanf("%d", &(list->data.score[n3 - 1].math));
					break;
				case 4:
					printf("\n\t\t\t\t\t   请输入英语成绩：");
					scanf("%d", &(list->data.score[n3 - 1].english));
					break;
				default:
					printf("\n\t\t\t\t\t\t无效指令");
					getchar();
					break;
				}
				if (n2 == 0 || n2 == 1 || n2 == 2 || n2 == 3 || n2 == 4)
					break;
			}
			break;
		case 1:
			printf("\n\t\t\t\t\t\t请输入姓名：");
			scanf("%s", list->data.name);
			printf("\n\t\t\t\t\t\t请输入学号：");
			scanf("%s", list->data.id);
			printf("\n\t\t\t\t\t\t第几次考试：");
			scanf("%d", &times);
			printf("\n\t\t\t\t\t\t请输入分数(C语言 数学 英语)：");
			scanf("%d %d %d", &(list->data.score[times - 1].programming), \
				& (list->data.score[times - 1].math), &(list->data.score[times - 1].english));
			break;
		default:
			printf("\n\t\t\t\t\t\t请重新输入");
			system("pause");
			break;
		}
		if (n1 == 0 || n1 == 1)
			break;
	}
}

//搜索链表
Node* search(char id[MAX])//已知BUG：学号不存在，到达链表尾崩溃
{
	Node* list;
	list = head;
	for (; list && strcmp(list->data.id, id); list = list->next);//ID search
	return list;
}

//删除链表节点
void  delet(Node** list, char id[MAX])				//void函数可以减少赋值一步，避免出错；
{
	Node* p = (*list);
	Node* q=NULL; //跟随指针
	if (!strcmp(p->data.id, id)) {		//第一个数据就是所找数据时的特殊情况
		(*list) = (*list)->next;   //删除第一个结点
	}
	else {
		for (; p && strcmp(p->data.id, id); q = p, p = p->next);
		if (!p)
			printf("unknown id\n"); else {
			q->next = p->next;    //将跟随指针跳过所删除的结点，指向下一个
		}
	}

}

//排序函数
void put_in_order(Node* phead,int code_data, int code_num)
{          //排序，不输出
	int code_order;
	Node* p = phead;
	Node* tail = NULL;
	Student temp;
	//printf("\t\t\t\t\t\t0-->由高到低排序输出");
	//printf("\t\t\t\t\t\t1-->由低到高排序输出");
	//printf("\t\t\t\t\t\t      请输入：");
	//scanf("%d", &code_order);
	code_order = 0;
	//printf("\t\t\t\t\t\t0-->按数学成绩排序输出");
	//printf("\t\t\t\t\t\t1-->按英语成绩排序输出");
	//printf("\t\t\t\t\t\t2-->按c语言成绩排序输出");
	//printf("\t\t\t\t\t\t      请输入：");
	//scanf("%d", &code_data);
	//printf("\t\t\t\t\t\t您想按第几次成绩排序:");
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
				default:printf("\t\t\t\t\t\t请重新输入");
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
				case 0://while中的p->next->next != NULL是为了避免读取最后一个未初始化的尾节点而将其传到链表头节点
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
				default:printf("\t\t\t\t\t\t请重新输入");
						break;
				}
			if (code_data = 0 || code_data == 1 || code_data == 2)
				break;
			}
			break;
		default:printf("\t\t\t\t\t\t请重新输入");
			break;
		}
		if (code_order == 0 || code_order == 1)
			break;
	}
}

//下面的函数用于将数组随机化。
void f_rand(int a[], int* t) { //随机数
	srand((unsigned)time(NULL));
	for (int i = 0; i < length; i = i + 1) {
		a[i] = rand();
		*t = rand() % 400 - 200;
	}
}

//下面的函数用于加密。
void encrypt(char* location_1, char* code_location) { //加密。加密前的文本位置，密码位置
	FILE* before_encrypt, * after_encrypt, * encrypt; //加密前，After_Encrypt，加密
	char* location_2 = "After_Encrypt.txt"; //After_Encrypt的文本位置
	int ch;
	int a[length]; //存储密码的数组
	int t; //再次加密
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

//下面的函数用于解密。
void decode(char* location_2, char* code_location) { //解密。After_Encrypt的位置，密码位置
	FILE* before_decode, * after_decode, * code; //解密前，After_Decode，密码
	char* location_3 = "After_Decode.txt"; //After_Decode的位置
	int b[length]; //存储已有密码的数组
	int ch;
	int t; //再次加密

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

//人数统计
int statistics(void)
{
	int total=0;
	Node* list;
	list = head;
	for (; list; total++, list = list->next);
	return total-1;
}

//排名
int rank(char id[MAX])
{
	Node* list;
	int ranking = 1;
	list = head;
	for (; list && strcmp(list->data.id, id);ranking++, list = list->next);//ID search
	return ranking;
}

//最值统计
int extreme_value(Node* list, int choice, int code_num)
{
	int extreme = 0 ,mode;
	Node* tail = NULL, *p=list;
	Student temp;
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
	printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-教师   │\n");
	printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
	printf("\n\n");
	printf("\n\n");
	printf("\t\t\t\t\t\t 0——>   最高分\n\n");
	printf("\t\t\t\t\t\t 1——>   最低分\n\n");
	printf("\t\t\t\t\t\t    输入指令编号：\n");
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
				printf("\n\t\t\t\t\t\t      无效指令!");
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
				printf("\n\t\t\t\t\t\t      无效指令!");
				getchar();
				break;
			}
		} while (choice != 0 && choice != 1 && choice != 2);
			return extreme;
	}
	return extreme;
}

//班级均分统计
double average_all(Node* list, int choice, int code_num)//mode==0是仅仅用于计算avr,mode==1用于完整版本输出average
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
				printf("\n\t\t\t\t\t\t      无效指令!");
				getchar();
		}
	} while (choice != 0 && choice != 1 && choice != 2 && choice != 3);
	return avr;
}

//个人均分统计
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
			printf("\n\t\t\t\t\t\t      无效指令!");
			getchar();
			break;
		}
	}while (choice != 0 && choice != 1 && choice != 2 && choice != 3);
	return avr;
}

//班级方差统计
double variance_all(Node* phead) 
{
	double temp = 0;
	int cnt = 0,code_num,choice;
	Node* p = phead;
	double sum_variance_all = 0;
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
	printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-教师   │\n");
	printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
	printf("\n\n");
	printf("\n\n");
	printf("\t\t\t\t\t\t您想算第几次成绩的方差:");
	scanf("%d", &code_num);
	double avr;
	code_num--;
	do {
		system("cls");
		printf("\n\n");
		printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
		printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-教师   │\n");
		printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
		printf("\n\n");
		printf("\n\n");
		printf("\t\t\t\t\t\t\tMENU\n\n");
		printf("\t\t\t\t\t\t 0——>数学波动指数\n\n");
		printf("\t\t\t\t\t\t 1——>英语波动指数\n\n");
		printf("\t\t\t\t\t\t 2——>C语言波动指数\n\n");
		printf("\t\t\t\t\t\t 3——>总分波动指数\n\n");
		printf("\t\t\t\t\t\t    输入指令编号：\n");
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
				printf("\n\t\t\t\t\t\t      无效指令!");
				getchar();
				break;
		}
	} while (choice != 0 && choice != 1 && choice != 2 && choice != 3);
	return sum_variance_all / cnt;
}

//学生成绩方差
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
			printf("\n\t\t\t\t\t\t      无效指令!");
			getchar();
			break;
		}
	} while (choice != 0 && choice != 1 && choice != 2);
	return sum_variance_all / cnt;
}

//生成成绩报告
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
	printf("\n\t\t\t\t\t\t   你在第%d次考试中：\n", code_num);
	printf("\t\t\t数学得分%d，班级排名第%d,", list->data.score[code_num - 1].math, ranking_m);
	if (((float)ranking_m / (float)member) <= 0.2)
		printf("表现优秀，希望继续保持，尽可能努力在难题上有所突破！\n");
	else  if (((float)ranking_m / (float)member) > 0.2 && ((float)ranking_m / (float)member) < 0.6)
		printf("表现不错，希望做得更好，争取下一次考试能再上一层楼！\n");
	else if (((float)ranking_m / (float)member) >= 0.6)
		printf("不太理想，需要好好找下原因，不要急于求成，要多巩固基础哦！\n");

	printf("\t\t\t英语得分%d，班级排名第%d,", list->data.score[code_num - 1].english, ranking_e);
	if (((float)ranking_e / (float)member) <= 0.2)
		printf("表现优秀，希望继续保持，尽可能努力在难题上有所突破！\n");
	else  if (((float)ranking_e / (float)member) > 0.2 && ((float)ranking_e / (float)member) < 0.6)
		printf("表现不错，希望做得更好，争取下一次考试能再上一层楼！\n");
	else if (((float)ranking_e / (float)member) >= 0.6)
		printf("不太理想，需要好好找下原因，不要急于求成，要多巩固基础哦！\n");

	printf("\t\t\tC语言得分%d，班级排名第%d,", list->data.score[code_num - 1].programming, ranking_c);
	if (((float)ranking_c / (float)member) <= 0.2)
		printf("表现优秀，希望继续保持，尽可能努力在难题上有所突破！\n");
	else  if (((float)ranking_c / (float)member) > 0.2 && ((float)ranking_c / (float)member) < 0.6)
		printf("表现不错，希望做得更好，争取下一次考试能再上一层楼！\n");
	else if (((float)ranking_c / (float)member) >= 0.6)
		printf("不太理想，需要好好找下原因，不要急于求成，要多巩固基础哦！\n");

}

//分析界面
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
			printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
			printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-学生   │\n");
			printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
			printf("\n\n");
			printf("\t\t\t\t姓名：%s", temp->data.name);
			printf("\t\t\t\t学号：%s", temp->data.id);
			printf("\n\n");
			printf("\t\t\t\t\t\t\tMENU\n\n");
			printf("\t\t\t\t\t\t 1——>你的平均成绩\n\n");
			printf("\t\t\t\t\t\t 2——>成绩波动指数\n\n");
			printf("\t\t\t\t\t\t 3——>你的成绩报告\n\n");
			printf("\t\t\t\t\t\t 4——>  你的位次\n\n");
			printf("\t\t\t\t\t\t    输入指令编号：\n");
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
				printf("\n\t\t\t\t\t\t      无效指令!");
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
			printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
			printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-教师   │\n");
			printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
			printf("\n\n");
			printf("\n\n");
			printf("\t\t\t\t\t\t\tMENU\n\n");
			printf("\t\t\t\t\t\t 1——>全班平均成绩\n\n");
			printf("\t\t\t\t\t\t 2——>成绩波动指数\n\n");
			printf("\t\t\t\t\t\t 3——> 最高最低分\n\n");
			printf("\t\t\t\t\t\t    输入指令编号：\n");
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
				printf("\t\t\t\t\t\t      无效指令!");
				getchar();
				break;
			}
			if (choice == 1 || choice == 2 || choice == 3 )
				break;
		}
	}
	return change;
}

//数据分析实现
void f_analyze(int change)
{
	Node* temp;
	int choice, code_num,r_num,extreme, code_data;
	temp = search(user);
	system("cls");
	printf("\n\n");
	if (type)
	{
		printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
		printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-教师   │\n");
		printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
		printf("\n\n");
	}
	else
	{
		printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
		printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-学生   │\n");
		printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
		printf("\n\n");
		printf("\t\t\t\t   姓名：%s", temp->data.name);
		printf("\t\t\t\t   学号：%s", temp->data.id);
		printf("\n\n");
	}
	while (1)
	{
		switch (change)
		{
		case 1:
			printf("\n\n");
			printf("\t\t\t\t\t\t    0——>数学平均成绩\n\n");
			printf("\t\t\t\t\t\t    1——>英语平均成绩\n\n");
			printf("\t\t\t\t\t\t    2——>C语言平均成绩\n\n");
			printf("\t\t\t\t\t\t    3——>总分平均成绩\n\n");
			printf("\t\t\t\t\t\t       输入指令编号：\n");
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
					printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-学生   │\n");
					printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\t\t\t\t   姓名：%s", temp->data.name);
					printf("\t\t\t\t   学号：%s", temp->data.id);
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      数学平均分：%.2lf\n\n\n\n\n", avr_m);
					break;
				case 1:
					avr_e = average_one(temp, choice);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-学生   │\n");
					printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\t\t\t\t   姓名：%s", temp->data.name);
					printf("\t\t\t\t   学号：%s", temp->data.id);
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      C语言平均分：%.2lf\n\n\n\n\n", avr_e);
					break;
				case 2:
					avr_c = average_one(temp, choice);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-学生   │\n");
					printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\t\t\t\t   姓名：%s", temp->data.name);
					printf("\t\t\t\t   学号：%s", temp->data.id);
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      英语平均分：%.2lf\n\n\n\n\n", avr_c);
					break;
				case 3:
					avr_a = average_one(temp, choice);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-学生   │\n");
					printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\t\t\t\t   姓名：%s", temp->data.name);
					printf("\t\t\t\t   学号：%s", temp->data.id);
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      总分平均分：%.2lf\n\n\n\n\n", avr_a);
					break;
				default:
					printf("\n\t\t\t\t\t\t         无效指令!\n");
					getchar();
					break;
				}
				if (choice == 0 || choice == 1 || choice == 2 || choice == 3)
					break;
			}
				break;
		case 2://波动指数
			system("cls");
			printf("\n\n");
			printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
			printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-学生   │\n");
			printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
			printf("\n\n");
			printf("\t\t\t\t   姓名：%s", temp->data.name);
			printf("\t\t\t\t   学号：%s", temp->data.id);
			printf("\n\n");
			printf("\t\t\t\t\t\t\t   MENU\n\n");
			printf("\t\t\t\t\t\t    0——>数学波动指数\n\n");
			printf("\t\t\t\t\t\t    1——>英语波动指数\n\n");
			printf("\t\t\t\t\t\t    2——>C语言波动指数\n\n");
			printf("\t\t\t\t\t\t       输入指令编号：\n");
			printf("\t\t\t\t\t\t             ");
			scanf("%d", &choice);
			s = variance_one(search(user),choice);
			printf("\t\t\t\t\t\t       波动指数：%.2lf\n\n\n\n\n", s);
			break;
		case 3://成绩报告
			system("cls");
			printf("\n\n");
			printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
			printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-学生   │\n");
			printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
			printf("\n\n");
			printf("\t\t\t\t   姓名：%s", temp->data.name);
			printf("\t\t\t\t   学号：%s", temp->data.id);
			printf("\n\n");
			printf("\n\n\n\n\t\t\t\t\t\t   您想生成第几次成绩报告:");
			scanf("%d", &code_num);
			report(code_num);
			break;
		case 4://位次排名
			printf("\t\t\t\t\t\t   0-->按数学成绩排序输出\n\n");
			printf("\t\t\t\t\t\t   1-->按英语成绩排序输出\n\n");
			printf("\t\t\t\t\t\t   2-->按c语言成绩排序输出\n\n");
			printf("\t\t\t\t\t\t         请输入：");
			scanf("%d", &code_data);
			printf("\n\t\t\t\t\t\t   您想按第几次成绩排序:");
			scanf("%d", &code_num);
			put_in_order(head,code_data,code_num);
			r_num = rank(user);
			printf("\n\n\t\t\t\t\t\t       本次排名：%d\n\n\n\n\n",r_num);
			break;
		case 5:
			printf("\t\t\t\t\t\t    0——>数学平均成绩\n\n");
			printf("\t\t\t\t\t\t    1——>英语平均成绩\n\n");
			printf("\t\t\t\t\t\t    2——>C语言平均成绩\n\n");
			printf("\t\t\t\t\t\t    3——>总分平均成绩\n\n");
			printf("\t\t\t\t\t\t       输入指令编号：\n");
			printf("\t\t\t\t\t\t             ");
			scanf("%d", &choice);
			printf("\t\t\t\t\t\t   您想算第几次成绩：");
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
					printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-教师   │\n");
					printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      数学平均分：%.2lf\n\n\n\n\n", avr_m);
					break;
				case 1:
					avr_e = average_all(head, choice, code_num);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-教师   │\n");
					printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      C语言平均分：%.2lf\n\n\n\n\n", avr_e);
					break;
				case 2:
					avr_c = average_all(head, choice, code_num);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-教师   │\n");
					printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      英语平均分：%.2lf\n\n\n\n\n", avr_c);
					break;
				case 3:
					avr_a = average_all(head, choice, code_num);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t     │   电子科技大学1605班学生成绩管理系统-教师   │\n");
					printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t      总分平均分：%.2lf\n\n\n\n\n", avr_a);
					break;
				default:
					printf("\n\t\t\t\t\t\t         无效指令!");
					getchar();
					break;
				}
				if (choice == 0 || choice == 1 || choice == 2 || choice == 3)
					break;
			}
			break;
		case 6:
			s = variance_all(head);
			printf("\t\t\t\t\t\t    波动指数：%.2lf\n\n\n\n\n", s);
			break;
		case 7://最值
			system("cls");
			printf("\n\n");
			printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
			printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-教师   │\n");
			printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
			printf("\n\n");
			printf("\n\n");
			printf("\t\t\t\t\t\t 0——>数学成绩最值\n\n");
			printf("\t\t\t\t\t\t 1——>英语成绩最值\n\n");
			printf("\t\t\t\t\t\t 2——>C语言成绩最值\n\n");
			printf("\t\t\t\t\t\t    输入指令编号：\n");
			printf("\t\t\t\t\t\t          ");
			scanf("%d", &choice);
			printf("\t\t\t\t\t\t您想算第几次成绩：");
			scanf("%d", &code_num);
			extreme = extreme_value(head, choice, code_num);
			printf("\t\t\t\t\t\t            %d\n\n\n\n\n",extreme);
			break;
		default:
			printf("\n\t\t\t\t\t\t      无效指令!");
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
	printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
	printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-学生   │\n");
	printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
	printf("\n\n");
	Node* p;
	int choice;
	float avr;
	p = search(user);
	printf("\t\t\t\t\t\t您想查询第几次成绩:");
	scanf("%d", &choice);
	/*while (1) {
		for (p = phead; strcmp(p->data.id, user) && p; p = p->next);
		if (p)
			break;
		else {
			printf("\t\t\t\t\t\t学号不存在！");
				Sleep(1000);
		}
	}*/
	choice--;
	avr = (p->data.score[choice].math + p->data.score[choice].english + p->data.score[choice].programming) / 3;
	if (avr >= 85)
	{
		printf("\n\t\t\t\t\t\t  你太棒了，绩点4.0");
	}
	else if (avr >= 60)
	{
		printf("\n\t\t\t\t\t\t  你的绩点为：%.1f", 4.0 - (85.0 - avr) * 0.1);
	}
	else
	{
		printf("\n\t\t\t\t\t\t      你挂科了");
	}
}

//插入排序
void insert_sort(Node* phead) {
	Node* p = phead;//插入排序法 
	Student temp;
	Node* in_order, * out_order, * temp_order;
	for (out_order = p->next; out_order; out_order = out_order->next) {
		for (in_order = out_order->prior; in_order; in_order = in_order->prior) { //默认第一个数为有序数 
			if (in_order->data.score[0].math > out_order->data.score[0].math)
				break;
		}   //找到分界点 
		if (!in_order) {
			in_order = (Node*)malloc(sizeof(Node)); //此类为特殊情况，当无序值比所有有序值都大时，在链表会导致链表指向空指针，因此需要分配内存空间 
			in_order->next = p;
			p->prior = in_order;
		}
		if (in_order != out_order->prior) {  //可以减少复杂度，当无序比有序数都小时直接结束 
			temp = out_order->data;
			for (temp_order = out_order->prior; temp_order != in_order; temp_order = temp_order->prior)
				temp_order->next->data = temp_order->data;//数据往后移动一位 
			in_order->next->data = temp; //正式将无序数插入 有序数组 
		}
		p->prior = NULL;//需要让头结点恢复原样 
	}
}