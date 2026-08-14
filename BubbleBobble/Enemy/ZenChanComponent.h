#pragma once

#include "BaseComponent.h"
#include "BubbleBobble/Level/ColliderComponent.h"

#include <string_view>
#include <glm/vec3.hpp>

namespace dae
{
	class ZenChanComponent final : public BaseComponent
	{
	public:
		ZenChanComponent(GameObject* owner, glm::vec3& direction, ColliderType type);
		~ZenChanComponent() override = default;

		ZenChanComponent(const ZenChanComponent& other) = delete;
		ZenChanComponent(ZenChanComponent&& other) = delete;
		ZenChanComponent& operator=(const ZenChanComponent& other) = delete;
		ZenChanComponent& operator=(ZenChanComponent&& other) = delete;

		void Update(const float&) {}
		void FixedUpdate() {}
		void Render() const {}
	private:
		static constexpr int m_srcSize{ 16 };
		static constexpr int m_dstSize{ 32 };
		static constexpr std::string_view m_spriteSheetPath{ "Sprites/Enemies/ZenChanSpriteSheet.png" };
	};
}