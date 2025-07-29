#ifndef PRIORITYQUEUE
#define PRIORITYQUEUE

#include <map>
#include <list>
#include <tuple>
#include <limits.h>
#include "LeftistHeap.hpp"

class PriorityQueue {
    public:
    std::map<char, LeftistHeap*> queue;

    void QUNION(char C, char D);
    std::tuple<char, char, int> MAX(char C);
    void INIT(char C, std::list<std::tuple<char, char, int>> L);
    void ADD(int a, char C);
    PriorityQueue();
    ~PriorityQueue();
};

#endif