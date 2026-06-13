#include "TextComponent.h"

#include <stdexcept>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Font.h"
#include "Renderer.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(
	GameObject* owner,
	std::shared_ptr<Font> font,
	const std::string& text,
	const SDL_Color& color)
	: RenderComponent(owner)
	, m_Text(text)
	, m_Color(color)
	, m_Font(std::move(font)), m_NeedsUpdate(true)
{}

void dae::TextComponent::Update(const float& )
{
	if (!m_NeedsUpdate)
	{
		return;
	}

	if (m_Text.empty())
	{
		m_Texture.reset();
		m_NeedsUpdate = false;
		return;
	}

	if (m_Texture)
	{
		m_Texture.reset();
	}

	SDL_Surface* surface =
		TTF_RenderText_Blended(
			m_Font->GetFont(),
			m_Text.c_str(),
			m_Text.length(),
			m_Color);

	if (!surface)
	{
		throw std::runtime_error(
			std::string("Render text failed: ") + SDL_GetError());
	}

	SDL_Texture* texture =
		SDL_CreateTextureFromSurface(
			Renderer::GetInstance().GetSDLRenderer(),
			surface);

	SDL_DestroySurface(surface);

	if (!texture)
	{
		throw std::runtime_error(
			std::string("Create text texture failed: ") + SDL_GetError());
	}

	m_Texture = std::make_shared<Texture2D>(texture);

	m_NeedsUpdate = false;
}

void dae::TextComponent::SetText(const std::string& text)
{
	if (m_Text == text)
	{
		return;
	}

	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(const SDL_Color& color)
{
	if (SDL_memcmp(&m_Color, &color, sizeof(SDL_Color)) == 0)
	{
		return;
	}

	m_Color = color;
	m_NeedsUpdate = true;
}