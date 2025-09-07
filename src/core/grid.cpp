#include "grid.h"
#include "../config.h"
#include "../utils/logger.h"
#include <string>
#include <utility>
#include <vector>

Grid::Grid(unsigned long long length) : gridVector(window::WINDOW_HEIGHT / length, std::vector<GridTypes>(window::WINDOW_WIDTH / length, GridTypes::Empty)) {
    widthCount = window::WINDOW_WIDTH / length;
    heightCount = window::WINDOW_HEIGHT / length;
    Logger::info("Grid size: " + std::to_string(widthCount) + "x" + std::to_string(heightCount) + '.');
}

Grid::~Grid() {
    Logger::info("Grid was destroyed.");
}

void Grid::setType(unsigned long long w, unsigned long long h, GridTypes type) {
    switch (type) {
        case GridTypes::Start:
        if (startPosition.first != -1u && startPosition.second != -1u) {
            gridVector[startPosition.second][startPosition.first] = GridTypes::Empty;
        }
        startPosition = {w, h};
        break;
        
        case GridTypes::Finish:
        if (finishPosition.first != -1u && finishPosition.second != -1u) {
            gridVector[finishPosition.second][finishPosition.first] = GridTypes::Empty;
        }
        finishPosition = {w, h};
        break;
    }
    gridVector[h][w] = type;
}

std::pair<unsigned long long, unsigned long long> Grid::getSizes() {
    return {widthCount, heightCount};
}

GridTypes Grid::getType(unsigned long long w, unsigned long long h) {
    return gridVector[h][w];
}

unsigned long long Grid::getStart() {
    if (startPosition.first == -1u || startPosition.second == -1u)
        return -1u;
    return startPosition.second * widthCount + startPosition.first;
}

unsigned long long Grid::getFinish() {
    if (finishPosition.first == -1u || finishPosition.second == -1u) 
        return -1u;
    return finishPosition.second * widthCount + finishPosition.first;
}

void Grid::reset() {
    for (auto& box : gridVector) {
        for (auto& item : box) {
            item = GridTypes::Empty;
        }
    }

    startPosition = {-1u, -1u};
    finishPosition = {-1u, -1u};
}