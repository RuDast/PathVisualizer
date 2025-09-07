#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../core/graph.h"
#include "../core/grid.h"
#include <queue>
#include <vector>

class Dijkstra {
public:
    Dijkstra(Graph* graph, Grid *grid, unsigned long long start, unsigned long long finish);
    ~Dijkstra();

    void run(unsigned long long source, unsigned long long finish);
    int step();
    bool show_path();
    void showSF();
    float getDist();
    int getCount();
    double fweight(int curX, int curY, int finX, int finY);

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
};

#endif // DIJKSTRA_H
