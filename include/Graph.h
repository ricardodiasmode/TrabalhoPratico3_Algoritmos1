#ifndef GRAPH_H
#define GRAPH_H
#pragma once

#include <list>
#include<fstream>
#include <vector>

using namespace std;


class Graph {
    // Variaveis
private:
    int NumeroDeVertices;

    // Lista que representa as arestas de um aeroporto no outro
    vector<int>* ListaDeAdjacencia;

public:
    // Construtor
    Graph(int NumeroDeVertices, int NumeroDeTrilhas, bool Aprox, ifstream& ArquivoParaLer);

    // Destrutor
    ~Graph();

    // Adiciona uma aresta do node1 para o node2
    void AdicionarAresta(int node1, int node2);

    int FindMinimumVertexCover();
    void Dfs(vector<int> Visited[], int atual, int pai);
    int* FindAproxVertexCover();
};

#endif // !GRAPH_H
