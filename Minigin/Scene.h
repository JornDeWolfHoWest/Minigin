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
	private:
		friend class SceneManager;
		std::string m_name{};

		std::vector<std::unique_ptr<GameObject>> m_objects{};
	};

}
