#include "MakeLevelFactory.h"
#include <GameObject.h>
#include "Disc.h"
#include "LevelCube.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Texture2D.h"
#include "../Enums.h"
#include <SDL3/SDL.h>


int game::MakeLevelFactory::m_CubeHeightOffset = 8;

game::Level* game::MakeLevelFactory::CreateLevel(dae::Scene& scene, game::Score* score,
	LevelSettings levelSettings)
{
	int windowWidth = 1024, windowHeight = 576;

	auto levelObject = std::make_unique<dae::GameObject>();
	auto level = std::make_unique<Level>(levelObject.get(),levelSettings.levelSize, levelSettings.discAmount, score);
	

	int levelMiddleX = windowWidth / 2;
	int levelMiddleY = windowHeight / 2;

	levelObject->SetLocalPosition(static_cast<float>(levelMiddleX), static_cast<float>(levelMiddleY), 0);
	levelObject->SetWorldScale(levelSettings.scale, levelSettings.scale);

	//LevelCubes
	std::string cubeTexture1 = "CubeStage1.png";
	std::string cubeTexture2 = "CubeStage2.png";
	std::string cubeTexture3 = "CubeStage3.png";

	auto cubeSize = dae::ResourceManager::GetInstance().LoadTexture("Sprites/" + cubeTexture1)->GetSize();
	cubeSize *= 2;
	dae::ResourceManager::GetInstance().LoadTexture("Sprites/" + cubeTexture2);
	dae::ResourceManager::GetInstance().LoadTexture("Sprites/" + cubeTexture3);

	int heightIncrement = static_cast<int>(cubeSize.y) - m_CubeHeightOffset - 10;
	int levelHeight = heightIncrement * levelSettings.levelSize + m_CubeHeightOffset;
	int startHeight = -levelHeight / 2;
	for (int row = 0; row < levelSettings.levelSize; ++row)
	{
		for (int col = 0; col <= row; ++col)
		{
			auto cubeObject = std::make_unique<dae::GameObject>();
			auto renderComponent = std::make_unique<dae::RenderComponent>(cubeObject.get(), cubeTexture1);
			cubeObject->SetWorldScale(cubeSize.x, cubeSize.y);
			cubeObject->AddComponent(std::move(renderComponent));

			auto levelCube = std::make_unique<LevelCube>(cubeObject.get(), LevelType::Single, level.get(), row, col, glm::vec3(16, 8, 0),
				glm::vec3(24, 20, 0), glm::vec3(8, 20, 0));
			levelCube->SetTexture(cubeTexture1, 0);
			levelCube->SetTexture(cubeTexture2, 1);
			levelCube->SetTexture(cubeTexture3, 2);
			levelCube->SetCurrentTexture();


			level->SetLevel(levelCube.get(), row, col);

			levelCube->AddObserver(level.get());
			cubeObject->AddComponent(std::move(levelCube));

			float halfRowOffset = (row + 1) * (-cubeSize.x * 0.5f);
			float colOffset = col * cubeSize.y;

			float x = static_cast<float>(halfRowOffset + colOffset);
			float y = static_cast<float>(startHeight + heightIncrement * row);

			cubeObject->SetLocalPosition(x, y, 0);
			levelObject->AddChild(std::move(cubeObject));
		}
	}

	//Discs
	std::string discTexture = "Disc.png";
	auto discSize = dae::ResourceManager::GetInstance().LoadTexture("Sprites/" + discTexture)->GetSize();

	CreateDisc(level.get(), levelObject.get(), cubeSize, heightIncrement, startHeight, discTexture, discSize, 5, -1);
	CreateDisc(level.get(), levelObject.get(), cubeSize, heightIncrement, startHeight, discTexture, discSize, 5, 6);
	/**/
	level->ActivateDiscs();
	auto levelPointer = level.get();
	levelObject->AddComponent(std::move(level));
	scene.Add(std::move(levelObject));
	return levelPointer;
}

void game::MakeLevelFactory::CreateDisc(Level* level, dae::GameObject* levelObject,
	glm::vec2 cubeSize, int heightIncrement, int startHeight,
	std::string discTexture, glm::vec2 discSize,
	int row, int col)
{
	auto discObject = std::make_unique<dae::GameObject>();

	auto disc = std::make_unique<Disc>( discObject.get(), level, row, col, glm::vec3(8, 6, 0));
	disc->AddObserver(level);
	level->SetLevel(disc.get(), row, col);

	auto renderComponent = std::make_unique<dae::RenderComponent>(discObject.get(), discTexture);
	renderComponent->SetTexture(discTexture);

	discObject->AddComponent(std::move(disc));
	discObject->AddComponent(std::move(renderComponent));

	float x = static_cast<float>((row + 1) * -cubeSize.x / 2 + col * cubeSize.x + (cubeSize.x - discSize.x) / 2);
	float y = static_cast<float>(startHeight + heightIncrement * row + cubeSize.y - discSize.y);

	discObject->SetLocalPosition(x, y, 0);
	discObject->SetActive(false);
	levelObject->AddChild(std::move(discObject));
}
