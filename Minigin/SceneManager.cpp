#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(const float& delta_time)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(delta_time);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::DeleteScene(const std::string& name)
{
	for (auto it = m_scenes.begin(); it != m_scenes.end();)
	{
		if ((*it)->GetName() == name)
		{
			it = m_scenes.erase(it);
		}
		else
		{
			++it;
		}
	}
}