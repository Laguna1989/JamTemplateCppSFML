#ifndef GAME_HUD_HPP_INCLUDEGUARD
#define GAME_HUD_HPP_INCLUDEGUARD

#include <string>
#include <SFML/Graphics.hpp>

#include "JamTemplate/GameObject.hpp"

#include "JamTemplate/SmartText.hpp"

class Hud : public JamTemplate::GameObject {
public:
	Hud() 
	{
	}

	void increaseScore()
	{
		m_score++;
		m_text->setText("Money   " + std::to_string(m_score));
	}

private:

	int m_score{ -1 };
	JamTemplate::SmartText::Sptr m_text;

	void doUpdate(float const elapsed) override
	{
		m_text->update(elapsed);
	}

	void doDraw() const override
	{
		m_text->draw(getGame()->getRenderTarget());
	}

	void doCreate() override
	{
		m_text = std::make_shared<JamTemplate::SmartText>();
		m_text->loadFont("assets/font.ttf");
		m_text->setCharacterSize(8);
		m_text->setMoveWithCam(false);
		m_text->setOutline(1, sf::Color::Black);
		increaseScore();
	}

};

#endif
