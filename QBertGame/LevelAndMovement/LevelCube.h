#pragma once
#include <functional>
#include <vector>

#include "RenderComponent.h"
#include "Walkable.h"

class dae::GameObject;

namespace game
{
	enum class LevelType;

	class LevelCubeObserver;

	class LevelCube final : public Walkable
	{
	public:
		void Update(const float&) override {}
		void FixedUpdate() override {}
		void Render() const override {}


		LevelCube(dae::GameObject* owner, LevelType type, Level* level, int row, int col,
			const glm::vec3& topMiddle = glm::vec3(0, 0, 0), const glm::vec3& rightMiddle = glm::vec3(0, 0, 0),
			const glm::vec3& leftMiddle = glm::vec3(0, 0, 0));
		virtual ~LevelCube() = default;

		void SetTexture(std::string textureName, size_t index);

		WalkableType GetWalkableType() override;

		void StepOn(MovementSystem* movement) override;

		void NextLevel() override;

		void AddObserver(LevelCubeObserver* observer);

		void SetCurrentTexture();
	private:
		void StepOn(bool forward = true);
		size_t MaxStates(LevelType type) const;

		void StepOnStandard(bool forward);
		void StepOnCycle(bool forward);

		void NotifyObservers(std::function<void(LevelCubeObserver*)> observerFunction);

		size_t m_State;
		size_t m_MaxStates;

		std::vector<std::string> m_Textures;

		std::vector<LevelCubeObserver*> m_LevelCubeObservers;

		dae::RenderComponent* m_RenderComponent;

		LevelType m_Type;
	};
}
