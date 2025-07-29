/**
 * Para compilar todos os arquivos num único executável:
 * " g++ main.cpp Graph.cpp Cell.cpp DSU.cpp LeftistHeap.cpp LeftistNode.cpp PriorityQueue.cpp -o main -Wall "
*/

/**
 * Grafo representado como uma matriz dinâmica. 
 * Qualquer valor inteiro diferente de 0, representa a existência de uma aresta.
*/

#include <iostream>
#include "Graph.hpp"

int main () {
	Graph *grafo1 = new Graph(true);
	
	grafo1->add_vertex('A');
	grafo1->add_vertex('B');
	grafo1->add_vertex('C');
	grafo1->add_vertex('D');
	grafo1->add_vertex('E');
	grafo1->add_vertex('F');
	grafo1->add_vertex('G');
	grafo1->add_vertex('H');
	

	grafo1->add_edge('A', 'E', 4);
	grafo1->add_edge('A', 'G', 1);
	grafo1->add_edge('B', 'A', 2);
	grafo1->add_edge('B', 'C', 2);
	grafo1->add_edge('C', 'D', 3);
	grafo1->add_edge('D', 'B', 1);
	grafo1->add_edge('E', 'G', 2);
	grafo1->add_edge('F', 'E', 1);
	grafo1->add_edge('G', 'F', 3);
	grafo1->add_edge('G', 'H', 2);
	

	std::cout << "Matriz de adjacência do grafo exemplo 1:" << std::endl;
	grafo1->print_matrix();

	std::cout << "\nMatriz de adjacência do grafo exemplo 1 depois de MGA:" << std::endl;
	grafo1->MGA();
	grafo1->print_matrix();


	Graph *grafo2 = new Graph(true);
	
	grafo2->add_vertex('A');
	grafo2->add_vertex('B');
	grafo2->add_vertex('C');
	grafo2->add_vertex('D');
	

	grafo2->add_edge('B', 'A', 2);
	grafo2->add_edge('B', 'C', 3);
	grafo2->add_edge('C', 'D', 1);
	grafo2->add_edge('D', 'B', 2);
	

	std::cout << "Matriz de adjacência do grafo exemplo 2:" << std::endl;
	grafo2->print_matrix();

	std::cout << "\nMatriz de adjacência do grafo exemplo 2 depois de MGA:" << std::endl;
	grafo2->MGA();
	grafo2->print_matrix();
	
	return 0;
}
