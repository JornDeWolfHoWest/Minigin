#include "GameDone.h"
#include <GameObject.h>


void game::GameDone::LevelDisc()
{}

void game::GameDone::NextLevel()
{}

void game::GameDone::GameComplete()
{
	GetOwner()->SetActive(true);
}
