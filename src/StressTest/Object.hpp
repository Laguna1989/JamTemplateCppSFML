#ifndef GAME_OBJECT_HPP_INCLUDEGUARD
#define GAME_OBJECT_HPP_INCLUDEGUARD

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <random>

#include "../JamTemplate/GameState.hpp"
#include "../JamTemplate/Game.hpp"
#include "../JamTemplate/Random.hpp"
#include "../JamTemplate/Transform.hpp"
#include "../JamTemplate/SmartShape.hpp"
#include "../JamTemplate/Animation.hpp"
#include "../JamTemplate/MathHelper.hpp"

class Object : public JamTemplate::GameObject, public JamTemplate::Transform {
public:
	using Sptr = std::shared_ptr<Object>;
	Object()
	{
		m_shape = std::make_shared<JamTemplate::Animation>();
		//m_shape->makeRect(sf::Vector2f(10, 10));
		m_shape->add("assets/coin.png", "idle", sf::Vector2u{ 16,16 }, JamTemplate::MathHelper::vectorBetween(0U, 11U), 0.15f);
		m_shape->play("idle");

		m_shape->setColor(JamTemplate::Random::getRandomColor());

		float x = JamTemplate::Random::getFloat(80, 120) -8;
		float y = JamTemplate::Random::getFloat(55, 95) -8;
		
		float vx = JamTemplate::Random::getFloatGauss(0,50);
		float vy = JamTemplate::Random::getFloatGauss(0, 50);

		setPosition({ x, y });
		setVelocity({ vx,vy });
		//setAcceleration({ 0, -50 / 2 });
		setBoundsPosition(sf::FloatRect{ 0,0,200-10,150-10 });
		
	}

	~Object() = default;

	void Flash()
	{
		m_shape->flash(0.1f);
	}
	void Shake()
	{
		m_shape->shake(0.5f, 2.0f,0.05f);
	}
	
	std::shared_ptr<JamTemplate::Animation> getAnimation()
	{
		return m_shape;
	}

private:
	void doUpdate(float const elapsed) override
	{
		updateTransform(elapsed);
		m_shape->setPosition(getPosition());
		m_shape->update(elapsed);
		if (getAge() > 0.75) kill();
	}

	void doDraw() const override
	{
		m_shape->draw(getGame()->getRenderTarget());
		
	}

	std::shared_ptr<JamTemplate::Animation> m_shape;
};


#endif
