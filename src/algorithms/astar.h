#ifndef ASTAR_H
#define ASTAR_H

#include "../core/graph.h"
#include "../core/grid.h"
#include <queue>
#include <vector>

class Astar {
public:
    Astar(Graph* graph, Grid *grid, unsigned long long start, unsigned long long finish);
    ~Astar();

    int step();
    bool show_path();
    float getDist();
    int getCount();
    
private:
    Graph *graph;
    Grid *grid;
    std::priority_queue<Edge, std::vector<Edge>, EdgeComp> pqueue;
    std::vector<unsigned long long> dist;
    std::vector<long long> predecessors;
    unsigned long long startP, finishP;
    std::vector<unsigned long long> path;
    unsigned long long ind = 0;

    int frameCounter = 0;
    int interval = 0;

    float curDist = 0.f;
    int count = 0;

    double fweight(int curX, int curY, int finX, int finY);
};

#endif // ASTAR_H
