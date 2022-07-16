#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Aresta
{
    int origem;
    int destino;
};

int main()
{
    int numVertices = 100;

    vector<Aresta> grafo;

    srand(time(NULL));

    for (int i = 0; i < numVertices * (rand() % 10 + 1); i++)
    {
        Aresta novaAresta;

        novaAresta.origem = rand() % 100;
        novaAresta.destino = rand() % 100;

        /*Caso a aresta gerada aponte para o mesmo vértice de origem é gerada
        uma nova aresta*/
        if (novaAresta.destino == novaAresta.origem)
            novaAresta.destino = rand() % 100;

        grafo.push_back(novaAresta);

        cout << grafo.at(i).origem << "->" << grafo.at(i).destino << endl;
    }

    cout << "Numero de Arestas: " << grafo.size() << endl;

    return 0;
}
