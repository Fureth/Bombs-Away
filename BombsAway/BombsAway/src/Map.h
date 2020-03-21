#pragma once
#include <SDL.h>

// MAP LEGEND:
// 0 = Empty square
// 1 = Basic wall
// 2 = Unbreakable wall
// 3 = Door
// 4 = Wall with health
// 5 = Wall with key
// 6 = Health on floor
// 7 = Throw Powerup
// 8 = Enemy Type Wander
// 9 = Player start position
//

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 12;

class Map
{
public:

    Map();
    ~Map();

    void LoadMap(int arr[MAP_HEIGHT][MAP_WIDTH]);
    void DrawMap();
	int currentMap[MAP_HEIGHT][MAP_WIDTH];

private:

    SDL_Rect src, dest;
   //  SDL_Texture* wall;

};


// Can make this a tutorial level, maybe
static int demoLevel[MAP_HEIGHT][MAP_WIDTH] =
{
     {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
     {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
     {0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
     {0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,1,1,0,0,1},
     {0,0,1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1},
     {0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1},
     {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
     {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1},
     {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


// Level 1 Map
static int firstLevel[MAP_HEIGHT][MAP_WIDTH] =
{
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,2,2,2,2},
    {2,9,1,0,0,0,0,0,0,0,0,1,0,2,2,8,2,2,0,2},
    {2,0,1,0,2,2,2,2,2,2,0,1,0,2,2,0,2,2,0,2},
    {2,0,1,0,2,8,0,0,0,2,0,1,0,2,2,1,2,2,1,2},
    {2,0,1,0,2,2,2,2,1,2,0,1,0,2,2,1,2,2,1,2},
    {2,0,1,1,0,0,0,1,1,2,0,1,0,2,2,1,2,2,1,2},
    {2,1,2,2,2,2,2,2,2,2,0,1,0,2,2,1,2,2,1,2},
    {2,1,2,0,6,0,1,1,1,1,0,4,0,0,0,1,1,1,1,2},
    {2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2},
    {2,0,2,2,5,8,0,0,0,0,0,0,0,1,1,1,1,0,0,2},
    {2,8,2,2,8,8,0,1,1,1,1,1,1,1,1,1,1,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
	
};

// Test Map
static int test[MAP_HEIGHT][MAP_WIDTH] =
{
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,2,2,2,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,9,0,0,0,7,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,2,0,0,0,0,10,0,10,0,0,2},
	{2,0,0,0,0,0,0,0,2,2,2,0,0,10,0,8,0,10,0,2},
	{2,0,0,0,0,0,0,0,0,2,0,0,0,0,10,0,10,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}

};