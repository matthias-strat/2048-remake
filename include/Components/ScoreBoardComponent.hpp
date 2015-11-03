#pragma once

class ScoreBoardComponent
{
public:

	void increaseScore(int score);
	int getCurrentScore() const;
	int getBestScore() const;

private:
	int m_CurrentScore;
	int m_BestScore;
	sf::Text m_CurrentScoreText;
	sf::Text m_BestScoreText;
};