#include <algorithm>
#include "Scene.h"

using namespace dae;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(const GameObject& object)
{
	m_objects.erase(
		std::remove_if(
			m_objects.begin(),
			m_objects.end(),
			[&object](const auto& ptr) { return ptr.get() == &object; }
		),
		m_objects.end()
	);
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::FixedUpdate()
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Update(const float& deltaTime)
{
	// First delete all objects that are marked for deletion-
	if (m_objects.size() > 0)
	{
		for (int i = static_cast<int>(m_objects.size()) - 1; i >= 0; --i)
		{
			if (m_objects[i]->IsMarkedForDeletion())
			{
				auto* rawPtr = m_objects[i].release();

				m_objects.erase(m_objects.begin() + i);
				rawPtr->CheckForDeletion();
			}
			else
			{
				m_objects[i]->CheckForDeletion();
			}
		}
	}


	for(auto& object : m_objects)
	{
	 	object->Update(deltaTime);
	}
}

void Scene::Render()
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

const std::string& dae::Scene::GetName() const
{
	return m_name;
}

