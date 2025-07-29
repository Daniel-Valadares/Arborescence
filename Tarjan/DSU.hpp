#include <map>

#ifndef DISJOINTSETUNION
#define DISJOINTSETUNION

class DSU {
    private:
    std::map<char, char> parent;
    std::map<char, int> rank;

    public:
    void make_set(char v);
    char find_set(char v);
    void union_sets(char v, char u);
    void swap(char v, char u);
    DSU();
    ~DSU();
    
};

#endif