#include "Common.hpp"
#include "ScoreManager.hpp"
#include "Assets.hpp"

ScoreManager::ScoreManager(Assets& assets)
{
}

void ScoreManager::addScore(int score) noexcept
{
    m_Score += score;
    if (m_Score > m_BestScore)
        m_BestScore = m_Score;
}

int ScoreManager::getScore() const noexcept
{
    return m_Score;
}

int ScoreManager::getBestScore() const noexcept
{
    return m_BestScore;
}