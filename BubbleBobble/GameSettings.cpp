#include "GameSettings.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include <Scene.h>
#include <InputManager.h>

#include "BubbleBobble/PlayerComponents/ScoreObserverComponent.h"
#include "BubbleBobble/PlayerComponents/HealthObserverComponent.h"
#include "SpriteComponent.h"
#include <TextComponent.h>

namespace dae
{
	void GameSettings::Init()
	{
		m_pParser = std::make_unique<LevelParser>();
	}

	void GameSettings::SetGameState(GameState type, int level)
	{
		m_GameType = type;

		switch (m_GameType)
		{
		case GameState::Gameover:
		case GameState::Selection:
			break;

		case GameState::Singleplayer:
			CreateSingleplayerScene(level);
			break;

		case GameState::Coop:
			CreateMultiplayerScene(level);
			break;

		case GameState::Versus:
			CreateVersusScene();
			break;
		}
		//dae::InputManager::GetInstance().AddKeyCommand(
		//SDLK_F1,
		//{},
		//[]() {
		//	auto currentLevel = dae::GameSettings::GetInstance().GetCurrentLevel();
		//	currentLevel++;
		//	if (currentLevel == 3)
		//	{
		//		dae::GameSettings::GetInstance().SetGameState(dae::GameSettings::GameState::Gameover, -1);
		//		return;
		//	}
		//	dae::GameSettings::GetInstance().SetGameState(dae::GameSettings::GetInstance().GetGameState(),
		//		currentLevel);
		//})
	;
	}

	void GameSettings::SetChangeLevelFlag(int level)
	{
		m_ChangeLevelFlag = true;
		m_NewLevel = level;
	}

	void GameSettings::Update()
	{
		if (m_ChangeLevelFlag)
		{
			m_ChangeLevelFlag = false;

			if (m_GameType == GameState::Singleplayer)
			{
				CreateSingleplayerScene(m_NewLevel);
			}
			if (m_GameType == GameState::Coop)
			{
				CreateMultiplayerScene(m_NewLevel);
			}
		}
	}

	void GameSettings::SaveScore(int score)
	{
		m_Score += score;
	}

	void GameSettings::CreateSingleplayerScene(int level)
	{
		dae::InputManager::GetInstance().DeleteAllKeys();
		dae::SceneManager::GetInstance().RemoveSceneIfExists("LevelScene");
		auto& levelScene = dae::SceneManager::GetInstance().CreateScene("LevelScene");

		// Font
		auto smallFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

		// Score Observer UI
		auto scoreUI = std::make_unique<dae::GameObject>();
		scoreUI->SetLocalPosition(0.0f, 0.0f, 0.0f);
		scoreUI->AddComponent(std::make_unique<dae::TextComponent>(scoreUI.get(), smallFont, " "));
		scoreUI->AddComponent(std::make_unique<dae::ScoreObserverComponent>(scoreUI.get()));
		levelScene.Add(std::move(scoreUI));

		// Health Observer UI
		auto healthUI = std::make_unique<dae::GameObject>();
		healthUI->SetLocalPosition(0.0f, 400.0f, 0.0f);
		healthUI->AddComponent(std::make_unique<dae::TextComponent>(healthUI.get(), smallFont, " "));
		healthUI->AddComponent(std::make_unique<dae::HealthObserverComponent>(healthUI.get()));
		levelScene.Add(std::move(healthUI));

		// Level Parser
		dae::SceneManager::GetInstance().SwitchScene("LevelScene", true);
		m_pParser->Parse(&levelScene, "level" + std::to_string(level) + "Singleplayer.json");
		dae::SceneManager::GetInstance().SwitchScene("StartScreen", true);
	}

	void GameSettings::CreateMultiplayerScene(int ) //level)
	{
		
	}

	void GameSettings::CreateVersusScene()
	{
	}

	void GameSettings::CreateGameOverScene()
	{
		
	}
}