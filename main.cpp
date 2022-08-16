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

int k(int i, int n)
{
    if (i == 0)
        return 0;
    else
    {
        return (n - (i - 1) + k(i - 1, n));
    }
}

int main()
{
    int n = 10;
    int mult = 0; /* multiplicador para o número de arestas de 1 a 10 */
    int numAresta = 0;
    int tamVetor = ((n - 1) * n) / 2;

    bool matriz[n][n];

    bool vetor[tamVetor];
    bool vetorInverso[tamVetor];
    bool matrizInversa[n][n];

    vector<Vertice> grafo;
    vector<int> vetorCompacto;

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

    /* inicializacao da matriz */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz[i][j] = 0;
        }
    }

    /* geracao da matriz de adjacencia binaria */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < grafo[i].lista.size(); k++)
            {
                if (grafo[i].lista[k].valor == j)
                {
                    matriz[i][j] = 1;
                    matriz[j][i] = 1;
                }
            }
        }
    }

    cout << "Numero de Arestas = " << numAresta << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    /* representacao vetorial da matriz de adjacencia binaria */
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int pos = j - i + k(i, n - 1);

            vetor[pos - 1] = matriz[i][j];
        }
    }

    cout << endl
         << "Representacao vetorial parte triangular superior:" << endl;
    for (int i = 0; i < tamVetor; i++)
    {
        cout << "pos " << i + 1 << " = " << vetor[i] << endl;
    }

    /* representacao compactada do vetor */
    for (int i = 0; i < tamVetor; i++)
    {
        if (vetor[i] == 1)
        {
            vetorCompacto.push_back(i);
        }
    }

    cout << endl
         << "Vetor compactado:" << endl;
    for (int i = 0; i < vetorCompacto.size(); i++)
    {
        cout << vetorCompacto[i] + 1 << endl;
    }

    /* obtencao do vetor completo a partir do vetor compactado */
    for (int i = 0; i < tamVetor; i++)
    {
        vetorInverso[i] = 0;
        for (int j = 0; j < vetorCompacto.size(); j++)
        {
            if (vetorCompacto[j] == i)
            {
                vetorInverso[i] = 1;
            }
        }
    }

    cout << endl
         << "Representacao vetorial extendida do vetor compacto:" << endl;
    for (int i = 0; i < tamVetor; i++)
    {
        cout << "pos " << i + 1 << " = " << vetorInverso[i] << endl;
    }

    /* inicializacao da matriz inversa */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrizInversa[i][j] = 0;
        }
    }

    /* geracao da matriz a partir da representacao vetorial */
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int pos = j - i + k(i, n - 1);

            matrizInversa[i][j] = vetorInverso[pos - 1];
            matrizInversa[j][i] = vetorInverso[pos - 1];
        }
    }

    cout << endl
         << "Matriz inversa" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrizInversa[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}