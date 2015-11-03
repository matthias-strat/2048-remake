#include "Pch.hpp"
#include "State.hpp"
#include "Configuration.hpp"
#include <States/MenuState.hpp>

#include <sstream>

MenuState::MenuState(StateStack& stack, Context context)
    : IState(stack, context)
{
    static const sf::Color fontColor{ 119, 110, 101 };
    const auto videoWidth{ context.config->getVideoWidth() };
    const auto videoHeight{ context.config->getVideoHeight() };
    const auto& font{ context.fonts->get(Fonts::Verdana) };
	
    m_MenuSprite.setTexture(getContext().textures->get(Textures::Menu));
    m_MenuSprite.setPosition(videoWidth / 2.f, videoHeight / 2.f + 30.f);
    m_MenuSprite.setOrigin(230 / 2.f, 300 / 2.f);

    m_ButtonSprite.setTexture(getContext().textures->get(Textures::MenuButton));
    m_ButtonSprite.setTextureRect({ 0, 0, 180, 40 });
    m_ButtonSprite.setPosition(videoWidth / 2.f, (videoHeight / 2.f + 30.f) - 300 / 2.f + 30);
    m_ButtonSprite.setOrigin(180 / 2.f, 0.f);

    m_ButtonText.setFont(font);
    m_ButtonText.setCharacterSize(16u);
    m_ButtonText.setString("Start");
    m_ButtonText.setPosition(videoWidth / 2.f, (videoHeight / 2.f + 30.f) - 300 / 2.f + 30 + 20);
    auto bounds{ m_ButtonText.getLocalBounds() };
    m_ButtonText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    m_ButtonText.setColor({ 248, 238, 228 });

    m_HeaderText.setFont(font);
    m_HeaderText.setCharacterSize(68u);
    m_HeaderText.setString("2048 Puzzle");
    m_HeaderText.setPosition(videoWidth / 2.f, 50.f);
    bounds = m_HeaderText.getLocalBounds();
    m_HeaderText.setOrigin(bounds.left + bounds.width / 2.f, 0.f);
    m_HeaderText.setColor(fontColor);

    m_SubHeaderText.setFont(font);
    m_SubHeaderText.setCharacterSize(28u);
    m_SubHeaderText.setString("A remake by Matthias Stratmann");
    m_SubHeaderText.setPosition(videoWidth / 2.f, 130.f);
    bounds = m_SubHeaderText.getLocalBounds();
    m_SubHeaderText.setOrigin(bounds.left + bounds.width / 2.f, 0.f);
    m_SubHeaderText.setColor(fontColor);

    m_FooterLeftText.setFont(font);
    m_FooterLeftText.setCharacterSize(14);
    m_FooterLeftText.setString("This game was created for learning purposes and the source code is publicly available.");
    bounds = m_FooterLeftText.getLocalBounds();
    m_FooterLeftText.setPosition(3.f, videoHeight - bounds.top - bounds.height - 3.f);
    m_FooterLeftText.setColor(fontColor);

    m_OriginalText.setFont(font);
    m_OriginalText.setCharacterSize(14);
    m_OriginalText.setString("Please visit http://gabrielecirulli.github.io/2048/ for the original version of this game.");
    auto initialHeight{ videoHeight - bounds.top - bounds.height - 3.f };
    bounds = m_OriginalText.getLocalBounds();
    m_OriginalText.setPosition(3.f, initialHeight - bounds.top - bounds.height - 3.f);
    m_OriginalText.setColor(fontColor);

    std::stringstream ss;
    ss << "powered by SFML " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH;

    m_FooterRightText.setFont(font);
    m_FooterRightText.setCharacterSize(14);
    m_FooterRightText.setString(ss.str());
    bounds = m_FooterRightText.getLocalBounds();
    m_FooterRightText.setPosition(videoWidth - bounds.left - bounds.width - 3.f, videoHeight - bounds.top - bounds.height - 3.f);
    m_FooterRightText.setColor(fontColor);
}

bool MenuState::update(sf::Time)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
        // Remove current state (menu) and push game state
        requestStackPop();
        requestStackPush(StateId::Game);
    }
    return true;
}

void MenuState::draw()
{
    auto& window{ *getContext().window };
    window.draw(m_MenuSprite);
    window.draw(m_ButtonSprite);
    window.draw(m_ButtonText);
    window.draw(m_HeaderText);
    window.draw(m_SubHeaderText);
    window.draw(m_FooterLeftText);
    window.draw(m_OriginalText);
    window.draw(m_FooterRightText);
}