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

vector<Vertice> criaGrafo();
void geraMatriz(bool matriz[N][N], vector<Vertice> grafo);
void representacaoVetorial(bool matriz[N][N], bool vetor[TAM_VETOR]);
vector<int> representacaoVetorialCompactada(bool vetor[TAM_VETOR]);
void vetorCompactadoParaMatriz(vector<int> vetorCompacto, bool vetorInverso[TAM_VETOR], bool matrizInversa[N][N]);
int k_recursivo(int i, int n);
int k_iterativo(int i);
void mapeamentoInverso(int k);
void soma(bool vetor[TAM_VETOR], bool vetorInverso[TAM_VETOR]);
void produto(bool vetor[TAM_VETOR], bool vetorInverso[TAM_VETOR]);

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

    int i = 4;
    int j = 8;

    cout << endl
         << "Mapeamento da entrada (" << i << ", " << j << ") da matriz para a posicao K do vetor:" << endl;
    cout << "Recursivo - " << j - i + k_recursivo(i, N - 1) << endl;
    cout << "Iterativo - " << j - i + k_iterativo(i) << endl
         << endl;

    mapeamentoInverso(j - i + k_recursivo(i, N - 1));

    soma(vetor, vetorInverso);

    produto(vetor, vetorInverso);

    return 0;
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
    /**
     * Complexidade O(n)
     */

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
    /**
     * Complexidade T(n) = n * 10 + 5
     * T(n) = 10n + 5
     */

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
    /**
     * Complexidade T(n) = n * n + 1
     * T(n) = n^2 + 1
     */

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
    /**
     * Complexidade T(n) = n * n * 10 + 3
     * T(n) = 10n^2 + 3
     */

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
    /**
     * Complexidade T(n) = n * n + i + 2
     * T(n) = n^2 + i + 2
     */

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
    /**
     * Complexidade O(TAM_VETOR)
     */

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
    /**
     * Complexidade T(n) = TAM_VETOR * vetorCompacto
     * T(n) = n(n-1)/2 * TAM_VETOR
     * T(n) = n(n-1)/2 * n(n-1)/2
     * T(n) = n(n-1)
     * T(n) = n^2 - n
     */

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
    /**
     * Complexidade T(n) = n * (n-1)/2 + n
     * T(n) = n(n-1)/2 + n
     * T(n) = (n^2 - n)/2 + n
     * T(n) = (n^2 + n)/2
     */

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

int k_recursivo(int i, int n)
{
    if (i == 0)
        return 0;
    else
    {
        return (n - (i - 1) + k_recursivo(i - 1, n));
    }

    /**
     * Complexidade O(i) = O(n)
     */
}

int k_iterativo(int i)
{
    int k[N];
    k[0] = 0;
    for (int j = 1; j < N; j++)
    {
        k[j] = (N - 1) - (j - 1) + k[j - 1];
    }
    return k[i];

    /**
     * Complexidade T(n) = n + 2
     */
}

void mapeamentoInverso(int k)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int aux = k_iterativo(i) + j;

            if (aux == k)
                cout << "Mapeamento inverso de k = " << k << " -> (" << i << ", " << j + i << ")" << endl;
        }
    }
    /**
     * Complexidade T(n) = n * n + n + 3
     * T(n) = n^2 + n + 3
     */
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
    /**
     * Complexidade T(n) = TAM_VETOR + 1 + TAM_VETOR
     * T(n) = n(n-1)/2 + 1 + n(n-1)/2
     * T(n) = n(n-1) + 1
     * T(n) = n^2 - n + 1
     */

    cout << endl;
    for (int i = 0; i < TAM_VETOR; i++)
    {
        cout << vetor[i];
    }
}

void produto(bool vetor[TAM_VETOR], bool vetorInverso[TAM_VETOR])
{
    bool resultado[TAM_VETOR];
    bool aux;

    for (int i = 0; i < N; i++)
    {
        resultado[i] = 0;
        for (int j = 0; j < N; j++)
        {
            aux += (vetor[j] * vetorInverso[i + ((j * N) - 1)]);
        }
        resultado[i] = aux;
    }
}
