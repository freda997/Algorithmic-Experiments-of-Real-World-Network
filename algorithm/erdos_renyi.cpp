#include "graph.h"
#include <random>


Graph create_erdos_renyi_graph(int n, float p) {
	random_device rd;
	mt19937 mt(rd());
	vector<int> FROM;
	vector<int> TO;
	int v = 1;
	int w = -1;
	double r;
	while (v < n) {
		r = rand_num<double>(mt, 0, 1);
		w = w + 1 + (log10(1 - r) / log10(1 - p));
		while (w >= v && v < n) {
			w = w - v;
			v = v + 1;
		}
		if (v < n) {
			FROM.push_back(v+1);
			TO.push_back(w+1);
		}
	}
	//cout << "graph edges: " << endl;
	/*print_vector_content<int>(FROM);
	print_vector_content<int>(TO);*/
	//cout << "node_size: " << n << endl;
	//cout << "number of edges: " << FROM.size() << endl;

	return make_graph(n, FROM, TO);
}