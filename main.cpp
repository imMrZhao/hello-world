#include "snake.h"

IMAGE imgHead, imgBody, imgFood, imgLandmine, imgPoison, imgWall;
IMAGE  imgBK1, imgBK2, imgBK3, imgBK4, imgBK5,imgBK6,imgBK7,imgBK8,imgBK9, imgBK10,imgBK11,imgBK12;
Snake *snake = NULL;
Node *food;
Node *poison;
Node *landmine;
Node *wall;

FILE *fp;
int array[6] = { 0 };

int hardDegree = 0;
int score;
int ifcontinue = 0;

int main(int argc, char *argv[])
{
	ReadFile();
	LoadImages();
	InitGame();
	putimage(0, 0, &imgBK1);
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(30, 0, "Î¢ÈíÑÅºÚ");

	while (1)
	{
		MouseChoose();

	}

	return 0;
}
