#pragma once
#include "GameObject.h"
#include "BaseComponent.h"
#include "Subject.h"
#include "HealthChangedEvent.h"
#include "ScoreChangedEvent.h"

namespace dae
{
    class Player : public BaseComponent, public Subject {
    private:
		int m_Health{};
        int m_Speed{};
        bool isMovingUp{};
		bool isMovingDown{};
		bool isMovingLeft{};
		bool isMovingRight{};
		int m_Score{};

        Player(const Player& other) = delete;
        Player(Player&& other) = delete;
        Player& operator=(const Player& other) = delete;
        Player& operator=(Player&& other) = delete;
    public:
		Player(GameObject* owner, int speed) : m_Health(3), m_Speed(speed), BaseComponent(owner)
        {

        }
		virtual ~Player() = default;

		virtual void Update(const float& deltaTime) override
		{
			GameObject* owner = GetOwner();
			if (isMovingUp)
			{
				owner->SetLocalPosition(glm::vec3{0,-1 * m_Speed * deltaTime,0} + owner->GetLocalPosition());
			}
			if (isMovingDown)
			{
				owner->SetLocalPosition(glm::vec3{ 0,1 * m_Speed * deltaTime,0 } + owner->GetLocalPosition());
			}
			if (isMovingLeft)
			{
				owner->SetLocalPosition(glm::vec3{ -1 * m_Speed * deltaTime,0,0 } + owner->GetLocalPosition());
			}
			if (isMovingRight)
			{
				owner->SetLocalPosition(glm::vec3{ 1 * m_Speed * deltaTime,0,0 } + owner->GetLocalPosition());
			}
		}
		virtual void Render() const override
		{
		}
        virtual void FixedUpdate() override
        {
        }

		int GetHealth() const { return m_Health; }

		int GetScore() const { return m_Score; }

		void AddScore(int score)
		{
			m_Score += score;
			Notify(ScoreChangedEvent(m_Score)); // Notify observers about the score change
		}

		void TakeDamage(int damage)
		{
			if (m_Health <= 0) return;
			m_Health -= damage;
			Notify(HealthChangedEvent(m_Health)); // Notify observers about the health change
		}

        void UpStart() {
			isMovingUp = true;
        }
        void DownStart() {
			isMovingDown = true;
        }
        void LeftStart() {
			isMovingLeft = true;
        }
        void RightStart() {
			isMovingRight = true;
        }
        void UpEnd() {
            isMovingUp = false;
        }
		void DownEnd() {
			isMovingDown = false;
		}
        void LeftEnd() {
            isMovingLeft = false;
        }
		void RightEnd() {
			isMovingRight = false;
		}
    };
}
