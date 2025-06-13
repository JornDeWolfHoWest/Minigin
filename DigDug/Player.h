#pragma once
#include "BaseComponent.h"
namespace dae
{
	class GameObject;
}
#include <memory>
#include <iostream>
using namespace dae;
class Player : BaseComponent
{
public:
	Player(std::shared_ptr<dae::GameObject> pObject)
		: BaseComponent(pObject.get()), m_Health(3) {
	}
	bool DamagePlayer()
	{
		--m_Health;
		return m_Health > 0;
	}
	void Update(const float& deltaTime) override
	{
		// if movement isn't -1 then move otherwise don'tµ
		glm::vec3 pos = GetOwner()->GetWorldPosition();
		glm::vec3 velocity{};

		// simple if move then add velocity
		float speed = 64;
		if (m_MoveDown)
			velocity.y = speed;
		else if (m_MoveUp)
			velocity.y = -speed;
		else if (m_MoveLeft)
			velocity.x = -speed;
		else if (m_MoveRight)
			velocity.x = speed;

		//float xAligned = static_cast<float>( static_cast<int>(pos.x) % 32);
		//float yAligned = static_cast<float>( static_cast<int>(pos.y) % 32);
		//if ((m_MoveDown + m_MoveLeft + m_MoveRight + m_MoveUp) > 1)
		//{
		//	// Too many keys
		//	std::cout << "too many keys";
		//	return;
		//}
		//if (m_MoveLeft and yAligned == 0)
		//	velocity.x = -32;
		//else if (m_MoveRight and yAligned == 0)
		//	velocity.x = 32;
		//else if ((m_MoveRight or m_MoveLeft) and yAligned != 0)
		//{
		//	if (yAligned < 4)
		//		velocity.y = 4;
		//	else if (yAligned > 28)
		//		velocity.y = -4;
		//
		//	if (yAligned < 16)
		//		velocity.y = 32;
		//	else
		//		velocity.y = -32;
		//	velocity.x = 0;
		//}
		//else if (m_MoveUp and xAligned == 0)
		//	velocity.y = -32;
		//else if (m_MoveDown and xAligned == 0)
		//	velocity.y = 32;
		//else if ((m_MoveDown or m_MoveUp) and xAligned != 0)
		//{
		//	if (yAligned < 4)
		//		velocity.x = 4;
		//	else if (yAligned > 28)
		//		velocity.x = -4;
		//
		//	if (xAligned < 16)
		//		velocity.x = 32;
		//	else
		//		velocity.x = -32;
		//	velocity.y = 0;
		//}
		//else
		//	velocity.x = 0;
		//	velocity.y = 0;

		pos.x += velocity.x * deltaTime;
		pos.y += velocity.y * deltaTime;
		GetOwner()->SetLocalPosition(pos);

	}
	glm::vec3 GetWorldPosition() const
	{
		return GetOwner()->GetWorldPosition();
	}
	void FixedUpdate() override {}
	void Render() const override {}
	void MoveTo(float x, float y, bool movementActive)
	{
		// here we get the keys that START and STOP PER KEY, we know if it stopped by movement active, so we can set up down left and right based on it
		if (x < 0)
			m_MoveLeft = movementActive;
		else if (x > 0)
			m_MoveRight = movementActive;
		if (y < 0)
			m_MoveUp = movementActive;
		else if (y > 0)
			m_MoveDown = movementActive;
	}
	int GetHealth() const {
		return m_Health;
	}
private:
	int m_Health{ 0 };
	bool m_MoveUp{ false },
		m_MoveDown{ false },
		m_MoveLeft{ false },
		m_MoveRight{ false };
};

