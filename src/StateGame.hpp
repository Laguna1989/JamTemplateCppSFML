#ifndef GAME_STATE_GAME_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_HPP_INCLUDEGUARD

#include <iostream>
#include <vector>

#include "JamTemplate/GameState.hpp"
#include "JamTemplate/Timer.hpp"
#include "JamTemplate/Collision.hpp"
#include "JamTemplate/ObjectGroup.hpp"
#include "JamTemplate/SmartSprite.hpp"
#include "JamTemplate/SmartShape.hpp"
#include "JamTemplate/TweenAlpha.hpp"

#include "Customer.hpp"
#include "Hud.hpp"


class StateGame : public JamTemplate::GameState {
public:
	StateGame() = default;

	std::shared_ptr<Hud> getHud() { return m_hud; }


private:

	std::shared_ptr<Hud> m_hud;
	JamTemplate::ObjectGroup<Customer>::Sptr m_customers;
	
	sf::RectangleShape m_sky;

	JamTemplate::SmartShape::Sptr m_overlay;

	void doInternalUpdate (float const elapsed) override
	{
		m_overlay->update(elapsed);
	}

	void doCreate() override
	{
		float w = static_cast<float>(getGame()->getRenderTarget()->getSize().x);
		float h = static_cast<float>(getGame()->getRenderTarget()->getSize().y);
		m_sky = sf::RectangleShape(sf::Vector2f(w,h));
		m_sky.setFillColor(sf::Color{ 30,30,50});

		m_hud = std::make_shared<Hud>();
		add(m_hud);

		m_customers = std::make_shared<JamTemplate::ObjectGroup<Customer>>();
		add(m_customers);
		
		using JamTemplate::TweenAlpha;
		using JamTemplate::SmartShape;

		m_overlay = std::make_shared<SmartShape>();
		m_overlay->makeRect(sf::Vector2f{ w,h });
		m_overlay->setColor(sf::Color{ 0,0,0 });
		m_overlay->update(0);
		auto tw = TweenAlpha<SmartShape>::create(m_overlay, 0.5f, sf::Uint8{ 255 }, sf::Uint8{ 0 });
		add(tw);

		spawnCustomer();
		auto t = std::make_shared<JamTemplate::Timer>(5, [this]() {spawnCustomer(); });
		add(t);
	}

	void spawnCustomer()
	{
		auto c = std::make_shared<Customer>(*this);
		add(c);
		m_customers->push_back(c);
	}
	void drawSky() const
	{
		getGame()->getRenderTarget()->draw(m_sky);

	}

	void doDraw() const override
	{
		drawSky();
		drawObjects();
		m_overlay->draw(getGame()->getRenderTarget());
	}	
};

#endif
