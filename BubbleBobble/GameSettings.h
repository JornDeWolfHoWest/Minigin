#pragma once
#include "LevelParser.h"
#include "Singleton.h"

namespace dae
{
	class GameSettings final : public Singleton<GameSettings>
	{
	public:
		enum class GameState
		{
			Singleplayer,
			Coop,
			Versus,
			Selection,
			Gameover
		};
	public:
		GameSettings() = default;
		~GameSettings() = default;

		GameSettings(const GameSettings& other) = delete;
		GameSettings(GameSettings&& other) = delete;
		GameSettings& operator=(const GameSettings& other) = delete;
		GameSettings& operator=(GameSettings&& other) = delete;

		void Init();
		LevelParser* GetParser() {
			if (!m_pParser)
			{
				m_pParser = std::make_unique<LevelParser>();
			}
			return m_pParser.get();
		}
		void SetGameState(GameState type, int level = 1);
		void SetChangeLevelFlag(int level);

		GameState GetGameState() const { return m_GameType; }
		void Update();
		void SaveScore(int score);
		int GetScore() const { return m_Score; }

		int GetCurrentLevel() const { return m_NewLevel; }

	private:
		bool m_ChangeLevelFlag{ false };
		int m_NewLevel{ 0 };
		int m_Score{ 0 };
		std::unique_ptr<LevelParser> m_pParser{};
		GameState m_GameType{ GameState::Selection };

		void CreateSingleplayerScene(int level);
		void CreateMultiplayerScene(int level);
		void CreateVersusScene();
		void CreateGameOverScene();
	};
};
