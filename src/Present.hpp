#ifndef GAME_PRESENT_HPP_INCLUDEGUARD
#define GAME_PRESENT_HPP_INCLUDEGUARD

#include <string>
#include <SFML/Graphics.hpp>

#include "JamTemplate/GameObject.hpp"
#include "JamTemplate/SmartSprite.hpp"
#include "JamTemplate/Transform.hpp"

class Present : public JamTemplate::GameObject, public JamTemplate::Transform {
public:
	Present()
	{
		m_sprite = std::make_shared<JamTemplate::SmartSprite>();
		std::string fn = "assets/gift" + std::to_string(JamTemplate::Random::getInt(1, 5)) + ".png";
		m_sprite->loadSprite(fn, sf::IntRect{ 0,0,8,8 });
		
		setAcceleration(sf::Vector2f{0, 100});
		setVelocity(sf::Vector2f{0,-100});
		setBoundsVelocity(sf::FloatRect{0,-100,0,400});
	}
	std::shared_ptr<JamTemplate::SmartSprite> getSprite() { return m_sprite; }

private:
	void doUpdate(float const elapsed) override
	{
		updateTransform(elapsed);
		m_sprite->setPosition(sf::Vector2f(getPosition().x, getPosition().y));
		m_sprite->update(elapsed);

		if (getPosition().y > 1000) kill();
		m_sprite->rotate(getAge()*50);
	}

	void doDraw() const override
	{
		m_sprite->draw(getGame()->getRenderTarget());	
	}

	JamTemplate::SmartSprite::Sptr m_sprite;
};

#endif
