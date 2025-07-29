#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <limits>
#include <string.h>
#include <unordered_map>
#include <stack>
#include <algorithm>

class ArestaPonderada;

class Vertice
{
public:
    std::string rotulo;
    std::list<ArestaPonderada *> arestasIn;  // Lista de arestas que entram no vértice
    std::list<ArestaPonderada *> arestasOut; // Lista de arestas que saem do vértice

    Vertice(const std::string &label) : rotulo(label) {}
};

class ArestaPonderada
{
public:
    const Vertice *verticeOrigem;
    const Vertice *verticeDestino;
    int peso;

    ArestaPonderada(const Vertice *origem, const Vertice *destino, int peso) : verticeOrigem(origem), verticeDestino(destino), peso(peso) {}
};

class GrafoDirecionado
{
private:
    std::vector<Vertice> vertices;
    std::vector<ArestaPonderada> arestas;

    bool DFS(const Vertice *v, std::unordered_map<const Vertice *, int> &cor, std::unordered_map<const Vertice *, const Vertice *> &pai, std::list<const Vertice *> &ciclo)
    {
        cor[v] = 1; // Marcado como cinza (visitado)
        for (const auto &aresta : v->arestasOut)
        {
            const Vertice *u = aresta->verticeDestino;
            if (cor[u] == 0) // Não visitado
            {
                pai[u] = v;
                if (DFS(u, cor, pai, ciclo))
                    return true;
            }
            else if (cor[u] == 1) // Cinza (visitado durante a DFS atual)
            {
                // Ciclo detectado
                // Armazena os vértices do ciclo
                const Vertice *temp = v;
                while (temp != u)
                {
                    ciclo.push_front(temp);
                    temp = pai[temp];
                }
                ciclo.push_front(u);
                return true;
            }
        }
        cor[v] = 2; // Marcado como preto (completamente visitado)
        return false;
    }

public:
    // Adiciona um vértice ao grafo
    void adicionarVertice(const std::string &rotulo)
    {
        vertices.emplace_back(rotulo);
    }

    // Adiciona uma aresta direcionada com peso a partir dos rótulos dos vértices de origem e destino
    void adicionarAresta(std::string v, std::string u, int peso)
    {
        const Vertice *origem;
        const Vertice *destino;
        for (const auto &vertice : vertices)
        {
            if (vertice.rotulo == v)
            {
                origem = &vertice;
            }
            if (vertice.rotulo == u)
            {
                destino = &vertice;
            }
        }
        ArestaPonderada *aresta = new ArestaPonderada(origem, destino, peso);
        const_cast<Vertice *>(origem)->arestasOut.push_back(aresta);
        const_cast<Vertice *>(destino)->arestasIn.push_back(aresta);
        arestas.push_back(*aresta);
    }

    void removerAresta(const std::string &v, const std::string &u)
    {
        // Encontrar a aresta no vetor de arestas
        auto it = std::remove_if(arestas.begin(), arestas.end(), [&](const ArestaPonderada &aresta)
                                 { return aresta.verticeOrigem->rotulo == v && aresta.verticeDestino->rotulo == u; });

        // Remover a aresta da lista de arestas
        arestas.erase(it, arestas.end());

        // Atualizar as listas de arestasIn e arestasOut nos vértices
        for (auto &vertice : vertices)
        {
            vertice.arestasIn.remove_if([&](const ArestaPonderada *aresta)
                                        { return aresta->verticeDestino->rotulo == u && aresta->verticeOrigem->rotulo == v; });

            vertice.arestasOut.remove_if([&](const ArestaPonderada *aresta)
                                         { return aresta->verticeOrigem->rotulo == v && aresta->verticeDestino->rotulo == u; });
        }
    }

    // Obtém os vértices do grafo
    const std::vector<Vertice> &obterVertices() const
    {
        return vertices;
    }

const std::vector<ArestaPonderada> &obterArestas() const
    {
        return arestas;
    }


    // Imprime o grafo com pesos
    void imprimirGrafo() const
    {
        for (const auto &vertice : vertices)
        {
            std::cout << "Vertice " << vertice.rotulo << ": Saidas: ";
            if (!vertice.arestasOut.empty())
            {
                for (const auto &aresta : vertice.arestasOut)
                {
                    std::cout << aresta->verticeDestino->rotulo << " ";
                }
            }
            else
            {
                std::cout << "0";
            }

            std::cout << " | Entradas: ";
            if (!vertice.arestasIn.empty())
            {
                for (const auto &aresta : vertice.arestasIn)
                {
                    std::cout << aresta->verticeOrigem->rotulo << " ";
                }
            }
            else
            {
                std::cout << "0";
            }

            std::cout << std::endl;
        }

        std::cout << "Arestas e seus pesos:" << std::endl;
        for (const auto &aresta : arestas)
        {
            std::cout << "(" << aresta.verticeOrigem->rotulo << " -> " << aresta.verticeDestino->rotulo << ", Peso: " << aresta.peso << ") ";
        }
        std::cout << std::endl;
    }

    // Implementação algoritmo de Edmonds
    GrafoDirecionado Edmonds(std::string r)
    {
        
        GrafoDirecionado AGM; // Aborecencia Geradora Minima
        // Adicionando todos os vertices do grafo na AGM
        for (const auto &vertice : vertices)
        {
            AGM.adicionarVertice(vertice.rotulo);
        }
        // Percorre todos os vértices diferentes da raiz, encontrando suas arestas de entrada de menor peso e adicionando-as na AGM
        for (const auto &vertice : vertices)
        {
            if (vertice.rotulo != r)
            {
                ArestaPonderada menor = *(vertice.arestasIn.front());
                for (const auto &aresta : vertice.arestasIn)
                {
                    if (aresta->peso < menor.peso)
                    {
                        menor = *aresta;
                    }
                }
                AGM.adicionarAresta(menor.verticeOrigem->rotulo, menor.verticeDestino->rotulo, menor.peso);
                std::list<const Vertice *> ciclo = AGM.possuiCiclo();
                // Verificação da existencia de ciclo após inclusão de nova aresta
                //Enquanto houver ciclo, continua o tratamento
                
                while (!ciclo.empty())
                {
                    int n = ciclo.size();
                    std::string verticesCiclo[n];
                    int i = 0;
                    // Guardando rótulos dos vértices do ciclo em um vetor
                    for (const auto &vertice : ciclo)
                    {
                        verticesCiclo[i] = vertice->rotulo;
                        i++;
                    }
                    std::list<ArestaPonderada *> foraDoCiclo;
                    // Encontra arestas no grafo original que ainda não estão na AGM, possuem vértice origem fora do ciclo e vértice destino dentro do ciclo
                    for (const auto &aresta : arestas)
                    {
                        bool flagOrigem = true;
                        // Verificando se o vértice de origem está fora do ciclo
                        for (int i = 0; i < n; ++i)
                        {
                            if (verticesCiclo[i] == aresta.verticeOrigem->rotulo)
                            {
                                flagOrigem = false;
                                break; 
                            }
                        }
                        // Caso o vértice de origem esteja fora do ciclo, verifica se o de destino está dentro e o adiciona a uma lista
                        if(flagOrigem){
                            for (int i = 0; i < n; ++i)
                        {
                            if (verticesCiclo[i] == aresta.verticeDestino->rotulo)
                            {
                                foraDoCiclo.push_back(new ArestaPonderada(aresta.verticeOrigem, aresta.verticeDestino, aresta.peso));
                                break; 
                            }
                        }
                        }
                    }

                    ArestaPonderada menorFora = *(foraDoCiclo.front());
                    // Das arestas encontradas anteriormente, separa a de menor peso
                    for (const auto &aresta : foraDoCiclo)
                    {
                        if (aresta->peso < menorFora.peso)
                        {
                            menorFora = *aresta;
                        }
                    }

                    // Procura uma aresta dentro do ciclo que possui mesmo vértice destino que a aresta encontrada do loop anterior e a remove da AGM
                    for (const auto &aresta : AGM.arestas)
                    {
                        if (aresta.verticeDestino->rotulo == menorFora.verticeDestino->rotulo)
                        {
                            AGM.removerAresta(aresta.verticeOrigem->rotulo, aresta.verticeDestino->rotulo);
                        }
                    }
                    // Substituição da aresta removida por uma fora do ciclo e de mesmo destino
                    AGM.adicionarAresta(menorFora.verticeOrigem->rotulo, menorFora.verticeDestino->rotulo, menorFora.peso);
                    ciclo = AGM.possuiCiclo();
                    // Liberação de memória
                    for (const auto &aresta : foraDoCiclo)
                    {
                        delete aresta;
                    }
                    foraDoCiclo.clear();
                }
            }
        }
        return AGM;
    }

    std::list<const Vertice *> possuiCiclo()
    {
        std::unordered_map<const Vertice *, int> cor;
        std::unordered_map<const Vertice *, const Vertice *> pai;
        std::list<const Vertice *> ciclo;

        for (const auto &vertice : vertices)
        {
            if (cor[&vertice] == 0) // Não visitado
            {
                if (DFS(&vertice, cor, pai, ciclo))
                    return ciclo;
            }
        }

        return ciclo;
    }
};