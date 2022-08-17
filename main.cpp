#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define N 10
#define TAM_VETOR (((N - 1) * N) / 2)

struct Vertice
{
    int valor;
    vector<Vertice> lista;
};

int k_recursivo(int i, int n)
{
    if (i == 0)
        return 0;
    else
    {
        return (n - (i - 1) + k_recursivo(i - 1, n));
    }
}

int k_iterativo(int i, int n)
{
}

vector<Vertice> criaGrafo()
{
    int mult = 0; /* multiplicador para o número de arestas de 1 a 10 */
    int numAresta = 0;
    vector<Vertice> grafo;

    /* inicializacao de todos os vertices */
    for (int i = 0; i < N; i++)
    {
        Vertice novo;
        novo.valor = i;

        grafo.push_back(novo);
    }

    /* geracao de 1 a 10 arestas aleatorias por vertice */
    mult = rand() % 10 + 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < mult; j++)
        {
            int aresta = rand() % (N - 1);
            while (aresta == i)
            {
                aresta = rand() % (N - 1);
            }
            grafo.at(i).lista.push_back(grafo.at(aresta));
            numAresta++;
        }
    }

    cout << "Numero de Arestas = " << numAresta << endl;

    return grafo;
}

void geraMatriz(bool matriz[N][N], vector<Vertice> grafo)
{
    /* inicializacao da matriz */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matriz[i][j] = 0;
        }
    }

    /* geracao da matriz de adjacencia binaria */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
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

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void representacaoVetorial(bool matriz[N][N], bool vetor[TAM_VETOR])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            int pos = j - i + k_recursivo(i, N - 1);

            vetor[pos - 1] = matriz[i][j];
        }
    }

    cout << endl
         << "Representacao vetorial parte triangular superior:" << endl;
    for (int i = 0; i < TAM_VETOR; i++)
    {
        cout << "pos " << i + 1 << " = " << vetor[i] << endl;
    }
}

vector<int> representacaoVetorialCompactada(bool vetor[TAM_VETOR])
{
    vector<int> vetorCompacto;

    for (int i = 0; i < TAM_VETOR; i++)
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

    return vetorCompacto;
}

void vetorCompactadoParaMatriz(vector<int> vetorCompacto, bool vetorInverso[TAM_VETOR], bool matrizInversa[N][N])
{
    /* obtencao do vetor completo a partir do vetor compactado */
    for (int i = 0; i < TAM_VETOR; i++)
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
    for (int i = 0; i < TAM_VETOR; i++)
    {
        cout << "pos " << i + 1 << " = " << vetorInverso[i] << endl;
    }

    /* inicializacao da matriz inversa */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrizInversa[i][j] = 0;
        }
    }

    /* geracao da matriz a partir da representacao vetorial */
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            int pos = j - i + k_recursivo(i, N - 1);

            matrizInversa[i][j] = vetorInverso[pos - 1];
            matrizInversa[j][i] = vetorInverso[pos - 1];
        }
    }

    cout << endl
         << "Matriz inversa" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << matrizInversa[i][j] << " ";
        }
        cout << endl;
    }
}

void soma(bool vetor[TAM_VETOR], bool vetorInverso[TAM_VETOR])
{
    int soma[TAM_VETOR];

    cout << endl
         << "Soma" << endl;
    for (int i = 0; i < TAM_VETOR; i++)
    {
        soma[i] = vetor[i] + vetorInverso[i];
        cout << soma[i];
    }
    cout << endl;
    for (int i = 0; i < TAM_VETOR; i++)
    {
        cout << vetor[i];
    }
}

int main()
{
    bool matriz[N][N];
    bool vetor[TAM_VETOR];
    bool vetorInverso[TAM_VETOR];
    bool matrizInversa[N][N];

    vector<Vertice> grafo;
    vector<int> vetorCompacto;

    srand(time(NULL));

    grafo = criaGrafo();

    geraMatriz(matriz, grafo);

    representacaoVetorial(matriz, vetor);

    vetorCompacto = representacaoVetorialCompactada(vetor);

    vetorCompactadoParaMatriz(vetorCompacto, vetorInverso, matrizInversa);

    soma(vetor, vetorInverso);

    return 0;
}