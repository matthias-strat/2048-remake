#include "Pch.hpp"
#include "GameObject.hpp"

std::size_t priv::getUniqueComponentId() noexcept
{
	static auto lastId{ 0u };
	return lastId++;
}

GameObject::GameObject()
	: m_IsActive{ true }
{ }

bool GameObject::isActive() const
{
	return m_IsActive;
}

void GameObject::activate()
{
	setIsActive(true);
}

void GameObject::deactivate()
{
	setIsActive(false);
}

void GameObject::setIsActive(bool active)
{
	m_IsActive = active;
}