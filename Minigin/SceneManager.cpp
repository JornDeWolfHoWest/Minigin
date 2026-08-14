#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::SwitchScene(const std::string& name, bool forceSwitch)
{
	const auto it = std::ranges::find_if(
		m_Scenes,
		[name](const auto& scene)
		{
			return scene->GetName() == name;
		});

	if (it == m_Scenes.end())
		return;

	m_SceneToSwitchTo = *(it);

	if (forceSwitch)
	{
		m_ActiveScene = m_SceneToSwitchTo;
		return;
	}
	m_SceneSwitchRequested = true;
}

void dae::SceneManager::Update(const float& deltaTime)
{
	if (m_SceneSwitchRequested)
	{
		m_ActiveScene = m_SceneToSwitchTo;
		m_SceneToSwitchTo.reset();
		m_SceneSwitchRequested = false;
	}
	m_ActiveScene->Update(deltaTime);
}

void dae::SceneManager::FixedUpdate() const
{
	m_ActiveScene->FixedUpdate();
}

void dae::SceneManager::Render() const
{
	m_ActiveScene->Render();
}

void dae::SceneManager::RemoveSceneIfExists(const std::string& name)
{
	auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(),
		[&name](const std::shared_ptr<Scene>& scene)
		{
			return scene && scene->GetName() == name;
		});

	if (it == m_Scenes.end())
		return;

	// If the scene we are removing is currently active, clear it safely
	if (m_ActiveScene == *it)
	{
		m_ActiveScene.reset();
	}

	// If it's scheduled to be switched to, clear that too
	if (m_SceneToSwitchTo == *it)
	{
		m_SceneToSwitchTo.reset();
	}

	m_Scenes.erase(it);
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	m_Scenes.emplace_back(std::make_shared<Scene>(name));
	if (m_ActiveScene == nullptr)
		m_ActiveScene = m_Scenes.back();
	return *m_Scenes.back();
}
