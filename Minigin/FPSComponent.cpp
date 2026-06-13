#include "FPSComponent.h"
#include <stdexcept>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "BaseComponent.h"
#include "TextComponent.h"


namespace dae
{
    FPSComponent::FPSComponent(GameObject* pOwner, TextComponent* pTextComponent) :
        BaseComponent(pOwner),
        m_FPS(0.f),
		m_ElapsedTime(0.f),
        m_pTextComponent(pTextComponent)
    {
		if (!m_pTextComponent)
		{
			throw std::runtime_error("FPSComponent requires a TextComponent");
		}
        m_pTextComponent->SetText("0 FPS");
    }

    FPSComponent::~FPSComponent()
    {

    }
    void FPSComponent::Update(const float& deltaTime)
    {
        m_ElapsedTime += deltaTime;
        if (m_ElapsedTime < 0.2f)
			return;
        m_ElapsedTime = 0.f;

        m_FPS = (1.0f / deltaTime);
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << m_FPS;
        std::string fps = ss.str() + " FPS";

		m_pTextComponent->SetText(fps);
    } 

    void FPSComponent::Render() const
    {
    }

    void FPSComponent::SetPosition(const float x, const float y)
    {
        m_transform.SetPosition(x, y, 0.0f);
    }
}