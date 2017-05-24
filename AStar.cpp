#include "AStar.h"

/* Astar class */

void Astar::setTest(Node start, Node end)
{
    int y, x;
    this->start = start;
    this->end = end;

    
    for(y = 0; y < HEIGHT; ++y)
    {
        for(x = 0; x < WIDTH; ++x)
        {
            Node& node = map[y][x];
            node.y = y;
            node.x = x;
            node.parent_y = node.parent_x = -1;
            node.isWall = false;
            node.is_in_open_list = false;
            node.is_in_closed_list = false;
            node.F_cost = node.G_cost = node.H_cost = 0;
        }
    }
}

void FindPath(int startingX, int startingY, int targetingX, int targetingY)
{
    int onOpenList = 0, parentXval = 0, parentYval = 0,
    a=0, b=0, m=0, u=0, v=0, temp=0, corner=0, numberOfOpenListItems=0,
    addedGCost = 0, tempGcost = 0, path = 0, x=0, y=0,
    tempX, pathX, pathY, cellPosition,
    newOpenListItemID=0;

    int startX = startingX / iTileSize;
    int startY = startingY / iTileSize;
    int targetX = targetingX / iTileSize;
    int targetY = targetingY / iTileSize;

}