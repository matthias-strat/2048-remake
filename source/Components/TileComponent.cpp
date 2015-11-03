#include "Pch.hpp"
#include <Components/TileComponent.hpp>

TileComponent::TileComponent(GridComponent* grid, int initialValue)
    : m_Grid{ grid },
    m_Value{ initialValue }
{
    assert(initialValue % 2 == 0);	// programmer made a mistake (initialValue mod 2 must be 0)
}
