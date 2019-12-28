#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include<Windows.h>
#include <conio.h>

/*全局数据*/
#define MAX 30
#define length 1000 //密码个数
int error;//报错检测

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
}Node;

Node* head;//头节点
int type;//账户类型(1-教师，0-学生)
char user[MAX] = { 0 }, pass[MAX] = { 0 };//登录用户
double avr_c, avr_m, avr_e, avr_a, s_c, s_m, s_e, s_a, s;//平均分,方差
int ranking_c, ranking_m, ranking_e;//排名


/*函数声明*/
void headview(void);//图标
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
void put_in_order(Node* phead);//排序函数
void f_rand(int a[], int* t); //随机数
void encrypt(char* location_1, char* code_location); //加密。加密前的文本位置，密码位置
void decode(char* location_2, char* code_location); //解密。After_Encrypt的位置，密码位置
int statistics(void);//人数统计
int rank(char id[MAX]);//排序
int extreme_value(Node* list,int choice);//班级最值统计
double average_all(Node* list, int choice, int code_num);//班级均分统计
double average_one(Node* list, int choice);//个人均分统计
double variance_all(Node* phead);//班级波动指数
int analyze(void);//数据分析界面
void f_analyze(int change);//数据分析实现


int main(void)
{
	//变量定义
	int choice,member;
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
			printf("\t\t\t\t\t\t请输入学号:	");
			error=scanf("%s", id);
			print_one(search(id));
			jump();
			break;
		case 2:
			system("cls");
			headview();
			add_student();
			jump();
			break;
		case 3:
			system("cls");
			headview();
			write();
			jump();
			break;
		case 4:
			system("cls");
			headview();
			printf("\n\n\n\t\t\t\t\t\t请输入学号：");
			error=scanf("%s", id);
			delet(&head, id);
			jump();
			break;
		case 5:

			break;
		case 6:
			save();
			system("cls");
			headview();
			printf("\n\n\n");
			printf("\t\t\t\t\t\t\t保存成功\n\n\n\n\n");
			return 0;
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

/*int main(void)
{
	init_node();
	int member,ranking;
	char id[30];
	member = statistics();
	printf("%d\n", member);
	//scanf("%s", id);
	//ranking = rank(id);
	//printf("%d", ranking);
	save();
}*/

//登录界面
bool login(void)
{
	FILE* apas,*spas,*ause,*suse;
	//apas = "apass.txt";
	//spas = "spass.txt";
	//ause = "auser.txt";
	//suse = "suser.txt";

	int times=0,j = 0,a=1,choice=10;//a用于依次验证密码
	char *USER[MAX] = { 0 },  *PASS[MAX] = { 0 };
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
		spas=fopen("spass.txt", "r+");

		if (spas == NULL) 
		{
			printf("Error: read file failure.\n");
			exit(-1);
		}
			for (int i = 0; i < 30; i++)
			{
				PASS[i] = malloc(sizeof(char*));
				fscanf(spas, "%s", PASS[i]);
			}
		fclose(spas);
		suse=fopen("suser.txt", "r+");
		if (suse == NULL) 
		{
			printf("Error: read file failure.\n");
			exit(-1);
		}
			for (int i = 0; i < 30; i++)
			{
				USER[i] = malloc(sizeof(char*));
				fscanf(suse, "%s", USER[i]);
			}
		fclose(suse);

		//printf("%s\n%s", PASS[1], USER[1]);//文件写入验证
		getchar();
		for (int i = 0; i < 30; i++)
			a *= (!(strcmp(user, USER[i]) == 0 && strcmp(pass, PASS[i]) == 0));//有对则0，全错则1
		while (a)
			{
				times++;	//密码输入错误 times++
				if (times > 3)
				{
					printf("\n\n\n\n\t\t\t\t账号或密码输入错误累计达到%d次，系统将于3秒后关闭", times);
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
				printf("\n\n\n\n\t\t\t\t账号或密码输入错误,你还有%d次登录机会，按任意键重新登录...", 4 - times);
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
		apas=fopen( "apass.txt", "r+");
		if (apas == NULL)
		{
			printf("Error: read file failure.\n");
			exit(-1);
		}
		for (int i = 0; i < 30; i++) {
			PASS[i] = malloc(sizeof(char*));
			fscanf(apas, "%s", PASS[i]);
		}
		fclose(apas);
		ause=fopen( "auser.txt", "r+");
		if (ause == NULL)
		{
			printf("Error: read file failure.\n");
			exit(-1);
		}
		for (int i = 0; i < 30; i++) {
			USER[i] = malloc(sizeof(char*));
			fscanf(ause, "%s", USER[i]);
		}
		fclose(ause);
		for (int i = 0; i < 30; i++)
			a *= (!(strcmp(user, USER[i]) == 0 && strcmp(pass, PASS[i]) == 0));//有对则0，全错则1
			while (a)
			{
				times++;	//密码输入错误 times++
				if (times > 3)
				{
					printf("\n\n\n\n\t\t\t\t账号或密码输入错误累计达到%d次，系统将于3秒后关闭", times);
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
				printf("\n\n\n\n\t\t\t\t账号或密码输入错误,你还有%d次登录机会，按任意键重新登录...", 4 - times);
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
	printf("\n");
	printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
	printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-教师   │\n");
	printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
	printf("\n\n");
	printf("\t\t\t\t\t\t\tMENU\n\n");
	//printf("\t\t\t\t\t\t 0——>查看全班成绩\n\n");
	printf("\t\t\t\t\t\t 1——>查看学生成绩\n\n");
	printf("\t\t\t\t\t\t 2——>新增学生成绩\n\n");
	printf("\t\t\t\t\t\t 3——>修改学生成绩\n\n");
	printf("\t\t\t\t\t\t 4——>删除学生信息\n\n");
	printf("\t\t\t\t\t\t 5——>成绩数据分析\n\n");
	printf("\t\t\t\t\t\t 6——>退出 并 保存\n\n");
	printf("\t\t\t\t\t\t    输入指令编号：\n");
	printf("\t\t\t\t\t\t          ");
	scanf("%d", &choice);
	return choice;
}

//学生端菜单界面
int swelcome(void)
{
	int change,choice=4;//修改传出指令
	system("cls");
	headview();
	printf("\n\n");
	printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
	printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-教师   │\n");
	printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
	printf("\n\n");
	printf("\t\t\t\t\t\t\tMENU\n\n");
	printf("\t\t\t\t\t\t 1——>查看你的成绩\n\n");
	printf("\t\t\t\t\t\t 2——>成绩数据分析\n\n");
	printf("\t\t\t\t\t\t 3——>    退出\n\n");
	printf("\t\t\t\t\t\t    输入指令编号：\n");
	printf("\t\t\t\t\t\t          ");
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
	default:
		break;
	}
	return choice;
}

//窗口初始化
void surface(void)
{
	SetConsoleTitle(L"UESTC_1605班成绩管理系统");
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
	printf("\t\t\t\t\t     ╭  % ╮                   ╭ ```╮  \n");
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
	FILE* txt;
	txt = fopen("std.txt", "r+");
	for (list = head; \
		fscanf(txt, "%s", list->data.name) != EOF; 
		list = list->next)//判断是否读到结尾的同时读入name
	{
		list->data.score->english = list->data.score->math = list->data.score->programming = 0;
		fscanf(txt, "%s", list->data.id);
		for (i = 0; i < 30; i++)
		{
			fscanf(txt, "%d %d %d", &(list->data.score[i].programming), \
				& (list->data.score[i].math), &(list->data.score[i].english));
		}
		(list->next) = (Node*)malloc(sizeof(Node));
	}
	fclose(txt);
	list->next = NULL;
}

//初始化链表
void init_node(void)
{
	head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	load();
}

//打印成绩
void print_one(Node* list)
{
	//list = list->next;测试节点转换
	int n = 1, i = 0;
	printf("\n\n");
	printf("\t\t\t\t\t\t      姓名：%s\n", list->data.name);
	printf("\t\t\t\t\t\t      学号：%s\n", list->data.id);
	printf("\t\t\t\t\t    查看第几次考试(查看全部成绩则忽略)：");
	scanf("%d", &n);
	printf("\n\t\t\t\t\t\tC语言\t数学\t英语\t\n");
	if (n) 
	{
		if (abs(list->data.score[n - 1].programming) >= 10000 && abs(list->data.score[n - 1].english) >= 10000 && abs(list->data.score[n - 1].math) >= 10000)
			list->data.score[n - 1].programming = list->data.score[n - 1].math = list->data.score[n - 1].english = 0;
		printf("\t\t\t\t\t\t%d\t%d\t%d\t\n", list->data.score[n - 1].programming, \
			list->data.score[n - 1].math, list->data.score[n - 1].english);
	}
	else
	{
		for (i; i < 30; i++)
		{
			if (abs(list->data.score[n - 1].programming) >= 10000 && abs(list->data.score[n - 1].english) >= 10000 && abs(list->data.score[n - 1].math) >= 10000)
				list->data.score[n - 1].programming = list->data.score[n - 1].math = list->data.score[n - 1].english = 0;
			printf("\t\t\t\t\t%d\t%d\t%d\t\n", list->data.score[i].programming, \
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
		printf("\t\t\t\t\t\t\th-->Home\n");
		temp = getch();
		switch (temp)
		{
		case 'h':
			save();
			break;
		default:
			printf("\t\t\t\t\t\t      无效指令!");
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
	txt = fopen("std.txt", "w+");
	for (list = head; list->next; list = list->next)
	{
		fprintf(txt, "%s\t", list->data.name);
		fprintf(txt, "%s\t", list->data.id);
		for (int i = 0; i < 30; i++)
		{
			fprintf(txt, "%d\t%d\t%d\t", list->data.score[i].programming, \
				list->data.score[i].math, list->data.score[i].english);
		}
		fprintf(txt, "\n");
	}
	fclose(txt);
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
		printf("\t\t\t\t\t\t第几次考试：");
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
				printf("\n\n\n");
				printf("\t\t\t\t\t\t      0-修改姓名\n\n");
				printf("\t\t\t\t\t\t      1-修改学号\n\n");
				printf("\t\t\t\t\t\t      2-修改C语言成绩\n\n");
				printf("\t\t\t\t\t\t      3-修改数学成绩\n\n");
				printf("\t\t\t\t\t\t      4-修改英语成绩\n\n");
				printf("\t\t\t\t\t\t         请输入：");
				scanf("%d", &n2);
				if (n2 != 0 && n2 != 1)
				{
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
					printf("\n\t\t\t\t\t\t请输入C语言成绩：");
					scanf("%d", &(list->data.score[n3 - 1].programming));
					break;
				case 3:
					printf("\n\t\t\t\t\t\t请输入数学成绩：");
					scanf("%d", &(list->data.score[n3 - 1].math));
					break;
				case 4:
					printf("\n\t\t\t\t\t请输入英语成绩：");
					scanf("%d", &(list->data.score[n3 - 1].english));
					break;
				default:
					printf("\n\t\t\t\t\t\t请重新输入");
					system("pause");
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
void put_in_order(Node* phead)
{          //排序，不输出
	int code_order, code_data, code_num;
	Node* p = phead;
	Node* tail = NULL;
	Student temp;
	//printf("\t\t\t\t\t\t0-->由高到低排序输出");
	//printf("\t\t\t\t\t\t1-->由低到高排序输出");
	//printf("\t\t\t\t\t\t      请输入：");
	//scanf("%d", &code_order);
	code_order = 0;
	printf("\t\t\t\t\t\t0-->按数学成绩排序输出");
	printf("\t\t\t\t\t\t1-->按英语成绩排序输出");
	printf("\t\t\t\t\t\t2-->按c语言成绩排序输出");
	printf("\t\t\t\t\t\t      请输入：");
	scanf("%d", &code_data);
	printf("\t\t\t\t\t\t您想按第几次成绩排序:");
	scanf("%d", &code_num);
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
	int extreme,mode;
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
	scanf("%d", mode);
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
				printf("\t\t\t\t\t\t      无效指令!");
				getchar();
				break;
			}
		} while (choice != 0 || choice != 1 || choice != 2);
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
				printf("\t\t\t\t\t\t      无效指令!");
				getchar();
				break;
			}
		} while (choice != 0 || choice != 1 || choice != 2);
			return extreme;
	}
}

//班级均分统计
double average_all(Node* list, int choice, int code_num)//mode==0是仅仅用于计算avr,mode==1用于完整版本输出average
{   
	double avr = 0;
	int sum = 0, cnt = 0;
	Node* temp;
	temp = search(user);
	do {
		switch (choice) 
		{
			case 0:
				for (; list; list = list->next)
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
				for (; list; list = list->next) 
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
				for (; list; list = list->next) 
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
				for (; list; list = list->next) 
				{
					if ((list->data.score[code_num].math != 0) && (list->data.score[code_num].english != 0) && (list->data.score[code_num].programming != 0))
					{
						sum = list->data.score[code_num].math + list->data.score[code_num].english + list->data.score[code_num].programming;
						cnt++;
					}
				}
				avr = sum / cnt;
				break;
			default:
				printf("\t\t\t\t\t\t      无效指令!");
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
			printf("\t\t\t\t\t\t      无效指令!");
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
	printf("\t\t\t\t\t\t您想算第几次成绩的方差:\n");
	scanf("%d", &code_num);
	double avr;
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
		switch (choice) 
		{
			case 0:
				for (; p; p = p->next) 
				{
					if (p->data.score[code_num].math != 0)
					{
						temp = pow(abs(p->data.score[code_num].math - avr), 2);
						sum_variance_all += temp;
						cnt++;
					}
				}
				s_m = sum_variance_all / cnt;
					return sum_variance_all / cnt;
				break;
			case 1:
				for (; p; p = p->next) 
				{
					if (p->data.score[code_num].english != 0)
					{
						temp = pow(abs(p->data.score[code_num].english - avr), 2);
						sum_variance_all += temp;
						cnt++;
					}
				}
				s_e = sum_variance_all / cnt;
					return sum_variance_all / cnt;
				break;
			case 2:
				for (; p; p = p->next) 
				{
					if (p->data.score[code_num].programming != 0)
					{
						temp = pow(abs(p->data.score[code_num].programming - avr), 2);
						sum_variance_all += temp;
						cnt++;
					}
				}
				s_c = sum_variance_all / cnt;
					return sum_variance_all / cnt;
				break;
			case 3:
				for (; p; p = p->next) 
				{
					if ((p->data.score[code_num].math != 0) && (p->data.score[code_num].english != 0) && (p->data.score[code_num].programming != 0))
					{
						temp = pow(abs(p->data.score[code_num].programming + p->data.score[code_num].math + p->data.score[code_num].english - avr), 2);
						sum_variance_all += temp;
						cnt++;
					}
				}
				s_a = sum_variance_all / cnt;
					return sum_variance_all / cnt;
				break;
			default:
				printf("\t\t\t\t\t\t      无效指令!");
				getchar();
				break;
		}
	} while (choice != 0 && choice != 1 && choice != 2 && choice != 3);
}

//学生成绩方差
double variance_one(Node* p, int choice)
{
	double temp = 0;
	int cnt = 0,  choice;
	double sum_variance_all = 0;
	double avr;
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
	printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-学生   │\n");
	printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
	printf("\n\n");
	printf("\t\t\t\t姓名：%s", p->data.name);
	printf("\t\t\t\t学号：%s", p->data.id);
	printf("\n\n");
	printf("\t\t\t\t\t\t\tMENU\n\n");
	printf("\t\t\t\t\t\t 0——>数学波动指数\n\n");
	printf("\t\t\t\t\t\t 1——>英语波动指数\n\n");
	printf("\t\t\t\t\t\t 2——>C语言波动指数\n\n");
	printf("\t\t\t\t\t\t    输入指令编号：\n");
	printf("\t\t\t\t\t\t          ");
	scanf("%d", &choice);
	avr = average_one(p, choice);
}

//分析界面
int analyze(void)
{
	int choice,change;
	headview();
	if (type)
	{
		Node* temp;
		temp = search(user);
		while (1)
		{
			system("cls");
			printf("\n\n");
			printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
			printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-教师   │\n");
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
				printf("\t\t\t\t\t\t      无效指令!");
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
	char id[MAX];
	int choice, code_num,r_num,extreme;;
	temp = search(user);
	system("cls");
	printf("\n\n");
	if (type)
	{
		printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
		printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-教师   │\n");
		printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
		printf("\n\n");
	}
	else
	{
		printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
		printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-学生   │\n");
		printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
		printf("\n\n");
		printf("\t\t\t\t姓名：%s", temp->data.name);
		printf("\t\t\t\t学号：%s", temp->data.id);
		printf("\n\n");
	}
	while (1)
	{
		switch (change)
		{
		case 1:
			printf("\t\t\t\t\t\t 0——>数学平均成绩\n\n");
			printf("\t\t\t\t\t\t 1——>英语平均成绩\n\n");
			printf("\t\t\t\t\t\t 2——>C语言平均成绩\n\n");
			printf("\t\t\t\t\t\t 3——>总分平均成绩\n\n");
			printf("\t\t\t\t\t\t    输入指令编号：\n");
			printf("\t\t\t\t\t\t          ");
			scanf("%d", &choice);
			while (1)
			{
				switch (choice)
				{
				case 0:
					avr_m = average_one(temp, choice);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-学生   │\n");
					printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\t\t\t\t姓名：%s", temp->data.name);
					printf("\t\t\t\t学号：%s", temp->data.id);
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t    数学平均分：%.2lf", avr_m);
					break;
				case 1:
					avr_e = average_one(temp, choice);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-学生   │\n");
					printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\t\t\t\t姓名：%s", temp->data.name);
					printf("\t\t\t\t学号：%s", temp->data.id);
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t    C语言平均分：%.2lf", avr_e);
					break;
				case 2:
					avr_c = average_one(temp, choice);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-学生   │\n");
					printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\t\t\t\t姓名：%s", temp->data.name);
					printf("\t\t\t\t学号：%s", temp->data.id);
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t    英语平均分：%.2lf", avr_c);
					break;
				case 3:
					avr_a = average_one(temp, choice);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-学生   │\n");
					printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\t\t\t\t姓名：%s", temp->data.name);
					printf("\t\t\t\t学号：%s", temp->data.id);
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t    总分平均分：%.2lf", avr_a);
					break;
				default:
					printf("\t\t\t\t\t\t      无效指令!");
					getchar();
					break;
				}
				if (choice == 0 || choice == 1 || choice == 2 || choice == 3)
					break;
			}
				break;
		case 2://波动指数

			break;
		case 3://成绩报告

			break;
		case 4://位次排名
			put_in_order(head);
			r_num = rank(user);
			printf("\t\t\t\t\t\t    本次排名：%d",r_num);
			break;
		case 5:
			printf("\t\t\t\t\t\t 0——>数学平均成绩\n\n");
			printf("\t\t\t\t\t\t 1——>英语平均成绩\n\n");
			printf("\t\t\t\t\t\t 2——>C语言平均成绩\n\n");
			printf("\t\t\t\t\t\t 3——>总分平均成绩\n\n");
			printf("\t\t\t\t\t\t    输入指令编号：\n");
			printf("\t\t\t\t\t\t          ");
			scanf("%d", &choice);
			printf("\t\t\t\t\t\t您想算第几次成绩：");
			scanf("%d", &code_num);
			while (1)
			{
				switch (choice)
				{
				case 0:
					avr_m = average_all(head, choice, code_num);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-教师   │\n");
					printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t    数学平均分：%.2lf", avr_m);
					break;
				case 1:
					avr_e = average_all(head, choice, code_num);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-教师   │\n");
					printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t    C语言平均分：%.2lf", avr_e);
					break;
				case 2:
					avr_c = average_all(head, choice, code_num);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-教师   │\n");
					printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\tt\    英语平均分：%.2lf", avr_c);
					break;
				case 3:
					avr_a = average_all(head, choice, code_num);
					system("cls");
					printf("\n\n");
					printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
					printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-教师   │\n");
					printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
					printf("\n\n");
					printf("\n\n");
					printf("\t\t\t\t\t\t    总分平均分：%.2lf", avr_a);
					break;
				default:
					printf("\t\t\t\t\t\t      无效指令!");
					getchar();
					break;
				}
				if (choice == 0 || choice == 1 || choice == 2 || choice == 3)
					break;
			}
			break;
		case 6:
			s = variance_all(head);
			printf("\t\t\t\t\t\t    波动指数：%.2lf", s);
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
			printf("\t\t\t\t\t\t            %d",extreme);
			break;
		default:
			printf("\t\t\t\t\t\t      无效指令!");
			getchar();
			break;
		}
		if (change == 7 || change == 1 || change == 2 || change == 3 || change == 4 || change == 5 || change == 6)
			break;
	}
}
