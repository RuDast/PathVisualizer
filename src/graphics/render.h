#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "../core/grid.h"

class Render {
public:
    Render(sf::RenderWindow *window, Grid* grid);
    ~Render();

    void createGrid();
    void drawGrid();

private:
    sf::RenderWindow *window = nullptr;
    Grid *grid = nullptr;
    std::vector<std::vector<sf::RectangleShape>> squares;
};

#endif // RENDER_H
