﻿#ifndef GAME_STATE_GAME_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_HPP_INCLUDEGUARD

#include "GameState.hpp"
#include <iostream>
#include <memory>
#include <vector>

// fwd decls
namespace JamTemplate {
class SmartShape;
class SmartSprite;
} // namespace JamTemplate

class Hud;

class StateGame : public JamTemplate::GameState {
public:
    StateGame() = default;

protected:
    std::shared_ptr<Hud> m_hud;

private:
    std::shared_ptr<JamTemplate::SmartShape> m_background;
    std::shared_ptr<JamTemplate::SmartShape> m_overlay;
    std::shared_ptr<JamTemplate::SmartSprite> m_sprite;

    void doCreate() override;

    virtual void doCreateInternal();

    virtual void doInternalUpdate(float const elapsed) override;
    virtual void doInternalDraw() const override;
};

#endif
