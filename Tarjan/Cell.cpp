#include "Cell.hpp"
#include <iostream>

Cell::Cell(int weight) {
    this->weight = weight;
    this->left = nullptr;
    this->below = nullptr;
    this->right = nullptr;
    this->up = nullptr;
}

Cell::Cell() : Cell(0){
}

Cell::~Cell() {
}