#pragma once

#include "BaseComponent.h"

#include <memory>
#include <string>

namespace dae
{
	class Texture2D;

	class RenderComponent : public BaseComponent
	{
	public:
		explicit RenderComponent(GameObject* owner, const std::string& filename = "");

		virtual ~RenderComponent() = default;

		RenderComponent(const RenderComponent&) = delete;
		RenderComponent(RenderComponent&&) noexcept = delete;
		RenderComponent& operator=(const RenderComponent&) = delete;
		RenderComponent& operator=(RenderComponent&&) noexcept = delete;

		virtual void Render() const override;
		virtual void Update(const float&) override {};
		virtual void FixedUpdate() override {};

		void SetTexture(const std::string& filename);

	protected:
		std::shared_ptr<Texture2D> m_Texture{};
	};
}