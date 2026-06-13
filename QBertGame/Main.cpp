#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include <filesystem>
namespace fs = std::filesystem;

#include <fstream>
#include <nlohmann/json.hpp>

#include <imgui.h>

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include <FPSComponent.h>
#include <RotatorComponent.h>
#include <RenderComponent.h>
#include <iostream>
#include <GameObject.h>
#include <memory>
#include <TextComponent.h>
#include <ImGUIComponent.h>
#include <Singleton.h>


#include "Enums.h"

#include "LevelAndMovement/PlayerInput.h"
#include "LevelAndMovement/Score.h"
#include "LevelAndMovement/Level.h"
#include "LevelAndMovement/MakeLevelFactory.h"
#include "LevelAndMovement/Qbert.h"
#include "LevelAndMovement/QbertFactory.h"
#include "LevelAndMovement/GameDone.h"
#include "LevelAndMovement/GameOver.h"

using JSON = nlohmann::json;


class GameScene : public dae::Singleton<GameScene>
{
public:
	static void SetGameType(game::GameType gameType) { m_GameType = gameType; }
	static game::GameType m_GameType;
private:
};

game::GameType GameScene::m_GameType{};

static void loadGameScene()
{
	dae::InputManager::GetInstance().DeleteAllKeys();
	auto& scene = dae::SceneManager::GetInstance().CreateScene("GameScene");
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//FPS
	auto go = std::make_unique<dae::GameObject>();
	auto textComponent = std::make_unique<dae::TextComponent>(go.get(), font, "", SDL_Color{ 255, 255, 0, 255 });
	auto fps = std::make_unique<dae::FPSComponent>(go.get(), textComponent.get());
	go->AddComponent(std::move(textComponent));
	go->AddComponent(std::move(fps));
	scene.Add(std::move(go));

	//Score
	go = std::make_unique<dae::GameObject>();
	auto score = std::make_unique<game::Score>(go.get(), font);
	auto scorePointer = score.get();
	go->AddComponent(std::move(score));
	go->SetLocalPosition(320, 10, 0);
	scene.Add(std::move(go));

	game::LevelSettings levelSettings{};

	std::ifstream file("./Data/level1.json");

	if (file.is_open())
	{
		try
		{
			JSON json;
			file >> json;

			levelSettings.levelSize = json.value("levelSize", 7);
			levelSettings.discAmount = json.value("discAmount", 0);
			levelSettings.scale = json.value("scale", 1.f);
		}
		catch (const std::exception& e)
		{
			throw std::runtime_error("Failed to load Level.json: " + std::string(e.what()));
		}
	}
	else
	{
		throw std::runtime_error("Could not open Level.json\n");
	}

	//Level
	auto level = game::MakeLevelFactory::CreateLevel(scene, scorePointer, levelSettings);

	//Qbert Players
	std::vector<game::Qbert*> players{};
	players.push_back(game::QbertFactory::CreateQbert(
		scene, GameScene::m_GameType == game::GameType::Coop ? level->GetBottomLeftCube() : level->GetTopCube(),
		game::Player::Player1,
		font));
	level->AddObserver(players[0]);
	if (GameScene::m_GameType == game::GameType::Coop)
	{
		players.push_back(game::QbertFactory::CreateQbert(scene, level->GetBottomRightCube(), game::Player::Player2, font));
		level->AddObserver(players[1]);

		if (!players[0] && !players[1])
		{
			auto player1 = players[0];
			auto player2 = players[1];
			player1->AddObserver(player2);
			player2->AddObserver(player1);
		}
	}

	//Game Over UI
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings;
	go = std::make_unique<dae::GameObject>();
	auto imGuiComponent = std::make_unique<dae::ImGUIComponent>(go.get(), []()
		{
			ImGui::Text("Game Over");
			if (ImGui::Button("Back to Main Menu"))
			{
				dae::SceneManager::GetInstance().SwitchScene("StartScene");
			}
		}, "Game Over", flags);
	imGuiComponent->SetPivot({ 0.5f, 0.5f });
	imGuiComponent->SetPosition({ 320, 240 });
	go->AddComponent(std::move(imGuiComponent));
	auto gameOver = std::make_unique<game::GameOver>(go.get());
	for (auto& player : players)
	{
		if (!player)
		{
			continue;
		}
		player->AddObserver(gameOver.get());
	}
	go->AddComponent(std::move(gameOver));
	scene.Add(std::move(go));

	//Game Complete UI
	go = std::make_unique<dae::GameObject>();
	imGuiComponent = std::make_unique<dae::ImGUIComponent>(go.get(), []()
		{
			ImGui::Text("Game Complete");
			if (ImGui::Button("Back to Main Menu"))
			{
				dae::SceneManager::GetInstance().SwitchScene("StartScene");
			}
		}, "Game Done", flags);
	imGuiComponent->SetPivot({ 0.5f, 0.5f });
	imGuiComponent->SetPosition({ 320, 240 });
	go->AddComponent(std::move(imGuiComponent));
	auto gameDone = std::make_unique<game::GameDone>(go.get());
	level->AddObserver(gameDone.get());
	go->AddComponent(std::move(gameDone));
	scene.Add(std::move(go));
}


static void loadStartScreen()
{
	//Create StartScene
	auto& scene = dae::SceneManager::GetInstance().CreateScene("StartScene");
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//Background
	auto go = std::make_unique<dae::GameObject>();
	auto renderComponent = std::make_unique<dae::RenderComponent>(go.get(), "background.png");
	go->AddComponent(std::move(renderComponent));
	scene.Add(std::move(go));

	//DAE
	go = std::make_unique<dae::GameObject>();
	renderComponent = std::make_unique<dae::RenderComponent>(go.get(), "logo.png");
	go->AddComponent(std::move(renderComponent));
	go->SetLocalPosition(370, 250, 0);
	scene.Add(std::move(go));


	//FPS
	go = std::make_unique<dae::GameObject>();
	auto textComponent = std::make_unique<dae::TextComponent>(go.get(), font, "FPS ", SDL_Color{255, 255, 0, 255});
	auto fps = std::make_unique<dae::FPSComponent>(go.get(), textComponent.get());
	go->AddComponent(std::move(textComponent));
	go->AddComponent(std::move(fps));
	scene.Add(std::move(go));


	go = std::make_unique<dae::GameObject>();
	renderComponent = std::make_unique<dae::RenderComponent>(go.get(), "Sprites/TitelScreenBert.png");
	go->AddComponent(std::move(renderComponent));
	go->SetLocalPosition(320, 400, 0);
	go->SetWorldScale(150, 150);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	renderComponent = std::make_unique<dae::RenderComponent>(go.get(), "Sprites/Title.png");
	go->AddComponent(std::move(renderComponent));
	go->SetLocalPosition(320, 300, 0);
	scene.Add(std::move(go));
	//UI
	go = std::make_unique<dae::GameObject>();
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings;
	auto imguiComponent = std::make_unique<dae::ImGUIComponent>(go.get(), []()
		{
			auto player1 = game::PlayerInputSetup::GetPlayer1();
			auto player2 = game::PlayerInputSetup::GetPlayer2();

			ImGui::Text("Player 1 Input:");
			if (ImGui::RadioButton("Keyboard##1", player1 == game::InputType::Keyboard))
			{
				game::PlayerInputSetup::SetPlayer1(game::InputType::Keyboard);
			}
			ImGui::SameLine();
			if (ImGui::RadioButton("Controller##1", player1 == game::InputType::Controller))
			{
				game::PlayerInputSetup::SetPlayer1(game::InputType::Controller);
			}

			ImGui::Text("Player 2 Input:");
			if (ImGui::RadioButton("Keyboard##2", player2 == game::InputType::Keyboard))
			{
				game::PlayerInputSetup::SetPlayer2(game::InputType::Keyboard);
			}
			ImGui::SameLine();
			if (ImGui::RadioButton("Controller##2", player2 == game::InputType::Controller))
			{
				game::PlayerInputSetup::SetPlayer2(game::InputType::Controller);
			}

			ImGui::Text("Keyboard: WASD & arrow keys");
			ImGui::Text("Controller: DPAD");
			if (ImGui::Button("Single Player"))
			{
				GameScene::GetInstance().SetGameType(game::GameType::Single);
				dae::SceneManager::GetInstance().RemoveSceneIfExists("GameScene");
				loadGameScene();
				dae::SceneManager::GetInstance().SwitchScene("GameScene");
			}
			if (ImGui::Button("Co-op"))
			{
				GameScene::GetInstance().SetGameType(game::GameType::Coop);
				dae::SceneManager::GetInstance().RemoveSceneIfExists("GameScene");
				loadGameScene();
				dae::SceneManager::GetInstance().SwitchScene("GameScene");
			}
		}, "Menu", true, flags);
	imguiComponent->SetPosition({ 280, 280 });
	imguiComponent->SetPivot({ .5f, 1 });
	go->AddComponent(std::move(imguiComponent));

	scene.Add(std::move(go));
}

static void load()
{
	// Fuck cmake sdl3 mixer importing, kept crashing for hours, this remains of the sdl
	//ServiceLocator::Provide(new SDLSoundSystem("../Data/Sound/"));
	//ServiceLocator::GetSoundSystem().LoadSound("GameStartMusic", "GameStartMusic.wav");
	//ServiceLocator::GetSoundSystem().PlaySound("GameStartMusic");


	//SceneManager::GetInstance().CreateScene("GameScene");


	loadStartScreen();
	dae::SceneManager::GetInstance().SwitchScene("StartScreen");

}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
