#pragma once
#include "BaseComponent.h"
#include <memory>
#include "GameObject.h"
#include "TextureComponent.h"
class CheckForPlayerComponent
	: public dae::BaseComponent
{
	// Every update it will check if it's own position is within 5 of the player, if it is, it will hide the object via calling ->setdrawsize(0, 0); on the texture component, it will store the texturecomponent
public:
	CheckForPlayerComponent(dae::GameObject* pOwner, dae::GameObject* pPlayerObject, dae::TextureComponent* pTextureComponent, int& score)
		: BaseComponent(pOwner), m_PlayerObject(pPlayerObject), m_pTextureComponent(pTextureComponent), m_Score(score) {
	}
	void Update(const float&) override;

	void FixedUpdate() override {}
	void Render() const override {}
private:
	dae::GameObject* m_PlayerObject{ nullptr };
	dae::TextureComponent* m_pTextureComponent{ nullptr };
	int& m_Score;
};

