#pragma once

class IState;
class MenuState : public IState
{
public:
	MenuState(StateStack& stack, Context context);

	bool update(sf::Time ft) override;
	bool handleEvent(const sf::Event& event) override;
	void draw() override;

private:
	sf::Sprite m_MenuSprite;
	sf::Sprite m_ButtonSprite;
	sf::Text m_ButtonText;
	sf::Text m_HeaderText;
	sf::Text m_SubHeaderText;
	sf::Text m_FooterLeftText;
	sf::Text m_OriginalText;
	sf::Text m_FooterRightText;
};