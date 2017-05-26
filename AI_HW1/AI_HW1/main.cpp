#include "AStar.h"
using namespace std;

int main()
{
	InitPathFinder();
	int startingX = 2;
	int startingY = 3;
	int targetingX = 6;
	int targetingY = 3;
	
	int sel;
	cout << "1. 시작 위치, 도착 위치 설정" << endl;
	cout << "2. 디폴트 경로" << endl;
	cin >> sel;

	if (sel == 1)
	{
		cout << "Enter start X, start Y : ";
		cin >> startingX >> startingY;
		cout << "Enter target X, target Y : ";
		cin >> targetingX >> targetingY;
	}

    int path = FindPath(startingX, startingY, targetingX, targetingY);
	if (path == nonexistent)
	{
		cout << "No path!" << endl;
	}
	else if (path == found)
	{
		cout << "start and target are the same." << endl;
	}
    return 0;
}