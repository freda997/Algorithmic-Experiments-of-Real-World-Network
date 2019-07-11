#ifndef NODE_H
#define NODE_H
#include "project3.h"
class Node {
public: 
	Node(int a): id(a) {}
	Node():id(-1){}
	//~Node();
public:
	bool operator==(const Node &other) const {
		return id == other.id; 
	}
	bool operator==(const int other) const {
	return id == other;
	}
	int getNID() const { return id; }
public:
	int id;
};

//Node::Node(int a) : id(a) {}
//Node::Node() : id(-1) {}
//bool Node::operator==(const Node &other) const { }
//bool Node::operator==(const int other) const {  }
//int Node::getNID() const { return id; }
////Node:: ~Node() = default;

#endif