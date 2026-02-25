#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"

#include <filesystem>
namespace fs = std::filesystem;

using namespace dae;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto go = std::make_unique<dae::GameObject>(nullptr);
	go->SetTexture("background.png");
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>(nullptr);
	go->SetTexture("logo.png");
	go->SetLocalPosition(358, 180);
	scene.Add(std::move(go));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_unique<dae::TextObject>(nullptr, "Programming 4 Assignment", font);
	to->SetColor({ 255, 255, 0, 255 });
	to->SetPosition(292, 20);
	scene.Add(std::move(to));


	auto FPSfont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	std::unique_ptr<dae::GameObject> fpsObject = std::make_unique<dae::TextObject>(nullptr, "FPS", font);

	auto fpsComponent = new dae::FPSComponent{ static_cast<TextObject*>(fpsObject.get()) };
	fpsObject.get()->AddComponent(fpsComponent);
	scene.Add(std::move(fpsObject));
	
	
	auto baseObject = std::make_unique<dae::GameObject>(nullptr);
	baseObject->SetLocalPosition(100, 100);
	
	auto firstLogo = new dae::GameObject{ baseObject.get() };
	firstLogo->SetTexture("logo.png");
	Transform middle;
	middle.SetPosition(100, 100);
	auto rotatorComponent = new RotatorComponent{ middle, 100, 100, firstLogo};
	firstLogo->AddComponent(rotatorComponent);
	
	auto secondLogo = new dae::GameObject(firstLogo);
	secondLogo->SetTexture("logo.png");
	middle.SetPosition(0, 0);
	rotatorComponent = new dae::RotatorComponent{ middle, 100, -200, secondLogo };
	secondLogo->AddComponent(rotatorComponent);
	
	scene.Add(std::move(baseObject));
	
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
