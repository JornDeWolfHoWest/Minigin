#include "FPSComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "BaseComponent.h"

namespace dae
{
    FPSComponent::FPSComponent(std::shared_ptr<Font> font, GameObject* pOwner) :
        BaseComponent(pOwner),
        m_TextComponent(new TextComponent{ "0 FPS", font, pOwner })
    {
    }

    FPSComponent::~FPSComponent()
    {

    }
    void FPSComponent::Update(const float& deltaTime)
    {
        float FPS = (1.0f / deltaTime);

        m_TimeBetween += deltaTime;
        if (m_TimeBetween < 0.15f)
        {
            m_FPSList.emplace_back(FPS);
            return;
        }
        m_TimeBetween -= 0.15f;

        float average{};
        for (int i = 0; i < int(m_FPSList.size()); i++)
        {
            average += m_FPSList[i];
        }
        average /= m_FPSList.size();
        m_FPSList.clear();

        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << FPS;
        std::string fps = ss.str() + " FPS";

        m_TextComponent->SetText(fps);

        m_TextComponent->Update(deltaTime);
    }

    void FPSComponent::Render() const
    {
        m_TextComponent->Render();
    }

    void FPSComponent::SetPosition(const float x, const float y)
    {
		m_TextComponent->SetPosition(x, y);
    }
}