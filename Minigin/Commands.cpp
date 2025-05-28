#include "Commands.h"
#include "Player.h"

namespace dae {
    void UpStartCommand::execute() {
        m_Player->UpStart();
    }
	void UpEndCommand::execute() {
		m_Player->UpEnd();
	}
	void DownStartCommand::execute() {
		m_Player->DownStart();
	}
	void DownEndCommand::execute() {
		m_Player->DownEnd();
	}
	void LeftStartCommand::execute() {
		m_Player->LeftStart();
	}
	void LeftEndCommand::execute() {
		m_Player->LeftEnd();
	}
	void RightStartCommand::execute() {
		m_Player->RightStart();
	}
	void RightEndCommand::execute() {
		m_Player->RightEnd();
	}
	void DamageCommand::execute()
	{
		m_Player->TakeDamage(m_Damage);
	}
	void AddScoreCommand::execute()
	{
		m_Player->AddScore(m_Score);
	}
}