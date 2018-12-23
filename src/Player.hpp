#ifndef GAME_PLAYER_HPP_INCLUDEGUARD
#define GAME_PLAYER_HPP_INCLUDEGUARD

#include <iostream>

#include <SFML/Graphics.hpp>

#include "JamTemplate/Game.hpp"
#include "JamTemplate/Transform.hpp"
#include "JamTemplate/SmartSprite.hpp"
#include "JamTemplate/Animation.hpp"
#include "JamTemplate/MathHelper.hpp"

#include "GameProperties.hpp"
class StateGame;

class Player : public JamTemplate::GameObject, public JamTemplate::Transform {
public:
	Player(StateGame& sg) : m_gameState(sg)
	{
		setPosition(sf::Vector2f{ 20,70});
		setDragVelocity(sf::Vector2f{0.95f,0.95f});
		float mv = GP::playerMovementSpeed();
		setBoundsVelocity(sf::FloatRect{ -mv,-mv,2 * mv,2 * mv });
	}

	~Player() = default;


private:

	float m_shootTimer = 0.0f;

	void doUpdate(float const elapsed) override
	{
		updateShooting(elapsed);
		updateMovement(elapsed);
		m_sprite.update(elapsed);
	}

	void updateShooting(float elapsed)
	{
		m_shootTimer -= elapsed;
		if (m_shootTimer > 0) return;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			shootPresent();
		}
	}
	void updateMovement(float elapsed)
	{
		setAcceleration({ 0.f,0.f });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			setAcceleration({GP::playerAcceleration(),0});
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			setAcceleration({- GP::playerAcceleration() ,0 });
		}
		updateTransform(elapsed);
		m_sprite.setPosition(getPosition());
	}

	void doDraw() const override
	{
		m_sprite.draw(getGame()->getRenderTarget());
	}

	void doCreate()
	{
		float w = static_cast<float>(getGame()->getRenderTarget()->getSize().x);
		float h = static_cast<float>(getGame()->getRenderTarget()->getSize().y);
		setBoundsPosition(sf::FloatRect(0, 0, w-16, h-32));
		m_sprite.loadSprite("assets/santa.png", sf::IntRect{0,0,79,32});
	}
	void shootPresent();

	StateGame& m_gameState;

	JamTemplate::SmartSprite m_sprite;
};

#endif
