#pragma once

class GameObject;
class Component
{
public:
	using Ptr = std::unique_ptr<Component>;

	explicit Component(GameObject& gameObj) noexcept;
	virtual ~Component() {}

	auto& getGameObject() const noexcept;

protected:
	friend GameObject;

	virtual void onInitialize() {}
	virtual void onUpdate(float ft) {}

private:
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	GameObject& m_GameObject;
};