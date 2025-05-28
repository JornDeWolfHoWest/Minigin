#pragma once
#include "Observer.h"
#include "HealthChangedEvent.h"
#include <iostream>
#include "BaseComponent.h"
#include "TextComponent.h"
#include "Transform.h"

namespace dae
{
	class HealthDisplayComponent final : public BaseComponent, public Observer
	{

	public:
        void Update(const Event& event) override;

        void Update(const float& deltaTime) override;
        void FixedUpdate() override {};
        void Render() const override;
        void SetPosition(float x, float y);

        HealthDisplayComponent(std::shared_ptr<Font> font, GameObject* pOwner);
        virtual ~HealthDisplayComponent();
        HealthDisplayComponent(const HealthDisplayComponent& other) = delete;
        HealthDisplayComponent(HealthDisplayComponent&& other) = delete;
        HealthDisplayComponent& operator=(const HealthDisplayComponent& other) = delete;
        HealthDisplayComponent& operator=(HealthDisplayComponent&& other) = delete;

    private:
        TextComponent* m_TextComponent;
	};
}
