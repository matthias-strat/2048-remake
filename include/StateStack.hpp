#pragma once

#include "State.hpp"

class StateStack
{
public:
    explicit StateStack(IState::Context context);

    template <typename T> void registerState(StateId stateId);

    void update(sf::Time ft);
    void draw();
    void handleEvent(const sf::Event& event);

    void pushState(StateId stateId);
    void popState();
    void clearStates();

    bool isEmpty() const;

private:
    StateStack(const StateStack&) = delete;
    StateStack& operator=(const StateStack&) = delete;

    IState::Ptr createState(StateId stateId);

    void applyPendingChanges();

private:
    enum class Action { Push, Pop, Clear };

    struct PendingChange
    {
        explicit PendingChange(Action action, StateId stateId = StateId::None);

        Action action;
        StateId stateId;
    };

private:
    std::vector<IState::Ptr> m_Stack;
    std::vector<PendingChange> m_PendingChanges;

    IState::Context m_Context;
    std::map<StateId, std::function<IState::Ptr()>> m_Factories;
};

template <typename T> void StateStack::registerState(StateId stateId)
{
    // Ensure that T inherits from IState class.
    static_assert(std::is_base_of<IState, T>::value, "T must inherit from IState");

    m_Factories[stateId] = [this]()
    {
        return std::make_unique<T>(*this, m_Context);
    };
}
