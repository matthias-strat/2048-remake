#include "Pch.hpp"
#include "StateStack.hpp"

StateStack::StateStack(IState::Context context)
	: m_Context{ context }
{

}

void StateStack::update(sf::Time ft)
{
	// Iterate from top to bottom, stop as soon as update() a state returns false.
	for (auto iter{ m_Stack.rbegin() }; iter != m_Stack.rend(); ++iter)
	{
		if (!(*iter)->update(ft)) break;
	}

	applyPendingChanges();
}

void StateStack::handleEvent(const sf::Event& event)
{
	for (auto iter{ m_Stack.rbegin() }; iter != m_Stack.rend(); ++iter)
	{
		if (!(*iter)->handleEvent(event)) break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	// Draw all state from bottom to top
	for (const auto& state : m_Stack) state->draw();
}

void StateStack::pushState(StateId stateId)
{
	m_PendingChanges.emplace_back(PendingChange{ Action::Push, stateId });
}

void StateStack::popState()
{
	m_PendingChanges.emplace_back(PendingChange{ Action::Pop });
}

void StateStack::clearStates()
{
	m_PendingChanges.emplace_back(PendingChange{ Action::Clear });
}

bool StateStack::isEmpty() const
{
	return m_Stack.empty();
}

IState::Ptr StateStack::createState(StateId stateId)
{
	auto found = m_Factories.find(stateId);
	assert(found != m_Factories.end());	// programmer's mistake

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for (auto change : m_PendingChanges)
	{
		switch (change.action)
		{
			case Action::Push:
				m_Stack.emplace_back(createState(change.stateId));
				break;
			case Action::Pop:
				m_Stack.pop_back();
				break;
			case Action::Clear:
				m_Stack.clear();
				break;
		}
	}

	m_PendingChanges.clear();
}

StateStack::PendingChange::PendingChange(Action action, StateId stateId)
	: action{action},
	stateId{stateId}
{ }