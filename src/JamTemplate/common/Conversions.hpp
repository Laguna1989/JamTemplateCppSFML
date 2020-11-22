﻿#ifndef JAMTEMPLATE_CONVERSIONS_HPP_GUARD
#define JAMTEMPLATE_CONVERSIONS_HPP_GUARD

#include "vector.hpp"
#include <Box2D/Box2D.h>
#include <tileson.h>

namespace JamTemplate {
namespace C {

jt::vector2 vec(b2Vec2 const& v);
b2Vec2 vec(jt::vector2 const& v);
jt::vector2 vec(tson::Vector2f const& v);
jt::vector2 vec(tson::Vector2i const& v);

} // namespace C
} // namespace JamTemplate

#endif // !JAMTEMPLATE_CONVERSIONS_HPP_GUARD
