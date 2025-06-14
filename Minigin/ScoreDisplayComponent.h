#pragma once
#include "Observer.h"
#include "HealthChangedEvent.h"
#include <iostream>
#include "BaseComponent.h"
#include "TextComponent.h"
#include "Transform.h"

namespace dae
{
    class ScoreDisplayComponent final : public BaseComponent
    {

    public:
        void Update(const float& deltaTime) override;
        void FixedUpdate() override {};
        void Render() const override;
        void SetPosition(float x, float y);

        ScoreDisplayComponent(std::shared_ptr<Font> font, GameObject* pOwner, int& score);
        virtual ~ScoreDisplayComponent();
        ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
        ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
        ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
        ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

    private:
        TextComponent* m_TextComponent;
		int& m_Score;
		int m_PreviousScore{ INT_MIN };
    };
}
