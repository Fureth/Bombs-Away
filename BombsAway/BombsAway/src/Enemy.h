#pragma once
#ifndef __Enemy__
#define __Enemy__

#include "GameObject.h"
#include "TextureManager.h"
#include "Direction.h"

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

	bool keyEnemy = false;
	int enemyType = 0;

private:
	Direction currentDirection;
	int frameTimer = 0;
	const int frameTimerMid = 19;
	const int frameTimerMax = 39;
	const int invFrameMax = 90;
	int invFrame = 0;
	
	int enemySpeed = 0;

	/*int rowSelector;
	int frameSelector;*/
};

#endif /* defined (__Enemy__) */