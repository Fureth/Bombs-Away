#pragma once
#ifndef __Game__
#define __Game__

// Core Libraries
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

// Game Managers
#include "TextureManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"

// Game Objects
#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include "FSM.h"
#include "Explosion.h"
#include "Enemy.h"
#include "Wall.h"

const int FPS = 60;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 978;
const int DELAY_TIME = 1000.0f / FPS;


class Game
{


public:

	// See if a key is pressed down
	bool checkForKeystroke(SDL_Scancode c);
	
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}

		return s_pInstance;
	}

	
	
	// simply set the running variable to true
	void init() { m_bRunning = true; }

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	// public functions
	void render();
	void update();
	void handleEvents();
	void clean();

	// a function to access the private running variable
	bool running() { return m_bRunning; }


	// getters
	SDL_Renderer* getRenderer();
	glm::vec2 getMousePosition();
	FSM& GetFSM();

	// int* m_pCurrentMap[12][20];

	// Functions to create and delete game objects. Will likely need to update these functions to include level maps when more than 1 level is implemented.
	void createGameObjects();
	void deleteGameObjects();
	bool getObjectsCreated();

	// Functions which return pointers to game objects for use in other classes (Currently unused ones are commented out)
	Player* getPlayerObject();
	Bomb* getBombObject();
	Explosion* getExplosionObject();
	std::vector<Wall*>* getWallVector(); // Returns pointer to wall vector (of pointers to wall objects)
	std::vector<Enemy*>* getEnemyVector(); // Returns pointer to enemy vector

	// Mousebutton getter/setter
	bool getMouseBtn(int i);
	void setMouseBtn(int i, bool state);

private:
	Game();
	~Game();

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	FSM* m_pFSM; // Pointer to a state machine instance.
	
	int m_currentFrame;

	bool m_bRunning;

	bool m_bObjectsCreated = false; // Bool is set to true when game objects are created, set to false when they are deleted.
	
	// Bool array for mousebuttons (0 = Left, 1 = Right)
	bool m_bMouseBtn[2] = { false, false };
	
	static Game* s_pInstance;

	// GameObjects
	Map* m_pGameMap; // Map class used to load current level
	Player* m_pPlayer;
	Bomb* m_pBomb; // May need to make a vector later
	Explosion* m_pExplosion; // May need to make a vector later



	// Vector of Wall GameObjects
	std::vector<Wall*> m_pWallVec;

	// Vector of Enemy GameObjects
	std::vector<Enemy*> m_pEnemyVec;
	
	const Uint8* m_iKeystates; // Keyboard state container.
	
	glm::vec2 m_mousePosition; // Holds vector of mouse position on screen.
};

typedef Game TheGame;

#endif  defined (__Game__) 