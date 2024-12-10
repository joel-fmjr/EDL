#include <iostream>
#include <chrono>
#include <unordered_map>
#include <vector>

using namespace std;

const int TAMANHO = 1000000;

int numSequencia(int n, unordered_map<int, int> &sequencias)
{
    vector<int> sub_sequencias;
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
            sub_sequencias.push_back(aux);
        }
        else
        {
            sequencia += 2;
            aux = (3 * aux + 1);
            sub_sequencias.push_back(aux);
            aux = aux / 2;
            sub_sequencias.push_back(aux);
        }

    } while (aux > 1);

    sequencias[n] = sequencia;

    for (size_t i = 0; i < sub_sequencias.size(); i++)
    {
        if (sequencias.find(sub_sequencias[i]) == sequencias.end())
        {
            sequencias[sub_sequencias[i]] = sequencia - (i + 1);
        }
        else
        {
            break;
        }
    }
    return sequencia;
}

int main()
{
    auto start = chrono::steady_clock::now();
    int maiorSequencia = 0;
    unsigned maiorN = 0;
    unordered_map<int, int> sequencias;

    for (size_t i = 1; i < TAMANHO; i++)
    {
        if (sequencias.find(i) != sequencias.end())
        {
            continue;
        }

        int sequencia = numSequencia(i, sequencias);

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