﻿#include "StateGame.hpp"
#include "Game.hpp"
#include "GameProperties.hpp"
#include "Hud.hpp"
#include "SmartShape.hpp"
#include "SmartSprite.hpp"
#include "TweenAlpha.hpp"
#include "color.hpp"

void StateGame::doInternalUpdate(float const elapsed) { m_overlay->update(elapsed); }

void StateGame::doInternalDraw() const
{
    m_background->draw(getGame()->getRenderTarget());
    drawObjects();
    m_overlay->draw(getGame()->getRenderTarget());
}

void StateGame::doCreate()
{
    float w = static_cast<float>(getGame()->getRenderTarget()->getSize().x);
    float h = static_cast<float>(getGame()->getRenderTarget()->getSize().y);
    m_hud = std::make_shared<Hud>();

    using JamTemplate::SmartShape;
    using JamTemplate::TweenAlpha;

    m_background = std::make_shared<SmartShape>();
    m_background->makeRect({ w, h });
    m_background->setColor(GP::PaletteBackground());
    m_background->update(0.0f);

    m_overlay = std::make_shared<SmartShape>();
    m_overlay->makeRect(jt::vector2 { w, h });
    m_overlay->setColor(jt::color { 0, 0, 0 });
    m_overlay->update(0);
    auto tw
        = TweenAlpha<SmartShape>::create(m_overlay, 0.5f, std::uint8_t { 255 }, std::uint8_t { 0 });
    tw->setSkipFrames();
    add(tw);

    doCreateInternal();
    add(m_hud);
}

void StateGame::doCreateInternal() { }
