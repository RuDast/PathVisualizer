#include "render.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../utils/logger.h"
#include <vector>
#include "../config.h"

using sf::RenderWindow;
using sf::Color;


Render::Render(RenderWindow *window, Grid *grid) : window(window), grid(grid) {
    auto [w, h] = grid->getSizes();
    squares = std::vector<std::vector<sf::RectangleShape>>(h, std::vector<sf::RectangleShape>(w));
    Logger::info("Render was created.");
}

Render::~Render() {
    Logger::info("Render was destroyed.");
}

void Render::createGrid() {
    auto [w, h] = grid->getSizes();
    for (unsigned long long i = 0; i < h; ++i) {
        for (unsigned long long j = 0; j < w; ++j) {
            auto current = &squares[i][j];
            current->setFillColor(Color::White);
            current->setPosition({static_cast<float>(j * window::GRID_LENGHT), static_cast<float>(i * window::GRID_LENGHT)});
            current->setSize({window::GRID_LENGHT, window::GRID_LENGHT});
            current->setOutlineThickness(2.f);
            current->setOutlineColor(Color::Black);
        }
    }
    Logger::info("Grid was created.");
}

void Render::drawGrid() {
    auto [w, h] = grid->getSizes();
    for (unsigned long long i = 0; i < h; ++i) {
        for (unsigned long long j = 0; j < w; ++j) {
            auto current = &squares[i][j];
            auto type = grid->getType(j, i);

            switch (type) {
                case GridTypes::Empty:
                current->setFillColor(Color::White);
                break;

                case GridTypes::Path:
                current->setFillColor(Color::Yellow);
                break;
            
                case GridTypes::Visited:
                current->setFillColor(Color::Cyan);
                break;

                case GridTypes::Finish:
                case GridTypes::Start:
                current->setFillColor(Color::Green);
                break;

                case GridTypes::Neighbour:
                current->setFillColor(Color::Magenta);
                break;

                case GridTypes::Close:
                current->setFillColor(Color::Red);
            }
            window->draw(*current);
        }
    }
}
