#pragma once

#include "ResourceIdentifiers.hpp"
#include "StateIdentifiers.hpp"

class StateStack;
class Configuration;

// Represents the base interface class for a game state class.
class IState
{
public:
	using Ptr = std::unique_ptr<IState>;

	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Configuration& config);

		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
		Configuration* config;
	};

	virtual ~IState();

	virtual bool update(sf::Time ft) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;
	virtual void draw() = 0;

protected:
	IState(StateStack& stack, Context context);

	Context getContext() const;

	void requestStackPush(StateId stateId) const;
	void requestStackPop() const;
	void requestStackClear() const;

private:
	IState(const IState&) = delete;
	IState& operator=(const IState&) = delete;

	StateStack* m_Stack;
	Context m_Context;
};