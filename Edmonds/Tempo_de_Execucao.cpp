#include <iostream>
#include "Edmonds.hpp"
#include <chrono>
#include <time.h>
int main()
{

    int inicioVertices = 10;
    int fimVertices = 100;
    int incrementoVertices = 10;
    std::srand( (unsigned)time( NULL ) );
    
    // Criando 10 grafos com quantidades de vértices variando de 10 em 10 começando de 10 até 100
    for (int numVertices = inicioVertices; numVertices <= fimVertices; numVertices += incrementoVertices)
    {
        GrafoDirecionado grafo;

        // Adiciona vértices ao grafo
        for (int i = 0; i < numVertices; ++i)
        {
            std::string rotulo = "V" + std::to_string(i);
            grafo.adicionarVertice(rotulo);
        }

        // Adiciona uma aresta para cada combinação de vértices possível
        for (int i = 0; i < numVertices; ++i)
        {
            for (int j = i + 1; j < numVertices; ++j)
            {
            
                int peso = rand() % 100 + 1; // Peso das arestas é aleatório entre 1 e 100
                grafo.adicionarAresta("V" + std::to_string(i), "V" + std::to_string(j), peso);           
                
            }
        }

        
        auto start = std::chrono::high_resolution_clock::now(); // Guarda tempo antes do início da execução do método de Edmonds
        grafo.Edmonds("V0");
        int numArestas = grafo.obterArestas().size();
        auto stop = std::chrono::high_resolution_clock::now(); // Guarda tempo após fim da execução do método de Edmonds
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); // Tempo de execução = fim - início
        std::cout << "Tempo de execucao para " << numVertices << " vertices e " <<numArestas <<" arestas: " << duration.count() << " microsegundos";
        std::cout << "\n==================================== \n";

    }

    std::cout << "\nFIM\n";
    return 0;

}