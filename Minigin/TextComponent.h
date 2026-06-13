#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "Transform.h"
#include "BaseComponent.h"
#include "RenderComponent.h"
#include <SDL3/SDL.h>

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent final : public RenderComponent
	{
	public:
		void Update(const float&) override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		void SetColor(const SDL_Color& color);

		TextComponent(	GameObject* parent,
						std::shared_ptr<Font> font,
						const std::string& text,
						const SDL_Color& color = { 255, 255, 255, 255 });
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_NeedsUpdate{};

		std::string m_Text{};
		SDL_Color m_Color{ 255, 255, 255, 255 };

		std::shared_ptr<Font> m_Font{};
	};
}
