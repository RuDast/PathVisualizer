#include "graph.h"
#include "../utils/logger.h"
#include <iostream>
#include <ostream>
#include <vector>

Graph::Graph(unsigned long long size) : adj(size, std::vector<Edge>()) {
    Logger::info("Graph was created.");
    
}

Graph::~Graph() {
    // Destructor
}

void Graph::add_edge(unsigned long long from, unsigned long long to, double weight) {

    adj[from].push_back({to, weight});
}

void Graph::print() {
    for (unsigned long long i = adj.size() - 1; i >= 500; --i) {
        std::cout << i << ": ";
        for (auto item : adj[i]){
            std::cout << item.to << ' ';
        }
        std::cout << std::endl;
    }
}
