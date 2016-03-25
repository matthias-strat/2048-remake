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

private:
    sf::Sprite m_Sprite;
    int m_Score{0}, m_BestScore{0};
};