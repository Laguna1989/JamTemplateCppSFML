#ifndef GAME_CUSTOMER_HPP_INCLUDEGUARD
#define GAME_CUSTOMER_HPP_INCLUDEGUARD

#include <iostream>

#include <SFML/Graphics.hpp>

#include "JamTemplate/Game.hpp"
#include "JamTemplate/Transform.hpp"
#include "JamTemplate/SmartShape.hpp"
#include "JamTemplate/SmartText.hpp"
#include "JamTemplate/Animation.hpp"
#include "JamTemplate/MathHelper.hpp"

#include "GameProperties.hpp"
class StateGame;

class Customer : public JamTemplate::GameObject, public JamTemplate::Transform {
public:
	Customer(StateGame& sg) : m_gameState(sg)
	{
		setPosition(sf::Vector2f{ 10, 20 });
	}

	~Customer() = default;



private:

	StateGame& m_gameState;
	JamTemplate::SmartShape m_shape;

	JamTemplate::SmartText m_text;

	bool m_sold{false};

	void doUpdate(float const elapsed) override;
	void doDraw() const override
	{
		m_shape.draw(getGame()->getRenderTarget());
		m_text.draw(getGame()->getRenderTarget());
	}

	void doCreate()
	{
		m_shape.makeRect(sf::Vector2f{12,16});
		m_shape.setColor(sf::Color{ 180,100,90 });

		float w = getGame()->getRenderTarget()->getSize().x;
		float h = getGame()->getRenderTarget()->getSize().y;
		float mindist = w * 0.08;

		setPosition(sf::Vector2f{ JamTemplate::Random::getFloat(mindist, w - mindist), h + 10 });

		m_text.loadFont("assets/font.ttf");
		m_text.setCharacterSize(8);
		//m_text.setScale(sf::Vectokr2f{ 0.5f,0.5f });
		m_text.setOutline(1, sf::Color::Black);
		m_text.setText("sell me\nfirecrackers!");

	}

};

#endif
