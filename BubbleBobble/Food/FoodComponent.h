#pragma once

#include "BaseComponent.h"
#include "BubbleBobble/Level/ColliderComponent.h"

#include <string_view>
#include <glm/vec3.hpp>

namespace dae
{
	class FoodComponent final : public BaseComponent
	{
	public:
		FoodComponent(GameObject* owner, int itemType) : BaseComponent(owner), m_itemType{ itemType } {}
		~FoodComponent() override = default;

		FoodComponent(const FoodComponent& other) = delete;
		FoodComponent(FoodComponent&& other) = delete;
		FoodComponent& operator=(const FoodComponent& other) = delete;
		FoodComponent& operator=(FoodComponent&& other) = delete;

		void Update(const float&) {}
		void FixedUpdate() {}
		void Render() const {}
		
		[[nodiscard]] int GetItemType() const { return m_itemType; }
	private:
		int m_itemType{ 0 };
	};
}