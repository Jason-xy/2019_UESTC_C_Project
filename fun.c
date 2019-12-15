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
	int programming = 0;
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
void load(void);
Node* search(Node* list, char* id)；
Node* add_student(Node* list, char id)；
Student write(void)；
void delet(Node** list, char* id)；
void update(Node* list, char id)；
void welcome(void)；
void print_one(Node* list)；
void put_in_order(Node *phead);
void jump(void)；
void save(void);
void modeset(int w, int h)；

/*************
****函数体*****
**************/


void load(void)
{
	int i=0;
	Node* list;
	FIEL* std.txt;
	txt=FIEL;
	fopen(txt,"r+");
	for(list=head,i=0;\
	fscanf_s(txt,"%s",list->data.name,MAX)!=EOF;i++,\
	(list->next)=(Node*)malloc(sizeof(Node)),list=list->next)
	{
	fscanf_s(txt,"%s",list->data.name,MAX);
	fscanf_s(txt,"%s",list->data.id,MAX);
	fscanf_s(txt,"%d",&(list->data.score[i].math));
	fscanf_s(txt,"%d",&(list->data.score[i].english));
	fscanf_s(txt,"%d",&(list->data.score[i].programming));
	}
	fclose(txt);
}

//初始化函数
void init_node(void)
{
	Node* head;
	head = (Node*)malloc(sizeof(Node));
	load();
}

//链表搜索
Node* search(Node* list, char* id)
{
	for (; list && !strcmp(list->data.id, id); list = list->next);//ID search
	return list;
}


//节点添加
Node* add_student(Node* list)//在最后一个添加一个成员,list为头结点
{
	for (; list; list = list->next);
	(list->next) = (Node*)malloc(sizeof(Node));
	Node* new_member = list->next;
	printf("请输入新成员的id\n");
	scanf_s("%s", new_member->data.id);
	printf("请输入新成员的姓名\n");
	scanf_s("%s", new_member->data.name);
}


//修改信息
Student write(void)
{
	Student data;
	int n1, n2, n3,times;
	printf("修改单项信息输入0\n填入全部信息输入1\n");
	scanf_s("%d", &n1);
	switch (n1)
	{
	case 0:
		printf("0-修改姓名\n1-修改学号\n2-修改C语言成绩\n\
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
			scanf_s("%d", &data.score[n3-1],programming);
			break;
		case 3:
			scanf_s("%d", &data.score[n3-1],math);
			break;
		case 4:
			scanf_s("%d", &data.score[n3-1],english);
			break;
		default:
			printf("Error");
			break;
		}
		break;
	case 1:
		printf("请输入姓名：");
		scanf_s("%s", data.name);
		printf("\n请输入学号：");
		scanf_s("%s", data.id);
		printf("",times);
		scanf_s("%d",&times);
		printf("\n请输入分数(C语言-数学-英语)：");
		scanf_s("%d-%d-%d", &data.score[times-1].programming,\
		&data.score[times-1].math, &data.score[times-1].english);
		break;
	default:
		break;
	}
}


//删除链表节点
void  delet(Node** list, char *id)				//void函数可以减少赋值一步，避免出错；
{
	Node* p = (*list);
	Node* q; //跟随指针
	if (!strcmp(p->data.id, *id)) {		//第一个数据就是所找数据时的特殊情况
		(*list) = (*list)->next;   //删除第一个结点
	}
	else {
		for (; p && strcmp(p->data.id, *id); q = p, p = p->next);
		if (!p)
			printf("unknown id"); else {
			q->next = p->next;    //将跟随指针跳过所删除的结点，指向下一个
		}
	}

}

//更新信息
void update(Node* list, char id)
{
	(search(list,id)->data)=write();
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
	printf("姓名：%s", *(list->data.name));
	printf("学号：%s", *(list->data.id));
	printf("查看第几次考试(查看全部成绩则忽略)：");
	scanf_s("%d", n);
	printf("成绩：\nC语言\t数学\t英语\t\n");
	if (n)
		printf("%d\t%d\t%d\t\n", list->data.score[*n - 1].program, \
			list->data.score[*n - 1].math, list->data.score[*n - 1].english);
	else
		for (int i = 0; i < 30; i++)
			printf("%d\t%d\t%d\t\n", list->data.score[i].program, \
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
	case 113: save();
		EXIT_SUCCESS;
	default:
		printf("Error");
		goto begain;
		break;
	}
}

void save(void)
{
	
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
void put_in_order(Node *phead) {          //排序，不输出
	int code_order,code_data;
	Student temp;
	printf("由高到低排序输入0，由低到高排序输入1\n");
	scanf("%d",&code_order);
	printf("按数学成绩排序输入0，按英语成绩排序输入1，按c语言成绩排序输入2，按总成绩排名输入3");
	printf("%d", &code_data);
		switch (code_order) {
		case 0:
			switch (code_data) {
			case 0:
				for (; phead->next; phead = phead->next) {
					if ((phead->data.score.math) < (phead->next->data.score.math)) {
						temp = (phead->next->data);//交换结构
						(phead->next->data) = phead->data;
						phead->data = temp;
					}
				}break;
			case 1:
				for (; phead->next; phead = phead->next) {
				if ((phead->data.score.english) < (phead->next->data.score.english)) {
					temp = (phead->next->data);//交换结构
					(phead->next->data) = phead->data;
					phead->data = temp;
				}
			}break;
			case 2:
				for (; phead->next; phead = phead->next) {
					if ((phead->data.score.programming) < (phead->next->data.score.programming)) {
						temp = (phead->next->data);//交换结构
						(phead->next->data) = phead->data;
						phead->data = temp;
					}
				}
				break;
			default:printf("undefined code");
			}break;
		case 1:
			switch (code_data) {
			case 0:
				for (; phead->next; phead = phead->next) {
					if ((phead->data.score.math)>(phead->next->data.score.math)) {
						temp = (phead->next->data);//交换结构
						(phead->next->data) = phead->data;
						phead->data = temp;
					}
				}break;
			case 1:
				for (; phead->next; phead = phead->next) {
					if ((phead->data.score.english) > (phead->next->data.score.english)) {
						temp = (phead->next->data);//交换结构
						(phead->next->data) = phead->data;
						phead->data = temp;
					}
				}break;
			case 2:
				for (; phead; phead = phead->next) {
					if ((phead->data.score.programming) > (phead->next->data.score.programming)) {
						temp = (phead->next->data);//交换结构
						(phead->next->data) = phead->data;
						phead->data = temp;
					}
				}
				break;
			default:printf("undefined code");
			}break;
		default:printf("undefined code");
	}

