#include "snake.h"

void PrintSnake()
{
	IMAGE imgHead2;
	Node* p = NULL;
	for (p = snake->head->next; p != NULL; p = p->next)
	{
		putimage(p->x, p->y, &imgBody);
	}
	rotateimage(&imgHead2, &imgHead, -snake->dir);
	putimage(snake->head->x, snake->head->y, &imgHead2);
}

void PrintFood()
{
	Node* p = NULL;
	for (p = food; p != NULL; p = p->next)
	{
		putimage(p->x, p->y, &imgFood);
	}
}

void PrintLandmine()
{
	Node* p = NULL;
	for (p = landmine; p != NULL; p = p->next)
	{
		putimage(p->x, p->y, &imgLandmine);
	}
}

void PrintPoison()
{
	Node* p = NULL;
	for (p = poison; p != NULL; p = p->next)
	{
		setfillcolor(RGB(rand() % 255, rand() % 255,rand() % 255));
		fillcircle(p->x, p->y, PoisonRadius);
	}
}

void PrintWall()
{
	Node* p = NULL;
	for (p = wall; p != NULL; p = p->next)
	{
		putimage(p->x, p->y, &imgWall);
	}
}

void PrintAll()
{
	PrintBK();
	PrintSnake();
	PrintFood();
	PrintLandmine();
	PrintPoison();
	PrintWall();
}

void PrintBK()
{
	switch (hardDegree)
	{
	case 1:
		putimage(0, 0, &imgBK10);
		outtextxy(750, 60, "第一关");
		break;
	case 2:
		putimage(0, 0, &imgBK11);
		outtextxy(750, 60, "第二关");
		break;
	case 3:
		putimage(0, 0, &imgBK12);
		outtextxy(750, 60, "第三关");
	}
}

//打印分数
void PrintScore()
{
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(30, 0, "微软雅黑");
	outtextxy(MAP_WIDTH -200,30 , "您目前得分是:");

	// 输出数值，先将数字格式化输出为字符串
	if (snake->score < 0)
		snake->score = 0;
	char s[10];
	sprintf_s(s, "%d", snake->score);
	outtextxy(MAP_WIDTH - 150, 60, s);
}
void PrintGameover()
{
	settextcolor(WHITE);
	setbkcolor(BLACK);
	cleardevice();
	settextstyle(150, 0, "华文行楷");
	outtextxy(500, 50, "游戏结束！");
	settextstyle(80, 0, "华文行楷");
	outtextxy(500, 200, "您本次的得分为:");
	if (snake->score < 0)
		snake->score = 0;
	char s[10];
	settextstyle(80, 0, "微软雅黑");
	sprintf_s(s, "%d", snake->score);
	outtextxy(1100, 200, s);
	settextstyle(100, 0, "微软雅黑");
	outtextxy(500, 400, "按ESC返回到主界面");
	outtextxy(500, 500, "按TAB进入排行榜");
}
void PrintCharts()
{
	ReadFile();
	setbkcolor(RGB(255, 215, 0));
	cleardevice();
	settextcolor(BLACK);
	settextstyle(150, 0, "华文行楷");
	outtextxy(550, 50, "排行榜");
	settextstyle(50, 0, "华文行楷");
	settextstyle(80, 0, "华文行楷");
	outtextxy(350, 220, "名次");
	outtextxy(700, 220, "关卡");
	outtextxy(1050, 220, "得分");

	outtextxy(325, 310, "第一名");
	outtextxy(325, 410, "第二名");
	outtextxy(325, 510, "第三名");
	outtextxy(325, 610, "第四名");
	outtextxy(325, 710, "第五名");

	char s[10];
	settextcolor(BLACK);
	sprintf_s(s, "%d", array[5]);
	outtextxy(1100, 300, s);
	sprintf_s(s, "%d", array[4]);
	outtextxy(1100, 400, s);
	sprintf_s(s, "%d", array[3]);
	outtextxy(1100, 500, s);
	sprintf_s(s, "%d", array[2]);
	outtextxy(1100, 600, s);
	sprintf_s(s, "%d", array[1]);
	outtextxy(1100, 700, s);
	MOUSEMSG msg;
	while (1)
	{
		msg = GetMouseMsg();
		FlushMouseMsgBuffer();
		//char s[10];
		//sprintf_s(s, "%d", msg.x);
		//outtextxy(MAP_WIDTH - 300, MAP_HEIGHT - 250, s);
		//char c[10];
		//sprintf_s(c, "%d", msg.y);
		//outtextxy(MAP_WIDTH - 300, MAP_HEIGHT - 200, c);
		Sleep(1000 / FPS);
		if (0 <= msg.x && msg.x <= 80 && 0 <= msg.y && msg.y <= 50)
		{
			settextstyle(50, 0, "华文行楷");
			settextcolor(RED);
			outtextxy(0, 0, "返回");
			if (msg.mkLButton)
				break;
		}
		else
		{
			settextstyle(50, 0, "华文行楷");
			settextcolor(BLACK);
			outtextxy(0, 0, "返回");
		}

	}
}

void PrintChoose()
{
	int key, flag = 0;
	BeginBatchDraw();
	while (1)
	{
		switch (flag)
		{
		case 0:
			fillcircle(580, 430, 20);
			hardDegree = 1;
			break;
		case 1:
			fillcircle(580, 530, 20);
			hardDegree = 2;
			break;
		case 2:
			fillcircle(580, 630, 20);
			hardDegree = 3;
			break;
		}
		if (_kbhit())
		{
			key = _getch();
			if (key == 0xE0)
			{
				switch (_getch())
				{
				case 72:
					flag--;
					/*printf("UP");*/
					break;
				case 80:
					flag++;
					/*printf("DOWN");*/
					break;
				}
			}
			else if (key == 13)  //Enter 13
				break;
		}
		if (flag > 2)
			flag = 0;
		else if (flag < 0)
			flag = 2;

		settextcolor(RED);
		settextstyle(120, 0, "华文行楷");
		outtextxy(450, 50, "选择关卡难度");
		settextstyle(70, 0, "微软雅黑");
		settextcolor(YELLOW);
		outtextxy(380, 200, "按 ↑  ↓ 切换难度，按ENTER确认");
		settextstyle(80, 0, "华文行楷");
		settextcolor(WHITE);
		outtextxy(600, 400, "简单难度");
		outtextxy(600, 500, "中等难度");
		outtextxy(600, 600, "困难难度");
		setfillcolor(RED);
		FlushBatchDraw();
		cleardevice();
	}
	EndBatchDraw();
}