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
		outtextxy(750, 60, "��һ��");
		break;
	case 2:
		putimage(0, 0, &imgBK11);
		outtextxy(750, 60, "�ڶ���");
		break;
	case 3:
		putimage(0, 0, &imgBK12);
		outtextxy(750, 60, "������");
	}
}

//��ӡ����
void PrintScore()
{
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(30, 0, "΢���ź�");
	outtextxy(MAP_WIDTH -200,30 , "��Ŀǰ�÷���:");

	// �����ֵ���Ƚ����ָ�ʽ�����Ϊ�ַ���
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
	settextstyle(150, 0, "�����п�");
	outtextxy(500, 50, "��Ϸ������");
	settextstyle(80, 0, "�����п�");
	outtextxy(500, 200, "�����εĵ÷�Ϊ:");
	if (snake->score < 0)
		snake->score = 0;
	char s[10];
	settextstyle(80, 0, "΢���ź�");
	sprintf_s(s, "%d", snake->score);
	outtextxy(1100, 200, s);
	settextstyle(100, 0, "΢���ź�");
	outtextxy(500, 400, "��ESC���ص�������");
	outtextxy(500, 500, "��TAB�������а�");
}
void PrintCharts()
{
	ReadFile();
	setbkcolor(RGB(255, 215, 0));
	cleardevice();
	settextcolor(BLACK);
	settextstyle(150, 0, "�����п�");
	outtextxy(550, 50, "���а�");
	settextstyle(50, 0, "�����п�");
	settextstyle(80, 0, "�����п�");
	outtextxy(350, 220, "����");
	outtextxy(700, 220, "�ؿ�");
	outtextxy(1050, 220, "�÷�");

	outtextxy(325, 310, "��һ��");
	outtextxy(325, 410, "�ڶ���");
	outtextxy(325, 510, "������");
	outtextxy(325, 610, "������");
	outtextxy(325, 710, "������");

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
			settextstyle(50, 0, "�����п�");
			settextcolor(RED);
			outtextxy(0, 0, "����");
			if (msg.mkLButton)
				break;
		}
		else
		{
			settextstyle(50, 0, "�����п�");
			settextcolor(BLACK);
			outtextxy(0, 0, "����");
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
		settextstyle(120, 0, "�����п�");
		outtextxy(450, 50, "ѡ��ؿ��Ѷ�");
		settextstyle(70, 0, "΢���ź�");
		settextcolor(YELLOW);
		outtextxy(380, 200, "�� ��  �� �л��Ѷȣ���ENTERȷ��");
		settextstyle(80, 0, "�����п�");
		settextcolor(WHITE);
		outtextxy(600, 400, "���Ѷ�");
		outtextxy(600, 500, "�е��Ѷ�");
		outtextxy(600, 600, "�����Ѷ�");
		setfillcolor(RED);
		FlushBatchDraw();
		cleardevice();
	}
	EndBatchDraw();
}