#include "Customer.hpp"
#include "StateGame.hpp"


void Customer::doUpdate(float const elapsed)
{
	float a = getAge();
	std::cout << a << std::endl;
	float h = getGame()->getRenderTarget()->getSize().y;
	if (a < 1)
	{
		setPosition(sf::Vector2f{ getPosition().x,  h - a * h / 2 });
		//std::cout << getPosition().x << " " << getPosition().y << "\n";
	}
	else if (a > 1 && a - elapsed <= 1)
	{
		m_shape.shake(1.0, 1,0.025f);
	}
	else if (a < 3)
	{
		if (JamTemplate::InputManager::justPressed(sf::Keyboard::Space))
		{
			m_sold = true;
			m_shape.flash(0.2f, sf::Color::Green);
			m_gameState.getHud()->increaseScore();
		}
		
		m_text.setText("more more more");
	}
	else if (m_sold && a > 3 && a < 4)
	{
		a -= 3;
		setPosition(sf::Vector2f{ getPosition().x,   h / 2 + a * h*0.25f });
	}
	else if (m_sold && a > 4 && a - elapsed < 4)
	{
		m_text.setText("tzzzzz");
		m_shape.flash(0.25);
	}
	else if (m_sold &&  a > 4.2)
	{
		getGame()->shake(0.5, 1);
		kill();
	}
	else if (a > 3 && a < 4)
	{
		m_text.setText("boooring :(");
		a -= 3;
		setPosition(sf::Vector2f{ getPosition().x,   h / 2 + a * h*0.75f });
	}


	if (a > 5)
	{
		kill();
	}

	m_shape.setPosition(getPosition());
	m_shape.update(elapsed);

	auto p = getPosition() + sf::Vector2f{ 0, -16 };
	auto pi = sf::Vector2i{ static_cast<int>(p.x), static_cast<int>(p.y) };
	m_text.setPosition(sf::Vector2f{ static_cast<float>(pi.x), static_cast<float>(pi.y) });
	m_text.update(elapsed);
}
