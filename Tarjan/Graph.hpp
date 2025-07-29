#include <iostream>
#include <bits/stdc++.h>
#include <list>
#include <limits.h>
#include <map>
#include <stack>
#include <tuple>
#include "Cell.hpp"
#include "PriorityQueue.hpp"
#include "DSU.hpp"

#ifndef GRAPH
#define GRAPH

class Graph {
    private:
    std::list<char> labels;
    bool directed;
    Cell *first_cell;

    std::map<char, char> vertex_color;
    std::stack<char> predecessors;

    std::map<std::tuple<char, char>, bool> has_edge;
    
    void clean_mem();

    public:
    Graph();
    Graph(bool directed);
    ~Graph();
    void add_vertex(char label);
    void add_edge(char origin_label, char destination_label, int weight);
    void remove_vertex(char label);
    void remove_edge(char origin_label, char destination_label);
    void print_matrix();
    std::list<std::tuple<char, char, int>> get_incidence_list(char label);
    void MGA();
    std::list<char> find_roots();
};


#endif