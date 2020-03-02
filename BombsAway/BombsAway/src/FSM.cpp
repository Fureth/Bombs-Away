#include "FSM.h"
#include "Game.h"
#include <iostream>

// Begin State.
void State::render()
{
	SDL_RenderPresent(Game::Instance()->getRenderer());
}

void State::resume() {}

StateType State::getStateType()
{
	return m_stateType;
}

void State::setType(StateType newType)
{
	m_stateType = newType;
}

// End State.

// Begin PauseState.
PauseState::PauseState()
{
	std::cout << "Rendering Pause..." << std::endl;
	TheTextureManager::Instance()->load("../Assets/textures/Pause.png", "pause", TheGame::Instance()->getRenderer());
	setType(PAUSE);
}

void PauseState::enter()
{
	std::cout << "Entering Pause..." << std::endl;
	TheSoundManager::Instance()->pauseMusic();
}

void PauseState::update()
{
	if (Game::Instance()->getMouseBtn(0))
	{
		if ((506 <= Game::Instance()->getMousePosition().x) && (Game::Instance()->getMousePosition().x <= 765) && (358 <= Game::Instance()->getMousePosition().y) && (Game::Instance()->getMousePosition().y <= 436))
		{
			Game::Instance()->GetFSM().popState();
		}
		else if ((508 <= Game::Instance()->getMousePosition().x) && (Game::Instance()->getMousePosition().x <= 763) && (459 <= Game::Instance()->getMousePosition().y) && (Game::Instance()->getMousePosition().y <= 533))
		{
			Game::Instance()->setMouseBtn(0, false);
			Game::Instance()->GetFSM().popState();
			Game::Instance()->GetFSM().changeState(new TitleState());
			Game::Instance()->deleteGameObjects();
		}
	}
}

void PauseState::render()
{
	TheTextureManager::Instance()->draw("pause", 320, 192, TheGame::Instance()->getRenderer(), false);
	//State::render();
}

void PauseState::exit()
{
	std::cout << "Exiting Pause..." << std::endl;
	TheSoundManager::Instance()->resumeMusic();
}
// End PauseState.

// Begin GameState.
GameState::GameState()
{
	std::cout << "Rendering Game..." << std::endl;
	TheTextureManager::Instance()->load("../Assets/textures/Game.png", "game", TheGame::Instance()->getRenderer());

	TheSoundManager::Instance()->load("../Assets/audio/backgroundMusic.WAV",
		"bgm", sound_type::SOUND_MUSIC);

	TheSoundManager::Instance()->playMusic("bgm", -1);

	setType(GAME);
}

void GameState::enter()
{
	std::cout << "Entering Game..." << std::endl;
}

void GameState::update()
{
	if (Game::Instance()->checkForKeystroke(SDL_SCANCODE_P))
	{
		Game::Instance()->GetFSM().pushState(new PauseState());
	}
}

void GameState::render()
{
	TheTextureManager::Instance()->draw("game", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, TheGame::Instance()->getRenderer());
}

void GameState::exit()
{
	std::cout << "Exiting Game..." << std::endl;
}

void GameState::resume()
{
	std::cout << "Resuming Game..." << std::endl;
}
// End GameState.

// Begin TitleState.
TitleState::TitleState()
{
	if (TheSoundManager::Instance()->musicPlaying())
	{
		TheSoundManager::Instance()->stopMusic();
	}
	std::cout << "Rendering Title..." << std::endl;
	TheTextureManager::Instance()->load("../Assets/textures/Title.png", "title", TheGame::Instance()->getRenderer());
	setType(TITLE);
}

void TitleState::enter()
{
	std::cout << "Entering Title..." << std::endl;
}

void TitleState::update()
{
	if (Game::Instance()->getMouseBtn(0))
	{
		if ((408 <= Game::Instance()->getMousePosition().x) && (Game::Instance()->getMousePosition().x <= 759) && (550 <= Game::Instance()->getMousePosition().y) && (Game::Instance()->getMousePosition().y <= 670))
		{
			// Start new game
			Game::Instance()->GetFSM().changeState(new GameState());
			Game::Instance()->createGameObjects();
		}
		else if ((416 <= Game::Instance()->getMousePosition().x) && (Game::Instance()->getMousePosition().x <= 755) && (720 <= Game::Instance()->getMousePosition().y) && (Game::Instance()->getMousePosition().y <= 835))
		{
			// Controls page
			std::cout << "There is no controls page at this moment!" << std::endl;
			std::cout << "Movement: W = up, A = left, S = down, D = right" << std::endl;
			std::cout << "Press space to lay a bomb, and \'p\' to pause" << std::endl;
		}
	}
}

void TitleState::render()
{
	TheTextureManager::Instance()->draw("title", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, TheGame::Instance()->getRenderer());
	//State::render();
}

void TitleState::exit()
{
	std::cout << "Exiting Title..." << std::endl;
}
// End TitleState.

// Begin FSM.
FSM::FSM() {}
FSM::~FSM() {}

void FSM::update()
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->update(); // Invokes the Update of the current state.
	}
}

void FSM::render()
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->render(); // Invokes the Render of the current state.
	}
}
void FSM::changeState(State* pState)
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->exit(); // Invokes the Exit of the current state.
		delete m_vStates.back(); // Deallocates current state.
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	//PushState(pState);
	pState->enter(); // Invoke the Enter of the NEW current state.
	m_vStates.push_back(pState); // Push the address of the NEW current state into the vector.
}

void FSM::pushState(State* pState)
{
	pState->enter(); // Invoke the Enter of the NEW current state.
	m_vStates.push_back(pState); // Push the address of the NEW current state into the vector.
}

void FSM::popState() // e.g. PauseState to GameState.
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->exit(); // Invokes the Exit of the current state.
		delete m_vStates.back(); // Deallocates current state.
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	m_vStates.back()->resume();
}

void FSM::clean()
{
	while (!m_vStates.empty())
	{
		m_vStates.back()->exit(); // Invokes the Exit of the current state.
		delete m_vStates.back(); // Deallocates current state.
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
}

vector<State*>& FSM::getStates()
{
	return m_vStates;
}

// End FSM.
