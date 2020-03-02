#pragma once
#ifndef __Explosion__
#define __Explosion__

#include "GameObject.h"
#include "TextureManager.h"

class Explosion : public GameObject {
public:
	Explosion();
	~Explosion();

	// Draw the object
	void draw();

	// Update the object
	void update();

	// remove anything that needs to be deleted
	void clean();

	bool getExplosion();
	void setExplosion(bool boom);

private:
	bool activeExplosion = false;
	const int explosionTimerMax = 60;
	int explosionTimer = 0;
};


#endif /* defined (__Explosion__) */