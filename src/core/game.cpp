#include "game.h"
#include "../config.h"
#include "grid.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "../utils/logger.h"
#include <windows.h>
#include "../algorithms/astar.h"

#define ull unsigned long long

using sf::RenderWindow;
using sf::VideoMode;
using namespace window;

Game::Game() : window(RenderWindow(VideoMode(
        {WINDOW_WIDTH, WINDOW_HEIGHT}
    ), std::string(WINDOW_NAME) + ": A* algorithm")), grid(GRID_LENGHT), render(&window, &grid), handler(&window, &grid, [this]() { this->start(); }, [this](int num) { this->numsChange(num); }),
    graph(grid.getSizes().first * grid.getSizes().second)  {
    window.setFramerateLimit(FRAME_LIMIT);
  
    auto [w, h] = grid.getSizes();

    for (ull i = 0; i < h; ++i) {
        for (ull j = 0; j < w; ++j) {
            if (grid.getType(j, i) == GridTypes::Close) 
                continue;
            auto ind = i * w + j;
            
            if (j + 1 < w && grid.getType((ind + 1) % w, (ind + 1) / w) != GridTypes::Close) {
                graph.add_edge(ind, ind + 1, 1);
            }
            if (j > 0 && grid.getType((ind - 1) % w, (ind - 1) / w) != GridTypes::Close) {
                graph.add_edge(ind, ind - 1, 1);
            }
            if (i + 1 < h && grid.getType((ind + w) % w, (ind + w) / w) != GridTypes::Close) {
                graph.add_edge(ind, ind + w, 1);
            }
            if (i > 0 && grid.getType((ind - w) % w, (ind - w) / w) != GridTypes::Close) {
                graph.add_edge(ind, ind - w, 1);
            }

            if (i > 0 && j > 0 && grid.getType(j - 1, i - 1) != GridTypes::Close)
                graph.add_edge(ind, ind - w - 1, 1.41);
            if (i > 0 && j + 1 < w && grid.getType(j + 1, i - 1) != GridTypes::Close)
                graph.add_edge(ind, ind - w + 1, 1.41);
            if (i + 1 < h && j > 0 && grid.getType(j - 1, i + 1) != GridTypes::Close)
                graph.add_edge(ind, ind + w - 1, 1.41);
            if (i + 1 < h && j + 1 < w && grid.getType(j + 1, i + 1) != GridTypes::Close)
                graph.add_edge(ind, ind + w + 1, 1.41);
        }
    }

    render.createGrid();

    Logger::info("Window was created.");
}

Game::~Game() {
    Logger::info("Game was destroyed.");
}

void Game::run() {
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {   
            handler.update(event);
        }

        curTime = clock.getElapsedTime().asSeconds();

        if (algoNum == 1) {
            if (isRunning && algo1.has_value()) {
                for (int step = 0; step < 3; ++step) {
                    auto resp = algo1->step();
                    if (resp == 1) {
                        isRunning = false;
                        isShow = true;
                        finishTime = curTime;
                        break;
                    } else if (resp == -1) {
                        isRunning = false;
                        finishTime = curTime;
                        showError("A*", finishTime - startTime);
                        break;
                    }
                }
            }
        } else if (algoNum == 2) {
            if (isRunning && algo2.has_value()) {
                for (int step = 0; step < 3; ++step) {
                    auto resp = algo2->step();
                    if (resp == 1) {
                        isRunning = false;
                        isShow = true;
                        finishTime = curTime;
                        break;
                    } else if (resp == -1) {
                        isRunning = false;
                        finishTime = curTime;
                        showError("Dijkstra", finishTime - startTime);
                        break;
                    }
                }
            }
        }

        if (algoNum == 1) {
            if (isShow && algo1.has_value()) {
                if (!algo1->show_path()) {
                    isShow = false;
                    showEnd("A* algorithm", finishTime - startTime, algo1->getDist(), algo1->getCount());
               }
            }
        } else if (algoNum == 2) {
            if (isShow && algo2.has_value()) {
                if (!algo2->show_path()) {
                    isShow = false;
                    showEnd("Dijkstra algorithm", finishTime - startTime, algo2->getDist(), algo2->getCount());
                }
            }
        }

        window.clear(sf::Color::White);
        render.drawGrid();
        window.display();
    }
}

void Game::start() {
    if (grid.getStart() == -1U || grid.getFinish() == -1u)
        return ;
    Logger::info("Game start! Algorithm #" + std::to_string(algoNum));
    Logger::info("w: " + std::to_string(grid.getSizes().first) + " h: " + std::to_string(grid.getSizes().second));
    // graph.print();
    if (algoNum == 1) {
        algo1.emplace(&graph, &grid, grid.getStart(), grid.getFinish());
        startTime = curTime;
    }
    else if (algoNum == 2) {
        algo2.emplace(&graph, &grid, grid.getStart(), grid.getFinish());
        startTime = curTime;
    }
    isRunning = true;
}

void Game::numsChange(int num) {
    if (num == 1 || num == 2) {
        if (num == 1) {
            window.setTitle(std::string(WINDOW_NAME) + ": A* algorithm");
        } else {
            window.setTitle(std::string(WINDOW_NAME) + ": Dijkstra algorithm");
        }
        algoNum = num;
    } else algoNum = 1;
}

void Game::showEnd(std::string name, float time, float distance, int count) {
    std::string text = "work time: " + std::to_string(time) + "\ncurrent distance: " + std::to_string(distance) + "\nboxes count: " + std::to_string(count);
    MessageBox(NULL, text.c_str(), name.c_str(), MB_ICONINFORMATION);
}

void Game::showError(std::string name, float time) {
    std::string text = "Error! " + name + " algorithm can not found a path!\nwork time: " + std::to_string(time);
    MessageBox(NULL, text.c_str(), name.c_str(), MB_ICONERROR); 
}