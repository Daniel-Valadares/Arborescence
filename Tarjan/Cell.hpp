#ifndef CELL
#define CELL

class Cell {
    public:
    Cell *left, *up, *right, *below;
    int weight;
    Cell();
    Cell(int weight);
    ~Cell();
};

#endif