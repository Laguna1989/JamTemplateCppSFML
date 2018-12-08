#ifndef JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"

namespace JamTemplate
{
	class SmartSprite
	{
	public:

		using Sptr = std::shared_ptr<SmartSprite>;

		void loadSprite(std::string fileName) 
		{
			m_sprite = sf::Sprite(TextureManager::get(fileName));
		}

		

		void setPosition(sf::Vector2f pos)
		{
			m_sprite.setPosition(pos);
		}

		sf::Vector2f getPosition() const
		{
			return m_sprite.getPosition();
		}

		void setColor(const sf::Color& col)
		{
			m_sprite.setColor(col);
		}
		const sf::Color getColor() const
		{
			return m_sprite.getColor();
		}

		void draw(std::shared_ptr<sf::RenderTarget> sptr) const
		{
			sptr->draw(m_sprite);
		}


	private:
		sf::Sprite m_sprite;

	};
}// namespace JamTemplate

#endif
