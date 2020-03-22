#pragma once
#ifndef __Enemy__
#define __Enemy__

#include "GameObject.h"
#include "TextureManager.h"
#include "Direction.h"
#include <glm/detail/type_vec2.hpp>

class Enemy : public GameObject {
public:
	Enemy(glm::vec2 startPos, int enemyType);
	~Enemy();

	// Draw the object
	void draw();

	// Update the object
	void update();

	// remove anything that needs to be deleted
	void clean();

	// Basic wander AI used for movement
	void wander();

	void randomizeDirection();
	void changeDirection();
	Direction getDirection();

private:
	Direction currentDirection;
	std::string textureSelect;
	const int roamTimerMax = 39;
	int roamTimer = 0;
	int enemySpeed = 0;
	int enemyType = 0;
};

#endif /* defined (__Enemy__) */