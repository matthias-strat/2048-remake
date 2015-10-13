#include "Pch.hpp"
#include "State.hpp"
#include "Configuration.hpp"
#include <States/GameState.hpp>

GameState::GameState(StateStack& stack, Context context)
	: IState(stack, context),
	m_Done{ false },
	m_Started{ false }
{
	buildScene();
}

bool GameState::update(sf::Time ft)
{
	if (m_Started && !m_Done)
	{
		auto distVec{ m_Dest - m_Tiles[0]->getPosition() };
		auto distance{ std::sqrt(distVec.x*distVec.x + distVec.y*distVec.y) };
		if (distance > 1.f)
		{
			m_Tiles[0]->move(m_Velocity*ft.asSeconds());
			return true;
		}
		else
		{
			m_Tiles[0]->setPosition(m_Dest);
			m_Done = true;
		}
	}
	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			requestStackPop();
			requestStackPush(StateId::Menu);
			return true;
		}
		
		if (event.key.code == sf::Keyboard::Down) m_Started = true;
	}
	return true;
}

void GameState::draw()
{
	auto& window{ *getContext().window };

	window.draw(m_HeaderText);
	window.draw(m_SubHeaderText);
	window.draw(m_GridSprite);
	for (const auto& tile : m_Tiles) window.draw(*tile.get());
}

void GameState::buildScene()
{
	static const sf::Color fontColor{ 119, 110, 101 };
	const auto videoWidth{ getContext().config->getVideoWidth() };
	const auto videoHeight{ getContext().config->getVideoHeight() };
	const auto& font{ getContext().fonts->get(Fonts::Verdana) };

	m_HeaderText.setFont(font);
	m_HeaderText.setCharacterSize(68u);
	m_HeaderText.setString("2048 Puzzle");
	m_HeaderText.setPosition(videoWidth / 2.f, 50.f);
	auto bounds{ m_HeaderText.getLocalBounds() };
	m_HeaderText.setOrigin(bounds.left + bounds.width / 2.f, 0.f);
	m_HeaderText.setColor(fontColor);

	m_SubHeaderText.setFont(font);
	m_SubHeaderText.setCharacterSize(28u);
	m_SubHeaderText.setString("A remake by Matthias Stratmann");
	m_SubHeaderText.setPosition(videoWidth / 2.f, 130.f);
	bounds = m_SubHeaderText.getLocalBounds();
	m_SubHeaderText.setOrigin(bounds.left + bounds.width / 2.f, 0.f);
	m_SubHeaderText.setColor(fontColor);

	m_GridSprite.setTexture(getContext().textures->get(Textures::Grid));
	m_GridSprite.setPosition(videoWidth / 2.f, videoHeight / 2.f + 50.f);
	m_GridSprite.setOrigin(480 / 2.f, 480 / 2.f);

	addTile(3, 0, 100, 200);

	m_Dest = { videoWidth / 2.f - 480.f / 2.f + 16.f + (3 * 16.f) + (3 * 100.f), videoHeight / 2.f - 480.f / 2.f + 16.f + (3 * 16.f) + (3 * 100.f) + 50.f };
	m_Velocity = m_Dest - m_Tiles[0]->getPosition();
	m_Velocity.x *= 12.f;
	m_Velocity.y *= 12.f;
}

void GameState::addTile(unsigned char slotX, unsigned char slotY, int texX, int texY)
{
	auto videoWidth{ getContext().config->getVideoWidth() };
	auto videoHeight{ getContext().config->getVideoHeight() };
	auto sprite{ std::make_unique<sf::Sprite>() };
	sprite->setTexture(getContext().textures->get(Textures::Tiles));
	sprite->setTextureRect({ texX, texY, 100, 100 });
	sprite->setPosition(videoWidth / 2.f - 480.f / 2.f + 16.f + (slotX*16.f) + (slotX*100.f), videoHeight / 2.f - 480.f / 2.f + 16.f + (slotY*16.f) + (slotY*100.f) + 50.f);
	m_Tiles.emplace_back(std::move(sprite));
}