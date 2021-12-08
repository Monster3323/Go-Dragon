#include<iostream>//┌─    ┬─  ┐   ├─    ┼─    ┤ └─   ┴─    ┘ ●─ ○
#include<stdlib.h>
#include<time.h>
using namespace std;
#define Max 100
typedef int status;

int v[19][19] = { 0 };
int num[2][Max] = { 0 };

typedef struct
{
	int data;
	int posx, posy;
}piece;

typedef struct
{
	piece* base;
	int front, rear;
}SqQueue;

status InitQueue(SqQueue& q)
{
	q.base = new piece[Max];
	if (!q.base)
		return 1;
	q.rear = q.front = 0;
	return 1;
}

status EnQueue(SqQueue& q, piece v)
{
	if ((q.rear + 1) % Max == q.front)
		return -1;
	q.base[q.rear] = v;
	q.rear = (q.rear + 1) % Max;

	return 1;
}

status DeQueue(SqQueue& q, piece& v)
{
	if (q.front == q.rear)
		return -1;
	v = q.base[q.front];
	q.front = (q.front + 1) % Max;
	return 1;
}

int Isempty(SqQueue q)
{
	if (q.front == q.rear)
		return 1;
	return 0;
}



void Initpiece(piece checkerboard[19][19])
{

	int i, j;
	checkerboard[0][0].data = 2;
	checkerboard[0][18].data = 3;
	checkerboard[18][0].data = 4;
	checkerboard[18][18].data = 5;
	for (i = 1; i < 18; i++)
	{
		for (j = 1; j < 18; j++)
		{
			checkerboard[0][j].data = 6;
			checkerboard[18][j].data = 7;
			checkerboard[j][0].data = 8;
			checkerboard[j][18].data = 9;
			checkerboard[i][j].data = 10;
		}
	}
	for(int i=0;i<19;i++)
		for (int j = 0; j < 19; j++)
		{
			checkerboard[i][j].posx = i;
			checkerboard[i][j].posy = j;
		}
}

void Display(piece checkerboard[19][19])
{
	int i = 0, j = 0;
	for (i = 0; i < 19; i++)
	{
		for (j = 0; j < 19; j++)
		{
			if (checkerboard[i][j].data == 2) printf("┌─");
			if (checkerboard[i][j].data == 3) printf("┐");
			if (checkerboard[i][j].data == 4) printf("└─");
			if (checkerboard[i][j].data == 5) printf("┘");
			if (checkerboard[i][j].data == 6) printf("┬─");
			if (checkerboard[i][j].data == 7) printf("┴─");
			if (checkerboard[i][j].data == 8) printf("├─");
			if (checkerboard[i][j].data == 9) printf("┤");
			if (checkerboard[i][j].data == 10) printf("┼─");
			if (checkerboard[i][j].data == 0) printf("○");
			if (checkerboard[i][j].data == 1) printf("●");
		}
		printf("\n");
	}
}

int JudgeDragon(piece checkerboard[][19],int sign,SqQueue s)
{
	int m = 0;
	piece q;
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (checkerboard[i][j].data == sign && v[i][j] == 0)
			{
				EnQueue(s, checkerboard[i][j]);
				v[i][j] = 1;
				while (!Isempty(s))
				{
					DeQueue(s, q);
					++num[sign][m];
					if (q.posy > 0)
					{
						if (checkerboard[q.posx][q.posy-1].data == sign && v[q.posx][q.posy - 1] == 0)
						{
							EnQueue(s, checkerboard[q.posx][q.posy - 1]);
							v[q.posx][q.posy - 1] = 1;
						}
							
					}
					if (q.posy < 18)
					{
						if (checkerboard[q.posx][q.posy + 1].data == sign && v[q.posx][q.posy + 1] == 0)
						{
							EnQueue(s, checkerboard[q.posx][q.posy + 1]);
							v[q.posx][q.posy + 1]=1;
						}
							
					}
					if (q.posx > 0)
					{
						if (checkerboard[q.posx - 1][q.posy].data == sign && v[q.posx - 1][q.posy] == 0)
						{
							EnQueue(s, checkerboard[q.posx - 1][q.posy]);
							v[q.posx - 1][q.posy] = 1;
						}
					}
					if (q.posx < 18)
					{
						if (checkerboard[q.posx + 1][q.posy].data == sign && v[q.posx + 1][q.posy] == 0)
						{
							EnQueue(s, checkerboard[q.posx + 1][q.posy]);
							v[q.posx + 1][q.posy] = 1;
						}	
					}
				}
				++m;
			}
		}
	}
	return 1;
}

void randomborder(piece checkerboard[19][19])
{
	srand((unsigned)time(NULL));
	for(int i=0;i<19;i++)
		for (int j = 0; j < 19; j++)
		{
			int aa = rand() % 3;
			if (aa != 2)
				checkerboard[i][j].data = aa;
		}
}

int Judgecount(int sign)
{
	int i = 0, count = 0;
	while (num[sign][i] != 0)
	{
		++count;
		++i;
	}
	return count;
}

void DisPlayCount(int count,int sign)
{
	for (int i = 0; i < count; i++)
	{
		if (sign == 1)
			cout << "第" << i + 1 << "个白色大龙有" << num[sign][i] << "个棋子"<<endl;
		if (sign == 0)
			cout << "第" << i + 1 << "个黑色大龙有" << num[sign][i] << "个棋子"<<endl;
	}
}

int main() {
	piece p[19][19];
	SqQueue s;
	int Wcount = 0, Bcount = 0;
	InitQueue(s);
	Initpiece(p);
	randomborder(p);
	Display(p);
	JudgeDragon(p, 0, s);
	JudgeDragon(p, 1, s);
	Bcount = Judgecount(0);
	Wcount = Judgecount(1);
	cout << "黑色大龙有" << Bcount << "个"<<endl;
	DisPlayCount(Bcount, 0);
	cout << "白色大龙有" << Wcount << "个"<<endl;
	DisPlayCount(Wcount, 1);

}