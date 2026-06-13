#pragma once
#include "imgui.h"

#include <string>
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae {
	class GameObject;
	class ImGUIComponent final : public BaseComponent
	{
	public:
		void Render() const override;
		void Update(const float&) override {};
		void FixedUpdate() override {};
		void SetPosition(const ImVec2& position);
		void SetPivot(const ImVec2& pivot);

		void SetOpen(bool* open) { m_Open = open; }

		bool IsActive() const { return  m_Active; }
		void SetActive(bool active) { m_Active = active; }

		ImGUIComponent(GameObject* owner, const std::function<void()>& function, const std::string& name = "UI", bool open = false, ImGuiWindowFlags flags = 0);
		~ImGUIComponent() = default;
		ImGUIComponent(const ImGUIComponent& other) = delete;
		ImGUIComponent(ImGUIComponent&& other) noexcept = delete;
		ImGUIComponent& operator=(const ImGUIComponent& other) = delete;
		ImGUIComponent& operator=(ImGUIComponent&& other) noexcept = delete;

	protected:

		const std::string m_Name{};
		std::function<void()> m_Function{};
		ImVec2 m_Position{};
		ImVec2 m_Pivot{};
		ImGuiWindowFlags m_Flags = 0;
		bool m_Open = false;

	private:
		bool m_Active;

		friend class Scene;
	};
}