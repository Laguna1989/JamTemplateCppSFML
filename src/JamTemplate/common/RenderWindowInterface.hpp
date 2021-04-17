﻿#ifndef GUARD_JAMTEMPLATE_RENDERWINDOW_INTERFACE_GUARD_HPP
#define GUARD_JAMTEMPLATE_RENDERWINDOW_INTERFACE_GUARD_HPP

#include "Vector.hpp"
#include <memory>
#include <string>

namespace jt {

class Sprite;

class RenderWindowInterface {
public:
    virtual bool isOpen() const = 0;
    virtual void checkForClose() = 0;

    virtual jt::Vector2 getSize() const = 0;

    virtual void draw(std::shared_ptr<jt::Sprite>) = 0;

    virtual void display() = 0;

    // TODO
    // virtual jt::Vector2 mapPixelToCoords(jt::Vector2 const& point) = 0;
};
} // namespace jt
#endif