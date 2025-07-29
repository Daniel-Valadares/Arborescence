#include "DSU.hpp"

DSU::DSU(){}
DSU::~DSU(){}

void DSU::make_set(char v) {
    this->parent[v] = v;
    this->rank[v] = 0;
}

char DSU::find_set(char v) {
    if (v == this->parent[v])
        return v;
    return this->parent[v] = find_set(this->parent[v]);
}

void DSU::union_sets(char v, char u) {
    v = find_set(v);
    u = find_set(u);

    if (v != u) {
        if (rank[u] < rank[v]) {
            char tmp = v;
            v = u;
            u = tmp;
        }
        parent[v] = u;
        if (rank[v] == rank[u]) rank[v]++;
    }
}
