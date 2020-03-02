#pragma once
#ifndef __Enemy__
#define __Enemy__

#include "GameObject.h"
#include "TextureManager.h"
#include "Direction.h"

class Enemy : public GameObject {
public:
	Enemy(glm::vec2 startPos);
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
};

#endif /* defined (__Enemy__) */