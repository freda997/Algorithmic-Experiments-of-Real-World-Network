#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include <random>
#include <chrono>
using namespace std;
#ifndef UTILS_HPP
#define UTILS_HPP
///*Return the index of first occurence of target */
//template <typename T>
//int getIndex(const vector<T>&s, T target)
//
//{
//	for (int i = 0; i != s.size(); i++)
//	{
//		if (s[i] == target)
//		{
//			return i;
//		}
//	}
//
//	return -1;
//}

/*Retrieve the indices of all occurences of target in the given vector.*/
/*emplate <typename T>
std::vector<int> getIndices(const vector<T>&s, T target) 

{
	std::vector<int> results;

	for (int i = 0; i != s.size(); i++)
	{
		if (s[i] == target)
		{
			results.push_back(i);
		}
	}

	return results;
}*/
/*Find all possible pairs from vector*/


template <typename TR>
TR rand_num(mt19937& mt,int lb,int ub)
{
	uniform_real_distribution<TR> distribution(lb,ub);
	return distribution(mt);
}

template <typename tp>
void print_vector_content(const vector<tp>& v) {
	cout << "[ ";
	for (auto i : v) {
		cout << i << " ";
	}
	cout << "]" << endl;
}

template <typename ts>
void print_set_content(const unordered_set<ts>& v) {
	cout << "[ ";
	for (auto i : v) {
		cout << i << " ";
	}
	cout << "]" << endl;
}



template<typename TK, typename TV>
std::vector<TK> extract_keys(map<TK, TV> const& input_map) {
	std::vector<TK> retval;
	for (auto const& element : input_map) {
		retval.push_back(element.first);
	}
	return retval;
}

template <typename t>
/*return a random element from vector*/
t random_element(mt19937& mt,vector<t> v )
{
	int lb = 0;
	int ub = v.size() - 1;
	if (lb == ub) return v[0];
	uniform_int_distribution<int> distribution(lb, ub);
	int rand_ind=distribution(mt);
	return v[rand_ind];
}
#endif