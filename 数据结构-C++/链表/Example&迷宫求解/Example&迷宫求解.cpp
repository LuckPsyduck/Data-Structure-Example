// 迷宫求解.cpp : 定义控制台应用程序的入口点。
//
#include"stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

enum Direction { DOWN, RIGHT, UP, LEFT };
const int ROWS = 8, COLS = 10;

void mazeTraversal(char[][COLS], const int, const int, int, int, int);
void mazeGenerator(char[][COLS], int *, int *);
void printMaze(const char[][COLS]);
bool validMove(const char[][COLS], int, int);
bool coordsAreEdge(int, int);

void main()
{
	cout << "maze.cpp运行结果:\n";
	cout << "迷宫问题求解:\n";
	char maze[ROWS][COLS];
	int xStart, yStart, x, y;
	srand(time(0));
	for (int loop = 0; loop<ROWS; ++loop)
		for (int loop2 = 0; loop2<COLS; ++loop2)
			maze[loop][loop2] = '#';
	mazeGenerator(maze, &xStart, &yStart);
	x = xStart;//开始行
	y = yStart;//开始列
	mazeTraversal(maze, xStart, yStart, x, y, RIGHT);
	printMaze(maze); cin.get();
}

void mazeTraversal(char maze[][COLS], const int xCoord, const int yCoord,
	int row, int col, int direction)
{
	static bool flag = false;//开始位置标志变量
	maze[row][col] = 'x';  //在当前位置插入x
	if (coordsAreEdge(row, col) && row != xCoord&&col != yCoord) 
	{
		cout << endl << "成功走出迷宫!\n"; return;
	}
	else if (row == xCoord&&col == yCoord&&flag)
	{
		cout << "\n返回迷宫开始位置.\n"; return;
	}
	else 
	{
		flag = true;
		for (int move = direction, count = 0; count<4; ++count, ++move, move %= 4)
			switch (move) 
			{
			case DOWN://向下移动
				if (validMove(maze, row + 1, col)) 
				{
					mazeTraversal(maze, xCoord, yCoord, row + 1, col, LEFT);
					return;
				}
				break;
			case RIGHT://向右移动
				if (validMove(maze, row, col + 1)) 
				{
					mazeTraversal(maze, xCoord, yCoord, row, col + 1, DOWN);
					return;
				}
				break;
			case UP://向上移动
				if (validMove(maze, row - 1, col))
				{
					mazeTraversal(maze, xCoord, yCoord, row - 1, col, RIGHT);
					return;
				}
				break;
			case LEFT://向左移动
				if (validMove(maze, row, col - 1))
				{
					mazeTraversal(maze, xCoord, yCoord, row, col - 1, UP);
					return;
				}
				break;
			}
	}
}

//有效移动
bool validMove(const char maze[][COLS], int r, int c)
{
	return(r >= 0 && r <= ROWS - 1 && c >= 0 && c <= COLS - 1 && maze[r][c] != '#');
}

bool coordsAreEdge(int x, int y)
{
	if ((x == 0 || x == ROWS - 1) && (y >= 0 && y <= COLS - 1))
		return true;
	else if ((y == 0 || y == COLS - 1) && (x >= 0 && x <= ROWS - 1))
		return true;
	else return false;
}

void printMaze(const char maze[][COLS])
{
	for (int x = 0; x<ROWS; ++x) 
	{
		for (int y = 0; y<COLS; ++y)
			cout << maze[x][y] << ' ';
		cout << '\n';
	}
	cout << endl;
}

void mazeGenerator(char maze[][COLS], int *xPtr, int *yPtr)
{
	int a, x, y, entry, exit;
	do {
		entry = rand() % 4;
		exit = rand() % 4;
	} while (entry == exit);
	// 确定入口位置
	if (entry == 0) 
	{
		*xPtr = 1 + rand() % (ROWS - 2);//避免死角
		*yPtr = 0;
		maze[*xPtr][*yPtr] = '0';
	}
	else if (entry == 1) 
	{
		*xPtr = 0;
		*yPtr = 1 + rand() % (COLS - 2);
		maze[*xPtr][*yPtr] = '0';
	}
	else if (entry == 2) 
	{
		*xPtr = 1 + rand() % (ROWS - 2);
		*yPtr = COLS - 1;
		maze[*xPtr][*yPtr] = '0';
	}
	else 
	{
		*xPtr = ROWS - 1;
		*yPtr = 1 + rand() % (COLS - 2);
		maze[*xPtr][*yPtr] = '0';
	}
	//确定出口位置
	if (exit == 0) 
	{
		a = 1 + rand() % (ROWS - 2);
		maze[a][0] = '0';
	}
	else if (exit == 1)
	{
		a = 1 + rand() % (COLS - 2);
		maze[0][a] = '0';
	}
	else if (exit == 2) 
	{
		a = 1 + rand() % (ROWS - 2);
		maze[a][COLS - 1] = '0';
	}
	else 
	{
		a = 1 + rand() % (COLS - 2);
		maze[ROWS - 1][a] = '0';
	}
	for (int loop = 1; loop<(ROWS - 2)*(COLS - 2); ++loop) 
	{
		x = 1 + rand() % (ROWS - 2);//添加圆点到迷宫
		y = 1 + rand() % (COLS - 2);
		maze[x][y] = '0';
	}
}
