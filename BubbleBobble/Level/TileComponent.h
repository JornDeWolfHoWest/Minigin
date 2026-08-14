#pragma once
#include "BaseComponent.h"
#include <Physics2DUtils.h>
#include <string>

namespace dae
{
	class Transform;

	class TileComponent final : public BaseComponent
	{
	public:
		TileComponent(GameObject* owner, int tileIdx, ColliderType type);
		virtual ~TileComponent() override = default;

		TileComponent(const TileComponent& other) = delete;
		TileComponent(TileComponent&& other) = delete;
		TileComponent& operator=(const TileComponent& other) = delete;
		TileComponent& operator=(TileComponent&& other) = delete;

		void Update(const float&) override {}
		void FixedUpdate() override {}
		void Render() const override {}

	private:
		Transform* m_pTransform{ nullptr };
		int m_tileSrcSize{ 8 };
		int m_tileSize{ 16 };
		int m_tileRow{ 0 };
		int m_tileCol{ 0 };
		std::string m_smallTileSheetPath{ "Sprites/Levels/Tiles/TileMap.png" };
	};
}