#pragma once
#include <memory>
#include <string>
#include <vector>
#include "GameObject.h"

namespace dae
{
	class Scene final
	{
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(const GameObject& object);
		void RemoveAll();

		void Update(const float& deltaTime);
		void FixedUpdate();
		void Render();


		Scene(const std::string& name) : m_name(name) {}

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		[[nodiscard]] const std::string& GetName() const;

		template<typename Component>
		[[nodiscard]] Component* GetComponent(bool searchChildren = true) const;

		template<typename Component>
		[[nodiscard]] std::vector<Component*> GetComponents(bool searchChildren = true) const;
	private:
		friend class SceneManager;
		std::string m_name{};

		std::vector<std::unique_ptr<GameObject>> m_objects{};
	};


	template<typename Component>
	inline Component* Scene::GetComponent(bool searchChildren) const
	{
		static_assert(std::is_base_of_v<BaseComponent, Component>, "T must derive from BaseComponent");

		for (const auto& object : m_objects)
		{
			if (object)
			{
				if (auto* comp = object->GetComponent<Component>(searchChildren))
				{
					return comp;
				}
			}
		}
		return nullptr;
	}

	template<typename Component>
	inline std::vector<Component*> Scene::GetComponents(bool searchChildren) const
	{
		static_assert(std::is_base_of_v<BaseComponent, Component>, "Component must derive from BaseComponent");

		std::vector<Component*> results;
		for (const auto& object : m_objects)
		{
			if (object)
			{
				auto comps = object->GetComponents<Component>(searchChildren);
				results.insert(results.end(), comps.begin(), comps.end());
			}
		}
		return results;
	}
}
