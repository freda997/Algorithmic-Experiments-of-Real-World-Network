#include "graph.h"
#include <random>
#include <unordered_set>
#include <unordered_map>
#include <queue>

/*return the id and distance of furthest vertex through bfs*/
pair<int, int> BFS_helper(Graph& g, const Node start) {
	unordered_set<int> visited;
	queue <int> q, d;
	pair<int, int> result;
	visited.insert(start.getNID());
	q.push(start.getNID());
	d.push(0);  //set start index's depth level to 0;
	vector<Node> neighbors;
	bool end = false;
	int current;
	int depth;
	while (!q.empty()) {
		if (end && q.size() == 1) {
			result = make_pair(q.front(), d.front());
		}
		end = true;
		current = q.front();
		depth = d.front();
		q.pop();
		d.pop();
		for (auto n : g.get_neighbors(Node(current))) {
			if (visited.find(n.getNID()) == visited.end()) {
				visited.insert(n.getNID());
				q.push(n.getNID());
				d.push(depth + 1); //assign incremented depth level to next node
			}
		}
	}
	return result;
}

pair<vector<int>, unordered_map<int, vector<int>>> degen_order_helper( Graph&g) {
	pair<vector<int>, unordered_map<int, vector<int>>> result; //<L,N>
	//vector<int> all_nodes(extract_keys<int, Node>(g.get_id_to_node_map()));
	vector<int> L;
	unordered_set<int> in_L;
	unordered_map<int, vector<int>> N; //<node id , nodes that come after current node in ordering>
	//map<int, vector<int>> D; // <degree (sorted),all vertices w/ the degree>
	map<int, unordered_set<int>> D; // <degree (sorted),all vertices w/ the degree in hashset>
	int dv;
	unordered_map<int, int> neighbor_size; //<nid, number of neighbor preceding degen ordering>
	for (int v = 1; v <= g.size();v++) {
		dv = g.get_node_degree(v); //dv initialize the degree of current v
		neighbor_size.insert(pair<int, int> (v, dv));
		//vector<int> new_degree_vecs;
		pair<map<int, unordered_set<int>>::iterator, bool> it = D.insert(pair<int, unordered_set<int>>(dv, unordered_set<int>())); //get D[dv]
		(it.first->second).insert(v); //add v to D[dv]
		N.insert(pair<int, vector<int>>(v, vector<int>()));
	}
	for ( int q = 0; q < g.size(); q++) { //repeat n times
		int i;
		//cout << "D content: ";
		//for (auto const& p : D) { ////print the map
		//	//cout << "degree: " << p.first << ": ";
		//	//print_set_content<int>(p.second);
		//}
		//cout << endl;

		for (auto const& p : D) { //find smallest degree i such that D[i] is not empty
			
			if (!p.second.empty()) {
				i = p.first;
				
				break;
			}
		}
		int v = *D[i].begin(); //always select first elment of D[i]
		//cout << "node " << v << "; degree: " << i;
		L.insert(L.begin(), v);  //insert v to the beginning of L
		D[i].erase(v); //delete v from D[i]
		in_L.insert(v); //mark v as being in L;
		//cout << "; neighbors: ";
		for (auto w : g.get_neighbors(Node(v))) { //loop through each neighbor of v 
			int wid = w.getNID();		
			if (in_L.find(wid) == in_L.end()){ //if w not in L -->degree(w) >= degree(v)
				//cout << wid << " ";
				int dw = neighbor_size[wid]; 
				int new_dw = dw-1; //degree of w subtracted by 1
				neighbor_size[wid] =new_dw;  //subtract one from neighbor count
				D[dw].erase(wid); 
				D[new_dw].insert(wid); //move w to new degree index in D
				auto it = N.insert(pair<int, vector<int>>(v, vector<int>())); //get Nv
				it.first->second.push_back(wid);//add w to Nv
			}
		}
		//cout << endl;
	}
	result.first = L;
	result.second = N;
	return result;

}
vector<pair<int, int>> get_all_pairs(const vector<int>& v) {
	vector<pair<int, int>> result;
	for (unsigned int i = 0; i < v.size(); i++) {
		int first = v[i];
		for (unsigned int t = i + 1; t < v.size(); t++) {
			if (first != v[t]) {
				result.push_back(pair<int, int>(first, v[t]));
				////cout <<  first << " , " << v[t] << endl;
			}
		}
	}
	return result;
}

int triangle_counting_helper( Graph& g) {
	auto r = degen_order_helper(g); //get degen ordring of the graph.
	int tri_count = 0;
	//cout << "ordring: ";
	//print_vector_content<int>(r.first);
	vector<int> L(r.first);
	unordered_map<int, vector<int>> N(r.second);
	for (int v : L) {
		vector<int> Nv = N[v];
		//cout << "N"<<v<<": ";
		//print_vector_content<int>(Nv);
		vector<pair<int, int>> all_pairs = get_all_pairs(Nv);
		for (auto p : all_pairs) { //p: <u,v> who are earlier in the ordering
			if (g.is_neighbor(Node(p.first), Node(p.second))) {
				tri_count++;
				//cout << "Triangle formed by: " << v << " " << p.first << " " << p.second<<endl;
			}
		}
	}
	return tri_count;

}

int twoEdgePaths_count_helper( Graph& g) {
	//vector<int> all_nodes(extract_keys<int, Node>(g.get_id_to_node_map()));
	int total = 0;
	for (int v = 1; v <= g.size(); v++) {
		int v_degree = g.get_node_degree(v);
		total += (v_degree*(v_degree-1) / 2);
	}
	return total;
}

int get_diameter(Graph&graph) {
	random_device rd;
	mt19937 mt(rd());
	int last_dmax = 0;
	int current_dmax;
	//int ini_vertex = random_element<int>(mt, graph.getStartEdge());
	uniform_int_distribution<int> dis (1,graph.get_num_nodes());
	int ini_vertex = dis(mt);
	//int ini_vertex = rand_num<int>(mt, 1, graph.get_num_nodes());  //get random vertex from graph
	pair<int, int> result = BFS_helper(graph, Node(ini_vertex));
	int furthest_vertex = result.first;
	current_dmax = result.second;
	while (current_dmax > last_dmax) {	
		ini_vertex = furthest_vertex;
		last_dmax = current_dmax;
		result = BFS_helper(graph, Node(ini_vertex));
		furthest_vertex = result.first;
		current_dmax = result.second;
		
	}
	return last_dmax;
	
}



float get_clustering_coefficient(Graph &graph) {
	int tri_count = triangle_counting_helper(graph);
	//cout << "triangle count: " << tri_count << endl;
	if (tri_count == 0) return (double)0.0;
	int denom = twoEdgePaths_count_helper(graph);
	float result = (float)3.0 * (float)tri_count /(float)denom;
	//cout << "Cluster Coefficient: " << result << endl;

	return result;
}
std::map<int, int> get_degree_distribution(Graph &graph) {  //return <degree, number of nodes w/ that degree>
	map<int, int> result;
	int total=0;
	for (int i = 0; i < graph.size(); i++) {  //maximum degree of a node is size-1
		result[i] = 0; //initialize H[i] to 
	}
	for (int v = 1; v <= graph.get_num_nodes(); v++) {
		int vDegree = graph.get_node_degree(v);
		result[vDegree]++;
		total += vDegree;
	}
	double avg = total / graph.get_num_nodes(); //print average degree of the graph
	//cout << "average degree is " << avg<<endl;
	return result;
}	