#include "CheckForPlayerComponent.h"

void CheckForPlayerComponent::Update(const float&)
{
	if (m_PlayerObject)
	{
		if (not m_pTextureComponent->IsEnabled())
			return;
		glm::vec3 playerPos = m_PlayerObject->GetWorldPosition();
		glm::vec3 objectPos = GetOwner()->GetWorldPosition();
		if (glm::distance(playerPos, objectPos) < 16.0f)
		{
			m_pTextureComponent->SetEnabled(false);
			m_Score += 10;
		}
	}
}