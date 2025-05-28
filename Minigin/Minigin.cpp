#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <chrono>
#include <thread>
#include "GameObject.h"
#include "BaseComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "iostream"
#include "Commands.h"
#include "Player.h"
#include "HealthDisplay.h"
#include <steam_api.h>
#include "ScoreDisplayComponent.h"
#include "ScoreChangedEvent.h"
#include "HealthChangedEvent.h"
#include "ScoreAchievementComponent.h"


using namespace std::chrono;

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string &dataPath)
{
	
	std::cout << "Initializing Minigin" << std::endl;
	//if (!SteamAPI_Init())
	//{
	//	std::cerr << "Fatal error - Steam must be running to play this game //(SteamAPI_Init() failed)." << std::endl;
	//}
	//else
	//{
	//	std::cout << "Succesfully initialized SteamAPI" << std::endl;
	//}
	//SteamUserStats()->RequestCurrentStats();
	//SteamUserStats()->RequestCurrentStats();

	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);

}

dae::Minigin::~Minigin()
{
	//SteamAPI_Shutdown();
	InputManager::GetInstance();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	/*
	{
	std::cout << "Exercise 1\n";
	const int arraySize = 100'000;
	const int arraySize2 =  1'000;
	const int sampleAmount = 10;
	const int stepSizeLimit = 2048;
	const int stepSizeTotalLog = static_cast<int>(std::log2(stepSizeLimit))+1;

	long long* samplesList = new long long[stepSizeTotalLog] {};

	int* list = new int[arraySize] {};
	for (int samples = 0; samples < sampleAmount; samples++)
	{
		for (int index = 0; index < arraySize; index++)
		{
			list[index] = 1;
		}
		int currentStepSampleIndex = 0;
		for (int stepSize = 1; stepSize <= stepSizeLimit; stepSize *= 2)
		{
			const auto start_time = std::chrono::high_resolution_clock::now();
			for (int index = 0; index < arraySize; index += stepSize)
			{
				list[index] *= 2;
			}
			const auto end_time = std::chrono::high_resolution_clock::now();
			auto delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
			samplesList[currentStepSampleIndex] += delta_time;
			++currentStepSampleIndex;
		}

	}
	delete[] list;
	for (int samplesNumber = 0; samplesNumber < stepSizeTotalLog; samplesNumber++)
	{
		std::cout << samplesList[samplesNumber]/ sampleAmount << "\n";
	}
	delete[] samplesList;

	struct Transform
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1 };
	};

	class GameObject3D
	{
	public:
		Transform transform{};
		int ID{};
	};

	std::cout << "\nExercise 2\n";
	long long* samplesList2 = new long long[stepSizeTotalLog] {};

	GameObject3D** list2 = new GameObject3D*[arraySize2] {};
	for (int index = 0; index < arraySize2; index++)
	{
		list2[index] = new GameObject3D();
	}
	for (int samples = 0; samples < sampleAmount; samples++)
	{
		for (int index = 0; index < arraySize2; index++)
		{
			list2[index]->ID = 1;
		}
		int currentStepSampleIndex = 0;
		for (int stepSize = 1; stepSize <= stepSizeLimit; stepSize *= 2)
		{
			const auto start_time = std::chrono::high_resolution_clock::now();
			for (int index = 0; index < arraySize2; index += stepSize)
			{
				list2[index]->ID *= 2;
			}
			const auto end_time = std::chrono::high_resolution_clock::now();
			auto delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
			samplesList2[currentStepSampleIndex] += delta_time;
			++currentStepSampleIndex;
		}
	}
	for (int index = 0; index < arraySize2; index++)
	{
		delete list2[index];
	}
	delete[] list2;
	for (int samplesNumber = 0; samplesNumber < stepSizeTotalLog; samplesNumber++)
	{
		std::cout << samplesList2[samplesNumber] / sampleAmount << "\n";
	}
	delete[] samplesList2;


	class GameObject3DAlt
	{
	public:
		Transform* transform;
		int ID;
	};

	std::cout << "\nExercise 2 Alt Setup\n";
	long long* samplesList2Alt = new long long[stepSizeTotalLog] {};

	GameObject3DAlt** list2Alt = new GameObject3DAlt * [arraySize2] {};
	for (int index = 0; index < arraySize2; index++)
	{
		list2Alt[index] = new GameObject3DAlt();
		list2Alt[index]->transform = new Transform();
	}
	std::cout << "\nExercise 2 Alt Starting\n";
	for (int samples = 0; samples < sampleAmount; samples++)
	{
		for (int index = 0; index < arraySize2; index++)
		{
			list2Alt[index]->ID = 1;
		}
		int currentStepSampleIndex = 0;
		for (int stepSize = 1; stepSize <= stepSizeLimit; stepSize *= 2)
		{
			const auto start_time = std::chrono::high_resolution_clock::now();
			for (int index = 0; index < arraySize2; index += stepSize)
			{
				list2Alt[index]->ID *= 2;
			}
			const auto end_time = std::chrono::high_resolution_clock::now();
			auto delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
			samplesList2Alt[currentStepSampleIndex] += delta_time;
			++currentStepSampleIndex;
		}
	}
	for (int index = 0; index < arraySize2; index++)
	{
		delete list2Alt[index]->transform;
		delete list2Alt[index];
	}
	delete[] list2Alt;
	for (int samplesNumber = 0; samplesNumber < stepSizeTotalLog; samplesNumber++)
	{
		std::cout << samplesList2Alt[samplesNumber] / sampleAmount << "\n";
	}
	delete[] samplesList2Alt;

	}
	*/

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	load();
	float fps = 60;
	float fixed_time_step = 1000.f / fps;
	// todo: this update loop could use some work.
	bool do_continue = true;
	auto last_time = high_resolution_clock::now();
	while (do_continue)
	{
		float lag = 0.0f;
		const auto current_time = high_resolution_clock::now();
		const float delta_time = duration<float>(current_time - last_time).count();
		last_time = current_time;
		lag += delta_time;

		//SteamAPI_RunCallbacks();

		while (lag >= fixed_time_step)
		{
			sceneManager.Update(fixed_time_step);
			lag -= fixed_time_step;
		}
		sceneManager.Update(delta_time);
		renderer.Render();
		do_continue = input.ProcessInput();


		const auto sleep_time = current_time + milliseconds(int(fixed_time_step)) - high_resolution_clock::now();
		std::this_thread::sleep_for(sleep_time);
	}
	std::cout << "\nQuiting\n";
}
