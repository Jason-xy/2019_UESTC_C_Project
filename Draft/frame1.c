#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<Windows.h>
#include <conio.h>
/*全局数据*/
#define MAX 30
/*函数声明*/
void head(void);//图标
SMALL_RECT SizeOfWindow(HANDLE hConsoleOutput);//窗口
void modeset(int w, int h);//窗口
void surface(void);//窗口初始化
bool login(void);//登录
int awelcome(void);//管理员主菜单，返回选项
int swelcome(void);//学生主菜单，返回选项




int main(void)
{
	//变量定义
	int choice;

	//窗台美化
	surface();

	//用户登录|菜单选择
	if (login() == 1)
		choice = awelcome();
	else
		choice = swelcome();

	//功能实现
	switch (choice)
	{
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		break;
	default:
		break;
	}
	//printf("OKKKK");运行终点验证
	//getchar();
	return 0;
}

//登录界面
bool login(void)
{
	FILE* apas,*spas,*ause,*suse;
	//apas = "apass.txt";
	//spas = "spass.txt";
	//ause = "auser.txt";
	//suse = "suser.txt";

	int times=0,j = 0,a=1,choice;//a用于依次验证密码
	char user[MAX] = { 0 }, pass[MAX] = { 0 };
	char *USER[MAX] = { 0 },  *PASS[MAX] = { 0 };
	again:system("cls");
	head();
	printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
	printf("\t\t\t\t     │      电子科技大学1605班学生成绩管理系统     │\n");
	printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t你的账户类型？   1——>学生 | 2——>教师\n\n");
	printf("\t\t\t\t\t\t\t你的选择：");
	scanf_s("%d", &choice);
	system("cls");
	begain:head();
	printf("\t\t\t\t     ╭ ==============================○●○●======╮\n");
	printf("\t\t\t\t     │      电子科技大学1605班学生成绩管理系统     │\n");
	printf("\t\t\t\t     ╰ ======○●○●==============================╯\n");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t   用户名:	");
	scanf_s("%s", user,MAX - 1);
	printf("\n\t\t\t\t\t   密码:	");
	scanf_s("%s",pass, MAX - 1);
	//printf("%s\n%s", user, pass);输入验证
	switch (choice)
	{
	case 1:
		spas=fopen("spass.txt", "rt+");

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
		fopen_s(&suse, "suser.txt", "r+");
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
		fopen_s(&ause, "auser.txt", "r+");
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
	int choice;
	system("cls");
	head();
	printf("\n\n");
	printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
	printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-教师   │\n");
	printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
	printf("\n\n");
	printf("\t\t\t\t\t\t\tMENU\n\n");
	printf("\t\t\t\t\t\t 0——>查看全班成绩\n\n");
	printf("\t\t\t\t\t\t 1——>查看学生成绩\n\n");
	printf("\t\t\t\t\t\t 2——>新增学生成绩\n\n");
	printf("\t\t\t\t\t\t 3——>修改学生成绩\n\n");
	printf("\t\t\t\t\t\t 4——>删除学生成绩\n\n");
	printf("\t\t\t\t\t\t 5——>成绩数据分析\n\n");
	printf("\t\t\t\t\t\t 6——>退出 并 保存\n\n");
	printf("\t\t\t\t\t\t    输入指令编号：\n");
	printf("\t\t\t\t\t\t          ");
	scanf_s("%d", choice);
	return choice;
}

//学生端菜单界面
int swelcome(void)
{
	int change,choice;//修改传出指令
	system("cls");
	head();
	printf("\n\n");
	printf("\t\t\t\t  ╭ ==============================○●○●======╮\n");
	printf("\t\t\t\t  │   电子科技大学1605班学生成绩管理系统-教师   │\n");
	printf("\t\t\t\t  ╰ ======○●○●==============================╯\n");
	printf("\n\n");
	printf("\t\t\t\t\t\t\tMENU\n\n");
	printf("\t\t\t\t\t\t 1——>查看你的成绩\n\n");
	printf("\t\t\t\t\t\t 2——>成绩数据分析\n\n");
	printf("\t\t\t\t\t\t 3——>退出 并 保存\n\n");
	printf("\t\t\t\t\t\t    输入指令编号：\n");
	printf("\t\t\t\t\t\t          ");
	scanf("%d", &change);
	switch (choice)
	{
	case 1:choice = 1;
		break;
	case 2:choice = 5;
		break;
	case 3:choice = 6;
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
	head();
	printf("\n\n\t\t\t\t\t这是一个看似简单，却拥有无限可能的成绩系统！\n");
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
void head(void)
{
	printf("\n");
	printf("\t\t\t\t\t     ╭  % ╮                   ╭ ```╮  \n");
	printf("\t\t\t\t\t     (@^o^@) 学生成绩管理系统 (⌒:⌒)\n");
	printf("\t\t\t\t\t     (~):(~)                  (~)v(~) \n");
	printf("\n\n");
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
