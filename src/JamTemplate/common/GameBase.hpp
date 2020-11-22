﻿#ifndef GAMEBASE_HPP_GUARD
#define GAMEBASE_HPP_GUARD

#include "GameObject.hpp"
#include "color.hpp"
#include "rendertarget.hpp"
#include "vector.hpp"
#include <chrono>
#include <memory>

namespace JamTemplate {
class GameState;

class GameBase : public GameObject, public std::enable_shared_from_this<GameBase> {
public:
    GameBase();
    // this function will likely be called by the user from within update().
    // To ensure consisten behavior within one frame, the actual switching will take place in
    // doSwitchState() which will happen at the beginning of the next update loop.
    void switchState(std::shared_ptr<GameState> newState);

    // cannot be const because getView is not const
    jt::vector2 getCamOffset();
    void setCamOffset(jt::vector2 const& ofs);
    void moveCam(jt::vector2 const& v);

    void shake(float t, float strength, float shakeInterval = 0.005f);

    virtual void setRenderTarget(std::shared_ptr<jt::renderTarget> rt) = 0;
    virtual std::shared_ptr<jt::renderTarget> getRenderTarget() = 0;

protected:
    std::shared_ptr<GameState> m_state { nullptr };
    std::shared_ptr<GameState> m_nextState { nullptr };

    jt::vector2 m_CamOffset { 0.0f, 0.0f };

    std::chrono::steady_clock::time_point timeLast;

    float m_shakeTimer { -1.0f };
    float m_shakeStrength { 0.0f };
    float m_shakeInterval { 0.0f };
    float m_shakeIntervalMax { 0.0f };
    jt::vector2 m_shakeOffset { 0, 0 };

    jt::color m_backgroundColor { jt::colors::Black };

    std::weak_ptr<GameBase> getPtr();

    // overwritten functions from GameObject
    virtual void doUpdate(float const elapsed) override = 0;
    virtual void doDraw() const override = 0;

    virtual void updateShake(float elapsed) = 0;
    virtual void resetShake() = 0;

    void doSwitchState();
};

} // namespace JamTemplate

#endif