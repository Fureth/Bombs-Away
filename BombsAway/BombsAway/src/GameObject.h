#pragma once
#ifndef __GameObject__
#define __GameObject__

#include <vector>
#include <glm\vec2.hpp>
#include <string>
#include "GameObjectType.h"
#include "Direction.h"

class GameObject {
public:
	GameObject();
	~GameObject();

	// Draw the object
	virtual void draw() = 0;

	// Update the object
	virtual void update() = 0;

	// remove anything that needs to be deleted
	virtual void clean() = 0;

	// getters for common variables
	glm::vec2 getPosition();
	glm::vec2 getScale();
	glm::vec2 getVelocity();
	glm::vec2 getAcceleration();
	int getWidth();
	int getHeight();
	bool getIsColliding();
	GameObjectType getType();

	// setters for common variables
	void setPosition(glm::vec2 newPosition);
	void setWidth(int newWidth);
	void setHeight(int newHeight);
	void setVelocity(glm::vec2 newVelocity);
	void setIsColliding(bool collision);
	void setType(GameObjectType newType);

	glm::vec2 getPreviousPosition();
	void setPreviousPosition(glm::vec2 position);

	bool getIsActive();
	void setIsActive(bool active);

	// Health functions
	virtual int getHealth();
	virtual void changeHealth(bool lifeUp);
	// Health variables
	int currentHealth;
	int invFrame = 0;
	const int invFrameMax = 180;
	bool isInvul = false;
	
private:
	// transform variables
	glm::vec2 m_position;
	glm::vec2 m_scale;
	glm::vec2 m_previousPosition;

	// movement variables
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;

	// size variables
	int m_width;
	int m_height;

	// animation variables
	int m_currentRow;
	int m_currentFrame;
	int m_numFrames;
	std::string m_textureID;

	// collision variables
	bool m_isActive;
	bool m_isColliding;
	GameObjectType m_type;

};

#endif 