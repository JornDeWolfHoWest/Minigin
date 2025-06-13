#include "SelectorArrow.h"
#include "TextComponent.h"

SelectorArrow::SelectorArrow(dae::TextComponent* pTextComponent)
	: m_pTextComponent(pTextComponent) {
}

void SelectorArrow::SetPosition(float x, float y)
{
	m_pTextComponent->SetPosition(x, y);
}

void SelectorArrow::ChangePositionY(float x)
{
	auto pos = m_pTextComponent->GetPosition();
	pos.y += x;
	if (pos.y > 240)
		pos.y = 210;
	else if (pos.y < 210)
		pos.y = 240;
	m_pTextComponent->SetPosition(pos.x, pos.y);

}
glm::vec3 SelectorArrow::GetPosition()
{
	return m_pTextComponent->GetPosition();
}