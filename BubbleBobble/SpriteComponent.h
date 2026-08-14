#pragma once
#include "RenderComponent.h"
#include <glm/glm.hpp>
#include <SDL3/SDL.h>

namespace dae
{
	class SpriteComponent final : public RenderComponent
	{
	public:
		SpriteComponent(GameObject* owner, const std::string& textureFilePath);
		SpriteComponent(GameObject* owner, const std::string& textureFilePath, const glm::vec2& srcSize, int row, int col, const glm::vec2& destSize);

		virtual ~SpriteComponent() override = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		void SetSourceSize(const glm::ivec2& newSize);
		void SetSourcePosition(const glm::ivec2& newPos);
		void SetDestinationSize(const glm::vec2& newSize);

	private:
		SDL_Rect m_sourceFrame{};

		float m_destWidth{ 0.0f };
		float m_destHeight{ 0.0f };

		glm::vec3 m_lastPosition{ 0.0f, 0.0f, 0.0f };
		SDL_FlipMode m_flipMode{ SDL_FLIP_NONE };
	};
}