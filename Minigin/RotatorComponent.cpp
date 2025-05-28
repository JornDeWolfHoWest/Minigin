#include "FPSComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "RotatorComponent.h"
#include "GameObject.h"

namespace dae
{
    RotatorComponent::RotatorComponent(float radius, float m_Speed, GameObject* pOwner) :
        BaseComponent(pOwner), m_Radius(radius), m_Speed(m_Speed)
    {
    }

    RotatorComponent::~RotatorComponent()
    {

    }

    void RotatorComponent::Update(const float& deltaTime)
    {
        m_Angle += m_Speed * deltaTime;
        double angleInRadians = m_Angle * (M_PI / 180.0);

        // Calculate the x and y coordinates
        double x = m_Radius * std::cos(angleInRadians);
        double y = m_Radius * std::sin(angleInRadians);

        GetOwner()->SetLocalPosition(glm::vec3{x, y, 0});
    }

    void RotatorComponent::Render() const
    {

    }
    void RotatorComponent::SetRadius(float radius)
    {
        m_Radius = radius;
    }
    void RotatorComponent::SetSpeed(float speed)
    {
        m_Speed = speed;
    }
}