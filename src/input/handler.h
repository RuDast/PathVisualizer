#ifndef HANDLER_H
#define HANDLER_H

#include <SFML/Graphics.hpp>
#include <functional>
#include "../core/grid.h"

class Handler {
public:
    Handler(sf::RenderWindow *window, Grid *grid, std::function<void()> enterCallback, std::function<void(int num)> numsCallback);
    ~Handler();

    void update(const std::optional<sf::Event> event);

private:
    sf::RenderWindow *window;
    Grid *grid;
    std::function<void()> enterCallback;
    std::function<void(int num)> numsCallback;
    unsigned s_fCounter = 0;
};

#endif // HANDLER_H
