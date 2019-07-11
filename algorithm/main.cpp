#include "graph.h"
#include "tests.h"
#include "plotting_utils.hpp"
static int AVERAGEOF = 6;  //how many graphs of n to take average over
static int MIN = 10;
static int MAX = 1500000;
void network_analysis(int node_num) {
	float total_cc = 0.0;
	float total_diameter = 0.0;
	float p = 2 * (log(node_num) / node_num);
	for (int i = 0; i < AVERAGEOF; i++) {	// sampling serveral random graph and take the average
		Graph g = create_erdos_renyi_graph(node_num, p);
		float diameter = (float)get_diameter(g);
		total_diameter += diameter;
		float cc = get_clustering_coefficient(g);
		total_cc += cc;
	}
	timing result;
	result.d = total_diameter / (float)AVERAGEOF;
	result.cc = total_cc / (float)AVERAGEOF;
	result.n = node_num;
	add_timings_to_file(result, "network.csv");
}

int main() {
	//generate all variables for given n. n range from MIN to MAX
	cout << "starting" << endl;
	create_empty_timings_file("network.csv");
	for (int n = MIN; n <= MAX; n *= 2) {
		network_analysis(n);
	}
	
	//generate degree distribution for require three n. 
	for (int n : vector<int>{ 1000,10000,100000 }) { //plotting for these three number 
		float p = 2 * (log(n) / n);
		Graph g = create_erdos_renyi_graph(n, p);
		create_empty_degree_file("degDis"+to_string(n)+".csv");  //create degree distribution csv
		auto dd = get_degree_distribution(g);
		degree result;
		for (auto p : dd) {
			result.d = p.first;
			result.nc = p.second;
			add_degree_to_file(result, "degDis" + to_string(n) + ".csv");
		}

	}


	//int numNode=5;
	//vector<int> from{ 0,0,0,0,1,3,2,0,4,1,5};
	//vector<int> to{   1,2,3,4,3,4,5,5,5,2,3};

	//vector<int> from{ 1,2,1,3,3,4};
	//vector<int> to{2,3,3,4,5,5};
	////Graph g = make_graph(numNode, from, to);
	//int node_num = 100;
	//float p = 2 * (log(node_num) / node_num);
	//cout << "p set to " << p << endl;
	//Graph g = create_erdos_renyi_graph(node_num,p);
	//int diameter = get_diameter(g);
	//cout << "diameters: " <<diameter << endl;
	//float cc = get_clustering_coefficient(g);
	//cout << "cluster coefficient = " << cc<<endl;
	//run_tests();
	//auto dd = get_degree_distribution(g);
	return 0;
}