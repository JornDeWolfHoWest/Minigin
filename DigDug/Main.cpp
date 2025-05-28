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

//steam
#include <steam_api.h>

std::string baseDataPath = "../Data/";


using namespace dae;
class Game
{
public:

	void loadMainMenu()
	{
		std::cout << "\n\nBegin load Main Menu:\n\n";
		//auto& input = InputManager::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		ResourceManager::GetInstance().LoadTexture("OtherSpriteSheet.png");
		auto& mainMenuScene = sceneManager.CreateScene("MainMenu");

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

	}

	void load()
	{
		std::cout << "\n\nBegin load:\n\n";
		// init audio
		ServiceLocator::Provide(new SDLSoundSystem(baseDataPath));
		ServiceLocator::GetSoundSystem().LoadSound("pew", "bp_missile_large.ogg");

		//int numAchievements = SteamUserStats()->GetNumAchievements()
		//for (int i = 0; i < numAchievements; ++i)
		//if (SteamUserStats()->StoreStats()) {
		//	std::cout << "All achievements have been reset!" << std::endl;
		//}
		//else {
		//	std::cerr << "Failed to store stats after resetting achievements." //std::endl;
		//}
		auto& input = InputManager::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();

		auto& demoScene = sceneManager.CreateScene("Demo");

		loadMainMenu();

		if (true)
			return;


		gameObject = std::make_shared<dae::GameObject>(nullptr);
		gameObject->SetTexture("background.tga");
		demoScene.Add(gameObject);
		
		gameObject = std::make_shared<dae::GameObject>(nullptr);
		gameObject->SetTexture("logo.tga");
		gameObject->SetLocalPosition(glm::vec3{ 216, 180 , 0 });
		demoScene.Add(gameObject);

		font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto a = new dae::TextComponent("Programming 4 Assignment", font, gameObject.get());
		a->SetPosition(80, 20);

		auto& scene = sceneManager.CreateScene("main");
		font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
		fontSmall = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
		//auto fpsComponent = new dae::FPSComponent{ font, fpsObject.get() };
		//fpsComponent->SetPosition(10, 10);



		baseObject = std::make_shared<dae::GameObject>(nullptr);
		baseObject->SetLocalPosition(glm::vec3{ 300, 300, 0 });

		TextComponent* explainingTextPlayer1 = new TextComponent("Use WASD to move pacman, F to deal damage to pacman and V to add score to pacman (in 10s)", fontSmall, baseObject.get());
		TextComponent* explainingTextPlayer2pt1 = new TextComponent("Use D-PAD to move pacman (but with a fancy hat), G to deal damage to pacman (but with a fancy hat)", fontSmall, baseObject.get());
		TextComponent* explainingTextPlayer2pt2 = new TextComponent("and B to add score to pacman (but with a fancy hat) (in 100s)", fontSmall, baseObject.get());
		TextComponent* explainingTextPlayer2pt3 = new TextComponent("[NOTE ACHIEVEMENT ONLY WORKS FOR FANCY HAT (for testing)]", fontSmall, baseObject.get());
		explainingTextPlayer1->SetPosition(10, 80);
		explainingTextPlayer2pt1->SetPosition(10, 95);
		explainingTextPlayer2pt2->SetPosition(10, 110);
		explainingTextPlayer2pt3->SetPosition(10, 125);

		firstLogo = std::make_shared<dae::GameObject>(baseObject.get());
		firstLogo->SetTexture("logo.tga");
		new dae::RotatorComponent{ 100, 100, firstLogo.get() };

		secondLogo = std::make_shared<dae::GameObject>(firstLogo.get());
		secondLogo->SetTexture("logo.tga");
		new dae::RotatorComponent{ 100, -200, secondLogo.get() };

		scene.Add(baseObject);

		player1Object = std::make_shared<dae::GameObject>(nullptr);
		player1Object->SetTexture("pacman.png");
		Player* player1 = new Player(player1Object.get(), 300);
		player1Object->SetLocalPosition(glm::vec3{ 170, 200, 0 });
		scene.Add(player1Object);

		class audioTestCommand : public Command
		{
		public:
			void execute() override
			{
				ServiceLocator::GetSoundSystem().PlaySound("pew");
			}
		};
		// Add play sound on
		input.AddKeyCommand(new KeyCommand{ SDLK_c, new audioTestCommand{}, nullptr });

		input.AddKeyCommand(new KeyCommand{ SDLK_w, new UpStartCommand(player1), new UpEndCommand(player1) });
		input.AddKeyCommand(new KeyCommand{ SDLK_s, new DownStartCommand(player1), new DownEndCommand(player1) });
		input.AddKeyCommand(new KeyCommand{ SDLK_a, new LeftStartCommand(player1), new LeftEndCommand(player1) });
		input.AddKeyCommand(new KeyCommand{ SDLK_d, new RightStartCommand(player1), new RightEndCommand(player1) });

		HealthDisplayComponent* healthDisplay = new HealthDisplayComponent(font, baseObject.get());
		player1->AddObserver(healthDisplay);
		healthDisplay->SetPosition(10, 160);
		healthDisplay->Update(HealthChangedEvent(player1->GetHealth()));

		ScoreDisplayComponent* scoreDisplay = new ScoreDisplayComponent(font, baseObject.get());
		player1->AddObserver(scoreDisplay);
		scoreDisplay->SetPosition(10, 180);
		scoreDisplay->Update(ScoreChangedEvent(player1->GetScore()));




		player2Object = std::make_shared <dae::GameObject>(nullptr);
		player2Object->SetTexture("pacman_Hat.png");
		Player* player2 = new Player(player2Object.get(), 200);
		player2Object->SetLocalPosition(glm::vec3{ 200, 200, 0 });
		scene.Add(player2Object);
		HealthDisplayComponent* healthDisplay2 = new HealthDisplayComponent(font, baseObject.get());
		player2->AddObserver(healthDisplay2);
		healthDisplay2->SetPosition(10, 200);
		healthDisplay2->Update(HealthChangedEvent(player2->GetHealth()));

		ScoreDisplayComponent* score2Display = new ScoreDisplayComponent(font, baseObject.get());
		player2->AddObserver(score2Display);
		score2Display->SetPosition(10, 220);
		score2Display->Update(ScoreChangedEvent(player2->GetScore()));


		ScoreAchievementComponent* scoreAchievement = new ScoreAchievementComponent(baseObject.get());
		player2->AddObserver(scoreAchievement);




		// Damage on the key F for Player 1
		input.AddKeyCommand(new KeyCommand{ SDLK_f, new DamageCommand(player1, 1), nullptr });
		// Damage on the key G for Player 2
		input.AddKeyCommand(new KeyCommand{ SDLK_g, new DamageCommand(player2, 1), nullptr });
		// Add score on the key V for Player 1
		input.AddKeyCommand(new KeyCommand{ SDLK_v, new AddScoreCommand(player1, 10), nullptr });
		// Add score on the key B for Player 2
		input.AddKeyCommand(new KeyCommand{ SDLK_b, new AddScoreCommand(player2, 100), nullptr });


		input.AddControllerKeyCommand(new ControllerButtonCommand{ XINPUT_GAMEPAD_DPAD_UP, new UpStartCommand(player2), new UpEndCommand(player2) });
		input.AddControllerKeyCommand(new ControllerButtonCommand{ XINPUT_GAMEPAD_DPAD_DOWN, new DownStartCommand(player2), new DownEndCommand(player2) });
		input.AddControllerKeyCommand(new ControllerButtonCommand{ XINPUT_GAMEPAD_DPAD_LEFT, new LeftStartCommand(player2), new LeftEndCommand(player2) });
		input.AddControllerKeyCommand(new ControllerButtonCommand{ XINPUT_GAMEPAD_DPAD_RIGHT, new RightStartCommand(player2), new RightEndCommand(player2) });
		/*
		*/
	}
private:
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