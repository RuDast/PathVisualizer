#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Edge {
    unsigned long long to;
    double weight;

    Edge(unsigned long long to, double weight) : to(to), weight(weight) {
    
    }

    bool operator<(const Edge &other) const {
        return weight > other.weight;
    }
};

struct EdgeComp {
    bool operator()(const Edge &a, const Edge &b) const {
        return a.weight > b.weight;
    }
};

class Graph {
public:
    Graph(unsigned long long size);
    ~Graph();

    void add_edge(unsigned long long from, unsigned long long to, double weight);
    void print();

private:
    std::vector<std::vector<Edge>> adj; 

    friend class Dijkstra;
    friend class Astar;
};


#endif // GRAPH_H
