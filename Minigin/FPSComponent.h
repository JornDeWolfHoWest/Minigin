#pragma once
#include "BaseComponent.h"
#include <memory>
#include "Transform.h"

namespace dae
{
    class TextComponent;
    class Font;
    class Texture2D;
    class FPSComponent final : public BaseComponent
    {
    public:
        void Update(const float& deltaTime) override;
        void FixedUpdate() override {};
        void Render() const override;
        void SetPosition(float x, float y);

        FPSComponent(GameObject* pOwner, TextComponent* pTextComponent);
        virtual ~FPSComponent();
        FPSComponent(const FPSComponent& other) = delete;
        FPSComponent(FPSComponent&& other) = delete;
        FPSComponent& operator=(const FPSComponent& other) = delete;
        FPSComponent& operator=(FPSComponent&& other) = delete;

    private:
        TextComponent* m_pTextComponent;
        Transform m_transform{};
        float m_FPS;
		float m_ElapsedTime;
    };
}