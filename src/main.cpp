﻿#include "GameProperties.hpp"
#include "JamTemplate/Game.hpp"
#include "StateMenu.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    JamTemplate::Game::Sptr game = std::make_shared<JamTemplate::Game>(800, 600, 2.0f, GP::GameName());
    auto window = game->getRenderWindow();

    game->switchState(std::make_shared<StateMenu>());

    sf::Clock clock;

    while (window->isOpen()) {
        sf::Time elapsed = clock.restart();
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }
        game->update(elapsed.asSeconds());
        game->draw();
    }

    return 0;
}
