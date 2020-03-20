#pragma once
#ifndef __CollisionManager__
#define __CollisionManager__

// core libraries
#include <iostream>

#include "GameObject.h"
#include <glm/gtx/norm.hpp>
#include <SDL.h>
#include "Game.h"


class CollisionManager
{
public:

	static int squaredDistance(glm::vec2 P1, glm::vec2 P2);
	static bool basicCollisionCheck(GameObject* object1, GameObject* object2);
	static bool tileCollisionCheck(GameObject* object, int tileMap[12][20]);
	static bool playerCollisionMovement(GameObject* object, int tileMap[12][20]);
private:
	CollisionManager();
	~CollisionManager();
};

typedef CollisionManager Collision;

#endif /* defined (__CollisionManager__) */
