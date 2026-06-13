#pragma once
#include <BaseComponent.h>
#include <functional>
#include <vector>

namespace game
{
	enum class LevelType
	{
		Single,
		Double,
		Cycle
	};
	class LevelObserver
	{
	public:
		LevelObserver() = default;
		virtual ~LevelObserver() = default;
		virtual void LevelDisc() = 0;
		virtual void NextLevel() = 0;
		virtual void GameComplete() = 0;
	};
	class LevelCubeObserver
	{
	public:
		LevelCubeObserver() = default;
		virtual ~LevelCubeObserver() = default;
		virtual void CubeDone() = 0;
		virtual void CubeActivated() = 0;
		virtual void CubeUndone() = 0;
	};

	class DiscObserver
	{
	public:
		DiscObserver() = default;
		virtual ~DiscObserver() = default;
		virtual void DiscDoneMoving() = 0;
	};


	enum class Side;
	enum class Direction;
	class Walkable;
	class Disc;
	class LevelObserver;
	class Score;

	struct LevelSettings
	{
		int levelSize = 7;
		int discAmount = 2;
		float scale = 2.0f;
	};

	//The actual level is 2 sizes bigger but the LevelIndex(int row, int col) will return the index for the cubes when using row: 0-6 and col: 0-(0,1,2,3,4,5,6) depending on the row.
	class Level final : public dae::BaseComponent, public LevelCubeObserver, public DiscObserver
	{
	public:
		void Update(const float&) override;
		void FixedUpdate() override {};
		void Render() const override {};

		Level(dae::GameObject* owner, int levelSize, int discAmount, game::Score* score);
		virtual ~Level() = default;

		void SetLevel(Walkable* walkable, int row, int col);

		Walkable* GetTopCube() const;
		Walkable* GetTopRightCube() const;
		Walkable* GetTopLeftCube() const;
		Walkable* GetBottomRightCube() const;
		Walkable* GetBottomLeftCube() const;

		Walkable* GetWalkable(Side side, Direction direction, int row, int col) const;

		static unsigned int LevelIndex(int row, int col);

		int GetLevelSize() const { return m_LevelSize; }

		void CubeDone() override;
		void CubeActivated() override;
		void CubeUndone() override;
		void DiscDoneMoving() override;

		void AddScore(unsigned int score);

		void AddObserver(LevelObserver* observer);
		void ActivateDiscs();

	private:
		Walkable* GetWalkableTop(Direction direction, int row, int col) const;
		Walkable* GetWalkableRight(Direction direction, int row, int col) const;
		Walkable* GetWalkableLeft(Direction direction, int row, int col) const;

		void RemoveUsedDisc(std::vector<int>& discs, int row) const;

		void NextLevel();

		void NotifyObservers(std::function<void(LevelObserver*)> observerFunction);

		std::vector<Walkable*> m_Level;
		std::vector<LevelObserver*> m_LevelObservers;
		Score* m_Score;
		const int m_LevelSize;
		const int m_DiscAmount;
		const int m_Win;
		int m_WinCounter;
		int m_LevelCounter;
		const int m_MaxLevel;

		static const int m_CubeScore{ 25 };
	};
}
