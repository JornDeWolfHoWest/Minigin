#pragma once
#include "BaseComponent.h"
#include "Transform.h"

namespace dae {
    class GameObject;
    class Font;
    class Texture2D;
    class RotatorComponent final : public BaseComponent
    {
    public:
        void Update(const float& deltaTime) override;
        void FixedUpdate() override {};
        void SetRadius(float radius);
        void SetSpeed(float speed);

        RotatorComponent(float radius, float speed, GameObject* pOwner);
        virtual ~RotatorComponent() = default;
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

