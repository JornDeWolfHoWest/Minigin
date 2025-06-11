#pragma once
#include <memory>
#include <string>
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class GameObject;

	class TextureComponent : BaseComponent
	{
	public:
		TextureComponent(GameObject* parent, const std::string& filename);
		void Update(const float&) override {}
		void FixedUpdate() override {}
		void Render() const;
		void SetSrcRect(const float x, const float y, const float width, const float height);
		void SetDrawSize(const float width, const float height);
	private:
		float m_SrcX{0}, m_SrcY{0}, m_SrcWidth{0}, m_SrcHeight{0},
			m_DrawWidth{0}, m_DrawHeight{0};

		std::shared_ptr<Texture2D> m_texture{};
	};

}
