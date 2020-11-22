﻿#ifndef JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define JAMTEMPLATE_GAME_HPP_INCLUDEGUARD

#include "GameBase.hpp"
#include "rendertarget.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <memory>
#include <string>

namespace JamTemplate {

//
// Game class to be implemented by sfml/sdl
//
class Game final : public JamTemplate::GameBase {
public:
    using Sptr = std::shared_ptr<Game>;

    Game(unsigned int w, unsigned int h, float zoom, std::string const& title);

    void runGame(std::shared_ptr<GameState> InitialState);

    void setRenderTarget(std::shared_ptr<jt::renderTarget> rt);
    std::shared_ptr<jt::renderTarget> getRenderTarget();

private:
    std::shared_ptr<jt::renderTarget> m_renderTarget { nullptr };
    std::shared_ptr<sf::View> m_view { nullptr };
    std::shared_ptr<sf::RenderWindow> m_renderWindow { nullptr };
    float m_zoom;

    // override functions from GameBase
    virtual void doUpdate(float const elapsed) override;
    virtual void doDraw() const override;

    void updateShake(float elapsed);
    void resetShake();

    void setView(std::shared_ptr<sf::View> view);
    std::shared_ptr<sf::View> getView();

    void setRenderWindow(std::shared_ptr<sf::RenderWindow> w);
    std::shared_ptr<sf::RenderWindow> getRenderWindow();
};

} // namespace JamTemplate
#endif