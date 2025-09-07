#ifndef GRID_H
#define GRID_H

#include <utility>
#include <vector>
enum class GridTypes {
    Empty, 
    Start, 
    Finish, 
    Visited, 
    Path,
    Neighbour, 
    Close
};

class Grid {
public:
    Grid(unsigned long long length);
    ~Grid();

    void setType(unsigned long long w, unsigned long long h, GridTypes type);
    std::pair<unsigned long long, unsigned long long> getSizes();
    GridTypes getType(unsigned long long w, unsigned long long h);
    unsigned long long getStart();
    unsigned long long getFinish();
    void reset();

private:
    unsigned long long widthCount;
    unsigned long long heightCount;
    std::pair<unsigned long long, unsigned long long> startPosition = {-1u, -1u};
    std::pair<unsigned long long, unsigned long long> finishPosition = {-1u, -1u};
    std::vector<std::vector<GridTypes>> gridVector;
};

#endif // GRID_H
