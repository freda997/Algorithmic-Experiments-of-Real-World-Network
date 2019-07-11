#include "graph.h"
#include <algorithm>
Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v) {
	return Graph(num_nodes, u, v);
}


int Graph::get_num_nodes() {
		return Node_size;
	}
int Graph::get_num_edges() {// number of edges
	return edge_size;
}
bool Graph::is_neighbor(Node u, Node v) {
	vector<int> neighbors = edges[u.getNID()];
	return std::find(neighbors.begin(),neighbors.end(), v.getNID())!=neighbors.end();
}
std::vector<Node> Graph::get_neighbors(Node u) {
	vector<Node> results;
	for (int nid : edges[u.getNID()]) results.push_back(Node(nid));
	return results;
}

unordered_map<int, vector<int>> build_edges(const vector<int> &FROM,const vector<int> &TO) {  //adj list that record all edges of node
	unordered_map<int, vector<int>> result;
	for (unsigned int i = 0; i < FROM.size(); i++) {
		result[FROM[i]].push_back(TO[i]);
		result[TO[i]].push_back(FROM[i]);
	}
	return result;
}

// allows lookup of nodes from ids
std::map<int, Node> Graph::get_id_to_node_map() {
	std::map<int,Node> results;
	for ( int i = 1; i <= Node_size; i++) {
		results.insert(pair<int, Node>(i, Node(i)));
	}
	return results;
}

int Graph::get_node_degree(int n) const {
	return degrees.at(n);
}
//const vector<int>& Graph::get_allNodes() const {
//	return all_nodes;
//}
Graph::Graph() 
	: Node_size(0){}

Graph::Graph(int numOfNodes, vector<int> u, vector<int> v)
	: Node_size(numOfNodes), edge_size(u.size())
{
	//all_nodes = extract_keys<int, Node>(get_id_to_node_map());
	//Node_size = all_nodes.size();
	edges = build_edges(u, v);
	for (int i = 0; i < Node_size;i++) {
		//all_nodes.push_back(i + 1);  //nid: 1 ~ n
		int v_degree =get_neighbors(Node(i+1)).size();
		degrees[i+1]=v_degree;
	}
	

}

Graph& Graph::operator=( const Graph & g) {
	Node_size = g.Node_size;
	edge_size = g.edge_size;
	//all_nodes = g.all_nodes;
	degrees=g.degrees;
	edges = g.edges;
	return *this;
}
//const vector<int>& Graph::getStartEdge() const {
//	return eFrom;
//}
int Graph::size() const {
	return Node_size;
}


	
	/*vector<int> getallnodeid() {
		vector<int> results;
		for (int i = 0; i < efrom.size(); i++) {
			results.insert(pair<int, node>(efrom[i], node(efrom[i])));
			results.insert(pair<int, node>(eto[i], node(eto[i])));
		}
		return results;
	}
*/
//private:
//	int Node_size;
//	const vector<int> eFrom;
//	const vector<int> eTo;
//

