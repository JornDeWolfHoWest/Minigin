#pragma once
#include "BaseComponent.h"
#include <memory>
#include <SDL_ttf.h>
#include "Transform.h"
#include "TextComponent.h"

namespace dae {
    class GameObject;
    class Font;
    class Texture2D;
    class RotatorComponent final : public BaseComponent
    {
    public:
        void Update(const float& deltaTime) override;
        void FixedUpdate() override {};
        void Render() const override;
        void SetRadius(float radius);
        void SetSpeed(float m_Speed);

        RotatorComponent(float radius, float m_Speed, GameObject* pOwner);
        virtual ~RotatorComponent();
        RotatorComponent(const RotatorComponent& other) = delete;
        RotatorComponent(RotatorComponent&& other) = delete;
        RotatorComponent& operator=(const RotatorComponent& other) = delete;
        RotatorComponent& operator=(RotatorComponent&& other) = delete;

    private:
        float m_Radius{};
        float m_Angle{};
        float m_Speed{};
    };
}

