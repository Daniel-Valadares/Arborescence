#include "Graph.hpp"

Graph::Graph(bool directed) {
    this->directed = directed;
    this->first_cell = nullptr;
}

Graph::Graph() : Graph(false){}

Graph::~Graph() {
    clean_mem();
}

void Graph::clean_mem() {
    for (auto label_i = labels.begin(); label_i != labels.end();) {
        auto next_label = label_i;
        next_label++;
        this->remove_vertex(*label_i);
        label_i = next_label;
    }
}

void Graph::add_vertex(char label) {
    labels.push_back(label);
    
    if (this->first_cell == nullptr) {
        this->first_cell = new Cell();
    }
    else {
        Cell *aux_ptr=this->first_cell;
        
        /* Adding the new line */
        while (aux_ptr->below != nullptr) {
            aux_ptr = aux_ptr->below;
        }
        
        aux_ptr->below = new Cell();
        aux_ptr->below->up = aux_ptr;

        aux_ptr = aux_ptr->right;
        while (aux_ptr != nullptr) {
            aux_ptr->below = new Cell();
            aux_ptr->below->up = aux_ptr;
            aux_ptr->below->left = aux_ptr->left->below;
            aux_ptr->left->below->right = aux_ptr->below;

            aux_ptr = aux_ptr->right;
        }

        aux_ptr = this->first_cell;
        
        /* Adding the new column */
        while (aux_ptr->right != nullptr) {
            aux_ptr = aux_ptr->right;
        }
        
        aux_ptr->right = new Cell();
        aux_ptr->right->left = aux_ptr;

        aux_ptr = aux_ptr->below;
        while (aux_ptr != nullptr) {
            aux_ptr->right = new Cell();
            aux_ptr->right->left = aux_ptr;
            aux_ptr->right->up = aux_ptr->up->right;
            aux_ptr->up->right->below = aux_ptr->right;

            aux_ptr = aux_ptr->below;
        }
    }    
}

void Graph::add_edge(char origin_label, char destination_label, int weight) {
    std::tuple<char, char> edge(origin_label, destination_label);
    this->has_edge[edge] = true;
    
    int line_i = -1, column_i = -1;
    int i = 0;
    for (auto label_i = labels.begin(); label_i != labels.end(); label_i++) {
        if (*label_i == origin_label) {
            line_i = i;
        }
        if (*label_i == destination_label) {
            column_i = i;
        }
        i++;
    }

    if (line_i != -1 && column_i != -1) {
        Cell *aux_ptr = this->first_cell;
        
        i = 0;
        while (i < line_i) {
            aux_ptr = aux_ptr->below;
            i++;
        }

        i = 0;
        while (i < column_i) {
            aux_ptr = aux_ptr->right;
            i++;
        }

        aux_ptr->weight = weight;

        if (!this->directed) {
            aux_ptr = this->first_cell;
        
            i = 0;
            while (i < column_i) {
                aux_ptr = aux_ptr->below;
                i++;
            }

            i = 0;
            while (i < line_i) {
                aux_ptr = aux_ptr->right;
                i++;
            }

            aux_ptr->weight = weight;
        }
    }
}

void Graph::remove_vertex(char label) {
    long unsigned int removed_label_i = -1;
    long unsigned int i = 0;
    auto label_pos_i = labels.begin();
    for (;label_pos_i != labels.end(); label_pos_i++) {
        if (*label_pos_i == label) {
            removed_label_i = i;
            break;
        }
        i++;
    }

    if (this->labels.size()==1 && removed_label_i==0) { 
        delete this->first_cell; 
        this->first_cell = nullptr;

        std::tuple<char, char> edge(label, label);
        has_edge[edge] = false;
    }
    else if (removed_label_i >= 0){
        Cell *aux_ptr = this->first_cell;
        
        if (removed_label_i == 0) {
            this->first_cell = this->first_cell->below->right;
            
            /* Removing the line*/
            aux_ptr = aux_ptr->below;
            while (aux_ptr != nullptr) {
                if (aux_ptr->right != nullptr) {
                    aux_ptr->right->up->left = nullptr;
                }
                delete aux_ptr->up;
                aux_ptr->up = nullptr;
                aux_ptr = aux_ptr->right;
            }

            /* Removing the column */
            aux_ptr = this->first_cell;
            while (aux_ptr != nullptr) {
                if (aux_ptr->below != nullptr) {
                    aux_ptr->below->left->up = nullptr;
                }
                delete aux_ptr->left;
                aux_ptr->left = nullptr;
                aux_ptr = aux_ptr->below;
            }
        }
        else if (removed_label_i == labels.size()-1) {
            /* Removing the line */
            while (aux_ptr->below->below != nullptr) {
                aux_ptr = aux_ptr->below;
            }

            while (aux_ptr != nullptr) {
                if (aux_ptr->right != nullptr) {
                    aux_ptr->right->below->left = nullptr;
                }
                delete aux_ptr->below;
                aux_ptr->below = nullptr;
                aux_ptr = aux_ptr->right;
            }

            /* Removing the column */
            aux_ptr = this->first_cell;
            while (aux_ptr->right->right != nullptr) {
                aux_ptr = aux_ptr->right;
            }

            while (aux_ptr != nullptr) {
                if (aux_ptr->below != nullptr) {
                    aux_ptr->below->right->up = nullptr;
                }
                delete aux_ptr->right;
                aux_ptr->right = nullptr;
                aux_ptr = aux_ptr->below;
            }
        }
        else {
            /* Removing the line */
            i = 1;
            while (i < removed_label_i) {
                aux_ptr = aux_ptr->below;
                i++;
            }

            Cell *delete_ptr = aux_ptr; 
            while (aux_ptr != nullptr) {
                delete_ptr = aux_ptr->below;
                aux_ptr->below->below->up = aux_ptr;
                aux_ptr->below = aux_ptr->below->below;
                if (aux_ptr->right != nullptr) {
                    aux_ptr->right->below->left = nullptr;
                }
                delete delete_ptr;
                aux_ptr = aux_ptr->right;
            }

            /* Removing the column */
            aux_ptr = this->first_cell;
            i = 1;
            while (i < removed_label_i) {
                aux_ptr = aux_ptr->right;
                i++;
            }

            delete_ptr = aux_ptr; 
            while (aux_ptr != nullptr) {
                delete_ptr = aux_ptr->right;
                aux_ptr->right->right->left = aux_ptr;
                aux_ptr->right = aux_ptr->right->right;
                if (aux_ptr->below != nullptr) {
                    aux_ptr->below->right->up = nullptr;
                }
                delete delete_ptr;
                aux_ptr = aux_ptr->below;
            }
        }

        for (auto label_i = labels.begin(); label_i != labels.end(); label_i++) {
            std::tuple<char, char> edge(*label_i, label);
            has_edge[edge] = false;

            std::get<0>(edge) = label;
            std::get<1>(edge) = *label_i;
            
            has_edge[edge] = false;
        }
    }

    labels.erase(label_pos_i);
}

void Graph::remove_edge(char origin_label, char destination_label) {
    int line_i = -1, column_i = -1;
    int i = 0;
    for (auto label_i = labels.begin(); label_i != labels.end(); label_i++) {
        if (*label_i == origin_label) {
            line_i = i;
        }
        if (*label_i == destination_label) {
            column_i = i;
        }
        i++;
    }

    if (line_i != -1 && column_i != -1) {
        std::tuple<char, char> edge(origin_label, destination_label);
        this->has_edge[edge] = false;
        
        Cell *aux_ptr = this->first_cell;
        
        i = 0;
        while (i < line_i) {
            aux_ptr = aux_ptr->below;
            i++;
        }

        i = 0;
        while (i < column_i) {
            aux_ptr = aux_ptr->right;
            i++;
        }

        aux_ptr->weight = 0;

        if (!this->directed) {
            aux_ptr = this->first_cell;
        
            i = 0;
            while (i < column_i) {
                aux_ptr = aux_ptr->below;
                i++;
            }

            i = 0;
            while (i < line_i) {
                aux_ptr = aux_ptr->right;
                i++;
            }

            aux_ptr->weight = 0;
        }
    }
}

void Graph::print_matrix() {
    std::cout << "  ";
    for (auto i = labels.begin(); i != labels.end(); i++) {
        std::cout<< *i << " ";
    }
    std::cout << std::endl;

    Cell *line_ptr = this->first_cell, *column_ptr;
    auto label_i = labels.begin();
    while (line_ptr != nullptr) {
        column_ptr = line_ptr;
        
        std::cout << *label_i << " ";
        while (column_ptr != nullptr) {
            std::cout << column_ptr->weight << " ";
            column_ptr = column_ptr->right;
        }
        std::cout << std::endl;
        
        std::advance(label_i, 1);
        line_ptr = line_ptr->below;
    }
}

void Graph::MGA() {
    std::list<char> roots = find_roots();

    for (auto root_i = roots.begin(); root_i != roots.end(); root_i++) { 
        for (auto label_i = labels.begin(); label_i != labels.end(); label_i++) {
            std::tuple<char, char> edge(*label_i, *root_i);
            if (has_edge[edge]) {
                remove_edge(std::get<0>(edge), std::get<1>(edge));
            }
        }
    }
}

std::list<char> Graph::find_roots() {
    std::list<char> roots;
    PriorityQueue *pq = new PriorityQueue();
    DSU *SSet = new DSU();
    DSU *WSet = new DSU();
    std::map<char, std::tuple<char, char, int>> enter;
    std::map<char, char> min;
    
    for (auto label_i = labels.begin(); label_i != labels.end(); label_i++) {
        pq->INIT(*label_i, get_incidence_list(*label_i));
        SSet->make_set(*label_i);
        WSet->make_set(*label_i);
        std::tuple<char, char, int> edge('*', '*', INT_MIN);
        enter[*label_i] = edge;
        roots.push_back(*label_i);
        min[*label_i] = *label_i;
    }

    std::list<std::tuple<char, char, int>> H;
    std::list<char> rset;

    while (!roots.empty()) {
        char k = roots.front();
        roots.pop_front();

        std::tuple<char, char, int> edge = pq->MAX(k);
        char i = std::get<0>(edge);
        char j = std::get<1>(edge); 
        if (std::get<2>(edge) <= 0 ) rset.push_back(k);
        else if (SSet->find_set(i) != k) {
            H.push_back(edge);
            if (WSet->find_set(i) != WSet->find_set(j)) {
                WSet->union_sets(WSet->find_set(i), WSet->find_set(j));
                enter[k] = edge;
            }
            else {
                int val = INT_MAX;
                char vertex;
                std::tuple<char, char, int> edge_aux = edge;
                while (std::get<0>(edge_aux) != '*') {
                    if (std::get<2>(edge_aux) < val) {
                        val = std::get<2>(edge_aux);
                        vertex = std::get<0>(edge_aux);
                    }
                    edge_aux = enter[SSet->find_set(std::get<0>(edge_aux))];
                }

                pq->ADD(val-std::get<2>(edge), k);
                min[k] = min[vertex];
                edge_aux = enter[SSet->find_set(i)];
                int i = 1;
                while (std::get<0>(edge_aux) != '*') {
                    pq->ADD(val-std::get<2>(edge_aux), SSet->find_set(std::get<1>(edge_aux)));
                    pq->QUNION(k, SSet->find_set(std::get<1>(edge_aux)));
                    SSet->union_sets(k, SSet->find_set(std::get<1>(edge_aux)));

                    edge_aux = pq->MAX(k);

                    i++;
                }
                roots.push_back(k);
            }
        }
    }

    std::list<char> resp;
    for (auto label_i = rset.begin(); label_i != rset.end(); label_i++) {
        resp.push_back(min[*label_i]);
    }

    return resp;
}

std::list<std::tuple<char, char, int>> Graph::get_incidence_list(char label) {
    std::list<std::tuple<char, char, int>> resp;
    int column_i = -1;
    int i = 0;
    for (auto label_i = labels.begin(); label_i != labels.end(); label_i++) {
        if (*label_i == label) {
            column_i = i;
            break;
        }
        i++;
    }

    i = 0;
    if (column_i != -1) {
        Cell *aux_ptr = this->first_cell;
        
        while (i < column_i) {
            aux_ptr = aux_ptr->right;
            i++;
        }
    
        for (auto label_i = labels.begin(); label_i != labels.end(); label_i++) {
            if (aux_ptr->weight != 0) {
                std::tuple<char, char, int> edge(*label_i, label, aux_ptr->weight);
                resp.push_back(edge);
            }
            aux_ptr = aux_ptr->below;
        }
    }

    return resp;
}

