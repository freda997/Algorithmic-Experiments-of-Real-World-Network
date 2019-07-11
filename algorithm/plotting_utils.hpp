#include <algorithm>
#include <iterator>
#include <chrono> 
#include <fstream>
#include <ctime>
#include <string>
#include <cmath>
#include <iostream>
#include <random>
using namespace std;

struct timing {
	int n; //number of nodes
	float cc; //cluster coefficeint
	float d; //diameter
};

struct degree {
	int d;  //degree
	int nc; //number of node w/ that degree
};

void add_degree_to_file(degree t, string filename)
{
	ofstream f;
	f.open(filename, ios::app);
	f << t.d << "," << t.nc  << "\n";
	f.close();
}

void add_timings_to_file( timing t, string filename)
{
	ofstream f;
	f.open(filename, ios::app);
	f  << t.n << "," << t.cc <<  "," << t.d  << "\n";
	f.close();
}

void create_empty_timings_file(string filename)
{
	ofstream f;
	f.open(filename, ios::trunc);
	f << "n,cc,diameter\n";
	f.close();
}

void create_empty_degree_file(string filename)
{
	ofstream f;
	f.open(filename, ios::trunc);
	f << "d,nc\n";
	f.close();
}
