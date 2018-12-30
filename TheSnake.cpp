#include "snake.h"

//����һ���� ֻ����ͷ
void CreateSnake()
{
	snake = (Snake*)malloc(sizeof(Snake));
	snake->length = 1;
	snake->dir = 0;
	snake->speed = hardDegree ;
	snake->score = 0;

	snake->head = NULL;
	AddHead();

}
//����β���һ��
void ClearTail()
{
	Node* p = NULL;
	p = snake->tail;
	p->previous->next = NULL;
	snake->tail = p->previous;

	free(p);
}
//����β���һ��
void AddTail()
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->next = NULL;
	p->previous = snake->tail;
	snake->tail->next = p;
	p->x = snake->tail->x+BodyRadius/2;// + cos(snake->dir)* MOVE_DIS;
	p->y = snake->tail->y+BodyRadius/2;//+ sin(snake->dir)* MOVE_DIS;
	snake->tail = p;
}
//����ͷ���һ��  
void AddHead()
{
	Node *p = NULL;
	p = (Node*)malloc(sizeof(Node));
	p->previous = NULL;
	p->radius = HeadRadius;

	if (snake->head == NULL)
	{
		p->x = MAP_WIDTH / 2;
		p->y = MAP_HEIGHT / 2;
		snake->head = p;
		snake->tail = p;
		snake->head->next = NULL;
	}
	else
	{
		p->x = snake->head->x + cos(snake->dir)* BodyRadius;
		p->y = snake->head->y + sin(snake->dir)* BodyRadius;
		p->next = snake->head;
		snake->head->previous = p;
		snake->head = p;
		p->next->radius = BodyRadius;
	}
}
//�ƶ���
void Move()
{
	float disx = 0,disy = 0,sqr = 0;
	Node *p = NULL;
	for (p = snake->tail; p != snake->head; p = p->previous)
	{
		disx = p->x - p->previous->x;
		disy = p->y - p->previous->y;
		sqr = sqrt(disx * disx + disy * disy);
		p->x -= disx / sqr * (MOVE_DIS + snake->speed);
		p->y -= disy / sqr * (MOVE_DIS + snake->speed);
	}
	snake->head->x += cos(snake->dir)* (MOVE_DIS + snake->speed);
	snake->head->y += sin(snake->dir)* (MOVE_DIS + snake->speed);

}

//free������
void FreeSnake()
{
	Node* p = NULL;
	Node* q = NULL;
	for (p = snake->head; p != NULL; p = q)
	{
		q = p->next;
		free(p);
	}
	free(snake);
}


//������������Ƿ���ײ��levelΪ�����ص��ĳ̶�
int CheckThings(Node *p1, Node* p2, int level)
{
	int ret = 0;
	int sDis = 0; //�����ƽ��
	sDis = (p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) *(p1->y - p2->y);
	if (sDis <= ((p1->radius) + (p2->radius) - level)*((p1->radius) + (p2->radius) - level))
	{
		ret = 1;
	}
	return ret;
}

//���һ��������һ�������ȫ�������Ƿ�����ײ �����ɵ�ʱ����
int CheckOneToAll(Node* one,Node* All)
{
	int ret = 0;
	Node *p = NULL;
	for (p = All->next; p != NULL; p = p->next)
	{
		if (CheckThings(p, one, 0))
		{
			ret = 1;
			break;
		}
	}
	return ret;
}
int CheckCreate(Node *one)
{
	int ret = 0;
	if (CheckSnake(one)||CheckOneToAll(one, food)|| CheckOneToAll(one, poison)|| CheckOneToAll(one, landmine)|| CheckOneToAll(one,wall))
		ret = 1;
	return ret;
}
//���ĳһ���������������Ƿ���ײ  
int CheckSnake(Node* thing)
{
	int ret = 0;
	Node *p = NULL;
	for (p = snake->head; p != NULL; p = p->next)
	{
		if (CheckThings(p, thing, 0))
		{
			ret = 1;
			break;
		}
	}
	return ret;
}

//�����ͷ��ĳһ�ණ���е�ÿһ���Ƿ�����ײ,������ײ���������ײ����һ��
int TouchThings(Node* thing,int level)
{
	int ret = 0;
	Node *p = NULL,*q = NULL;
		for (p = thing->next,q=thing; p != NULL; q=p,p = p->next)
		{
			if (CheckThings(p, snake->head, level))
			{
				/*if (p->previous != NULL)
				{*/
					q->next = p->next;
				/*}*/
				//else
				//{
				//	thing = p->next;
				//}
				if (p->next != NULL)
				{
					p->next->previous = p->previous;
				}
				free(p);
				ret = 1;
				break;
			}
	}
	return ret;
}

//����ֵ���������� ��һ������������Ϸ
int TouchHead()
{
	int ret = 1;
	if (TouchThings(food,FoodRadius/5))
	{
		AddHead();
		snake->length++;
		snake->score += hardDegree*10;
		CreateThings(food);
	}
	if (TouchThings(poison,PoisonRadius/5))
	{
		if (snake->length > 1)
		{
			ClearTail();
			snake->length--;
			snake->score -= hardDegree * 5;
		}
		else
		{
			ret = 0;
		}
	}
	if (TouchThings(landmine,LandmineRadius/5))
	{
		if (snake->length > 1)
		{
			int halfLength = snake->length / 2;
			snake->length -= halfLength;
			snake->score -= hardDegree * 20;
			for (int j = 0; j < halfLength; j++)
			{
				ClearTail();
			}
			ret = 1;
		}
		else
		{
			ret = 0;
		}
	}
	if (TouchThings(wall, 10))
	{
		ret = 0;
	}
	if (snake->length > 10)     //һ��ʳ������˵�ԭ��
	{
		if (TouchThings(snake->head->next->next->next->next->next->next->next->next,5))
		{
			ret = 0;
		}
	}
	return ret;
}