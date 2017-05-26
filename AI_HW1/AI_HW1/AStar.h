#pragma once

#include <iostream>
using namespace std;

const int iMapHeight = 5;
const int iMapWidth = 7;

const int onOpenList = 0;
const int onClosedList = 1;

const int notfinished = 0, notStarted = 0;
const int found = 1, nonexistent = 2;
const int walkable = 0, unwalkable = 1;

int  walkability[iMapWidth+1][iMapHeight+1];
int openList[iMapWidth * iMapHeight + 2];   
int whichList[iMapWidth + 1][iMapHeight + 1];
int openX[iMapWidth * iMapHeight + 2];
int openY[iMapWidth * iMapHeight + 2];
int parentX[iMapWidth + 1][iMapHeight + 1];
int parentY[iMapWidth + 1][iMapHeight + 1];
int Fcost[iMapWidth * iMapHeight + 2];
int Gcost[iMapWidth + 1][iMapHeight + 1];
int Hcost[iMapWidth * iMapHeight + 2];
int pathLength;
int pathLocation;
int* pathBank;

// int pathStatus;
// int xPath;
// int yPath;

int FindPath(int startingX, int startingY, int targetingX, int targetingY);
void CheckCorner(int &corner, int a, int b, int parentXval, int parentYval);
void Pop_Heap(int v, int numberOfOpenListItems);
void Push_Heap(int m, int numberOfOpenListItems);
void Update_and_Sort_Heap(int a, int b, int numberOfOpenListItems);

