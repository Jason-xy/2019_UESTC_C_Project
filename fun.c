#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#
#include"fun.h"

#define MAX 30

/*************
***变量定义****
**************/

typedef struct {
	int math = 0;
	int english = 0;
	int chinese = 0;
}Score;


typedef struct {
	char name[30] = { 0 };
	char id[30] = { 0 };
	Score score[30];
}Student;

typedef struct node {
	Student data;
	struct node* next;
}Node;

/*************
***函数声明****
**************/
void init_node(void)；
Node* search(Node* list, char* id)；
Node* add_student(Node* list, char id)；
Student write(void)；
Node* delet(Node* list, char id)；
Node* update(Node* list, char id)；
void welcome(void)；
void print_one(Node* list)；
void jump(void)；
void modeset(int w, int h)；

/*************
****函数体****
**************/

//初始化函数
void init_node(void)
{
	Node* head;
	head = (Node*)malloc(sizeof(Node));
	//后续文件读写储存功能，方便转移与多次使用。
}

//链表搜索
Node* search(Node* list, char* id)
{
	for (; list && !strcmp(list->data.id, id); list = list->next);
	return list;
}


//节点添加
Node* add_student(Node* list, char id)
{

}


//修改信息
Student write(void)
{
	Student data;
	int n1, n2, n3;
	printf("修改单项信息输入0\n填入全部信息输入1\n");
	scanf_s("%d", &n1);
	switch (n1)
	{
	case 0:
		printf("0-修改姓名\n1-修改学号\n2-修改语文成绩\n\
3-修改数学成绩\n4-修改英语成绩\n");
		scanf_s("%d", &n2);
		printf("修改第几次成绩：\n");
		scanf_s("%d", &n3);
		switch (n2)
		{
		case 0:
			fgets(data.name, MAX, stdin);
			break;
		case 1:
			fgets(data.id, MAX, stdin);
			break;
		case 2:
			scanf_s("%d", &data.score->chinese);
			break;
		case 3:
			scanf_s("%d", &data.score->math);
			break;
		case 4:
			scanf_s("%d", &data.score->english);
			break;
		default:
			printf("Error");
			break;
		}
		break;
	case 1:
		printf("请输入姓名：");
		scanf_s("%s", &data.name);
		printf("\n请输入学号：");
		scanf_s("%s", &data.id);
		printf("\n请输入分数(语文-数学-英语)：");
		scanf_s("%d-%d-%d", &data.score->chinese, &data.score->math, &data.score->english);
		break;
	default:
		break;
	}
}


//删除链表节点
Node* delet(Node* list, char id)
{

}

//更新信息
Node* update(Node* list, char id)
{

}

//菜单栏
void welcome(void)
{
modeset(40, 30);
	SetConsoleTitle("UESTC_1605班成绩管理系统");
	for (int i = 0; i < 5; i++)
		printf(" ");
	for (int i = 0; i < 30; i++)
		printf("*");
	for (int i = 0; i < 5; i++)
		printf(" ");
	printf("\n     *        电子科技大学        *     \n     *    ***    1605班    ***    *     \n     *        成绩管理系统        *     \n");//5+8，5+7，5+8个空格
	for (int i = 0; i < 5; i++)
		printf(" ");
	for (int i = 0; i < 30; i++)
		printf("*");
	for (int i = 0; i < 5; i++)
		printf(" ");
	//TODO 登录验证组件
	printf("\n\n\n");
	printf("                  MENU                  \n\n");
	printf("          0——>查看全班成绩\n");
	printf("          1——>查看学生成绩\n");
	printf("          2——>新增学生成绩\n");
	printf("          3——>修改学生成绩\n");
	printf("          4——>删除学生成绩\n");
	printf("          5——>成绩数据分析\n");
	printf("          6——>退出 并 保存\n\n");
	printf("             输入指令编号：\n");
	printf("                  ");
	//scanf_s("%d", choice); 记得下一个函数调用choice.
}

//打印成绩
void print_one(Node* list)
{
	int* n = NULL;
	printf("姓名：%s", &list->data.name);
	printf("学号：%s", list->data.id);
	printf("查看第几次考试(查看全部成绩则忽略)：");
	scanf_s("%d", n);
	printf("成绩：\n语文\t数学\t英语\t\n");
	if (n)
		printf("%d\t%d\t%d\t\n", list->data.score[*n - 1].chinese, \
			list->data.score[*n - 1].math, list->data.score[*n - 1].english);
	else
		for (int i = 0; i < 30; i++)
			printf("%d\t%d\t%d\t\n", list->data.score[i].chinese, \
				list->data.score[i].math, list->data.score[i].english);
}

//跳转界面
void jump(void)
{
	char temp;
begain:printf("请输入h返回主页面\n输入q退出");
	temp = getchar();
	switch (temp)
	{
	case 104:welcome();
		break;
	case 113: EXIT_SUCCESS;
	default:
		printf("Error");
		goto begain;
		break;
	}
}

//窗口大小控制
void modeset(int w, int h)
{
	//	此函数设置窗口大小为 w*h
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size = { w, h };
	SetConsoleScreenBufferSize(hOut, size);
	SMALL_RECT rc = { 1,1, w, h };
	SetConsoleWindowInfo(hOut, 1, &rc);
	return;
}

