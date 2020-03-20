#pragma once
#ifndef __Bomb__
#define __Bomb__

#include "GameObject.h"
#include "TextureManager.h"
#include "Direction.h"

class Bomb : public GameObject {
public:
    Bomb();
    ~Bomb();

    // Draw the object
    void draw();

    // Update the object
    void update();

    // remove anything that needs to be deleted
    void clean();

    // bomb specific functions
    void setBomb(bool set);
    bool getBomb();

	void setExplode(bool expl);
	bool getExplode();

	Direction getThrownFrom();
	void setThrownFrom(Direction thrown);

private:
    bool isSet = false;
	bool hasExploded = false;
    int bombTimer = 0;
    const int bombTimerMax = 180;

	Direction thrownFrom = NORTH;
};


#endif /* defined (__Bomb__) */