#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
    TextComponent::TextComponent(std::string text, std::shared_ptr<Font> font, GameObject* pOwner) :
        BaseComponent(pOwner),
        m_font(font),
        m_NeedsUpdate(true),
        m_Text(text)
    {
    }

    TextComponent::~TextComponent()
    {
    }

    void TextComponent::Update(const float&)
    {
        if (m_NeedsUpdate)
        {
            const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
            const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_Text.c_str(), color);
            if (surf == nullptr)
            {
                throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
            }
            auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
            if (texture == nullptr)
            {
                throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
            }
            SDL_FreeSurface(surf);
            m_textTexture = std::make_shared<Texture2D>(texture);
            m_NeedsUpdate = false;
        }
    }

    void TextComponent::Render() const
    {
        if (m_textTexture != nullptr)
        {
            const auto& pos = m_transform.GetPosition();
            Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
        }
    }

    void TextComponent::SetPosition(const float x, const float y)
    {
        m_transform.SetPosition(x, y, 0.0f);
    }
    void TextComponent::SetText(std::string text)
    {
        m_Text = text;
        m_NeedsUpdate = true;
    }
}