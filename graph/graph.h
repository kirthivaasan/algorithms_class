/* 

	@author Kirthivaasan Puniamurthy
*/

#ifndef graph_h
#define graph_h

#include <vector>

typedef std::size_t size_t;

namespace kirthi
{

class graph {
private:
	size_t graph_size;
    std::vector<std::vector<size_t> > g;
    bool inBounds(size_t node);
    bool DFS_Helper(size_t u, size_t v, std::vector<size_t>& visited, std::vector<bool>& visited_table);
public:
	graph(size_t t_num_nodes);
	~graph();
	void addEdge(size_t u, size_t v);
	void removeEdge(size_t u, size_t v);
    const std::vector<size_t>& getNeighbours(size_t node);
	void print();
    bool DFS(size_t u, size_t v);
    bool DFS(size_t u, size_t v, std::vector<size_t>& visited);
    size_t size();
};
} // namespace kirthi

#include "graph.cpp" // included inside kirthi namespace

#endif