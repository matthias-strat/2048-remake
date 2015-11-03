#pragma once

class IState;
class GameState : public IState
{
public:
    GameState(StateStack& stack, Context context);

    bool update(sf::Time ft) override;
    bool handleEvent(const sf::Event& event) override;
    void draw() override;

private:
    void buildScene();
    void addTile(unsigned char slotX, unsigned char slotY, int texX, int texY);

private:	
    sf::Text m_HeaderText;
    sf::Text m_SubHeaderText;
    sf::Sprite m_GridSprite;
    sf::Sprite m_ScoreboardSprite;
    std::vector<std::unique_ptr<sf::Sprite>> m_Tiles;
    sf::Vector2f m_Dest;
    bool m_Done;
    bool m_Started;
    sf::Vector2f m_Velocity;
};