#pragma once
#include "BaseComponent.h"
#include <memory>
#include <SDL_ttf.h>
#include "Transform.h"
#include "TextComponent.h"
#include <vector>

namespace dae
{
    class GameObject;
    class Font;
    class Texture2D;
    class FPSComponent final : public BaseComponent
    {
    public:
        void Update(const float& deltaTime) override;
        void FixedUpdate() override {};
        void Render() const override;
        void SetPosition(float x, float y);

        FPSComponent(std::shared_ptr<Font> font, GameObject* pOwner);
        virtual ~FPSComponent();
        FPSComponent(const FPSComponent& other) = delete;
        FPSComponent(FPSComponent&& other) = delete;
        FPSComponent& operator=(const FPSComponent& other) = delete;
        FPSComponent& operator=(FPSComponent&& other) = delete;

    private:
        float m_TimeBetween{};
        TextComponent* m_TextComponent;
        std::vector<float> m_FPSList{};
    };
}