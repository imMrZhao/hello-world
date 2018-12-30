#ifndef __SNAKE_HEAD__
#define __SNAKE_HEAD__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <graphics.h>

#define FPS	60  //帧数
#define PI 3.1415926535897932384626433832795
#define MAP_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define MAP_HEIGHT GetSystemMetrics(SM_CYSCREEN)
#define MOVE_DIS 1 //蛇每次移动的距离
#define MOVE_ANGLE 20 * PI / 180 //蛇每次转动的角度

#define SNAKE_SIZE 10
#define FOOD_SIZE 10
#define POISON_SIZE 10

#define FoodRadius 15
#define PoisonRadius 15
#define HeadRadius 15
#define BodyRadius 15
#define LandmineRadius 15
#define WallRadius 15

#define HEAD 1
#define BODY 2
#define WALL 3
#define FOOD 4
#define POISON 5
#define LANDMINE 6

typedef struct _node {
	float x;
	float y;
	int radius;
	struct _node* previous;
	struct _node* next;
}Node;

typedef struct _snake {
	Node* head;
	Node* tail;
	int speed;
	int length;
	double dir;
	int score;
}Snake;


extern IMAGE imgHead, imgBody, imgFood, imgLandmine, imgPoison,imgWall;
extern IMAGE  imgBK1, imgBK2, imgBK3, imgBK4, imgBK5, imgBK6, imgBK7, imgBK8, imgBK9, imgBK10,imgBK11,imgBK12;
extern Snake *snake;
extern Node *food, *poison, *landmine, *wall;

extern FILE *fp;
extern int array[6];
extern int hardDegree;
extern int score;
extern int ifcontinue;

//TheSnake
void CreateSnake();
void ClearTail();
void AddHead();
void Move();
void FreeSnake();
int CheckThings(Node *p1, Node* p2, int level);
int CheckSnake(Node* thing);
int TouchThings(Node* thing, int level);
int TouchHead();

int CheckOneToAll(Node* one, Node* All);
int CheckCreate(Node *one);

//CreateFunctions
void CreateThings(Node* thing);
void CreateFood();
void CreatePoison();
void CreateLandmine();
void CreateAll();
void FreeThings(Node *thing);
void FreeAll();
void CreateWall();

//PrintFunctions
void PrintSnake();
void PrintFood();
void PrintLandmine();
void PrintPoison();
void PrintWall();
void PrintAll();
void PrintBK();
void PrintScore();
void PrintGameover();
void PrintCharts();
void PrintChoose();

//ControlFunctions
void InitGame();
void KeyDown();
void StartGame();
void LoadImages();
void MouseChoose();
void Sort();
void ReadFile();
void WriteFile();


#endif
