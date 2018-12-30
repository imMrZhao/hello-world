#include "snake.h"

//生成一条蛇 只有蛇头
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
//在蛇尾清除一节
void ClearTail()
{
	Node* p = NULL;
	p = snake->tail;
	p->previous->next = NULL;
	snake->tail = p->previous;

	free(p);
}
//在蛇尾添加一节
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
//在蛇头添加一节  
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
//移动蛇
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

//free整条蛇
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


//检测两个物体是否碰撞，level为允许重叠的程度
int CheckThings(Node *p1, Node* p2, int level)
{
	int ret = 0;
	int sDis = 0; //距离的平方
	sDis = (p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) *(p1->y - p2->y);
	if (sDis <= ((p1->radius) + (p2->radius) - level)*((p1->radius) + (p2->radius) - level))
	{
		ret = 1;
	}
	return ret;
}

//检测一个物体与一类物体的全部个体是否发生碰撞 供生成的时候用
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
//检测某一个物体与整条蛇是否碰撞  
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

//检测蛇头与某一类东西中的每一个是否有碰撞,如有碰撞，则清除碰撞的这一个
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

//返回值是零则死亡 是一则正常进行游戏
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
	if (snake->length > 10)     //一吃食物就死了的原因
	{
		if (TouchThings(snake->head->next->next->next->next->next->next->next->next,5))
		{
			ret = 0;
		}
	}
	return ret;
}