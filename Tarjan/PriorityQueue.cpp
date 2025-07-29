#include "PriorityQueue.hpp"

PriorityQueue::PriorityQueue(){}
PriorityQueue::~PriorityQueue(){}

void PriorityQueue::QUNION(char C, char D) {
    this->queue[C]->Merge(this->queue[D]);
}

std::tuple<char, char, int> PriorityQueue::MAX(char C) {
    LeftistHeap* c_queue = this->queue[C];
    std::tuple<char, char, int> resp('*', '*', INT_MIN);

    if (c_queue->isEmpty()) {
        return resp;
    }
    
    c_queue->deleteMax(resp);

    return resp; 
}

void PriorityQueue::INIT(char C, std::list<std::tuple<char, char, int>> L) {
    this->queue[C] = new LeftistHeap();
    for (auto element = L.begin(); element != L.end(); element++) {
        this->queue[C]->Insert(*element);
    }
}

void PriorityQueue::ADD(int a, char C) {
    this->queue[C]->addConstant(a);
}

