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

#include "Player.hpp"
#include "Present.hpp"
#include "House.hpp"
#include "Hud.hpp"


class StateGame : public JamTemplate::GameState {
public:
	StateGame() = default;

	void spawnPresent()
	{
		auto b = std::make_shared<Present>();
		add(b);
		b->setPosition(m_player->getPosition());
		m_presents->push_back(b);
	}

	void spawnHouse()
	{
		auto h = std::make_shared<House>();
		h->setPosition(sf::Vector2f{300 + 64, 200-64});
		add(h);
		m_houses->push_back(h);
	}

private:

	std::shared_ptr<Hud> m_hud;
	std::shared_ptr<Player> m_player;
	JamTemplate::ObjectGroup<Present>::Sptr m_presents;
	JamTemplate::ObjectGroup<House>::Sptr m_houses;


	sf::RectangleShape m_sky;

	JamTemplate::SmartShape::Sptr m_overlay;

	void doInternalUpdate (float const /*elapsed*/) override
	{
		//std::cout << m_presents->size() << std::endl;
		for (const auto& hw: *m_houses)
		{
			auto const& h = hw.lock();
			if (h->getAge() <= 0.75f) continue;
			for (auto const& pw : *m_presents)
			{
				auto const& p = pw.lock();
				if (JamTemplate::Collision::BoundingBoxTest(p->getSprite(), h->getSprite()))
				{
					p->kill();
					h->flash();
					m_hud->increaseScore();
				}
			}
		}
	}

	void doCreate() override
	{

		float w = static_cast<float>(getGame()->getRenderTarget()->getSize().x);
		float h = static_cast<float>(getGame()->getRenderTarget()->getSize().y);
		m_sky = sf::RectangleShape(sf::Vector2f(w,h));
		m_sky.setFillColor(sf::Color{ 22,26,61});

		m_hud = std::make_shared<Hud>();
		add(m_hud);

		m_player = std::make_shared<Player>(*this);
		add(m_player);

		m_presents = std::make_shared<JamTemplate::ObjectGroup<Present> >();
		add(m_presents);
		
		using JamTemplate::TweenAlpha;
		using JamTemplate::SmartShape;

		m_overlay = std::make_shared<SmartShape>();
		m_overlay->makeRect(sf::Vector2f{ w,h });
		m_overlay->setColor(sf::Color{ 0,0,0 });
		auto tw = TweenAlpha<SmartShape>::create(m_overlay, 0.5f, sf::Uint8{ 255 }, sf::Uint8{ 0 });
		add(tw);

		m_houses = std::make_shared<JamTemplate::ObjectGroup<House>>();
		add(m_houses);

		JamTemplate::Timer::Sptr t = std::make_shared<JamTemplate::Timer>(1.5f, [this]() {spawnHouse(); });
		add(t);
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
