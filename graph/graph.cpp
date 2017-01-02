#include "graph.h"
#include <iostream>

namespace kirthi
{

graph::graph(size_t t_num_nodes) : graph_size(0) {
    g.resize(t_num_nodes);
}

graph::~graph() {
    
}

bool graph::inBounds(size_t node) {
    return node >= 0 && node < g.size(); // node < num_nodes
}

void graph::addEdge(size_t u, size_t v) {
    if (inBounds(u) && inBounds(v)) {
        std::vector<size_t>& neighbours = g[u];
        for (auto neighbour : neighbours) {
            if (neighbour == v) return; // neighbour already exists, no need to add.
        }
        neighbours.push_back(v);
        graph_size++;
    }
}

void graph::removeEdge(size_t u, size_t v) {
    if (inBounds(u) && inBounds(v)) {
        std::vector<size_t>& neighbours = g[u];
        for (auto it = neighbours.begin(); it != neighbours.end(); ++it) {
            if (*it == v) {
                neighbours.erase(it);
                graph_size--;
                return;
            }
        }
    }
}

const std::vector<size_t>& graph::getNeighbours(size_t node) {
    if (inBounds(node)) {
        return g[node];
    }
}

void graph::print() {
    for (size_t i = 0; i < g.size(); i++) {
        std::vector<size_t> neighbours = getNeighbours(i);
        if (neighbours.size() > 0) {
            std::cout << "Node " << i << " -> ";
            for (auto elem : neighbours) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }
}

size_t graph::size() {
    // graph_size counts number of elements in total (in the 2 dimensional vector)
    // it does not give the number of vertices / edges
    // the number of nodes is just g.size()
    return graph_size;
}

bool graph::DFS_Helper(size_t u, size_t v, std::vector<size_t>& visited, std::vector<bool>& visited_table) {
    //std::cout << "called dfs helper " << u << " " << v << std::endl;
    if (u == v) {
        visited.push_back(u);
        visited_table[u] = true;
        return true;
    } else {
        std::vector<size_t> neighbours = getNeighbours(u);
        visited.push_back(u);
        visited_table[u] = true;
        for (auto neighbour : neighbours) {
            if (!visited_table[neighbour]) {
                if(DFS_Helper(neighbour, v, visited, visited_table)) return true;
            }
        }
        return false;
    }
}

bool graph::DFS(size_t u, size_t v) {
    if (inBounds(u) && inBounds(v)) {
        std::vector<size_t> visited;
        std::vector<bool> visited_table(g.size(), false);
        return DFS_Helper(u, v, visited, visited_table);
    }
    return false;
}

bool graph::DFS(size_t u, size_t v, std::vector<size_t>& visited) {
    if (inBounds(u) && inBounds(v)) {
        std::vector<bool> visited_table(g.size(), false);
        return DFS_Helper(u, v, visited, visited_table);
    }
    return false;
}

}