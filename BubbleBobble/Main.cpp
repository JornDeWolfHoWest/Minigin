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
#include <iostream>
#include <memory>

#include <Minigin.h>
#include <SceneManager.h>
#include <ResourceManager.h>
#include <Scene.h>
#include <GameObject.h>
#include <Singleton.h>
#include <InputManager.h>
//#include <Services/SoundService.h>
//#include <Services/SDLSoundSystem.h>
//#include "SoundEffectsEnum.h"

#include <RenderComponent.h>
#include <TextComponent.h>
#include <ImGUIComponent.h>

#include "SpriteComponent.h"

#include "LevelParser.h"
#include "GameSettings.h"
#include "BubbleBobble/MainMenu/SelectorComponent.h"

#include "BubbleBobble/Level/TileComponent.h"
#include "BubbleBobble/Enemy/ZenChanComponent.h"
#include "BubbleBobble/PlayerComponents/PlayerComponent.h"


using JSON = nlohmann::json;

static void loadStartScreen()
{
	dae::InputManager::GetInstance().DeleteAllKeys();

	dae::GameSettings::GetInstance().GetParser(); // Init parser

	//dae::SoundLocator::RegisterAudio(std::make_unique<dae::SDLSoundSystem>());
	//dae::SoundLocator::GetAudio().RegisterSound(static_cast<SoundId>(SoundEffectsEnum::MainTheme), "MainTheme.mp3");
	//dae::SoundLocator::GetAudio().RegisterSound(static_cast<SoundId>(SoundEffectsEnum::ShootBullet), "ShootBullet.mp3");

	//dae::SoundLocator::GetAudio().Play(static_cast<SoundId>(SoundEffectsEnum::MainTheme), 1.0f);
	

	auto smallFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

	auto& titleScene = dae::SceneManager::GetInstance().CreateScene("Title");
	dae::SceneManager::GetInstance().SwitchScene("Title");

	auto title = std::make_unique<dae::GameObject>();
	title->SetLocalPosition(100.0f, 50.0f, 0.0f);
	title->AddComponent(std::make_unique<dae::TextComponent>(title.get(), smallFont, "Choose your gamemode!"));
	titleScene.Add(std::move(title));
	
	// Option 1
	auto option1 = std::make_unique<dae::GameObject>();
	option1->SetLocalPosition(164.0f, 150.0f, 0.0f);
	option1->AddComponent(std::make_unique<dae::TextComponent>(option1.get(), smallFont, "1. Singleplayer"));
	titleScene.Add(std::move(option1));

	// Option 2
	auto option2 = std::make_unique<dae::GameObject>();
	option2->SetLocalPosition(164.0f, 250.0f, 0.0f);
	option2->AddComponent(std::make_unique<dae::TextComponent>(option2.get(), smallFont, "2. Co-op"));
	titleScene.Add(std::move(option2));

	// Option 3
	auto option3 = std::make_unique<dae::GameObject>();
	option3->SetLocalPosition(164.0f, 350.0f, 0.0f);
	option3->AddComponent(std::make_unique<dae::TextComponent>(option3.get(), smallFont, "3. Versus"));
	titleScene.Add(std::move(option3));

	// Selector
	auto selector = std::make_unique<dae::GameObject>();
	selector->SetLocalPosition(100.0f, 150.0f, 0.0f);
	selector->AddComponent(std::make_unique<dae::SpriteComponent>(
		selector.get(),
		"Sprites/Menu/Selector.png",
		glm::ivec2{ 8, 8 },
		0,
		0,
		glm::vec2{ 32.0f, 32.0f }
	));
	selector->AddComponent(std::make_unique<dae::SelectorComponent>(selector.get()));
	titleScene.Add(std::move(selector));
}

static void load()
{
	loadStartScreen();
	dae::SceneManager::GetInstance().SwitchScene("StartScreen");

}

int main(int, char* [])
{
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if (!fs::exists(data_location))
		data_location = "../Data/";
#endif

	dae::Minigin engine(data_location);
	engine.Run(load);

	return 0;
}