#include "QbertFactory.h"

#include "GameObject.h"
#include "LevelCubeActivator.h"
#include "MovementSystem.h"
#include "PlayerInput.h"
#include "RenderComponent.h"
#include "Walkable.h"
#include "Level.h"
#include "Lives.h"
#include "TextComponent.h"
#include "Scene.h"


game::Qbert* game::QbertFactory::CreateQbert(dae::Scene& scene,
	Walkable* startCube,
	game::Player player,
	const std::shared_ptr<dae::Font>& font)
{
	auto qbertObject = std::make_unique<dae::GameObject>();
	qbertObject->SetWorldScale(32,32);

	auto renderComponent = std::make_unique<dae::RenderComponent>(qbertObject.get(),
		player == game::Player::Player1 ? "Sprites/bert.png" : "Sprites/Coopbert.png");
	qbertObject->AddComponent(std::move(renderComponent));

	auto qbert = std::make_unique<game::Qbert>(qbertObject.get());
	auto movementComponent = std::make_unique<MovementSystem>(qbertObject.get(), startCube, glm::vec3{ -8, -15, 1 }, Side::Top, 0.75f, false);
	movementComponent->AddObserver(qbert.get());
	qbertObject->AddComponent(std::move(movementComponent));

	auto levelCubeActivator = std::make_unique<LevelCubeActivator>(qbertObject.get(), true);
	qbertObject->AddComponent(std::move(levelCubeActivator));

	auto playerInput = std::make_unique<PlayerInputSetup>(qbertObject.get(), player);
	qbertObject->AddComponent(std::move(playerInput));

	qbert->CheckForComponentsNeeded();


	//Lives
	auto go = std::make_unique<dae::GameObject>();
	auto textComponent = std::make_unique<dae::TextComponent>(go.get(), font, "0", SDL_Color{ 55, 200, 200 });
	go->AddComponent(std::move(textComponent));

	auto lives = std::make_unique<Lives>(go.get(), qbert->GetLives());
	qbert->AddObserver(lives.get());
	go->AddComponent(std::move(lives));
	SDL_Color color{};
	if (player == game::Player::Player1)
	{
		go->SetLocalPosition(10, 470, 0);
		color = SDL_Color{ 239, 86, 0 };
	}
	else
	{
		go->SetLocalPosition(630, 470, 0);
		color = SDL_Color{ 16, 226, 239 };
	}
	scene.Add(std::move(go));

	auto qbertPointer = qbert.get();
	qbertObject->AddComponent(std::move(qbert));
	startCube->GetGameObject()->AddChild(std::move(qbertObject));
	return qbertPointer;
}
