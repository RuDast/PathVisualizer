#ifndef GAME_H
#define GAME_H

#include "graph.h"
#include "grid.h"
#include "../graphics/render.h"
#include "../input/handler.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <optional>
#include <string>
#include "../algorithms/dijkstra.h"
#include "../algorithms/astar.h"

class Game {
public:
    Game();
    ~Game();

    void run();
    void start();
    void numsChange(int num);
    void showEnd(std::string name, float time, float distance, int count);
    void showError(std::string name, float time);

private:
    sf::RenderWindow window;
    Grid grid;
    Render render;
    Handler handler;
    Graph graph;
    bool isRunning = false;
    bool isShow = false;
    unsigned algoNum = 1;
    std::optional<Astar> algo1;
    std::optional<Dijkstra> algo2;
    unsigned long long gameTime = 0;
    float startTime = 0.f;
    float finishTime = 0.f;
    float curTime = 0.f;
    sf::Clock clock;
};

#endif // GAME_H
