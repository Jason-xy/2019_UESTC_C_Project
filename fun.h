#ifndef _FUN_
#define _FUN_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

extern Student;

void welcome(void);
void jump(void);
void init_list(void);
Node* search(Node* list, char* id);
Node* add_student(Node* list, char id);
Student write(void);
void delet(Node** list, char *id);
Node* update(Node* list, char *id);
void print_one(Node* list);
void print_all(Node* list);
void modeset(int w, int h);
void analyse(Node *list);
void average(Node *list);
#endif // _FUN_

