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
    int n = 10;
    int mult = 0; /* multiplicador para o número de arestas de 1 a 10 */
    int numAresta = 0;

    vector<Vertice> grafo;

    srand(time(NULL));

    /* inicializacao de todos os vertices */
    for (int i = 0; i < n; i++)
    {
        Vertice novo;
        novo.valor = i;

        grafo.push_back(novo);
    }

    /* geracao de 1 a 10 arestas aleatorias por vertice */
    mult = rand() % 10 + 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < mult; j++)
        {
            int aresta = rand() % (n - 1);
            while (aresta == i)
            {
                aresta = rand() % (n - 1);
            }
            grafo.at(i).lista.push_back(grafo.at(aresta));
            numAresta++;
        }
    }

    bool matriz[n][n];

    /* inicializacao da matriz */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz[i][j] = 0;
        }
    }

    /* geracao da matriz de adjacencia */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < grafo[i].lista.size(); k++)
            {
                if (grafo[i].lista[k].valor == j)
                {
                    matriz[i][j] = 1;
                }
            }
        }
    }

    /* equalizacao da matriz de adjacencia */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matriz[i][j] != matriz[j][i])
            {
                matriz[i][j] = 1;
                matriz[j][i] = 1;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    cout << numAresta;

    return 0;
}
