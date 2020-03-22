#include "Game.h"

Game* Game::s_pInstance = 0;

SDL_Renderer* Game::getRenderer()
{
	return m_pRenderer;
}

glm::vec2 Game::getMousePosition()
{
	return m_mousePosition;
}

SDL_Renderer* getRenderer();

bool Game::checkForKeystroke(SDL_Scancode c)
{
	if (m_iKeystates != nullptr)
	{
		if (m_iKeystates[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}

<<<<<<< HEAD
=======
int Game::getCurrentLevel()
{
	return m_currentLevel;
}

void Game::setCurrentLevel(int newLevel)
{
	m_currentLevel = newLevel;
}

void Game::exitGame()
{
	m_bRunning = false;
}

>>>>>>> dc3582c195962cae77a3339080af0a0c60d66708
Game::Game()
{
	m_iKeystates = SDL_GetKeyboardState(nullptr); // start reading keyboard states, returns pointer
	srand(time(NULL)); // Initialize randomness for entire game, currently not used with the mapping build
}

Game::~Game()
{
}

void Game::createGameObjects()
{
	if (!m_bObjectsCreated)
	{
		m_pPlayer = new Player();
		m_pBomb = new Bomb();
		m_pExplosion = new Explosion();
		m_pGameMap = new Map();

		m_pGameMap->LoadMap(firstLevel);
		m_pGameMap->DrawMap();

		setTimer(99);
		timerCount = 0;

		m_bObjectsCreated = true;
	}
}

void Game::deleteGameObjects()
{
	if (m_bObjectsCreated)
	{
		delete m_pPlayer;
		delete m_pBomb;
		delete m_pExplosion;
		delete m_pGameMap;

		m_pPlayer = nullptr;
		m_pBomb = nullptr;
		m_pExplosion = nullptr;
		m_pGameMap = nullptr;

		if (!m_pWallVec.empty())
		{
			for (auto& currentWall : m_pWallVec)
			{
				currentWall = nullptr;
			}
			m_pWallVec.erase(remove(m_pWallVec.begin(), m_pWallVec.end(), nullptr), m_pWallVec.end());
		}
		if (!m_pEnemyVec.empty())
		{
			for (auto& currentEnemy : m_pEnemyVec)
			{
				currentEnemy = nullptr;
			}
			m_pEnemyVec.erase(remove(m_pEnemyVec.begin(), m_pEnemyVec.end(), nullptr), m_pEnemyVec.end());
		}
		if (!m_pPowerupVec.empty())
		{
			for (auto& currentPowerup : m_pPowerupVec)
			{
				currentPowerup = nullptr;
			}
			m_pPowerupVec.erase(remove(m_pPowerupVec.begin(), m_pPowerupVec.end(), nullptr), m_pPowerupVec.end());
		}

		m_bObjectsCreated = false;
	}
}

bool Game::getObjectsCreated()
{
	return m_bObjectsCreated;
}

Player* Game::getPlayerObject()
{
	return m_pPlayer;
}

Bomb* Game::getBombObject()
{
	return m_pBomb;
}

Explosion* Game::getExplosionObject()
{
	return m_pExplosion;
}

std::vector<Wall*>* Game::getWallVector()
{
	return &m_pWallVec;
}

std::vector<Enemy*>* Game::getEnemyVector()
{
	return &m_pEnemyVec;
}

std::vector<Powerup*>* Game::getPowerupVector()
{
	return &m_pPowerupVec;
}

bool Game::init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL Init success" << std::endl;

		// if succeeded create our window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

		// if window creation successful create our renderer
		if (m_pWindow != 0)
		{
			std::cout << "window creation success" << std::endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) // render init success
			{
				std::cout << "renderer creation success" << std::endl;
				
			}
			else
			{
				std::cout << "renderer init failure" << std::endl;
				return false; // render int fail
			} 
		}
		else
		{
			std::cout << "window init failure" << std::endl;
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init failure" << std::endl;
		return false; //SDL could not intialize
	}
	m_pFSM = new FSM();
	m_pFSM->changeState(new TitleState());

	// Load UI
	UI::loadUI();
	
	std::cout << "init success" << std::endl;
	m_bRunning = true; // everything initialized successfully - start the main loop
	

	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	// Order of rendering: FSM (Background) >> Bomb >> Player >> Enemy >> Walls >> Explosion >> FSM (Overlaid screen, if applicable)
	switch (GetFSM().getStates().back()->getStateType())
	{
	case TITLE: // Renders just the title screen.
		m_pFSM->render();
		break;
	case GAME: // Renders game background and all game objects.
		m_pFSM->render();

		// Can turn this block of code into a "render game objects" function
		m_pBomb->draw();
		m_pPlayer->draw();
		for (auto& currentPowerup : m_pPowerupVec)
		{
			currentPowerup->draw();
		}
		for (auto& currentEnemy : m_pEnemyVec)
		{
			currentEnemy->draw();
		}
		for (auto& currentWall : m_pWallVec)
		{
			currentWall->draw();
		}
		m_pExplosion->draw();
		// End block

		break;
	case PAUSE: // Renders game background and all game objects, as well as the pause screen on top.
		Instance()->GetFSM().getStates().front()->render(); // Invoke Render of GameState.

		// Can turn this block of code into a "render game objects" function
		m_pBomb->draw();
		m_pPlayer->draw();
		for (auto& currentPowerup : m_pPowerupVec)
		{
			currentPowerup->draw();
		}
		for (auto& currentEnemy : m_pEnemyVec)
		{
			currentEnemy->draw();
		}
		for (auto& currentWall : m_pWallVec)
		{
			currentWall->draw();
		}
		m_pExplosion->draw();
		// End block

		m_pFSM->render();
		break;
	case OPTIONS:
		m_pFSM->render();
		break;
	case LOSE: // Same as Pause
		Instance()->GetFSM().getStates().front()->render(); // Invoke Render of GameState.

		// Can turn this block of code into a "render game objects" function
		m_pBomb->draw();
		m_pPlayer->draw();
		for (auto& currentPowerup : m_pPowerupVec)
		{
			currentPowerup->draw();
		}
		for (auto& currentEnemy : m_pEnemyVec)
		{
			currentEnemy->draw();
		}
		for (auto& currentWall : m_pWallVec)
		{
			currentWall->draw();
		}
		m_pExplosion->draw();
		// End block

		m_pFSM->render();
		break;
	default:
		break;
	}
	
	if (m_pFSM->getStates().back()->getStateType() != TITLE && m_pFSM->getStates().back()->getStateType() != OPTIONS)
	{
		UI::displayUI();
	}

	SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
	// Order of updates: FSM >> Player >> Bomb >> Explosion >> Enemy >> Wall
	switch (GetFSM().getStates().back()->getStateType())
	{
	case TITLE: // When at title only check for FSM updates
		m_pFSM->update();
		break;
	case GAME: // Must update all game objects when in the game, and also check for FSM updates
	{
		m_pFSM->update();
		m_pPlayer->update();
		m_pBomb->update();

		// Might be able to move this into explosion class, although it seems unlikely due to collision calls
		if (m_pExplosion->getExplosion())
		{
			// Explosion vs Wall
			for (auto& currentWall : m_pWallVec)
			{
				Collision::basicCollisionCheck(m_pExplosion, currentWall);
				currentWall->update();
				if (currentWall->getDestruction())
				{
					m_pGameMap->currentMap[currentWall->getY()][currentWall->getX()] = 0;
					delete currentWall;
					currentWall = nullptr;
				}
			}

			// Explosion vs player
			Collision::basicCollisionCheck(m_pExplosion, m_pPlayer);

			// Explosion vs Enemies
			for (auto& currentEnemy : m_pEnemyVec)
			{
				Collision::basicCollisionCheck(m_pExplosion, currentEnemy);
				if (!currentEnemy->getIsActive())
				{
					delete currentEnemy;
					currentEnemy = nullptr;
				}
				
			}
		}

		m_pExplosion->update();

		// Remove any destroyed walls from vector
		if (!m_pWallVec.empty())
		{
			m_pWallVec.erase(remove(m_pWallVec.begin(), m_pWallVec.end(), nullptr), m_pWallVec.end());
		}

		// Remove any defeated enemies from vector
		if (!m_pEnemyVec.empty())
		{
			m_pEnemyVec.erase(remove(m_pEnemyVec.begin(), m_pEnemyVec.end(), nullptr), m_pEnemyVec.end());
		}
			
		for (auto& currentEnemy : m_pEnemyVec)
		{
			currentEnemy->setIsColliding(Collision::tileCollisionCheck(currentEnemy, m_pGameMap->currentMap));
			currentEnemy->update();
			// Enemy & Player collisions
			Collision::basicCollisionCheck(m_pPlayer, currentEnemy);
		}

		for (auto& currentPowerup : m_pPowerupVec)
		{
			if (Collision::basicCollisionCheck(m_pPlayer, currentPowerup) && !Collision::tileCollisionCheck(m_pPlayer, m_pGameMap->currentMap))
			{
				currentPowerup->setCollected();
			}
			currentPowerup->update();
			if (currentPowerup->getCollected())
			{
				delete currentPowerup;
				currentPowerup = nullptr;
			}
		}
			
		// Remove collected powerups
		if (!m_pPowerupVec.empty())
		{
			m_pPowerupVec.erase(remove(m_pPowerupVec.begin(), m_pPowerupVec.end(), nullptr), m_pPowerupVec.end());

		}
			
		// Player vs Wall collision checker (map based) -- Might be able to change this a bit
		m_pPlayer->setIsColliding(Collision::tileCollisionCheck(m_pPlayer, m_pGameMap->currentMap));
		if (m_pPlayer->getIsColliding())
		{
			m_pPlayer->setIsColliding(Collision::playerCollisionMovement(m_pPlayer, m_pGameMap->currentMap));
		}

		// Decrement game timer
		if (timerCount >= timerCountMax)
		{
			setTimer(getTimer() - 1);
			timerCount = 0;
		}
		else
		{
			timerCount++;
		}
		if (getTimer() == 0)
		{
			m_pPlayer->setIsActive(false);
		}
	}
	break;
	case PAUSE: // When paused only check for FSM updates
		m_pFSM->update();
		break;
	case OPTIONS:
		m_pFSM->update();
		break;
	case LOSE:
		m_pFSM->update();
		break;
	default:
		break;
	}
}

void Game::clean()
{
	std::cout << "cleaning game" << std::endl;

	// Clean statemachine
	m_pFSM->clean();
	delete m_pFSM;
	//m_pFSM = nullptr; // Optional.

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				m_bRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				m_bMouseBtn[0] = true;
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				// These commented lines are to determine the current mouse position
				std::cout << "x: " << getMousePosition().x << std::endl;
				std::cout << "y: " << getMousePosition().y << std::endl;
				m_bMouseBtn[1] = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
				m_bMouseBtn[0] = false;
			if (event.button.button == SDL_BUTTON_RIGHT)
				m_bMouseBtn[1] = false;
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;
		default:
			break;
		}
	}
}


FSM& Game::GetFSM()
{
	return *m_pFSM;
}

bool Game::getMouseBtn(int i)
{
	return m_bMouseBtn[i];
}

void Game::setMouseBtn(int i, bool state)
{
	m_bMouseBtn[i] = state;
}

int Game::getTimer()
{
	return gameTimer;
}

void Game::setTimer(int time)
{
	gameTimer = time;
}
