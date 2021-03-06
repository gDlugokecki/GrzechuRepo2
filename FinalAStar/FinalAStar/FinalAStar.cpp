// FinalAStar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

int NowX = 0;
int NowY = 0;
int NewX = 0;
int NewY = 0;
char map[20][20];
int Distance[20][20];
bool PointsToCheck[20][20];
bool PointsChecked[20][20];
int SumUpCost[20][20] = { 0 };
int MovementCost[20][20] = { 0 };
int parentX[20][20] = { 0 };
int parentY[20][20] = { 0 };
using namespace std;

void LoadMap()
{
	ifstream myfile("C:\\Users\\grzes\\Desktop\\AgwiazdkaVS\\Agwiazka\\grid.txt");
	for (int i = 19;i >= 0;i--)
	{
		for (int j = 0;j < 20;j++)
		{
			myfile >> map[i][j];
		}
	}
	myfile.close();
}
void ToTargetDistance() 
{
	for (int i = 0;i < 20;i++)
	{
		for (int j = 0;j < 20;j++)
		{
			Distance[i][j] = ( 38 - i - j );
		}
	}
}
void SetUpLists()
{
	for (int i = 0;i < 20;i++)
	{
		for (int j = 0;j < 20;j++)
		{
			if (i == 0 && j == 0)
			{
				PointsChecked[i][j] = true;
			}
			else
			{
				PointsChecked[i][j] = false;
				PointsToCheck[i][j] = false;
			}
		}
	}
}

void CalculateMovementCost(int x, int y)
{
	MovementCost[x][y] = MovementCost[parentX[x][y]][parentY[x][y]] + 1;
}

void WholeCost(int x, int y)
{
	SumUpCost[x][y] = MovementCost[x][y] + Distance[x][y];
}

void PoitsCheckedValue(int x,int y)
{
	PointsChecked[x][y] = true;
	PointsToCheck[x][y] = false;
	
}
void PointsToCheckValue(int x, int y)
{
	PointsToCheck[x][y] = true;
}
void Direction()
{
	int CheckValue = 99999;
	for (int i = 0;i < 20;i++)
	{
		for (int j = 0;j < 20;j++)
		{
			if (PointsToCheck[i][j] == true && SumUpCost[i][j] < CheckValue)
			{
				CheckValue = SumUpCost[i][j];
				NewX = i;
				NewY = j;
			}
		}
	}
}


int Move(int x, int y)
{
	if (x > 19 || x < 0 || y > 19 || y < 0 || PointsChecked[x][y] == true || map[x][y] == '5')
	{
		return 0;
	}
	else
	{
		PointsToCheckValue(x,y);
		parentX[x][y] = NowX;
		parentY[x][y] = NowY;
		CalculateMovementCost(x, y);
		WholeCost(x, y);
	}
}
void Path()
{
	int selectedX = 19;
	int selectedY = 19;

	while (selectedX != 0 || selectedY != 0)
	{
		map[selectedX][selectedY] = 'x';
		int temp = selectedX;
		selectedX = parentX[selectedX][selectedY];
		selectedY = parentY[temp][selectedY];
	}
}

void Draw()
{
	for (int i = 0;i < 20;i++)
	{
		for (int j = 0;j < 20;j++)
		{
			cout << map[i][j] << " ";
		}
	}
	cout << "/n";
}

int main()
{
	LoadMap();
	SetUpLists();
	ToTargetDistance();
	while (!(NowX == 19) || !(NowY == 19))
	{
		PointsToCheckValue(NowX, NowY);

		Move(NowX + 1, NowY);
		Move(NowX - 1, NowY);
		Move(NowX, NowY + 1);
		Move(NowX, NowY - 1);

		Direction();
		NowX = NewX;
		NowY = NewY;
	}
	Path();
	Draw();
	getchar();
    return 0;
}

