#include <iostream>
#include<fstream>
#include <chrono>
#include <Graph.h>

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv)
{
    auto start = high_resolution_clock::now();
    // Abrindo arquivo
    ifstream ArquivoParaLer;
    ArquivoParaLer.open(argv[2]);
    if (!ArquivoParaLer.is_open())
    {
        cout << "Arquivo nao encontrado" << endl;
        return -1;
    }
    string Linha;

    // Lendo o numero de vertices
    ArquivoParaLer >> Linha;
    int NumeroDeVertices;
    NumeroDeVertices = stoi(Linha);

    // Lendo o numero de trilhas
    ArquivoParaLer >> Linha;
    int NumeroDeTrilhas;
    NumeroDeTrilhas = stoi(Linha);

    string TarefaString = "tarefa1";

    // Criando o grafo
    Graph Grafo(NumeroDeVertices, NumeroDeTrilhas, argv[1] != TarefaString, ArquivoParaLer);

    /** Para tarefa 1: */
    if(argv[1] == TarefaString)
        cout << Grafo.FindMinimumVertexCover() << endl;
    /** Para tarefa 2: */
    else
    {
        int* ArrayASerImpresso = Grafo.FindAproxVertexCover();
        for (int i = 0; i < NumeroDeVertices; i++)
        {
            if(ArrayASerImpresso[i] != -1)
                cout << ArrayASerImpresso[i] << endl;
        }
        if (ArrayASerImpresso != nullptr)
            delete[] ArrayASerImpresso;
    }
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    // To get the value of duration use the count()
    // member function on the duration object
    //cout << "Duration: " << duration.count() << endl;

    return 0;
}