#include "AnimationComponent.h"

#include <cassert>

#include "GameObject.h"
#include "imgui.h"
#include "Renderer.h"
#include "Texture2D.h"

namespace dae
{
	AnimationComponent::AnimationComponent(GameObject* owner, const std::string& textureFilePath)
		: RenderComponent(owner, textureFilePath)
	{
		assert(m_Texture != nullptr && "Failed to load texture for AnimationComponent");
	}

	void AnimationComponent::AddAnimation(const std::string& name, const AnimationData& animation)
	{
		m_animations.emplace(name, animation);
		if (m_animations.size() == 1)
		{
			SetCurrentAnimation(name);
		}
	}

	void AnimationComponent::RemoveAnimation(const std::string& name)
	{
		m_animations.erase(name);
		if (m_currentAnimationName == name)
		{
			m_currentAnimationName.clear();
			m_currentAnimation = {};
		}
	}

	void AnimationComponent::SetCurrentAnimation(const std::string& name)
	{
		if (auto it = m_animations.find(name); it != m_animations.end())
		{
			m_currentAnimationName = name;
			m_currentAnimation = it->second;
			m_frameTimer = 0.0f;
		}
	}

	void AnimationComponent::SetDestinationSize(const glm::vec2& size)
	{
		m_destinationSize = size;
	}

	void AnimationComponent::SetForwardDirection(const glm::vec3& direction)
	{
		m_forwardDirection = direction;
		m_flipHorizontal = (m_forwardDirection.x < 0.0f);
	}

	void AnimationComponent::Update(const float& deltaTime)
	{
		if (m_currentAnimationName.empty())
			return;

		m_frameTimer += deltaTime;

		if (m_frameTimer >= m_currentAnimation.frameTime)
		{
			if (m_currentAnimation.animationFrames > 0)
			{
				m_currentAnimation.currentFrame = (m_currentAnimation.currentFrame + 1) % m_currentAnimation.animationFrames;
				m_currentAnimation.currentSprite.x = m_currentAnimation.sourceSprite.x + (m_currentAnimation.currentFrame * m_currentAnimation.sourceSprite.w);
				m_currentAnimation.currentSprite.y = m_currentAnimation.sourceSprite.y;
			}
			m_frameTimer = 0.0f;
		}
	}

	void AnimationComponent::Render() const
	{
		if (!m_Texture || m_currentAnimationName.empty())
			return;

		const auto& pos = GetOwner()->GetWorldPosition().GetPosition();
		const SDL_FlipMode flip = m_flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

		// Correctly unroll the position and size into floats to match your Renderer overload
		Renderer::GetInstance().RenderTexture(
			*m_Texture,
			pos.x,
			pos.y,
			m_destinationSize.x,
			m_destinationSize.y,
			m_currentAnimation.currentSprite,
			flip
		);
	}
}