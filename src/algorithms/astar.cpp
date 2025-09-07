#include "astar.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>
#include <vector>
#include "../utils/logger.h"

#define ull unsigned long long

Astar::Astar(Graph* graph, Grid *grid, ull start, ull finish) : graph(graph), 
    grid(grid), startP(start), finishP(finish) {
    auto INF = std::numeric_limits<ull>::max();
    dist.assign(graph->adj.size(), INF);
    dist[start] = 0;
    auto [w, h] = grid->getSizes();
    predecessors.assign(graph->adj.size(), -1);
    curDist = fweight(start % w, start / w, finish % w, finish / w);
    pqueue.push({start, curDist});
    Logger::info("Algorithm start.");
}

Astar::~Astar() {
    // Destructor
}

int Astar::step() {
    if (!pqueue.empty()) {
        auto u = pqueue.top().to;
        pqueue.pop();

        auto [w, h] = grid->getSizes();
        if (u != startP && u != finishP && grid->getType(u % w, u / w) != GridTypes::Close) {
            grid->setType(u % w, u / w, GridTypes::Visited);
        }

        if (u == finishP) {
            for (ull v = finishP; v != startP; v = predecessors[v]) {
                path.push_back(v);
            }
            path.push_back(startP);
            std::reverse(path.begin(), path.end());
            count = path.size();
            return 1;
        }

        for (ull i = 0; i < graph->adj[u].size(); ++i) {
            auto j = graph->adj[u][i].to;
            auto weight = graph->adj[u][i].weight;

            if (weight + dist[u] < dist[j] && grid->getType(j % w, j / w) != GridTypes::Close) {
                dist[j] = weight + dist[u];
                // predecessors[j] = u;
                auto hweight = fweight(j % w, j / w, finishP % w, finishP / w);
                pqueue.emplace(j, dist[j] * 0.5 + 0.5 * hweight);
                predecessors[j] = u;
                if (j != startP && j != finishP) {
                    grid->setType(j % w , j / w , GridTypes::Neighbour);
                }
            }
        }
        return 0;
        
    } else return -1;
}

bool Astar::show_path() {
    if (ind >= path.size()) return false;

    if (++frameCounter < interval) return true; // ждём интервал
    frameCounter = 0;

    auto u = path[ind++];
    auto [w, h] = grid->getSizes();
    if (u != startP && u != finishP) {
        grid->setType(u % w, u / w, GridTypes::Path);
    }
    return ind < path.size();
}

double Astar::fweight(int curX, int curY, int finX, int finY) {
    return sqrt(pow(curX - finX * 1.0, 2) + pow(curY - finY * 1.0, 2));
}

float Astar::getDist() {
    return curDist;
}

int Astar::getCount() {
    return count;
}