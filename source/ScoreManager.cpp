#include "Common.hpp"
#include "ScoreManager.hpp"
#include "Assets.hpp"

ScoreManager::ScoreManager(Assets& assets)
	: m_Assets{assets}
{
	const auto fntSize(18u);
	const auto halfWndHeight(defaultWindowHeight/2.f);

	m_ScoreText.setFont(assets.fntCode);
	m_ScoreText.setCharacterSize(fntSize);
	m_ScoreText.setString("0");
	m_ScoreText.setFillColor(assets.colTxtScore);
	m_ScoreText.setPosition(defaultWindowWidth - 115.f, halfWndHeight - 30.f);
	auto bounds(m_ScoreText.getLocalBounds());
	m_ScoreText.setOrigin(m_ScoreText.getOrigin().x, bounds.top + bounds.height/2.f);

	m_BestScoreText.setFont(assets.fntCode);
	m_BestScoreText.setCharacterSize(fntSize);
	m_BestScoreText.setString("0");
	m_BestScoreText.setFillColor(assets.colTxtScore);
	bounds = m_BestScoreText.getLocalBounds();
	m_BestScoreText.setPosition(defaultWindowWidth - 115.f, halfWndHeight + 30.f);
	m_BestScoreText.setOrigin(m_BestScoreText.getOrigin().x, bounds.top + bounds.height/2.f);
}

void ScoreManager::addScore(int score) noexcept
{
    m_Score += score;
    m_ScoreText.setString(std::to_string(m_Score));
    if (m_Score > m_BestScore)
    {
        m_BestScore = m_Score;
    	m_BestScoreText.setString(std::to_string(m_BestScore));
    }
}

int ScoreManager::getScore() const noexcept
{
    return m_Score;
}

int ScoreManager::getBestScore() const noexcept
{
    return m_BestScore;
}

void ScoreManager::reset() noexcept
{
	m_Score = 0;
	m_ScoreText.setString("0");
}

void ScoreManager::update(float dt)
{

}

void ScoreManager::draw(sf::RenderTarget& target)
{
	target.draw(m_ScoreText);
	target.draw(m_BestScoreText);
}