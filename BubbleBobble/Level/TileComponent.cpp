#include "TileComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Transform.h"

namespace dae
{
	TileComponent::TileComponent(GameObject* owner, int tileIdx, ColliderType type) :
		BaseComponent(owner),
		m_pTransform(nullptr),
		m_tileRow(tileIdx)
	{
		const auto pos = GetOwner()->GetLocalPosition();
		GetOwner()->SetLocalPosition(
			pos.GetPosition().x * static_cast<float>(m_tileSize),
			pos.GetPosition().y * static_cast<float>(m_tileSize),
			pos.GetPosition().z
		);

		GetOwner()->AddComponent(std::make_unique<SpriteComponent>(
			GetOwner(),
			m_smallTileSheetPath,
			glm::ivec2{ m_tileSrcSize, m_tileSrcSize },
			m_tileRow,
			m_tileCol,
			glm::vec2{ static_cast<float>(m_tileSize), static_cast<float>(m_tileSize) }
		));

		GetOwner()->AddComponent(std::make_unique<ColliderComponent>(
			GetOwner(),
			m_tileSize,
			type
		));
	}
}