#include "AStar.h"

int walkability[iMapWidth+1][iMapHeight+1];		// [x][y] 사각형이 벽인지 아닌지 표시
int openList[iMapWidth * iMapHeight + 2];		// open list : 최소 바이너리 힙(F_cost)
int whichList[iMapWidth + 1][iMapHeight + 1];	// [x][y] 사각형이  open인지 closed인지 아무것도 아닌지 표시
int openX[iMapWidth * iMapHeight + 2];			// open list의 아이디에 매치되는 사각형의 x 좌표
int openY[iMapWidth * iMapHeight + 2];			// open list의 아이디에 매치되는 사각형의 y 좌표
int parentX[iMapWidth + 1][iMapHeight + 1];		// [x][y] 위치의 parent x 좌표
int parentY[iMapWidth + 1][iMapHeight + 1];		// [x][y] 위치의 parent y 좌표
int Fcost[iMapWidth * iMapHeight + 2];			// open list의 아이디에 매치되는 사각형의 F_cost
int Gcost[iMapWidth + 1][iMapHeight + 1];		// [x][y] 위치의 G_cost
int Hcost[iMapWidth * iMapHeight + 2];			// open list의 아이디에 매치되는 사각형의 H_cost
int pathLength;
int pathLocation;
int* pathBank;									// 경로 저장소

void InitPathFinder()
{
	for (int x = 0; x < iMapWidth + 1; ++x)
	{
		for (int y = 0; y < iMapHeight + 1; ++y)
		{
			walkability[x][y] = walkable;
		}
	}
	walkability[4][2] = unwalkable;
	walkability[4][3] = unwalkable;
	walkability[4][4] = unwalkable;

}

int FindPath(int startingX, int startingY, int targetingX, int targetingY)
{  
// 필요한 변수 선언
    int parentXval = 0, parentYval = 0,
    a=0, b=0, m=0, v=0, corner=0, numberOfOpenListItems=0,
    addedGCost = 0, tempGCost = 0, path = 0, x=0, y=0,
    tempX, pathX, pathY, cellPosition,
    newOpenListItemID=0;

    int startX = startingX;
    int startY = startingY;
    int targetX = targetingX;
    int targetY = targetingY;

// 길을 찾을 필요가 없다면
    if (startX == targetX && startY == targetY)
        return found;
    
// 도착위치가 벽이라면
    if (walkability[targetX][targetY] == unwalkable)
        return nonexistent;

// whichList 초기화
    for (int x = 0; x < iMapWidth + 1; ++x)
    {
        for (int y = 0; y < iMapHeight + 1; ++y)
            whichList[x][y] = 0;
    }

    pathLength = notStarted;
    pathLocation = notStarted;
    Gcost[startX][startY] = 0;

// 시작 위치를 open list 에 넣는다.
    numberOfOpenListItems = 1;
    openList[1] = 1;
    openX[1] = startX; openY[1] = startY;

/* 경로 찾기 시작 */
    do
    {
        // open list 에 아이템이 있다면
        if (numberOfOpenListItems != 0)
        {
            /* open list(최소 힙)에서 아이템을 꺼낸다. */

            // 현재 F_cost가 최소인 사각형을 parent로 설정
            parentXval = openX[openList[1]];
            parentYval = openY[openList[1]];
            // 방금 open list 에서 꺼낸 아이템을 closed list 에 있는 것으로 표시
            whichList[parentXval][parentYval] = onClosedList;

            numberOfOpenListItems -= 1;

            openList[1] = openList[numberOfOpenListItems + 1];
            v = 1;
            Pop_Heap(v, numberOfOpenListItems);
            
            /* 방금 꺼낸 사각형의 주위 8방향을 탐색한다. */
            for (b = parentYval - 1; b <= parentYval + 1; ++b)
            {
                for (a = parentXval - 1; a <= parentXval + 1; ++a)
                {
                    // map을 벗어나면 pass
                    if (a == -1 || b == -1 || a == iMapWidth + 1 || b == iMapHeight + 1) continue;
                    // closedList에 있다면 pass
                    if (whichList [a][b] == onClosedList) continue;
                    // 지나갈 수 없는 벽이라면 pass
                    if (walkability [a][b] == unwalkable) continue;

                    // 모서리가 벽인지 확인
                    CheckCorner(corner, a, b, parentXval, parentYval);
                    
                    // 모서리가 벽이면 지나가지 못하므로 pass
                    if (corner == unwalkable) continue;

                    // open list에 없다면
                    if (whichList [a][b] != onOpenList)
                    {
                        // open list 에 추가
                        newOpenListItemID += 1;
                        m = numberOfOpenListItems + 1;
                        openList [m] = newOpenListItemID;
                        openX [newOpenListItemID] = a;
                        openY [newOpenListItemID] = b;

                        /* 지금 까지 이동거리인 G_cost 계산 */

                        if (abs(a - parentXval) == 1 && abs(b - parentYval) == 1)
                            addedGCost = 14;      // 부모 노드에서 대각선 이동이라면
                        else
                            addedGCost = 10;
                        
                        // Gcost 갱신
                        Gcost [a][b] = Gcost [parentXval][parentYval] + addedGCost;

                        // 휴리스틱 계산 = 맨하탄 거리
                        Hcost [openList[m]] = 10 * (abs(a - targetX) + abs(b - targetY));
                        // Fcost 계산
                        Fcost [openList[m]] = Gcost [a][b] + Hcost [openList[m]];
                        // parent 사각형 저장
                        parentX [a][b] = parentXval; parentY [a][b] = parentYval;

						// open list 에 추가
                        Push_Heap(m, numberOfOpenListItems);
                        numberOfOpenListItems += 1;

                        whichList [a][b] = onOpenList;
                    }

                    // open list 에 이미 있다면
                    else
                    {
                        if (abs(a - parentXval) == 1 && abs(b - parentYval) == 1)
                            addedGCost = 14;
                        else
                            addedGCost = 10;
                        
                        tempGCost = Gcost [parentXval][parentYval] + addedGCost;

                        // 새로 구한 G_cost가 더 작다면 현재 G_cost 갱신, parent 갱신
                        if (tempGCost < Gcost[a][b])
                        {
                            parentX [a][b] = parentXval;
                            parentY [a][b] = parentYval;
                            Gcost [a][b] = tempGCost;

                            // 최소 힙인 open list에서 바뀐 아이템을 찾고
                            // F_cost 갱신 후 재정렬
                            Update_and_Sort_Heap(a, b, numberOfOpenListItems);
                        }
                    }
                }   // for (a)
            }   // for (b)
        }   // if (numberOfOpenListItems != 0)

        //  open list 가 비었다면 no path
        else
        {
            path = nonexistent; break;
        }

        // 도착 위치가 open list에 들어가면 경로찾기 성공.
        if (whichList[targetX][targetY] == onOpenList)
        {
            path = found; break;
        }
    }
    while (1); // 경로를 찾거나 open list가 텅 빌 때까지 반복

    // 경로를 찾았다면
    if (path == found)
    {
        /* 도착 위치에서 거꾸로 parent를 추적해서 경로의 길이 계산 */
        pathX = targetX; pathY = targetY;
        do
        {
            tempX = parentX[pathX][pathY];
            pathY = parentY[pathX][pathY];
            pathX = tempX;

            pathLength += 1;
        // 시작 위치에 도달하면 끝.
        }
        while (pathX != startX || pathY != startY);

        // pathBank 경로 길이 만큼 할당
        pathBank = new int[pathLength * 8];

        /* 도착위치에서 거꾸로 parent를 추적해서 경로 구하기 */
        pathX = targetX; pathY = targetY;
        cellPosition = pathLength * 2;
        do
        {
            cellPosition -= 2;
            pathBank[cellPosition] = pathX;
            pathBank[cellPosition + 1] = pathY;

            tempX = parentX[pathX][pathY];
            pathY = parentY[pathX][pathY];
            pathX = tempX;
        }
        while (pathX != startX || pathY != startY);

		// 경로 출력
		cout << "(" << startX << ", " << startY << ") -> ";
		for (int i = 0; i < pathLength * 2; i += 2)
		{
			cout << "(" << pathBank[i] << ", " << pathBank[i + 1] << ")";
			if (i != pathLength * 2 - 2) cout << " -> ";
		}
		cout << endl;
    }

    return path;
}

void CheckCorner(int &corner, int a, int b, int parentXval, int parentYval)
{
	/* 대각선 방향으로 가려고 할 때 양 옆이 벽인지 확인 */
    corner = walkable;
    if (a == parentXval - 1)
    {
        if (b == parentYval - 1)
        {
            if (walkability[parentXval - 1][parentYval] == unwalkable
            || walkability[parentXval][parentYval - 1] == unwalkable)
            corner = unwalkable;
        }
        else if (b == parentYval + 1)
        {
            if (walkability[parentXval - 1][parentYval] == unwalkable
            || walkability[parentXval][parentYval + 1] == unwalkable)
            corner = unwalkable;
        }
    }
    else if (a == parentXval + 1)
    {
        if (b == parentYval - 1)
        {
            if (walkability[parentXval + 1][parentYval] == unwalkable
            || walkability[parentXval][parentYval - 1] == unwalkable)
            corner = unwalkable;
        }
        else if (b == parentYval + 1)
        {
            if (walkability[parentXval + 1][parentYval] == unwalkable
            || walkability[parentXval][parentYval + 1] == unwalkable)
            corner = unwalkable;
        }
    }
}

void Pop_Heap(int v, int numberOfOpenListItems)
{
    int u=0, temp=0;
    do 
    {
        u = v;
        if (2 * u + 1 <= numberOfOpenListItems) // if both children exist
        {
            if (Fcost[openList[u]] >= Fcost[openList[2 * u]])
                v = 2 * u;
            if (Fcost[openList[v]] >= Fcost[openList[2 * u + 1]])
                v = 2 * u + 1;
        }
        else   
        {
            if (2 * u <= numberOfOpenListItems)
            {
                if (Fcost[openList[u]] >= Fcost[openList[2 * u]])
                    v = 2 * u;
            }
        }

        if (u != v) // if parent's F is > one of its children, swap them
        {
            temp = openList[u];
            openList[u] = openList[v];
            openList[v] = temp;
        }
        else    // no change
            break;
    }
    while (1); // reorder the binary heap
}

void Push_Heap(int m, int numberOfOpenListItems)
{
    int temp;
    while (m != 1)
    {
        // Check if child's F cost is < parent's F cost.
        if (Fcost[openList [m]] <= Fcost[openList [m/2]])
        {
            temp = openList [m / 2];
            openList [m / 2] = openList [m];
            openList [m] = temp;
            m = m / 2;
        }
        else
            break;
    }
}

void Update_and_Sort_Heap(int a, int b, int numberOfOpenListItems)
{
    int m=0, temp = 0;
    for (int x = 1; x <= numberOfOpenListItems; ++x)
    {
        if (openX[openList[x]] == a && openY[openList[x]] == b)
        {
            Fcost[openList[x]] = Gcost[a][b] + Hcost[openList[x]];

            m = x;
            while (m != 1)
            {
                if (Fcost[openList[m]] < Fcost[openList[m/2]])
                {
                    temp = openList[m/2];
                    openList[m/2] = openList[m];
                    openList[m] = temp;
                    m = m/2;
                }
                else
                    break;
            } 
            break;
        }
    }
}

