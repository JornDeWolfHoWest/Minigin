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
        void Render() const override;
        void SetRadius(float radius);
        void SetPosition(Transform middle);
        void SetSpeed(float speed);

        RotatorComponent(Transform middle, float radius, float speed, GameObject* pOwner);
        virtual ~RotatorComponent();
        RotatorComponent(const RotatorComponent& other) = delete;
        RotatorComponent(RotatorComponent&& other) = delete;
        RotatorComponent& operator=(const RotatorComponent& other) = delete;
        RotatorComponent& operator=(RotatorComponent&& other) = delete;

    private:
        float m_Radius{};
        Transform m_Middle{};
        float m_Angle{};
        float m_Speed{};
    };
}

