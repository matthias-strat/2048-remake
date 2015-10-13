#include "Pch.hpp"
#include "State.hpp"
#include "StateStack.hpp"
#include "Configuration.hpp"

IState::IState(StateStack& stack, Context context)
	: m_Stack{ &stack },
	m_Context{ context }
{ }

IState::~IState()
{ }

IState::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Configuration& config)
	: window{ &window },
	textures{ &textures },
	fonts{ &fonts },
	config{ &config }
{ }

IState::Context IState::getContext() const
{
	return m_Context;
}

void IState::requestStackPush(StateId stateId) const
{
	m_Stack->pushState(stateId);
}

void IState::requestStackPop() const
{
	m_Stack->popState();
}

void IState::requestStackClear() const
{
	m_Stack->clearStates();
}