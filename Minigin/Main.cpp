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
#include <iostream>

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
	baseObject->SetLocalPosition(200, 200);
	
	auto firstLogo = new dae::GameObject{ baseObject.get() };
	firstLogo->SetTexture("logo.png");
	auto rotatorComponent = new RotatorComponent{ 100, 100, firstLogo};
	firstLogo->AddComponent(rotatorComponent);
	
	auto secondLogo = new dae::GameObject(firstLogo);
	secondLogo->SetTexture("logo.png");
	rotatorComponent = new dae::RotatorComponent{ 100, -200, secondLogo };
	secondLogo->AddComponent(rotatorComponent);
	
	scene.Add(std::move(baseObject));
}

//std::cout << "Exercise 1\n";
//const int arraySize = 100'000'000;
//const int arraySize2 = 1'000'000;
//const int sampleAmount = 10;
//const int stepSizeLimit = 2048;
//const int stepSizeTotalLog = int(std::log2(stepSizeLimit)) + 1;
//
//long long* samplesList = new long long[stepSizeTotalLog] {};
//
//int* list = new int[arraySize] {};
//for (int samples = 0; samples < sampleAmount; samples++)
//{
//	for (int index = 0; index < arraySize; index++)
//	{
//		list[index] = 1;
//	}
//	int currentStepSampleIndex = 0;
//	for (int stepSize = 1; stepSize <= stepSizeLimit; stepSize *= 2)
//	{
//		const auto start_time = std::chrono::high_resolution_clock::now();
//		for (int index = 0; index < arraySize; index += stepSize)
//		{
//			list[index] *= 2;
//		}
//		const auto end_time = std::chrono::high_resolution_clock::now();
//		auto delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
//		samplesList[currentStepSampleIndex] += delta_time;
//		++currentStepSampleIndex;
//	}
//
//}
//delete[] list;
//for (int samplesNumber = 0; samplesNumber < stepSizeTotalLog; samplesNumber++)
//{
//	std::cout << samplesList[samplesNumber] / sampleAmount << "\n";
//}
//delete[] samplesList;
//
//struct Transform
//{
//	float matrix[16] = {
//		1,0,0,0,
//		0,1,0,0,
//		0,0,1,0,
//		0,0,0,1 };
//};
//
//class GameObject3D
//{
//public:
//	Transform transform{};
//	int ID{};
//};
//
//std::cout << "\nExercise 2\n";
//long long* samplesList2 = new long long[stepSizeTotalLog] {};
//
//GameObject3D** list2 = new GameObject3D * [arraySize2] {};
//for (int index = 0; index < arraySize2; index++)
//{
//	list2[index] = new GameObject3D();
//}
//for (int samples = 0; samples < sampleAmount; samples++)
//{
//	for (int index = 0; index < arraySize2; index++)
//	{
//		list2[index]->ID = 1;
//	}
//	int currentStepSampleIndex = 0;
//	for (int stepSize = 1; stepSize <= stepSizeLimit; stepSize *= 2)
//	{
//		const auto start_time = std::chrono::high_resolution_clock::now();
//		for (int index = 0; index < arraySize2; index += stepSize)
//		{
//			list2[index]->ID *= 2;
//		}
//		const auto end_time = std::chrono::high_resolution_clock::now();
//		auto delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
//		samplesList2[currentStepSampleIndex] += delta_time;
//		++currentStepSampleIndex;
//	}
//}
//for (int index = 0; index < arraySize2; index++)
//{
//	delete list2[index];
//}
//delete[] list2;
//for (int samplesNumber = 0; samplesNumber < stepSizeTotalLog; samplesNumber++)
//{
//	std::cout << samplesList2[samplesNumber] / sampleAmount << "\n";
//}
//delete[] samplesList2;
//
//
//class GameObject3DAlt
//{
//public:
//	Transform* transform;
//	int ID;
//};
//
//std::cout << "\nExercise 2 Alt Setup\n";
//long long* samplesList2Alt = new long long[stepSizeTotalLog] {};
//
//GameObject3DAlt** list2Alt = new GameObject3DAlt * [arraySize2] {};
//for (int index = 0; index < arraySize2; index++)
//{
//	list2Alt[index] = new GameObject3DAlt();
//	list2Alt[index]->transform = new Transform();
//}
//std::cout << "\nExercise 2 Alt Starting\n";
//for (int samples = 0; samples < sampleAmount; samples++)
//{
//	for (int index = 0; index < arraySize2; index++)
//	{
//		list2Alt[index]->ID = 1;
//	}
//	int currentStepSampleIndex = 0;
//	for (int stepSize = 1; stepSize <= stepSizeLimit; stepSize *= 2)
//	{
//		const auto start_time = std::chrono::high_resolution_clock::now();
//		for (int index = 0; index < arraySize2; index += stepSize)
//		{
//			list2Alt[index]->ID *= 2;
//		}
//		const auto end_time = std::chrono::high_resolution_clock::now();
//		auto delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
//		samplesList2Alt[currentStepSampleIndex] += delta_time;
//		++currentStepSampleIndex;
//	}
//}
//for (int index = 0; index < arraySize2; index++)
//{
//	delete list2Alt[index]->transform;
//	delete list2Alt[index];
//}
//delete[] list2Alt;
//for (int samplesNumber = 0; samplesNumber < stepSizeTotalLog; samplesNumber++)
//{
//	std::cout << samplesList2Alt[samplesNumber] / sampleAmount << "\n";
//}
//delete[] samplesList2Alt;

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
