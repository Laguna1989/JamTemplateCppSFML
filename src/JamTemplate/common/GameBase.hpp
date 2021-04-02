﻿#ifndef GUARD_JAMTEMPLATE_GAMEBASE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMEBASE_HPP_GUARD

#include "Color.hpp"
#include "GameInterface.hpp"
#include "GameObject.hpp"
#include "MusicPlayerInterface.hpp"
#include "Rendertarget.hpp"
#include "Vector.hpp"
#include <chrono>
#include <functional>
#include <memory>

namespace jt {
class GameState;

class GameBase : public GameInterface,
                 public GameObject,
                 public std::enable_shared_from_this<GameBase> {
public:
    // Ugly c-style function Pointer required by emscripten. At least it is hidden in a using alias.
    using GameLoopFunctionPtr = void (*)();

    GameBase();
    // this function will likely be called by the user from within update().
    // To ensure consisten behavior within one frame, the actual switching will take place in
    // doSwitchState() which will happen at the beginning of the next update loop.
    void switchState(std::shared_ptr<GameState> newState);

    std::shared_ptr<GameState> getCurrentSate();
    virtual std::shared_ptr<MusicPlayerInterface> getMusicPlayer() = 0;

    // cannot be const because getView is not const
    jt::Vector2 getCamOffset();
    void setCamOffset(jt::Vector2 const& ofs);
    void moveCam(jt::Vector2 const& v);

    void shake(float t, float strength, float shakeInterval = 0.005f);

    virtual float getZoom() const = 0;

    virtual void setRenderTarget(std::shared_ptr<jt::renderTarget> rt) = 0;
    virtual std::shared_ptr<jt::renderTarget> getRenderTarget() const = 0;

    void run();
    virtual void runGame(
        std::shared_ptr<GameState> InitialState, GameLoopFunctionPtr gameloop_function)
        = 0;

protected:
    std::shared_ptr<GameState> m_state { nullptr };
    std::shared_ptr<GameState> m_nextState { nullptr };

    jt::Vector2 m_CamOffset { 0.0f, 0.0f };

    std::chrono::steady_clock::time_point timeLast;

    float m_shakeTimer { -1.0f };
    float m_shakeStrength { 0.0f };
    float m_shakeInterval { 0.0f };
    float m_shakeIntervalMax { 0.0f };
    jt::Vector2 m_shakeOffset { 0, 0 };

    jt::Color m_backgroundColor { jt::colors::Black };

    std::weak_ptr<GameInterface> getPtr();

    // overwritten functions from GameObject
    virtual void doUpdate(float const elapsed) override = 0;
    virtual void doDraw() const override = 0;

    virtual void updateShake(float elapsed) = 0;
    virtual void resetShake() = 0;

    void doSwitchState();
};

} // namespace jt

#endif
