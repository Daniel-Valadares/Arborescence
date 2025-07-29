#include <bits/stdc++.h>
#include <tuple>

using namespace std;

#ifndef LEFTISTNODE
#define LEFTISTNODE

// Node Class Declaration
class LeftistNode
{
public:
	LeftistNode(tuple<char, char, int> & element, LeftistNode *lt = NULL, LeftistNode *rt = NULL, int np = 0);
    tuple<char, char, int> element;
	LeftistNode *left;
	LeftistNode *right;
	int dist;
};

#endif
