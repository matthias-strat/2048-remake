#pragma once

#include "Component.hpp"

namespace priv
{
	std::size_t getUniqueComponentId() noexcept;
}

class GameObject : public sf::Drawable, sf::Transformable
{
public:
	static constexpr int MaxComponents{ 32 };

	using Ptr				= std::unique_ptr<GameObject>;
	using ComponentId		= std::size_t;
	using GroupId			= std::size_t;
	using ComponentArray	= std::array<Component*, MaxComponents>;
	using ComponentBitset	= std::bitset<MaxComponents>;

	template <typename T> static ComponentId getComponentTypeId() noexcept
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

		static auto typeId{ priv::getUniqueComponentId() };
		return typeId;
	}

public:
	GameObject();

	bool isActive() const;
	void activate();
	void deactivate();
	void setIsActive(bool active);

	template <typename T> bool hasComponent() const
	{
		return m_ComponentBitset[getComponentTypeId<T>()];
	}

	template <typename T> T& getComponent() const
	{
		assert(hasComponent<T>());	// specified component type not existent? (programmer mistake)
		auto ptr{ m_ComponentArray[getComponentTypeId<T>()] };
		return *reinterpret_cast<T*>(ptr);
	}
	
	template <typename T, typename... TArgs> T& addComponent(TArgs&&... args)
	{
		assert(!hasComponent<T>());	// specified component type already existent? (programmer mistake)
		
		T* component{ new T(*this, std::forward<TArgs>(args)...) };
		Component::Ptr ptr{ component };
		m_Components.emplace_back(std::move(ptr));
		
		m_ComponentArray[getComponentTypeId<T>()] = component;
		m_ComponentArray[getComponentTypeId<T>()] = true;

		component->onInitialize();
		return *component;
	}

private:
	bool m_IsActive;
	std::vector<Component::Ptr> m_Components;
	ComponentArray m_ComponentArray;
	ComponentBitset m_ComponentBitset;
};