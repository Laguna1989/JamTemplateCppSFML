#ifndef GAME_HOUSE_HPP_INCLUDEGUARD
#define GAME_HOUSE_HPP_INCLUDEGUARD

#include <string>
#include <SFML/Graphics.hpp>

#include "JamTemplate/GameObject.hpp"
#include "JamTemplate/SmartSprite.hpp"
#include "JamTemplate/Transform.hpp"
#include "JamTemplate/Game.hpp"

class House : public JamTemplate::GameObject, public JamTemplate::Transform {
public:
	House()
	{
		m_sprite = std::make_shared<JamTemplate::SmartSprite>();
		m_sprite->setPosition(sf::Vector2f{ -5000,-5000 });
		
		std::string fn = "assets/house" + std::to_string(JamTemplate::Random::getInt(1, 4)) + ".png";
		m_sprite->loadSprite(fn, sf::IntRect{ 0,0,64,64 });
		setVelocity(sf::Vector2f{-200,0});
	}

	void flash()
	{
		m_sprite->flash(0.5, sf::Color::White);
	}

	std::shared_ptr<JamTemplate::SmartSprite> getSprite() { return m_sprite; }

private:
	void doUpdate(float const elapsed) override
	{
		updateTransform(elapsed);
		m_sprite->setPosition(sf::Vector2f(getPosition().x, getPosition().y));
		m_sprite->update(elapsed);

		if (getPosition().x < -200) kill();
	}

	void doDraw() const override
	{
		m_sprite->draw(getGame()->getRenderTarget());	
	}

	JamTemplate::SmartSprite::Sptr m_sprite;
};

#endif
