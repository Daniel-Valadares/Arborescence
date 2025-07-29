 #include <iostream>
 #include "Edmonds.hpp"
    

    /*
    *    Seguem 4 exemplos de execução do método de Edmonds

    *   O primeiro exemplo (grafo1) gera um resultado correto. Há um ciclo de 2 vértices durante a construção da AGM e ele é detectado corretamente e tratado como
        proposto pelo artigo.

    *   O segundo exemplo (grafo2), apesar de ser em um grafo que possui cíclos, estes ciclos não chegam a aparecer durante a construção da AGM.
        A execução do método de edmonds para esse exemplo não passa pela etapa de tratamento de ciclos e o resultado gerado está correto.

    *   O terceiro exemplo (grafo3) possui um ciclo de 3 vértices que interfere na execução, assim como o ciclo do exemplo 1.
        Os testes mostraram que esse tipo de ciclo é tratado corretamente e o resultado gerado também está correto.

    *   O quarto exemplo (grafo4) é um grafo simples de 5 vértices com um ciclo de 4 vértices.
        O resultado gerado está correto.
    

         Aqui estão links de imagens pra vizualizar melhor como são os grafos 1, 2, 3 e 4 e como devem ser suas AGM com raiz no vértice A:

         grafo1 - https://prnt.sc/meUx3UMDYUBn
         grafo2 - https://prnt.sc/UoNU-t530kM_
         grafo3 - https://prnt.sc/gjSOI4ef6Z6v
         grafo4 - https://prnt.sc/FlOdA2-QWf6-
    
    */

int main(){
    
    // Exemplo 1

    GrafoDirecionado grafo1;

    grafo1.adicionarVertice("A");
    grafo1.adicionarVertice("B");
    grafo1.adicionarVertice("C");
    grafo1.adicionarVertice("D");

    grafo1.adicionarAresta("A", "B", -12); // A->B, -12
    grafo1.adicionarAresta("A", "C", -4);  // A->C, -4
    grafo1.adicionarAresta("A", "D", -4);  // A->D, -4
    grafo1.adicionarAresta("B", "C", -5);  // B->C, -5
    grafo1.adicionarAresta("B", "D", -7);  // B->D, -7
    grafo1.adicionarAresta("C", "B", -6);  // C->B, -6
    grafo1.adicionarAresta("C", "D", -8);  // C->D, -8
    grafo1.adicionarAresta("D", "C", -7);  // D->C, -7
    grafo1.adicionarAresta("D", "B", -5);  // D->B, -5

    std::cout << "Grafo 1: \n";

    grafo1.imprimirGrafo();

    std::cout << "\nAGM com raiz em A do grafo 1: \n";

    grafo1.Edmonds("A").imprimirGrafo();

    // Exemplo 2

    GrafoDirecionado grafo2;

    grafo2.adicionarVertice("A");
    grafo2.adicionarVertice("B");
    grafo2.adicionarVertice("C");
    grafo2.adicionarVertice("D");
    grafo2.adicionarVertice("E");

    grafo2.adicionarAresta("A", "B", 3); // A->B, 3
    grafo2.adicionarAresta("A", "C", 7); // A->C, 7
    grafo2.adicionarAresta("B", "C", 5); // B->C, 5
    grafo2.adicionarAresta("B", "D", 1); // B->D, 1
    grafo2.adicionarAresta("C", "E", 6); // C->E, 6
    grafo2.adicionarAresta("D", "C", 4); // D->C, 4
    grafo2.adicionarAresta("D", "E", 8); // D->E, 8
    grafo2.adicionarAresta("E", "A", 2); // E->A, 2
    std::cout << "==================================== \n";
    std::cout << "Grafo 2: \n";

    grafo2.imprimirGrafo();

    std::cout << "\nAGM com raiz em A do grafo 2: \n";

    grafo2.Edmonds("A").imprimirGrafo();

    // Exemplo 3

    GrafoDirecionado grafo3;

    grafo3.adicionarVertice("A");
    grafo3.adicionarVertice("B");
    grafo3.adicionarVertice("C");
    grafo3.adicionarVertice("D");
    grafo3.adicionarVertice("E");

    grafo3.adicionarAresta("A", "B", 4); // A->B, 4
    grafo3.adicionarAresta("A", "E", 5); // A->E, 5
    grafo3.adicionarAresta("B", "C", 1); // B->C, 1
    grafo3.adicionarAresta("C", "D", 2); // C->D, 2
    grafo3.adicionarAresta("C", "E", 4); // C->E, 4
    grafo3.adicionarAresta("D", "B", 3); // D->B, 3
    std::cout << "==================================== \n";
    std::cout << "Grafo 3: \n";

    grafo3.imprimirGrafo();

    std::cout << "\nAGM com raiz em A do grafo 3: \n";

    grafo3.Edmonds("A").imprimirGrafo();

    // Exemplo 4

    GrafoDirecionado grafo4;

    grafo4.adicionarVertice("A");
    grafo4.adicionarVertice("B");
    grafo4.adicionarVertice("C");
    grafo4.adicionarVertice("D");
    grafo4.adicionarVertice("E");

    grafo4.adicionarAresta("A", "B", 5); // A->B, 5
    grafo4.adicionarAresta("B", "C", 2); // B->C, 2
    grafo4.adicionarAresta("C", "D", 3); // C->D, 3
    grafo4.adicionarAresta("D", "E", 4); // D->E, 4
    grafo4.adicionarAresta("E", "B", 1); // E->B, 1
    std::cout << "==================================== \n";
    std::cout << "Grafo 4: \n";

    grafo4.imprimirGrafo();

    std::cout << "\nAGM com raiz em A do grafo 4: \n";

    grafo4.Edmonds("A").imprimirGrafo();

    std::cout << "\nFIM \n";
    return 0;
    }
