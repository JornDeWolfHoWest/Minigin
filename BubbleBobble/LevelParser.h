#pragma once

#include <functional>
#include <map>
#include <unordered_map>
#include <optional>
#include <variant>
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "BaseComponent.h"
#include "GameObject.h"
#include <Physics2DUtils.h>

namespace dae
{
	class Scene;

	class LevelParser final
	{

	public:
		LevelParser() = default;
		~LevelParser() = default;

		LevelParser(const LevelParser& other) = delete;
		LevelParser(LevelParser&& other) = delete;
		LevelParser& operator=(const LevelParser& other) = delete;
		LevelParser& operator=(LevelParser&& other) = delete;

		void Parse(Scene* scene, std::string_view filename);
	private:
		Scene* m_scene{};

		void ParseJSON(std::string_view filePath);
	};
}