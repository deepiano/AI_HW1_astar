#pragma once

#include <iostream>
#include <stack>
using namespace std;

const int iMapHeight = 5;
const int iMapWidth = 7;

const int onOpenList = 11;
const int onClosedList = 10;

const int notfinished = 0, notStarted = 0;
const int found = 1, nonexistent = 2;
const int walkable = 0, unwalkable = 1;

// int pathStatus;
// int xPath;
// int yPath;

void InitPathFinder();

int FindPath(int startingX, int startingY, int targetingX, int targetingY);
void CheckCorner(int &corner, int a, int b, int parentXval, int parentYval);
void Pop_Heap(int v, int numberOfOpenListItems);
void Push_Heap(int m, int numberOfOpenListItems);
void Update_and_Sort_Heap(int a, int b, int numberOfOpenListItems);

