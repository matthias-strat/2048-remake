#pragma once

#include "GridComponent.hpp"

class TileComponent
{
public:
	TileComponent(GridComponent* grid, int initialValue);

	int getValue() const;

private:
	GridComponent* m_Grid;
	int m_Value;

};