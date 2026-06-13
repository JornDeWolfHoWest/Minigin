#pragma once
#include <memory>

#include "Level.h"
#include "Texture2D.h"

namespace dae
{
	class Scene;
}

namespace game
{
	class MakeLevelFactory
	{
	public:
		static Level* CreateLevel(dae::Scene& scene,
			Score* score = nullptr,
			LevelSettings levelSettings = LevelSettings{});

	private:
		static void CreateDisc(Level* level, dae::GameObject* levelObject,
			glm::vec2 cubeSize, int heightIncrement, int startHeight,
			std::string discTexture, glm::vec2 discSize, int row,
			int col);

		static int m_CubeHeightOffset;
	};
}
