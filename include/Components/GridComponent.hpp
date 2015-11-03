#pragma once

class GridComponent
{
public:
	static const int DefaultNumColumns;
	static const int DefaultNumRows;

	struct Cell
	{
		sf::Vector2i position;
		sf::Vector2f worldPosition;
	};

	explicit GridComponent(int numColumns = DefaultNumColumns, int numRows = DefaultNumRows);

	int getNumColumns() const;
	int getNumRows() const;

	bool hasAvailableCells() const;

private:
	void initializeGrid();

private:
	int m_NumColumns;
	int m_NumRows;
	std::vector<std::vector<Cell>> m_Cells;
};