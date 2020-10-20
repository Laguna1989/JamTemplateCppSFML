﻿#ifndef JAMTEMPLATE_CONVERSIONS_HPP_GUARD
#define JAMTEMPLATE_CONVERSIONS_HPP_GUARD

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

namespace JamTemplate {

namespace C {
    sf::Vector2f vec(b2Vec2 const& v);
    b2Vec2 vec(sf::Vector2f const& v);
}
}

#endif // !JAMTEMPLATE_CONVERSIONS_HPP_GUARD
