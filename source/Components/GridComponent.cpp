#include "Pch.hpp"
#include <Components/GridComponent.hpp>

const int GridComponent::DefaultNumColumns{ 4 };
const int GridComponent::DefaultNumRows{ 4 };

GridComponent::GridComponent(int numColumns, int numRows)
	: m_NumColumns{ numColumns },
	m_NumRows{ numRows }
{
	
}

int GridComponent::getNumColumns() const
{
	return m_NumColumns;
}

int GridComponent::getNumRows() const
{
	return m_NumRows;
}