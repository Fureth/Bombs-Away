#pragma once
#ifndef __UIManager__
#define __UIManager__

#include "Game.h"

class UIManager
{
public:
	/*static UIManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new UIManager();
			return s_pInstance;
		}

		return s_pInstance;
	}*/

	static void loadUI();
	static void displayUI();
	
private:
	UIManager();
	~UIManager();

	//static UIManager* s_pInstance;
};

typedef UIManager UI;

#endif /* defined(__UIManager__) */