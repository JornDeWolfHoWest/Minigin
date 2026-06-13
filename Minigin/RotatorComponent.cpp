#include <stdexcept>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "RotatorComponent.h"
#include "GameObject.h"
#include "Transform.h"

static const float PI = (3.14159265f);
static const float DegToRadRatio = (PI / 180.0f);
using namespace dae;

RotatorComponent::RotatorComponent(float radius, float speed, GameObject* pOwner) :
    BaseComponent(pOwner), m_Radius(radius), m_Speed(speed)
{
}

void RotatorComponent::Update(const float& deltaTime)
{
    m_Angle += m_Speed * deltaTime;
    if (m_Angle < -360)
        m_Angle += 360;
    if (m_Angle > 360)
        m_Angle -= 360;
    double angleInRadians = m_Angle * DegToRadRatio;

    // Calculate the x and y coordinates
    double x = m_Radius * std::cos(angleInRadians);
    double y = m_Radius * std::sin(angleInRadians);

    GetOwner()->SetLocalPosition(static_cast<float>(x), static_cast<float>(y));
}
void RotatorComponent::SetRadius(float radius)
{
    m_Radius = radius;
}
void RotatorComponent::SetSpeed(float speed)
{
    m_Speed = speed;
}