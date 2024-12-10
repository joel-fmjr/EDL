#include <iostream>
#include <chrono>

using namespace std;

const int TAMANHO = 1000000;
unsigned sequencias[TAMANHO] = {};

int numDePassos(int n)
{
    int sequencia = 0;
    unsigned aux = n;

    do
    {
        if (aux < n)
        {
            int passos = sequencias[aux];
            if (passos > 0)
            {
                sequencia += passos;
                break;
            }
        }

        if (aux % 2 == 0)
        {
            sequencia++;
            aux = aux / 2;
        }
        else
        {
            sequencia += 2;
            aux = (3 * aux + 1) / 2;
        }

    } while (aux > 1);

    sequencias[n] = sequencia;
    return sequencia;
}

int main()
{
    auto start = chrono::steady_clock::now();
    int maiorSequencia = 0;
    unsigned maiorN = 0;

    for (int i = 1; i < TAMANHO; i++)
    {
        int sequencia = numDePassos(i);

        if (sequencia > maiorSequencia)
        {
            maiorSequencia = sequencia;
            maiorN = i;
        }
    }

    cout << maiorN << " - " << maiorSequencia << endl;
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << chrono::duration<double, milli>(diff).count() << " ms" << endl;
}