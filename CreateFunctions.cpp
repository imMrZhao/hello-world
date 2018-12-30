#include "snake.h"

void CreateThings(Node* thing)
{
	int x, y;
	/*static int count = (unsigned int)time(NULL);*/
	Node* p = (Node*)malloc(sizeof(Node));
	p->radius = thing->radius;
	srand((unsigned int)time(NULL));
	do {
		p->x = rand() % (MAP_WIDTH - WallRadius*12) + WallRadius * 6;
		p->y = rand() % (MAP_HEIGHT - WallRadius*12)+ WallRadius * 6;
		srand(rand());
	} while (CheckCreate(p) != 0);
	//if(count>32750)
	//	count = (unsigned int)time(NULL);
	//if (thing == NULL)
	//{
	//	thing = (Node*)malloc(sizeof(Node));
	//	thing->next = NULL;
	//	thing->previous = NULL;
	//	thing->x = x;
	//	thing->y = y;
	//	p = thing;
	//}
	//else
	//{
	p->next = thing->next;
	p->previous = thing;
	thing->next = p;
	/*}*/
}
void CreateFood()
{
	food->radius = FoodRadius;
	for (int i = 0; i < (10-hardDegree)/2 ; i++)
	{
		CreateThings(food);
	}
}

void CreatePoison()
{
	poison->radius = PoisonRadius;
	for (int i = 0; i < hardDegree +3; i++)
	{
		CreateThings(poison);
	}
}

void CreateLandmine()
{
	landmine->radius = LandmineRadius;
	for (int i = 0; i < hardDegree +2; i++)
	{
		CreateThings(landmine);
	}
}

void CreateAll()
{
	food = (Node*)malloc(sizeof(Node));
	food->next = NULL;
	poison = (Node*)malloc(sizeof(Node));
	poison->next = NULL;
	landmine = (Node*)malloc(sizeof(Node));
	landmine->next = NULL;
	wall = (Node*)malloc(sizeof(Node));
	wall->next = NULL;
	CreateSnake();
	CreateFood();
	CreatePoison();
	CreateLandmine();
	CreateWall();
}

void FreeThings(Node *thing)
{
	Node *p = NULL;
	Node *q = NULL;
	for (p = thing; p != NULL; p = q)
	{
		q = p->next;
		free(p);
	}
}
void FreeAll()
{
	FreeThings(food);
	FreeThings(poison);
	FreeThings(landmine);
	FreeThings(wall);
	FreeSnake();
}

void CreateWall()
{
	wall->radius = WallRadius;
	int x, y,amountx,amounty;
	amountx = MAP_WIDTH / (2 * WallRadius);
	amounty = MAP_HEIGHT / (2 * WallRadius);
	for (int i = 0; i < amountx; i++)
	{
		Node* p = (Node*)malloc(sizeof(Node));
		p->radius = wall->radius;
		p->x = i*WallRadius*2;
		p->y = 0;
		p->next = wall->next;
		p->previous = wall;
		wall->next = p;
	}
	for (int i = 0; i < amountx; i++)
	{
		Node* p = (Node*)malloc(sizeof(Node));
		p->radius = wall->radius;
		p->x = i * WallRadius * 2;
		p->y = MAP_HEIGHT - 2 *WallRadius;
		p->next = wall->next;
		p->previous = wall;
		wall->next = p;
	}
	for (int i = 0; i < amounty; i++)
	{
		Node* p = (Node*)malloc(sizeof(Node));
		p->radius = wall->radius;
		p->x = 0;
		p->y = i *  WallRadius * 2;
		p->next = wall->next;
		p->previous = wall;
		wall->next = p;
	}
	for (int i = 0; i < amounty; i++)
	{
		Node* p = (Node*)malloc(sizeof(Node));
		p->radius = wall->radius;
		p->x = MAP_WIDTH - WallRadius * 2;
		p->y = i * WallRadius * 2;
		p->next = wall->next;
		p->previous = wall;
		wall->next = p;
	}
	switch (hardDegree)
	{
	case 2:
		for (int i = 0; i < amounty/3; i++)
		{
			Node* p = (Node*)malloc(sizeof(Node));
			p->radius = wall->radius;
			p->x = MAP_WIDTH - 400;
			p->y = i * WallRadius * 2;
			p->next = wall->next;
			p->previous = wall;
			wall->next = p;
		}
		for (int i = 0; i < amounty / 3; i++)
		{
			Node* p = (Node*)malloc(sizeof(Node));
			p->radius = wall->radius;
			p->x = MAP_WIDTH - 1000;
			p->y = i * WallRadius * 2;
			p->next = wall->next;
			p->previous = wall;
			wall->next = p;
		}
		for (int i = 0; i < amounty / 3; i++)
		{
			Node* p = (Node*)malloc(sizeof(Node));
			p->radius = wall->radius;
			p->x = MAP_WIDTH - 400;
			p->y = MAP_HEIGHT- i * WallRadius * 2;
			p->next = wall->next;
			p->previous = wall;
			wall->next = p;
		}
		for (int i = 0; i < amounty / 3; i++)
		{
			Node* p = (Node*)malloc(sizeof(Node));
			p->radius = wall->radius;
			p->x = MAP_WIDTH - 1000;
			p->y = MAP_HEIGHT-i * WallRadius * 2;
			p->next = wall->next;
			p->previous = wall;
			wall->next = p;
		}
		break;
	case 3:
		for (int i = 0; i < amounty / 3; i++)
		{
			Node* p = (Node*)malloc(sizeof(Node));
			p->radius = wall->radius;
			p->x = MAP_WIDTH - 400;
			p->y = i * WallRadius * 2;
			p->next = wall->next;
			p->previous = wall;
			wall->next = p;
		}
		for (int i = 0; i < amounty / 3; i++)
		{
			Node* p = (Node*)malloc(sizeof(Node));
			p->radius = wall->radius;
			p->x = MAP_WIDTH - 1000;
			p->y = i * WallRadius * 2;
			p->next = wall->next;
			p->previous = wall;
			wall->next = p;
		}
		for (int i = 0; i < amounty / 3; i++)
		{
			Node* p = (Node*)malloc(sizeof(Node));
			p->radius = wall->radius;
			p->x = MAP_WIDTH - 400;
			p->y = MAP_HEIGHT - i * WallRadius * 2;
			p->next = wall->next;
			p->previous = wall;
			wall->next = p;
		}
		for (int i = 0; i < amounty / 3; i++)
		{
			Node* p = (Node*)malloc(sizeof(Node));
			p->radius = wall->radius;
			p->x = MAP_WIDTH - 1000;
			p->y = MAP_HEIGHT - i * WallRadius * 2;
			p->next = wall->next;
			p->previous = wall;
			wall->next = p;
		}
		for (int i = 0; i < amountx/4; i++)
		{
			Node* p = (Node*)malloc(sizeof(Node));
			p->radius = wall->radius;
			p->x = MAP_WIDTH / 2 + i * WallRadius * 2 - 100;
			p->y = MAP_HEIGHT - 486 ;
			p->next = wall->next;
			p->previous = wall;
			wall->next = p;
		}
		break;
	}

}