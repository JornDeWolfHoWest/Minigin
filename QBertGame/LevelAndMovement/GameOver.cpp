#include "GameOver.h"
#include "GameObject.h"

void game::GameOver::QbertLives(int lives)
{
	if (lives != 0)
	{
		return;
	}
	GetOwner()->SetActive(true);
}