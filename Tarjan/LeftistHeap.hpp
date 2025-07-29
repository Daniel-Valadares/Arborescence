//C++ program for leftist heap / leftist tree
// Source: https://www.geeksforgeeks.org/leftist-tree-leftist-heap/

#include <tuple>
#include <bits/stdc++.h>
#include "LeftistNode.hpp"

using namespace std;

#ifndef LEFTISTHEAP
#define LEFTISTHEAP

//Class Declaration
class LeftistHeap
{
public:
	LeftistHeap();
	LeftistHeap(LeftistHeap &rhs);
	~LeftistHeap();
	bool isEmpty();
	bool isFull();
	tuple<char, char, int> &findMax();
	void Insert(tuple<char, char, int> &element);
	void deleteMax();
	void deleteMax(tuple<char, char, int> &maxItem);
	void makeEmpty();
	void Merge(LeftistHeap *rhs);
	void addConstant(int a);
	LeftistHeap & operator =(LeftistHeap &rhs);

private:
	LeftistNode *root;
	LeftistNode *Merge(LeftistNode *h1,
					LeftistNode *h2);
	LeftistNode *Merge1(LeftistNode *h1,
						LeftistNode *h2);
	void swapChildren(LeftistNode * t);
	void reclaimMemory(LeftistNode * t);
	LeftistNode *clone(LeftistNode *t);
	void addConstant(int a, LeftistNode *h1);
};


#endif