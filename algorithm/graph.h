#include "node.h"
#include "project3.h"
#include "utils.hpp"
#include <unordered_map>
#ifndef GRAPH_H
#define GRAPH_H

class Graph : public AbstractGraph {
public: // all methods must be overriden
	virtual int get_num_nodes(); // number of nodes
	virtual int get_num_edges(); // number of edges
	virtual bool is_neighbor(Node u, Node v);
	virtual std::vector<Node> get_neighbors(Node u);

	// allows lookup of nodes from ids
	virtual std::map<int, Node> get_id_to_node_map();
public:
	Graph();
	Graph(int numOfNodes, vector<int> u, vector<int> v);
	Graph& operator=( const Graph & g);
	//const vector<int>& getStartEdge() const;
	//const vector<int>& get_allNodes() const;
	int size() const;
	int get_node_degree(int n) const;
	

private:
	int Node_size;
	 //vector<int> eFrom;
	 //vector<int> eTo;
	//vector<int> all_nodes;
	int edge_size;
	unordered_map<int, int> degrees; //<vid, degree>
	unordered_map<int, vector<int>> edges;
};

Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v);

#endif