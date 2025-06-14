#include <SDL.h>

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "GameObject.h"
#include <iostream>
#include "Renderer.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "Commands.h"
#include "Player.h"
#include "HealthDisplay.h"
#include "ScoreDisplayComponent.h"
#include "ScoreChangedEvent.h"
#include "HealthChangedEvent.h"
#include "ScoreAchievementComponent.h"
#include "InputManager.h"
#include "ServiceLocator.h"
#include "TextureComponent.h"
#include "SelectorArrow.h"
#include "CheckForPlayerComponent.h"
#include <time.h>
#include <thread>
//steam
#include <steam_api.h>
#include "Player.h"

std::string baseDataPath = "../Data/";

using namespace dae;


class Game
{
public:
	// ToDo move to seperate file

	class MuteCommand : public Command
	{
	public:
		MuteCommand() {}
		void execute() override
		{
			ServiceLocator::GetSoundSystem().SetMute(!ServiceLocator::GetSoundSystem().GetMute());	
		}
	private:
	};
	class StartGameControllerCommand : public Command
	{
	public:
		StartGameControllerCommand(Game* pGame, SelectorArrow* pArrow)
			: m_pGame(pGame), m_pArrow(pArrow) {
		}
		void execute() override
		{
			std::cout << m_pArrow->GetPosition().y;
			if (m_pArrow->GetPosition().y == 210)
			{
				m_pGame->loadGame(4);
			}
			else if (m_pArrow->GetPosition().y == 240)
			{
				m_pGame->loadGame(5);
			}
		}
	private:
		Game* m_pGame{ nullptr };
		SelectorArrow* m_pArrow{ nullptr };
	};
	class StartGameCommand : public Command
	{
	public:
		StartGameCommand(Game* pGame, SelectorArrow* pArrow)
			: m_pGame(pGame), m_pArrow(pArrow) {}
		void execute() override
		{
			std::cout << m_pArrow->GetPosition().y;
			if (m_pArrow->GetPosition().y == 210)
			{
				m_pGame->loadGame(1);
			}
			else if (m_pArrow->GetPosition().y == 240)
			{
				m_pGame->loadGame(2);
			}
		}
	private:
		Game* m_pGame{ nullptr };
		SelectorArrow* m_pArrow{ nullptr };
	};
	class BackToMainMenuCommand : public Command
	{
	public:
		BackToMainMenuCommand(Game* pGame)
			: m_pGame(pGame) {
		}
		void execute() override
		{
			m_pGame->loadMainMenu();
		}
	private:
		Game* m_pGame;
	};
	class UpArrowCommand : public Command
	{
	public:
		UpArrowCommand(SelectorArrow* pArrow)
			: m_pArrow(pArrow) {
		}
		void execute() override
		{
			m_pArrow->ChangePositionY(30);
		}
	private:

		SelectorArrow* m_pArrow;
	};
	class DownArrowCommand : public Command
	{
	public:
		DownArrowCommand(SelectorArrow* pArrow)
			: m_pArrow(pArrow) {
		}
		void execute() override
		{
			m_pArrow->ChangePositionY(-30);
		}
	private:

		SelectorArrow* m_pArrow;
	};
	void loadMainMenu()
	{

		ServiceLocator::GetSoundSystem().StopAllSounds();
		for (auto object : m_GameObjects)
		{
			object.reset();
		}
		m_GameObjects.clear();
		std::cout << "\n\nBegin load Main Menu:\n\n";

		ServiceLocator::GetSoundSystem().PlaySound("Credits");
		auto& input = InputManager::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto otherSpriteSheet = ResourceManager::GetInstance().LoadTexture("OtherSpriteSheet.png");

		input.DeleteAllKeys();
		sceneManager.DeleteAllScenes();
		auto& mainMenuScene = sceneManager.CreateScene("MainMenu");

		input.AddKeyCommand(new KeyCommand{ SDLK_F2, new MuteCommand(), nullptr });

		//go = std::make_shared<dae::GameObject>(nullptr);
		//go->SetTexture("background.tga");
		//mainMenuScene.Add(go);
		//
		//
		//go = std::make_shared<dae::GameObject>(nullptr);
		//go->SetTexture("OtherSpriteSheet.png");
		//go->SetLocalPosition(glm::vec3{ 216, 180 , 0 });
		//mainMenuScene.Add(go);


		gameObject = std::make_shared<dae::GameObject>(nullptr);

		// spawn text in middle
		auto textComponent = new TextComponent("1 Player", ResourceManager::GetInstance().LoadFont("dig-dug-arcade-font.otf", 12), gameObject.get());
		textComponent->SetPosition(220, 220);

		textComponent = new TextComponent("2 Players", ResourceManager::GetInstance().LoadFont("dig-dug-arcade-font.otf", 12), gameObject.get());
		textComponent->SetPosition(220, 250);

		mainMenuScene.Add(gameObject);

		gameObject = std::make_shared<dae::GameObject>(nullptr);
		
		auto textureComponent = new TextureComponent(gameObject.get(), "OtherSpriteSheet.png");
		textureComponent->SetSrcRect(1, 183, 159, 48);
		textureComponent->SetDrawSize(300, 100);
		gameObject->SetLocalPosition(glm::vec3{ 150, 60, 0 });
		mainMenuScene.Add(gameObject);

		gameObject = std::make_shared<dae::GameObject>(nullptr);
		textureComponent = new TextureComponent(gameObject.get(), "OtherSpriteSheet.png");
		textureComponent->SetSrcRect(68, 233, 63, 16);
		textureComponent->SetDrawSize(100, 25);
		gameObject->SetLocalPosition(glm::vec3{ 250, 400, 0});

		mainMenuScene.Add(gameObject);


		// Add arrow
		auto arrowObject = std::make_shared<dae::GameObject>(nullptr);
		// Texture is the > arrow in text
		mainMenuScene.Add(arrowObject);
		auto pText = new TextComponent(">", font, arrowObject.get());
		pText->SetPosition(200, 210);
		m_pArrow = std::make_shared<SelectorArrow>(pText);
		// add command to move arrow
		// sdlk enter
		input.AddKeyCommand(new KeyCommand{ SDLK_SPACE, new StartGameCommand(this, m_pArrow.get()), nullptr });
		input.AddKeyCommand(new KeyCommand{ SDLK_UP, new UpArrowCommand(m_pArrow.get()), nullptr });
		input.AddKeyCommand(new KeyCommand{ SDLK_DOWN, new DownArrowCommand(m_pArrow.get()), nullptr });

		// Controller keys for same functions universal inputs not only main controller
		input.AddControllerKeyCommand(new ControllerButtonCommand{ XINPUT_GAMEPAD_A, -1, new StartGameControllerCommand(this, m_pArrow.get()), nullptr });
		input.AddControllerKeyCommand(new ControllerButtonCommand{ XINPUT_GAMEPAD_DPAD_UP, -1, new UpArrowCommand(m_pArrow.get()), nullptr });
		input.AddControllerKeyCommand(new ControllerButtonCommand{ XINPUT_GAMEPAD_DPAD_DOWN, -1, new DownArrowCommand(m_pArrow.get()), nullptr });


	}

	class MoveCommand : public Command
	{
	public:
		MoveCommand(Player* pPlayer, glm::vec3 movementModifier)
			: m_pPlayer(pPlayer), m_MovementModifier(movementModifier) {
		}
		void execute() override
		{
			// move movement 
			m_pPlayer->MoveTo(m_MovementModifier.x, m_MovementModifier.y, m_MovementModifier.z == 1);
		}
	private:
		Player* m_pPlayer;
		glm::vec3 m_MovementModifier;
	};
	void loadGame(int gameType)
	{

		ServiceLocator::GetSoundSystem().StopAllSounds();
		ServiceLocator::GetSoundSystem().PlaySound("MusicStart");
		ServiceLocator::GetSoundSystem().PlaySound("MusicInGame");
		// Get the audio 
		std::cout << "\n\nBegin load Game:\n\n";
		bool controllerMainPlayer = false;
		if (gameType > 3)
		{
			controllerMainPlayer = true;
			// Controller is used for player one
			gameType -= 3;
		}
		m_pArrow.reset();
		auto& input = InputManager::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		sceneManager.DeleteAllScenes();
		auto& scene = sceneManager.CreateScene("Game");
		input.DeleteAllKeys();
		// Debug key
		input.AddKeyCommand(new KeyCommand{ SDLK_F1, new BackToMainMenuCommand(this), nullptr });
		input.AddKeyCommand(new KeyCommand{ SDLK_F2, new MuteCommand(), nullptr });

		// player object
		if (not m_pPlayerOneObject)
			m_pPlayerOneObject = std::make_shared<dae::GameObject>(nullptr);

		m_RootGameObjects = std::make_shared<dae::GameObject>(nullptr);
		std::shared_ptr<dae::GameObject> nextBlockToAdd;
		for (int  x = 0; x < 12; x++)
		{
			for (int y = 0; y < 12; y++)
			{
				nextBlockToAdd = std::make_shared<dae::GameObject>(m_RootGameObjects);
				auto pTextureComponent = new TextureComponent(nextBlockToAdd.get(), "OtherSpriteSheet.png");
				new CheckForPlayerComponent(nextBlockToAdd.get(), m_pPlayerOneObject.get(), pTextureComponent, m_Score);
				if (y < 3)
					pTextureComponent->SetSrcRect(73, 32, 8, 8);
				else if (y < 6)
					pTextureComponent->SetSrcRect(64, 14, 8, 8);
				else if (y < 9)
					pTextureComponent->SetSrcRect(64, 23, 8, 8);
				else
					pTextureComponent->SetSrcRect(64, 32, 8, 8);

				pTextureComponent->SetDrawSize(32, 32);
				nextBlockToAdd->SetLocalPosition(glm::vec3{ x * 32+120, y * 32+100, 0 });
				m_GameObjects.push_back(nextBlockToAdd);
			}
		}
		scene.Add(m_RootGameObjects);
		if (gameType == 1 or true)
		{
			// code for singleplayer
			std::cout << "Loading Singleplayer Game\n";
			
			if (not m_pPlayerOne)
				m_pPlayerOne = new Player(m_pPlayerOneObject);
			// set to character texture and then set srcrect

			auto texture = new TextureComponent(m_pPlayerOneObject.get(), "CharacterSpriteSheet.png");
			texture->SetSrcRect(850, 0, 50, 50);
			texture->SetDrawSize(32, 32);
			m_pPlayerOneObject->SetLocalPosition(glm::vec3{ 200, 200, 0 });

			scene.Add(m_pPlayerOneObject);
			// add to keys

			if (controllerMainPlayer)
			{
				input.AddControllerKeyCommand(new ControllerButtonCommand{ XINPUT_GAMEPAD_DPAD_UP, -1, new MoveCommand(m_pPlayerOne, glm::vec3{ 0, -4, 1 }), new MoveCommand(m_pPlayerOne, glm::vec3{0,-4, 0}) });
				input.AddControllerKeyCommand(new ControllerButtonCommand{ XINPUT_GAMEPAD_DPAD_DOWN, -1, new MoveCommand(m_pPlayerOne, glm::vec3{ 0, 4, 1 }), new MoveCommand(m_pPlayerOne, glm::vec3{0,4, 0}) });

				input.AddControllerKeyCommand(new ControllerButtonCommand{ XINPUT_GAMEPAD_DPAD_LEFT, -1, new MoveCommand(m_pPlayerOne, glm::vec3{ -4, 0, 1 }), new MoveCommand(m_pPlayerOne, glm::vec3{-4,0, 0}) });
				input.AddControllerKeyCommand(new ControllerButtonCommand{ XINPUT_GAMEPAD_DPAD_RIGHT, -1, new MoveCommand(m_pPlayerOne, glm::vec3{ 4, 0, 1 }), new MoveCommand(m_pPlayerOne, glm::vec3{4, 0, 0 }) });

			}
			else
			{
				input.AddKeyCommand(new KeyCommand{ SDLK_w, new MoveCommand(m_pPlayerOne, glm::vec3{ 0, -4, 1 }), new MoveCommand(m_pPlayerOne, glm::vec3{0,-4, 0}) });
				input.AddKeyCommand(new KeyCommand{ SDLK_s, new MoveCommand(m_pPlayerOne, glm::vec3{ 0, 4, 1 }), new MoveCommand(m_pPlayerOne, glm::vec3{0,4, 0}) });

				input.AddKeyCommand(new KeyCommand{ SDLK_a, new MoveCommand(m_pPlayerOne, glm::vec3{ -4, 0, 1 }), new MoveCommand(m_pPlayerOne, glm::vec3{-4,0, 0}) });
				input.AddKeyCommand(new KeyCommand{ SDLK_d, new MoveCommand(m_pPlayerOne, glm::vec3{ 4, 0, 1 }), new MoveCommand(m_pPlayerOne, glm::vec3{4, 0, 0 }) });

			}


		}
		//else if (gameType == 2)
		//{
		//	// code for coop
		//	std::cout << "Loading Coop Game\n";
		//}
		else
		{
			// code for versus
			std::cout << "Loading Versus Game\n";
		}
		// Add a listener for if the score changes to the base object
		auto scoreDisplay = new ScoreDisplayComponent(font, m_RootGameObjects.get(), m_Score);
		scoreDisplay->SetPosition(10, 10);

	}

	void load()
	{
		std::cout << "\n\nBegin load:\n\n";
		font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
		fontSmall = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
		// init audio
		std::string dataPath = baseDataPath + "Audio/";
		ServiceLocator::Provide(new SDLSoundSystem(
			dataPath
		));
		ServiceLocator::GetSoundSystem().LoadSound("Credits", "01. Credit Sound.mp3");
		ServiceLocator::GetSoundSystem().LoadSound("MusicStart", "02. Start Music.mp3");
		ServiceLocator::GetSoundSystem().LoadSound("MusicInGame", "03. In-Game Music.mp3");
		ServiceLocator::GetSoundSystem().LoadSound("Shot", "04. Dig Dug - Shot.mp3");
		ServiceLocator::GetSoundSystem().LoadSound("Pumping", "05. Dig Dug - Pumping.mp3");
		ServiceLocator::GetSoundSystem().LoadSound("MonsterBlow", "06. Monster - Blow.mp3");
		ServiceLocator::GetSoundSystem().LoadSound("LastEnemy", "07. Last One Sound.mp3");
		ServiceLocator::GetSoundSystem().LoadSound("MusicLastEnemy", "08. Last One Music.mp3");
		ServiceLocator::GetSoundSystem().LoadSound("StageClear", "09. Stage Clear.mp3");
		ServiceLocator::GetSoundSystem().LoadSound("NameEntry", "10. Name Entry.mp3");
		ServiceLocator::GetSoundSystem().LoadSound("MonsterMoving", "11. Monster - Moving.mp3");
		ServiceLocator::GetSoundSystem().LoadSound("FygarFlame", "12. Fygar - Flame.mp3");
		ServiceLocator::GetSoundSystem().LoadSound("RockDropping", "13. Rock - Dropping.mp3");
		ServiceLocator::GetSoundSystem().LoadSound("RockHit", "14. Rock - Hit.mp3" );
		ServiceLocator::GetSoundSystem().LoadSound("RockBroken", "15. Rock - Broken.mp3" );
		ServiceLocator::GetSoundSystem().LoadSound("Extend", "16. Extend Sound.mp3" );
		ServiceLocator::GetSoundSystem().LoadSound("Bonus", "17. Bonus Sound.mp3" );
		ServiceLocator::GetSoundSystem().LoadSound("HurryUp", "18. Hurry-Up Sound.mp3" );
		ServiceLocator::GetSoundSystem().LoadSound("MusicHurryUp", "19. Hurry-Up Music.mp3" );
		ServiceLocator::GetSoundSystem().LoadSound("Miss", "20. Miss.mp3" );
		ServiceLocator::GetSoundSystem().LoadSound("GameOver", "21. Game Over.mp3" );
		ServiceLocator::GetSoundSystem().LoadSound("HighScore", "22. High Score.mp3");
		
		
		//int numAchievements = SteamUserStats()->GetNumAchievements()
		//for (int i = 0; i < numAchievements; ++i)
		//if (SteamUserStats()->StoreStats()) {
		//	std::cout << "All achievements have been reset!" << std::endl;
		//}
		//else {
		//	std::cerr << "Failed to store stats after resetting achievements." //std::endl;
		//}
		//auto& input = InputManager::GetInstance();
		//auto& sceneManager = SceneManager::GetInstance();

		//auto& demoScene = sceneManager.CreateScene("Demo");
		

		// sleeping for a bit so all files can properly load
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		loadMainMenu();
	}
private:
	Player* m_pPlayerOne;
	std::shared_ptr<GameObject> m_pPlayerOneObject;
	std::vector<std::shared_ptr<dae::GameObject>> m_GameObjects;
	std::shared_ptr<dae::GameObject> m_RootGameObjects;
	int m_Score{0};
	std::shared_ptr<SelectorArrow> m_pArrow;
	std::shared_ptr<GameObject> gameObject;
	std::shared_ptr<TextComponent> to;
	std::shared_ptr<Font> fontSmall;
	std::shared_ptr<Font> font;
	std::shared_ptr<GameObject> fpsObject;
	std::shared_ptr<GameObject> baseObject;
	std::shared_ptr<GameObject> firstLogo;
	std::shared_ptr<GameObject> secondLogo;
	std::shared_ptr<GameObject> player1Object;
	std::shared_ptr<GameObject> player2Object;
};


int main(int, char* []) {

	Game game;
	dae::Minigin engine(baseDataPath);
	engine.Run([&game]() { game.load(); });

	ServiceLocator::DestroyAll();
	return 0;
}