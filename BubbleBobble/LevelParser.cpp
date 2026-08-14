#include "LevelParser.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "ResourceManager.h"
#include "Scene.h"

#include <nlohmann/json.hpp>

#include "GameObject.h"
#include "LevelParser.h"
#include "GameSettings.h"

#include "BubbleBobble/Level/TileComponent.h"
#include "BubbleBobble/Enemy/ZenChanComponent.h"
#include "BubbleBobble/PlayerComponents/PlayerComponent.h"

namespace dae
{
	void LevelParser::Parse(Scene* scene, std::string_view filename)
	{
		m_scene = scene;
		const auto extension = std::filesystem::path(filename).extension();
		if (extension == ".json")
		{
			ParseJSON(filename);
		}
	}
	void dae::LevelParser::ParseJSON(std::string_view filename)
	{
		const auto fullPath = ResourceManager::GetInstance().GetDataPath() / "Levels" / filename;

		std::ifstream file(fullPath, std::ios::binary);

		if (!file.is_open())
		{
			std::cerr << "Failed to open file: " << fullPath << "\n";
			return;
		}


		nlohmann::json levelData;
		try
		{
			file >> levelData;
		}
		catch (const nlohmann::json::parse_error& e)
		{
			std::cerr << "JSON Parse Error: " << e.what() << "\n";
			return;
		}

		if (levelData.contains("Map"))
		{
			for (const auto& tile : levelData["Map"])
			{
				const auto& location = tile.at("Location");
				auto& typeJson = tile.at("Type");

				const glm::ivec2 pos{
					location[0].get<int>(),
					location[1].get<int>() + 2
				};

				std::string type{
					typeJson.get<std::string>()
				};

				// Level 1 wal
				if (type == "wall1")
				{
					auto tileObject = std::make_unique<dae::GameObject>();

					tileObject->SetLocalPosition(
						static_cast<float>(pos.x),
						static_cast<float>(pos.y),
						0.0f
					);

					tileObject->AddComponent(
						std::make_unique<dae::TileComponent>(
							tileObject.get(),
							0,
							dae::ColliderType::Wall
						)
					);
					m_scene->Add(std::move(tileObject));
				}

				// Level 1 platform
				else if (type == "platform1")
				{
					auto tileObject = std::make_unique<dae::GameObject>();

					tileObject->SetLocalPosition(
						static_cast<float>(pos.x),
						static_cast<float>(pos.y),
						0.0f
					);

					tileObject->AddComponent(
						std::make_unique<dae::TileComponent>(
							tileObject.get(),
							0,
							dae::ColliderType::Platform
						)
					);
					m_scene->Add(std::move(tileObject));
				}

				// Level 2 wall
				else if (type == "wall2")
				{
					auto tileObject = std::make_unique<dae::GameObject>();

					tileObject->SetLocalPosition(
						static_cast<float>(pos.x),
						static_cast<float>(pos.y),
						0.0f
					);

					tileObject->AddComponent(
						std::make_unique<dae::TileComponent>(
							tileObject.get(),
							1,
							dae::ColliderType::Wall
						)
					);

					m_scene->Add(std::move(tileObject));
				}

				// Level 2 platform
				else if (type == "platform2")
				{
					auto tileObject = std::make_unique<dae::GameObject>();

					tileObject->SetLocalPosition(
						static_cast<float>(pos.x),
						static_cast<float>(pos.y),
						0.0f
					);

					tileObject->AddComponent(
						std::make_unique<dae::TileComponent>(
							tileObject.get(),
							1,
							dae::ColliderType::Platform
						)
					);

					m_scene->Add(std::move(tileObject));
				}

				// Level 3 wall
				else if (type == "wall3")
				{
					auto tileObject = std::make_unique<dae::GameObject>();

					tileObject->SetLocalPosition(
						static_cast<float>(pos.x),
						static_cast<float>(pos.y),
						0.0f
					);

					tileObject->AddComponent(
						std::make_unique<dae::TileComponent>(
							tileObject.get(),
							8,
							dae::ColliderType::Wall
						)
					);

					m_scene->Add(std::move(tileObject));
				}

				// Level 3 platform
				else if (type == "platform3")
				{
					auto tileObject = std::make_unique<dae::GameObject>();

					tileObject->SetLocalPosition(
						static_cast<float>(pos.x),
						static_cast<float>(pos.y),
						0.0f
					);

					tileObject->AddComponent(
						std::make_unique<dae::TileComponent>(
							tileObject.get(),
							8,
							dae::ColliderType::Platform
						)
					);

					m_scene->Add(std::move(tileObject));
				}
			}
		}

		if (levelData.contains("Enemies"))
		{
			for (const auto& enemy : levelData["Enemies"])
			{
				const auto& location = enemy.at("Location");

				const glm::ivec2 pos{
					location[0].get<int>(),
					location[1].get<int>()
				};

				auto zenChanObject = std::make_unique<dae::GameObject>();

				zenChanObject->SetLocalPosition(
					static_cast<float>(pos.x),
					static_cast<float>(pos.y),
					0.0f
				);

				glm::vec3 direction{ 1.0f, 0.0f, 0.0f };

				zenChanObject->AddComponent(
					std::make_unique<dae::ZenChanComponent>(
						zenChanObject.get(),
						direction,
						dae::ColliderType::Trigger
					)
				);

				m_scene->Add(std::move(zenChanObject));
			}
		}

		// PLAYER SPAWN

		if (levelData.contains("SpawnPosition"))
		{
			const auto& location = levelData["SpawnPosition"].at("Location");

			const glm::ivec2 pos{
				location[0].get<int>(),
				location[1].get<int>()
			};

			auto player = std::make_unique<dae::GameObject>();

			player->SetLocalPosition(
				static_cast<float>(pos.x),
				static_cast<float>(pos.y),
				0.0f
			);


			glm::vec3 startingDirection{ 1.0f, 0.0f, 0.0f };

			constexpr int playerNumber = 1;

			player->AddComponent(
				std::make_unique<dae::PlayerComponent>(
					player.get(),
					playerNumber,
					startingDirection
				)
			);

			m_scene->Add(std::move(player));
		}
	}
}