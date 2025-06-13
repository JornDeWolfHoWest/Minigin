#pragma once
#include "BaseComponent.h"
#include <memory>
#include <SDL_ttf.h>
#include "Transform.h"
#include "string"

namespace dae
{
    class GameObject;
    class Font;
    class Texture2D;
    class TextComponent final : public BaseComponent
    {
    public:
        void Update(const float& deltaTime) override;
        void FixedUpdate() override {};
        void Render() const override;
        glm::vec3 GetPosition();
        void SetPosition(float x, float y);
        void SetText(std::string text);

        TextComponent(std::string text, std::shared_ptr<Font> font, GameObject* pOwner);
        virtual ~TextComponent();
        TextComponent(const TextComponent& other) = delete;
        TextComponent(TextComponent&& other) = delete;
        TextComponent& operator=(const TextComponent& other) = delete;
        TextComponent& operator=(TextComponent&& other) = delete;

    private:
        bool m_NeedsUpdate;
        std::string m_Text;
        Transform m_transform{};
        std::shared_ptr<Font> m_font;
        std::shared_ptr<Texture2D> m_textTexture;
    };
}