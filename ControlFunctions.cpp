#include "snake.h"

//初始化界面  全屏
void InitGame()
{
	initgraph(MAP_WIDTH, MAP_HEIGHT);
	HWND hwnd = GetHWnd();
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, MAP_WIDTH, MAP_HEIGHT, SWP_SHOWWINDOW);
}

//监控按键
void KeyDown()
{
	int key;
	if (_kbhit())
	{
		key = _getch();
		if (key == 0xE0)
		{
			switch (_getch())
			{
			case 72:

				/*printf("UP");*/
				break;
			case 80:
				/*printf("DOWN");*/
				break;
			case 75:
				snake->dir -= MOVE_ANGLE;
				/*printf("LEFT");*/
				break;
			case 77:
				snake->dir += MOVE_ANGLE;
				/*printf("RIGHT");*/
				break;
			}
		}
		else if (key == 27)  //ESC 是 27
		{
			closegraph();
		}
		else if (key == 32)   //暂停
		{
			while (1)
			{
				Sleep(300);
				if (_getch() == 32)     //32是空格
					break;
			}
		}

	}

}

//开始游戏
void StartGame()
{
	int key;
	int flag = 1;
	int count = 0;
	CreateAll();
	snake->score += score;
	BeginBatchDraw();
	while (1)
	{
		KeyDown();
		Move();
		if (TouchHead() == 0)
		{
			ifcontinue = 0;
			break;
		}
		PrintAll();
		PrintScore();
		FlushBatchDraw();
		cleardevice();
		Sleep(1000 / FPS);
		if ( snake->length > 10+hardDegree * 10)
		{
			score = snake->score;
			ifcontinue = 1;
			break;
		}
		score = snake->score;
		count++;
		if (count > 500 &&flag == 1)
		{
			for (Node* p = poison->next; p != NULL; p = p->next)
			{
				p->x = 5555;
				p->y = 5555;
			}
			flag = 0;
		}
	}
	EndBatchDraw();
}

//读入图片
void LoadImages()
{

	loadimage(&imgBK1, "image\\bk1.png", MAP_WIDTH, MAP_HEIGHT);
	loadimage(&imgBK2, "image\\bk2.png", MAP_WIDTH, MAP_HEIGHT);
	loadimage(&imgBK3, "image\\bk3.png", MAP_WIDTH, MAP_HEIGHT);
	loadimage(&imgBK4, "image\\bk4.png", MAP_WIDTH, MAP_HEIGHT); 
	loadimage(&imgBK5, "image\\bk5.png", MAP_WIDTH, MAP_HEIGHT);
	loadimage(&imgBK6, "image\\bk6.png", 550, 300);
	loadimage(&imgBK7, "image\\bk7.png", 550, 300);
	loadimage(&imgBK8, "image\\bk8.png", 550, 300);
	loadimage(&imgBK10, "image\\bk10.png", MAP_WIDTH, MAP_HEIGHT);
	loadimage(&imgBK11, "image\\bk11.png", MAP_WIDTH, MAP_HEIGHT);
	loadimage(&imgBK12, "image\\bk12.png", MAP_WIDTH, MAP_HEIGHT);
	loadimage(&imgHead, "image\\head.jpg", HeadRadius*2, HeadRadius*2);
	loadimage(&imgBody, "image\\body.jpg", BodyRadius*2, BodyRadius*2);
	loadimage(&imgFood, "image\\food.jpg", FoodRadius*2, FoodRadius*2);
	loadimage(&imgWall, "image\\wall.jpg", WallRadius*2, WallRadius*2);
	loadimage(&imgLandmine, "image\\landmine.jpg", LandmineRadius*2, LandmineRadius*2);
	loadimage(&imgPoison, "image\\poison.jpg", PoisonRadius*2, PoisonRadius*2);
}

void MouseChoose()
{
	int key;
	static MOUSEMSG msg;
	msg = GetMouseMsg();
	FlushMouseMsgBuffer();
	if (645 <= msg.x && msg.x <= 870 +150 && 365 <= msg.y && msg.y <=430)
	{
		putimage(0, 0, &imgBK2);
		if (msg.mkLButton)
		{
			setbkcolor(BLACK);
			cleardevice();
			
			PrintChoose();
			setfillcolor(BLACK);
			do 
			{
				StartGame();
				hardDegree++;
				if (hardDegree > 3)
					ifcontinue = 0;
			} while (ifcontinue);

			array[0] = score;
			Sort();
			WriteFile();
			score = 0;

			PrintGameover();
			while (1)
			{
				if (_kbhit())
				{
					key = _getch();
					if (key == 27)    //ESC 是 27
					{
						break;
					}
					else if (key == 9)   //TAB 是 9
					{
						PrintCharts();
						break;
					}
				}
			}
			FreeSnake();

		}
	}
	else if (645 <= msg.x && msg.x <= 860 && 475 <= msg.y && msg.y <= 540)
	{
		putimage(0, 0, &imgBK3);
		if (msg.mkLButton)
		{
			PrintCharts();
		}
	}
	else if (612 <= msg.x && msg.x <= 910 && 595 <= msg.y && msg.y <= 660)
	{
		putimage(0, 0, &imgBK4);
	}
	else if (620 <= msg.x && msg.x <= 925 && 715 <= msg.y && msg.y <= 775)
	{
		putimage(0, 0, &imgBK5);
		if (msg.mkLButton)
		{
			setfillcolor(BLACK);
			while (1)
			{
				msg = GetMouseMsg();
				FlushMouseMsgBuffer();
				putimage(500, 365, &imgBK6);
				if (840 <= msg.x && msg.x <= 1000 && 580 <= msg.y && msg.y <= 610)
				{
					putimage(500, 365, &imgBK7);
					if (msg.mkLButton)
						closegraph();
				}
				else if (540 <= msg.x && msg.x <= 705 && 580 <= msg.y && msg.y <= 610)
				{
					putimage(500, 365, &imgBK8);
					if (msg.mkLButton)
						break;
				}
				Sleep(1000 / FPS);
			}
		}
	}
	else
	{
		putimage(0, 0, &imgBK1);
	}
	//char s[10];
	//sprintf_s(s, "%d", msg.x);
	//outtextxy(MAP_WIDTH - 300, MAP_HEIGHT - 250, s);
	//char c[10];
	//sprintf_s(c, "%d", msg.y);
	//outtextxy(MAP_WIDTH - 300, MAP_HEIGHT - 200, c);
	//Sleep(1000 / FPS);
}

void ReadFile()
{
	int n, m;

	fp = fopen("scores.txt", "r");
	if (fp)
	{

	}
	else
	{
		closegraph();
	}
	for (n = 0; n < 6; n++)
	{
		fscanf(fp, "%d", &m);
		array[n] = m;
	}
	fclose(fp);
	Sort();
}
void WriteFile()
{
	int n, m;
	char s[10];
	fp = fopen("scores.txt", "w");
	for (n = 5; n > 0; n--)
	{
		m = array[n];
		fputs(" ", fp);
		fprintf(fp, "%d", m);
		fputs(" ", fp);
	}
	fclose(fp);
}

void Sort()
{
	int t, i, count;
	int SIZE = 6;
	do {
		count = 0;
		for (i = 0; i < SIZE - 1; i++)
		{
			if (array[i] > array[i + 1])
			{
				t = array[i];
				array[i] = array[i + 1];
				*(array + i + 1) = t;
				count++;
			}
		}
	} while (count != 0);
}