#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void RemoveSceneIfExists(const std::string& name);
		Scene& CreateScene(const std::string& name);
		void SwitchScene(const std::string& name);

		void Update(const float& deltaTime);
		void FixedUpdate() const;
		void Render() const;
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes{};
		std::shared_ptr<Scene> m_ActiveScene{};
		std::shared_ptr<Scene> m_SceneToSwitchTo{};
		bool m_SceneSwitchRequested{ false };
	};
}
