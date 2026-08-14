#pragma once

#include "RenderComponent.h"

#include <string>
#include <unordered_map>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace dae
{
	struct AnimationData
	{
		SDL_Rect sourceSprite{};
		SDL_Rect currentSprite{};
		int animationFrames{ 0 };
		float frameTime{ (1.0f / 60.0f) * 8.0f };
		int currentFrame{ 0 };

		AnimationData() = default;

		AnimationData(const SDL_Rect& source, int numFrames, float frameTime = (1.0f / 60.0f) * 8.0f)
			: sourceSprite{ source }
			, currentSprite{ source }
			, animationFrames{ numFrames }
			, frameTime{ frameTime }
		{}

		AnimationData(int rowIdx, int numFrames, int srcSize = 16, float frameTime = (1.0f / 60.0f) * 8.0f)
			: sourceSprite{ 0, rowIdx * srcSize, srcSize, srcSize }
			, currentSprite{ sourceSprite }
			, animationFrames{ numFrames }
			, frameTime{ frameTime }
		{}
	};

	class AnimationComponent final : public RenderComponent
	{
	public:
		AnimationComponent(GameObject* owner, const std::string& textureFilePath);
		~AnimationComponent() override = default;

		AnimationComponent(const AnimationComponent& other) = delete;
		AnimationComponent(AnimationComponent&& other) = delete;
		AnimationComponent& operator=(const AnimationComponent& other) = delete;
		AnimationComponent& operator=(AnimationComponent&& other) = delete;

		void AddAnimation(const std::string& name, const AnimationData& animation);
		void RemoveAnimation(const std::string& name);
		void SetCurrentAnimation(const std::string& name);

		[[nodiscard]] const std::string& GetCurrentAnimationName() const { return m_currentAnimationName; }

		void SetDestinationSize(const glm::vec2& size);
		void SetForwardDirection(const glm::vec3& direction);
		[[nodiscard]] const glm::vec3& GetForwardDirection() const { return m_forwardDirection; }

		void Update(const float& deltaTime) override;
		void Render() const override;


	private:
		std::unordered_map<std::string, AnimationData> m_animations{};

		std::string m_currentAnimationName{};
		AnimationData m_currentAnimation{};

		glm::vec2 m_destinationSize{};
		glm::vec3 m_forwardDirection{ 1.0f, 0.0f, 0.0f };
		bool m_flipHorizontal{ false };

		float m_frameTimer{ 0.0f };
	};
}