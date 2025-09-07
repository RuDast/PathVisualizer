#include "handler.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <functional>
#include <string>
#include "../config.h"
#include "../utils/logger.h"

using namespace sf::Mouse;
using sf::Event;

Handler::Handler(sf::RenderWindow *window, Grid *grid, std::function<void()> enterCallback, std::function<void(int num)> numsCallback) : window(window),
    grid(grid), enterCallback(enterCallback), numsCallback(numsCallback) {
    Logger::info("Handler was created.");
}

Handler::~Handler() {
    Logger::info("Handler was destroyed.");    
}

void Handler::update(const std::optional<sf::Event> event) {
    if (!event.has_value()) {
        return ;
    }

    if (event->is<Event::Closed>()) {
        window->close();
        Logger::info("Window was closed by user.");
    } else if (event->is<Event::MouseButtonPressed>()) {
        if (event->getIf<Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
            auto position = event->getIf<Event::MouseButtonPressed>()->position;
            auto x = position.x / window::GRID_LENGHT;
            auto y = position.y / window::GRID_LENGHT;

            if (s_fCounter % 2 == 0) {
                grid->setType(x, y, GridTypes::Start);
                Logger::info("Start position is (" + std::to_string(x) + ", " + std::to_string(y) + ").");
            } else {
                grid->setType(x, y, GridTypes::Finish);
                Logger::info("Finish position is (" + std::to_string(x) + ", " + std::to_string(y) + ").");
            }
            s_fCounter = (s_fCounter + 1) % 2;
        } else if (event->getIf<Event::MouseButtonPressed>()->button == sf::Mouse::Button::Right) {
            auto position = event->getIf<Event::MouseButtonPressed>()->position;
            auto x = position.x / window::GRID_LENGHT;
            auto y = position.y / window::GRID_LENGHT;

            grid->setType(x, y, GridTypes::Close);
        }
    } else if (event->is<Event::KeyPressed>()) {
        if (event->getIf<Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) {
            enterCallback();
            Logger::info("Enter was pressed");
        } else if (event->getIf<Event::KeyPressed>()->code == sf::Keyboard::Key::Delete) {
            grid->reset();
            Logger::info("Delete was pressed.");
        } else if (event->getIf<Event::KeyPressed>()->code == sf::Keyboard::Key::Num1) {
            Logger::info("Num1 was pressed.");
            numsCallback(1);
        } else if (event->getIf<Event::KeyPressed>()->code == sf::Keyboard::Key::Num2) {
            Logger::info("Num2 was pressed.");
            numsCallback(2);
        }
    } 

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        auto position = sf::Mouse::getPosition(*window);
        auto x = position.x / window::GRID_LENGHT;
        auto y = position.y / window::GRID_LENGHT;
        
        auto [w, h] = grid->getSizes();
        if (x > w || y > h)
            return;

        grid->setType(x, y, GridTypes::Close);
    }
}

