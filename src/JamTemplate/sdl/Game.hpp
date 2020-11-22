﻿#ifndef JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define JAMTEMPLATE_GAME_HPP_INCLUDEGUARD

#include "GameObject.hpp"
#include "color.hpp"
#include "vector.hpp"
#include <memory>
#include <string>

namespace JamTemplate {
class GameState;

class Game final : public GameObject, public std::enable_shared_from_this<Game> {
public:
    using Sptr = std::shared_ptr<Game>;
    Game(unsigned int w, unsigned int h, float zoom, std::string const& title);

    // this function will likely be called by the user from within update().
    // To ensure consisten behavior within one frame, the actual switching will take place in
    // doSwitchState() which will happen at the beginning of the next update loop.
    void switchState(std::shared_ptr<GameState> newState);

    // void setRenderTarget(std::shared_ptr<sf::RenderTexture> rt);
    // std::shared_ptr<sf::RenderTexture> getRenderTarget();

    // void setRenderWindow(std::shared_ptr<sf::RenderWindow> w);
    // std::shared_ptr<sf::RenderWindow> getRenderWindow();

    // void setView(std::shared_ptr<sf::View> view);
    // std::shared_ptr<sf::View> getView();

    // cannot be const because getView is not const
    jt::vector2 getCamOffset();
    void setCamOffset(jt::vector2 const& ofs);
    void moveCam(jt::vector2 const& v);

    float getZoom() const;

    void shake(float t, float strength, float shakeInterval = 0.005f);

private:
    std::shared_ptr<GameState> m_state { nullptr };
    std::shared_ptr<GameState> m_nextState { nullptr };
    // std::shared_ptr<sf::RenderTexture> m_renderTarget { nullptr };
    // std::shared_ptr<sf::View> m_view { nullptr };
    // std::shared_ptr<sf::RenderWindow> m_renderWindow { nullptr };
    jt::vector2 m_CamOffset { 0.0f, 0.0f };

    float m_zoom;

    float m_shakeTimer { -1.0f };
    float m_shakeStrength { 0.0f };
    float m_shakeInterval { 0.0f };
    float m_shakeIntervalMax { 0.0f };
    jt::vector2 m_shakeOffset { 0, 0 };

    jt::color m_backgroundColor { jt::colors::Black };

    std::weak_ptr<Game> getPtr();

    // overwritten functions from GameObject
    virtual void doUpdate(float const elapsed) override;
    virtual void doDraw() const override;

    void updateShake(float elapsed);
    void resetShake();

    void doSwitchState();
};

} // namespace JamTemplate
#endif