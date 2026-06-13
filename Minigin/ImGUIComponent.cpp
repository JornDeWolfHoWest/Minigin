#include "ImGUIComponent.h"
#include "GameObject.h"

void dae::ImGUIComponent::Render() const
{
	if (!m_Active)
	{
		return;
	}
	ImGui::SetNextWindowPos(m_Position, 0, m_Pivot);
	if (ImGui::Begin(m_Name.c_str(), const_cast<bool*>(&m_Open), m_Flags))
	{
		m_Function();
	}
	ImGui::End();
}

void dae::ImGUIComponent::SetPosition(const ImVec2& position)
{
	m_Position = position;
}

void dae::ImGUIComponent::SetPivot(const ImVec2& pivot)
{
	m_Pivot = pivot;
}

dae::ImGUIComponent::ImGUIComponent(dae::GameObject* gameobject, const std::function<void()>& function, const std::string& name, bool open, ImGuiWindowFlags flags)
	: BaseComponent(gameobject), m_Name(name),
	m_Open(open),
	m_Flags(flags),
	m_Function(function),
	m_Active(true)
{}