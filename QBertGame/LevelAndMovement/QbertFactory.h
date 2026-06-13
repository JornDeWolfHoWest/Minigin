#pragma once
#include <memory>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)
#include "Qbert.h"

namespace dae
{
	class Scene;
	class Font;
}

namespace game
{
	enum class Player;
	class Walkable;

	class QbertFactory
	{
	public:
		static game::Qbert* CreateQbert(dae::Scene& scene, Walkable* startCube,
			game::Player player, const std::shared_ptr<dae::Font>& font);

	};
}
