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
		if ((506 <= Game::Instance()->getMousePosition().x) && (Game::Instance()->getMousePosition().x <= 765) && (458 <= Game::Instance()->getMousePosition().y) && (Game::Instance()->getMousePosition().y <= 536))
		{
			Game::Instance()->GetFSM().popState();
		}
		else if ((508 <= Game::Instance()->getMousePosition().x) && (Game::Instance()->getMousePosition().x <= 763) && (559 <= Game::Instance()->getMousePosition().y) && (Game::Instance()->getMousePosition().y <= 633))
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
	TheTextureManager::Instance()->draw("pause", 320, 292, TheGame::Instance()->getRenderer(), false);
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

	/*TheSoundManager::Instance()->load("../Assets/audio/nya.WAV",
		"bgm", sound_type::SOUND_MUSIC);

	TheSoundManager::Instance()->playMusic("bgm", -1);*/

	setType(GAME);
}

void GameState::enter()
{
	std::cout << "Entering Game..." << std::endl;
	TheSoundManager::Instance()->playMusic("bgm", -1);
}

void GameState::update()
{
	if (Game::Instance()->checkForKeystroke(SDL_SCANCODE_P))
	{
		Game::Instance()->GetFSM().pushState(new PauseState());
	}
	if (Game::Instance()->getPlayerObject()->getIsActive() == false) // If player is dead...
	{
		// Game Over!
		Game::Instance()->GetFSM().pushState(new LoseState());
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
		if ((451 <= Game::Instance()->getMousePosition().x) && (Game::Instance()->getMousePosition().x <= 830) && (388 <= Game::Instance()->getMousePosition().y) && (Game::Instance()->getMousePosition().y <= 513))
		{
			// Start new game
			Game::Instance()->setCurrentLevel(0);
			Game::Instance()->GetFSM().changeState(new GameState());
			Game::Instance()->createGameObjects();
		}
		else if ((466 <= Game::Instance()->getMousePosition().x) && (Game::Instance()->getMousePosition().x <= 817) && (584 <= Game::Instance()->getMousePosition().y) && (Game::Instance()->getMousePosition().y <= 688))
		{
			// Controls page
			Game::Instance()->GetFSM().changeState(new OptionsState());
		}
		else if ((531 <= Game::Instance()->getMousePosition().x) && (Game::Instance()->getMousePosition().x <= 752) && (751 <= Game::Instance()->getMousePosition().y) && (Game::Instance()->getMousePosition().y <= 850))
		{
			// Quit
			Game::Instance()->exitGame();
		}
	}
	if (Game::Instance()->checkForKeystroke(SDL_SCANCODE_SEMICOLON))
	{
		Game::Instance()->setCurrentLevel(-2);
		Game::Instance()->GetFSM().changeState(new Dev());
		Game::Instance()->createGameObjects();
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
// End Title

// Begin Options (labeled as this in case we decide to change to options rather than just controls later)
OptionsState::OptionsState()
{
	std::cout << "Rendering Controls...\n";
	TheTextureManager::Instance()->load("../Assets/textures/Controls.png", "controls", TheGame::Instance()->getRenderer());
	setType(OPTIONS);
}

void OptionsState::enter()
{
	std::cout << "Entering Controls..." << std::endl;
}

void OptionsState::update()
{
	if (Game::Instance()->getMouseBtn(0))
	{
		if ((1024 <= Game::Instance()->getMousePosition().x) && (Game::Instance()->getMousePosition().x <= 1244) && (28 <= Game::Instance()->getMousePosition().y) && (Game::Instance()->getMousePosition().y <= 100))
		{
			// Back to Title page
			Game::Instance()->GetFSM().changeState(new TitleState());
		}
	}
}

void OptionsState::render()
{
	TheTextureManager::Instance()->draw("controls", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, TheGame::Instance()->getRenderer());
}

void OptionsState::exit()
{
	std::cout << "Exiting Controls..." << std::endl;
}
// End Options

// Begin Lose
LoseState::LoseState()
{
	std::cout << "Rendering GameOver..." << std::endl;
	TheTextureManager::Instance()->load("../Assets/textures/GameOver.png", "lose", TheGame::Instance()->getRenderer());
	setType(LOSE);
}

void LoseState::enter()
{
	std::cout << "Entering GameOver..." << std::endl;
}

void LoseState::update()
{
	if (Game::Instance()->getMouseBtn(0))
	{
		if ((732 <= Game::Instance()->getMousePosition().x) && (Game::Instance()->getMousePosition().x <= 1126) && (664 <= Game::Instance()->getMousePosition().y) && (Game::Instance()->getMousePosition().y <= 768))
		{
			Game::Instance()->setMouseBtn(0, false);
			Game::Instance()->GetFSM().popState();
			Game::Instance()->GetFSM().changeState(new TitleState());
			Game::Instance()->deleteGameObjects();
		}
	}
}

void LoseState::render()
{
	TheTextureManager::Instance()->draw("lose", 140, 378, 1000, 400, TheGame::Instance()->getRenderer());
}

void LoseState::exit()
{
	std::cout << "Exiting To Title..." << std::endl;
}
// End Lose

// Begin Win
WinState::WinState()
{
    std::cout << "Rendering Winning screen..." << std::endl;
    TheTextureManager::Instance()->load("../Assets/textures/winScreen.png", "win", TheGame::Instance()->getRenderer());
    setType(WIN);
}

void WinState::enter()
{
    std::cout << "Entering Winning screen..." << std::endl;
}

void WinState::update()
{
    
    if (Game::Instance()->getMouseBtn(0))
    {
        if ((653 <= Game::Instance()->getMousePosition().x) && (Game::Instance()->getMousePosition().x <= 1091) && (613 <= Game::Instance()->getMousePosition().y) && (Game::Instance()->getMousePosition().y <= 745))
        {
            Game::Instance()->setMouseBtn(0, false);
            Game::Instance()->GetFSM().popState(); // Remove winstate
			Game::Instance()->deleteGameObjects(); // Delete the current gameobjects/map
			Game::Instance()->setCurrentLevel(Game::Instance()->getCurrentLevel() + 1);
			if (Game::Instance()->getCurrentLevel() == -1 || Game::Instance()->getCurrentLevel() > 3) // If attempting to go to new level from test
        	{
				Game::Instance()->GetFSM().changeState(new TitleState()); // Change to title
        	}
			else // Otherwise go to next level
			{
				Game::Instance()->GetFSM().changeState(new GameState()); // Change to a new gamestate, which reloads the new map
				Game::Instance()->createGameObjects();
			}
        }
    }
}

void WinState::render()
{
    TheTextureManager::Instance()->draw("win", 140, 378, 1000, 400, TheGame::Instance()->getRenderer());
}

void WinState::exit()
{
    std::cout << "Moving to next level..." << std::endl;
}
//End Win

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

// Begin Dev State

Dev::Dev()
{
	setType(TEST);
}

void Dev::enter()
{
	std::cout << "Entering Dev Mode...\n";
}

void Dev::update()
{
}

void Dev::render()
{
}

void Dev::exit()
{
}

// End Dev State