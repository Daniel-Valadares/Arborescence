#include "LeftistNode.hpp"
#include <bits/stdc++.h>

LeftistNode::LeftistNode(tuple<char, char, int> & element, LeftistNode *lt, LeftistNode *rt, int np)
{
	this->element = element;
	right = rt;
	left = lt,
	dist = np;
}