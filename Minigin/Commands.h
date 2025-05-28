#pragma once

namespace dae {

    class Player;

    class Command {
    public:
        virtual ~Command() {}
        virtual void execute() = 0;
    };

    class UpStartCommand : public Command {
    public:
        UpStartCommand(Player* player) : m_Player(player) {}
        virtual void execute() override;
    private:
        Player* m_Player;
    };
	class UpEndCommand : public Command {
	public:
		UpEndCommand(Player* player) : m_Player(player) {}
		virtual void execute() override;
	private:
		Player* m_Player;
	};


	class DownStartCommand : public Command {
	public:
		DownStartCommand(Player* player) : m_Player(player) {}
		virtual void execute() override;
	private:
		Player* m_Player;
	};
	class DownEndCommand : public Command {
	public:
		DownEndCommand(Player* player) : m_Player(player) {}
		virtual void execute() override;
	private:
		Player* m_Player;
	};

	class LeftStartCommand : public Command {
	public:
		LeftStartCommand(Player* player) : m_Player(player) {}
		virtual void execute() override;
	private:
		Player* m_Player;
	};
	class LeftEndCommand : public Command {
	public:
		LeftEndCommand(Player* player) : m_Player(player) {}
		virtual void execute() override;
	private:
		Player* m_Player;
	};

	class RightStartCommand : public Command {
	public:
		RightStartCommand(Player* player) : m_Player(player) {}
		virtual void execute() override;
	private:
		Player* m_Player;
	};
	class RightEndCommand : public Command {
	public:
		RightEndCommand(Player* player) : m_Player(player) {}
		virtual void execute() override;
	private:
		Player* m_Player;
	};

	// damage command
	class DamageCommand : public Command {
	public:
		DamageCommand(Player* player, int damage) : m_Player(player), m_Damage(damage) {}
		virtual void execute() override;
	private:
		Player* m_Player;
		int m_Damage;
	};


	// AddScore command
	class AddScoreCommand : public Command {
	public:
		AddScoreCommand(Player* player, int score) : m_Player(player), m_Score(score) {}
		virtual void execute() override;
	private:
		Player* m_Player;
		int m_Score;
	};
}