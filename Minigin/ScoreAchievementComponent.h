#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class GameObject;
    class Event;
    class ScoreAchievementComponent final : public BaseComponent, public Observer
    {
    public:
        ScoreAchievementComponent(GameObject* pOwner);
        virtual ~ScoreAchievementComponent();

        void Update(const float& deltaTime) override;
        void Render() const override;
        void Update(const Event& event) override;
        void FixedUpdate() override;


    private:
    };
}
