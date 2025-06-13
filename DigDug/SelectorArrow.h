#pragma once
#include "fwd.hpp"
using namespace glm;
namespace dae {
	class TextComponent;
}

class SelectorArrow
{
public:
	SelectorArrow(dae::TextComponent* pTextComponent);
	void SetPosition(float x, float y);
	void ChangePositionY(float x);
	vec3 GetPosition();
private:
	dae::TextComponent* m_pTextComponent{ nullptr };
};
