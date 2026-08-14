#pragma once
#include "BaseComponent.h"
#include "ScoreComponent.h"

namespace dae
{
	class TextComponent;


	class ScoreObserverComponent final : public BaseComponent, public ScoreObserver
	{
	public:
		explicit ScoreObserverComponent(GameObject* owner);
		virtual ~ScoreObserverComponent() override = default;

		ScoreObserverComponent(const ScoreObserverComponent& other) = delete;
		ScoreObserverComponent(ScoreObserverComponent&& other) = delete;
		ScoreObserverComponent& operator=(const ScoreObserverComponent& other) = delete;
		ScoreObserverComponent& operator=(ScoreObserverComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void FixedUpdate() override {}
		void Render() const override {}

		// ScoreObserver Interface Implementation
		void OnScoreChanged(int newScore, int playerIndex = 0) override;

		void Init(int player1Score, int player2Score = 0);

	private:
		void UpdateText();

		TextComponent* m_pTextComponent{ nullptr };
		int m_player1Score{ 0 };
		int m_player2Score{ 0 };
	};
}