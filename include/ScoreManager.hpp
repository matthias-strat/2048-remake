#pragma once

class Assets;
namespace sf
{
    class Sprite;
}

class ScoreManager
{
public:
    ScoreManager(Assets& assets);
    
    void addScore(int score) noexcept;
    
    int getScore() const noexcept;
    int getBestScore() const noexcept;

    void reset() noexcept;

    void update(float dt);
    void draw(sf::RenderTarget& target);

private:

private:
    sf::Sprite m_Sprite;
    int m_Score{0}, m_BestScore{0};
};