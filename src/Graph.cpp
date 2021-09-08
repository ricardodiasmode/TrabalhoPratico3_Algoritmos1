#include <Graph.h>
#include <iostream>
#include <queue>

Graph::Graph(int NumeroDeVertices, int NumeroDeTrilhas, bool Aprox, ifstream& ArquivoParaLer)
{
    this->NumeroDeVertices = NumeroDeVertices;

    ListaDeAdjacencia = new vector<int>[NumeroDeVertices+1];

    string Linha;
    for (int i = 0; i < NumeroDeTrilhas; i++)
    {
        int Trilha1;
        int Trilha2;
        ArquivoParaLer >> Linha;
        Trilha1 = stoi(Linha);
        ArquivoParaLer >> Linha;
        Trilha2 = stoi(Linha);
        AdicionarAresta(Trilha1 + (Aprox ? 0 : 1), Trilha2 + (Aprox ? 0 : 1));
    }
}

Graph::~Graph()
{
    if(ListaDeAdjacencia != nullptr)
        delete[] ListaDeAdjacencia;
}

void Graph::AdicionarAresta(int node1, int node2)
{
    ListaDeAdjacencia[node1].push_back(node2);
    ListaDeAdjacencia[node2].push_back(node1);
}

void Graph::Dfs(vector<int> Visited[], int atual, int pai)
{
    for (auto vizinho : ListaDeAdjacencia[atual])
    {
        if (vizinho != pai)
            Dfs(Visited, vizinho, atual);
    }

    for (auto vizinho : ListaDeAdjacencia[atual])
    {
        if (vizinho != pai)
        {
            // nao incluindo o vertice atual na cobertura
            Visited[atual][0] += Visited[vizinho][1];

            // incluindo o vertice atual na cobertura
            Visited[atual][1] += min(Visited[vizinho][1], Visited[vizinho][0]);
        }
    }
}

int Graph::FindMinimumVertexCover()
{
    vector<int> Visited[NumeroDeVertices + 1];

    for (int i = 1; i <= NumeroDeVertices; i++) 
    {
        // 0 == nao visitado
        Visited[i].push_back(0);

        // 1 == visitado
        Visited[i].push_back(1);
    }

    Dfs(Visited, 1, -1);

    return min(Visited[1][0], Visited[1][1]);
}

int* Graph::FindAproxVertexCover()
{
    bool Visitada[NumeroDeVertices][NumeroDeVertices];
    int* VertexCover = new int[NumeroDeVertices];

    for (int i = 0; i < NumeroDeVertices; i++)
    {
        VertexCover[i] = -1;
        for (int j = 0; j < NumeroDeVertices; j++)
        {
            Visitada[i][j] = false;
        }
    }
    VertexCover[0] = 0;

    for (int i = 0; i < NumeroDeVertices; i++)
    {
        for (int j = 0; j < (int)ListaDeAdjacencia[i].size(); j++)
        {
            int secondIndex = ListaDeAdjacencia[i][j];
            // Se encontrou uma aresta que ainda nao foi visitada
            if (Visitada[i][secondIndex] == false && Visitada[secondIndex][i] == false && i != j && i != secondIndex)
            {
                // Define todas as arestas do node i como visitadas
                for (int k = 0; k < NumeroDeVertices; k++)
                    Visitada[i][k] = true;
                Visitada[secondIndex][i] = true;

                // Adicionando 1 aa cobertura
                VertexCover[0] = VertexCover[0]+1;
                // Adicionando index do node atual no array
                VertexCover[VertexCover[0]] = i;
            }
        }
    }

    return VertexCover;
}
