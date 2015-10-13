#include "Pch.hpp"
#include "Component.hpp"

Component::Component(GameObject& gameObj) noexcept
	: m_GameObject{gameObj}
{ }

auto& Component::getGameObject() const noexcept
{
	return m_GameObject;
}