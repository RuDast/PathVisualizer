#include "dijkstra.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>
#include <string>
#include <vector>
#include "../utils/logger.h"

#define ull unsigned long long

Dijkstra::Dijkstra(Graph* graph, Grid *grid, ull start, ull finish) : graph(graph), 
    grid(grid), startP(start), finishP(finish) {
    auto INF = std::numeric_limits<ull>::max();
    dist.assign(graph->adj.size(), INF);
    dist[start] = 0;
    predecessors.assign(graph->adj.size(), -1);
    auto [w, h] = grid->getSizes();
    pqueue.push({start, 0});
    curDist = fweight(start % w, start / w, finish % w, finish / w);
    Logger::info("Algorithm start.");
}

Dijkstra::~Dijkstra() {
    // Destructor
}

void Dijkstra::run(ull source, ull finish) {
    if (source >= graph->adj.size() || finish >= graph->adj.size()) {
        Logger::error("Dijkstra: invalid source/finish.");
        return;
    }

    if (source == finish) {
        Logger::info("Dijkstra: source and finish are the same.");
        return;
    }
    Logger::info("Start: " + std::to_string(source) + " finish: " + std::to_string(finish) + '.');
    auto INF = std::numeric_limits<ull>::max();
    std::vector<bool> visited(graph->adj.size(), false);
    std::priority_queue<Edge, std::vector<Edge>, EdgeComp> queue;
    std::vector<long long> predecessors(graph->adj.size(), -1);
    std::vector<ull> path;
    std::vector<ull> distances(graph->adj.size(), INF);

    queue.push({source, 0});
    distances[source] = 0;

    while (!queue.empty()) {
        auto u = queue.top().to;
        queue.pop();

        if (!visited[u]) {
            visited[u] = true;

            for (ull i = 0; i < graph->adj[u].size(); ++i) {
                auto j = graph->adj[u][i].to;
                auto weight = graph->adj[u][i].weight;

                if (!visited[j] && weight + distances[u] < distances[j]) {
                    distances[j] = weight + distances[u];
                    predecessors[j] = u;
                    queue.emplace(j, distances[j]);
                }
            }
        }
    }

    for (long long cur = finish; cur != -1; cur = predecessors[cur]) {

        path.push_back(cur);
    }

    std::reverse(path.begin(), path.end());
    auto [w, h] = grid->getSizes();
    for (long long item : path) {
        if (item == source)
            continue;

        if (item == finish)
            continue;
        grid->setType(item % w , item / w , GridTypes::Path);
    }

}

int Dijkstra::step() {
    if (!pqueue.empty()) {
        auto u = pqueue.top().to;
        pqueue.pop();

        auto [w, h] = grid->getSizes();
        if (u != startP && u != finishP && grid->getType(u % w, u / w) != GridTypes::Close) {
            grid->setType(u % w , u / w , GridTypes::Visited);
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
                pqueue.emplace(j, dist[j]);
                predecessors[j] = u;
                if (j != startP && j != finishP) {
                    grid->setType(j % w , j / w , GridTypes::Neighbour);
                }
            }
        }
        return 0;
        
    } else return -1;
}

bool Dijkstra::show_path() {
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

float Dijkstra::getDist() {
    return curDist;
}

int Dijkstra::getCount() {
    return count;
}

double Dijkstra::fweight(int curX, int curY, int finX, int finY) {
    return sqrt(pow(curX - finX * 1.0, 2) + pow(curY - finY * 1.0, 2));
}