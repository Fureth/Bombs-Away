#include "UIManager.h"
#include "Game.h"

UIManager::UIManager()
{
	
}

UIManager::~UIManager()
{
}

void UIManager::loadUI()
{
	TheTextureManager::Instance()->load("../Assets/textures/HUD.png", "UIbase", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/Health.png", "HP", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/Time.png", "time", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/Player_1.png", "P1", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/Out_Of_Lives.png", "0HP", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/Power_Up_Box.png", "PuP", TheGame::Instance()->getRenderer());

	// Numbers
	TheTextureManager::Instance()->load("../Assets/textures/num0.png", "0", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/num1.png", "1", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/num2.png", "2", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/num3.png", "3", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/num4.png", "4", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/num5.png", "5", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/num6.png", "6", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/num7.png", "7", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/num8.png", "8", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/num9.png", "9", TheGame::Instance()->getRenderer());
}

void UIManager::displayUI()
{
	// Base of UI
	TheTextureManager::Instance()->draw("PuP", 0, 50, WINDOW_WIDTH, 160, TheGame::Instance()->getRenderer());

	// Timer
	TheTextureManager::Instance()->draw("time", 389, 0, 200, 70, TheGame::Instance()->getRenderer());
	int tens = TheGame::Instance()->getTimer() / 10;
	int ones = TheGame::Instance()->getTimer() % 10;
	switch (tens)
	{
	case 0:
		TheTextureManager::Instance()->draw("0", 500, -4, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 1:
		TheTextureManager::Instance()->draw("1", 500, -5, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 2:
		TheTextureManager::Instance()->draw("2", 510, -5, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 3:
		TheTextureManager::Instance()->draw("3", 495, 0, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 4:
		TheTextureManager::Instance()->draw("4", 510, 5, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 5:
		TheTextureManager::Instance()->draw("5", 505, 0, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 6:
		TheTextureManager::Instance()->draw("6", 505, 6, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 7:
		TheTextureManager::Instance()->draw("7", 510, 6, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 8:
		TheTextureManager::Instance()->draw("8", 515, 7, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 9:
		TheTextureManager::Instance()->draw("9", 525, 7, 80, 70, TheGame::Instance()->getRenderer());
		break;
	}
	switch (ones)
	{
	case 0:
		TheTextureManager::Instance()->draw("0", 520, -4, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 1:
		TheTextureManager::Instance()->draw("1", 520, -5, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 2:
		TheTextureManager::Instance()->draw("2", 530, -5, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 3:
		TheTextureManager::Instance()->draw("3", 515, 0, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 4:
		TheTextureManager::Instance()->draw("4", 530, 5, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 5:
		TheTextureManager::Instance()->draw("5", 525, 0, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 6:
		TheTextureManager::Instance()->draw("6", 525, 6, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 7:
		TheTextureManager::Instance()->draw("7", 530, 6, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 8:
		TheTextureManager::Instance()->draw("8", 535, 7, 80, 70, TheGame::Instance()->getRenderer());
		break;
	case 9:
		TheTextureManager::Instance()->draw("9", 545, 7, 80, 70, TheGame::Instance()->getRenderer());
		break;
	}

	// Player HP status
	TheTextureManager::Instance()->draw("P1", 0, 40, 200, 70, TheGame::Instance()->getRenderer());
	if (TheGame::Instance()->getPlayerObject()->getHealth() == 0)
	{
		TheTextureManager::Instance()->draw("0HP", 0, 75, 180, 60, TheGame::Instance()->getRenderer());
	}
	else
	{
		int spacer = -8;
		for (int i = 0; i < TheGame::Instance()->getPlayerObject()->getHealth(); i++)
		{
			spacer += 40;
			TheTextureManager::Instance()->draw("HP", spacer, 80, 40, 35, TheGame::Instance()->getRenderer());
		}
	}

}

	// 0
	//TheTextureManager::Instance()->draw("0", 500, 0, 80, 70, TheGame::Instance()->getRenderer());
	//TheTextureManager::Instance()->draw("0", 520, 0, 80, 70, TheGame::Instance()->getRenderer());
	// 1
	//TheTextureManager::Instance()->draw("1", 500, -5, 80, 70, TheGame::Instance()->getRenderer());
	//TheTextureManager::Instance()->draw("1", 520, -5, 80, 70, TheGame::Instance()->getRenderer());
	// 2
	//TheTextureManager::Instance()->draw("2", 510, -5, 80, 70, TheGame::Instance()->getRenderer());
	//TheTextureManager::Instance()->draw("2", 530, -5, 80, 70, TheGame::Instance()->getRenderer());
	// 3
	//TheTextureManager::Instance()->draw("3", 495, 0, 80, 70, TheGame::Instance()->getRenderer());
	//TheTextureManager::Instance()->draw("3", 515, 0, 80, 70, TheGame::Instance()->getRenderer());
	// 4
	//TheTextureManager::Instance()->draw("4", 510, 5, 80, 70, TheGame::Instance()->getRenderer());
	//TheTextureManager::Instance()->draw("4", 530, 5, 80, 70, TheGame::Instance()->getRenderer());
	// 5
	//TheTextureManager::Instance()->draw("5", 505, 0, 80, 70, TheGame::Instance()->getRenderer());
	//TheTextureManager::Instance()->draw("5", 525, 0, 80, 70, TheGame::Instance()->getRenderer());
	// 6
	//TheTextureManager::Instance()->draw("6", 505, 5, 80, 70, TheGame::Instance()->getRenderer());
	//TheTextureManager::Instance()->draw("6", 525, 5, 80, 70, TheGame::Instance()->getRenderer());
	// 7
	//TheTextureManager::Instance()->draw("7", 510, 5, 80, 70, TheGame::Instance()->getRenderer());
	//TheTextureManager::Instance()->draw("7", 530, 5, 80, 70, TheGame::Instance()->getRenderer());
	// 8
	//TheTextureManager::Instance()->draw("8", 515, 5, 80, 70, TheGame::Instance()->getRenderer());
	//TheTextureManager::Instance()->draw("8", 535, 5, 80, 70, TheGame::Instance()->getRenderer());
	// 9
	//TheTextureManager::Instance()->draw("9", 525, 2, 80, 70, TheGame::Instance()->getRenderer());
	//TheTextureManager::Instance()->draw("9", 545, 2, 80, 70, TheGame::Instance()->getRenderer());