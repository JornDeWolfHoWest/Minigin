#include "LevelCubeActivator.h"

game::LevelCubeActivator::LevelCubeActivator(dae::GameObject* owner, bool forward) :
	dae::BaseComponent(owner),
	m_Forward(forward)
{}
