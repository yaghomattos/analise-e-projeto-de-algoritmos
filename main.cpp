#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Vertice
{
    int valor;
    vector<Vertice> lista;
};

int main()
{
    int numVertices = 100;
    int mult = 0; /* multiplicador para o número de arestas de 1 a 10 */

    vector<Vertice> grafo;

    srand(time(NULL));

    /* inicializacao de todos os vertices */
    for (int i = 0; i < numVertices; i++)
    {
        Vertice novo;
        novo.valor = i;

        grafo.push_back(novo);
    }

    /* geracao de 1 a 10 arestas aleatorias por vertice */
    for (int i = 0; i < numVertices; i++)
    {
        mult = rand() % 10 + 1;
        for (int j = 0; j < mult; j++)
        {
            int aresta = rand() % 99;
            grafo.at(i).lista.push_back(grafo.at(aresta));
        }
    }

    for (int i = 0; i < numVertices; i++)
    {
        cout << grafo.at(i).valor << " Numero de Arestas: " << grafo.at(i).lista.size() << endl;
    }

    return 0;
}
