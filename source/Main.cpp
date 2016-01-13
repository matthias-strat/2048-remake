#include "Game.hpp"

/*
struct Tile;

class Grid : public sf::Drawable, public sf::Transformable
{
public:
    struct Cell
    {
        // A value indicating whether this cell is emptry.
        bool isEmpty{true};

        // Gets the associated Tile.
        Tile* tile{nullptr};

        // Gets the position of the cell in the grid.
        Vec2i position;

        // Gets the position of the cell in the world (relative to grids transform)
        Vec2f worldPosition;
    };

public:
    inline explicit Grid(Assets& assets) noexcept
        : m_Sprite{*assets.txGrid},
          m_TestSprite{*assets.txTile}
    {
        m_TestSprite.setPosition(spacing, spacing);
        m_TestSprite.setTextureRect(assets.getTileTextureRect(4));

        // Initialize cells
        m_Cells.resize(numTiles * numTiles);
        for (auto x(0); x < numTiles; ++x)
        {
            for (auto y(0); y < numTiles; ++y)
            {
                auto idx(get1DIndexFrom2D(x, y, numTiles));
                auto& c(m_Cells[idx]);
                c.position = {x, y};
                c.worldPosition = toWorldPosition(c.position);
            }
        }
    }

    inline Grid(const Grid&) = delete;
    inline Grid& operator=(const Grid&) = delete;

    inline Cell getCellAt(int x, int y) const
    {
        return m_Cells[y + numTiles * x];
    }

    inline void foreachCell(const std::function<void(Cell&)>& func, bool includeEmpties = true)
    {
        for (auto& cell : m_Cells)
        {
            if (cell.isEmpty && !includeEmpties) continue;
            func(cell);
        }
    }

private:
    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(m_Sprite, states);
        target.draw(m_TestSprite, states);
    }

private:
    sf::Sprite m_Sprite;

    std::vector<Cell> m_Cells;
    sf::Sprite m_TestSprite;
};

struct Tile
{
    bool isAlive{false};
    bool isMoving{false};
    int value{2};
    Grid::Cell* cell{nullptr};
    Grid::Cell* destCell{nullptr};
};

class TileManager : public sf::Drawable, public sf::Transformable
{
public:
    inline void update(float ft)
    {
    }

private:
    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
    }

private:

};

class Game
{
public:
    inline Game() noexcept
    {
        m_Assets.load();

        m_Grid = std::make_unique<Grid>(m_Assets);
        m_Grid->setPosition(windowWidth / 2.f, windowHeight / 2.f);
        m_Grid->setOrigin(gridSize / 2.f, gridSize / 2.f);

        m_Window.create({ windowWidth, windowHeight }, "2048", sf::Style::Close);
        m_Window.setVerticalSyncEnabled(true);
        m_Window.setKeyRepeatEnabled(false);
    }

    inline void run()
    {
        static const auto timeStep(sf::seconds(1.f / 60.f));
        static const auto quarterSecond(sf::seconds(0.25f));

        auto accumulator(sf::Time::Zero);
        sf::Clock clock;

        while (m_Window.isOpen())
        {
            auto dt(clock.restart());
            if (dt > quarterSecond) dt = quarterSecond;

            accumulator += dt;
            while (accumulator >= timeStep)
            {
                sf::Event event;
                while (m_Window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        m_Window.close();

                    handleEvent(event);
                }

                update(timeStep.asSeconds());
                accumulator -= timeStep;
            }

            auto alpha(accumulator / timeStep);

            m_Window.clear(m_Assets.colBackground);
            draw(alpha);
            m_Window.display();
        }
    }

private:
    inline void handleEvent(const sf::Event& event)
    {
        using k = sf::Keyboard::Key;

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == k::Left || event.key.code == k::A) m_XAxis = -1;
            else if (event.key.code == k::Right || event.key.code == k::D) m_XAxis = 1;

            if (event.key.code == k::Up || event.key.code == k::W) m_YAxis = -1;
            else if (event.key.code == k::Down || event.key.code == k::S) m_YAxis = 1;
        }
    }

    inline void update(float ft)
    {
        if (m_XAxis != 0)
        {
            std::cout << m_XAxis << "\n";
            m_XAxis = 0;
        }
        if (m_YAxis != 0)
        {
            std::cout << m_YAxis << "\n";
            m_YAxis = 0;
        }
    }

    inline void draw(float alpha)
    {
        m_Window.draw(*m_Grid);
    }

    inline void updateDebugText()
    {
    }

private:
    sf::RenderWindow m_Window;

    Assets m_Assets;

    UPtr<Grid> m_Grid{nullptr};

    sf::Text m_DebugText;

    int m_XAxis{0}, m_YAxis{0};
};
*/

int main()
{
    Game{}.run();
    return 0;
}
