#pragma once

class TileManager;
class Assets;

// Represents the drawable puzzle tile, this class just handles draw logic.
class Tile : public sf::Drawable, public sf::Transformable
{
    friend class TileManager;

public:
    explicit Tile(Assets& assets) noexcept;

    bool getIsAlive() const noexcept;
    void destroy() noexcept;

    int getValue() const noexcept;
    int increaseValue() noexcept;
    void setValue(int value) noexcept;

private:
    void update(float ft);
    void updateTexture() noexcept;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Assets& m_Assets;
    bool m_IsAlive{false};
    int m_Value{2};
    sf::Vertex m_Vertices[4];
};
