#include <stdio.h>

#define MAX 20

struct Edge
{
    int source;
    int destination;
    int cost;
};

int find(int parent[], int vertex)
{
    while (parent[vertex] != vertex)
        vertex = parent[vertex];

    return vertex;
}

void unionSets(int parent[], int a, int b)
{
    int rootA = find(parent, a);
    int rootB = find(parent, b);

    parent[rootA] = rootB;
}

int main()
{
    int n, i, j;
    int graph[MAX][MAX];
    struct Edge edges[MAX * MAX];
    int parent[MAX];
    int edgeCount = 0;
    int selectedEdges = 0;
    int totalCost = 0;

    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("\nEnter the road cost matrix:\n");
    printf("(Enter 0 if there is no direct road)\n\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);

            if (graph[i][j] != 0 && i < j)
            {
                edges[edgeCount].source = i;
                edges[edgeCount].destination = j;
                edges[edgeCount].cost = graph[i][j];
                edgeCount++;
            }
        }
    }

    for (i = 0; i < n; i++)
        parent[i] = i;

    /* Sort edges by cost */
    for (i = 0; i < edgeCount - 1; i++)
    {
        for (j = 0; j < edgeCount - i - 1; j++)
        {
            if (edges[j].cost > edges[j + 1].cost)
            {
                struct Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    printf("\nMinimum Cost Spanning Tree using Kruskal's Algorithm:\n");

    for (i = 0; i < edgeCount && selectedEdges < n - 1; i++)
    {
        int root1 = find(parent, edges[i].source);
        int root2 = find(parent, edges[i].destination);

        if (root1 != root2)
        {
            printf("City %d - City %d : Road Cost = %d\n",
                   edges[i].source + 1,
                   edges[i].destination + 1,
                   edges[i].cost);

            totalCost += edges[i].cost;
            unionSets(parent, root1, root2);
            selectedEdges++;
        }
    }

    printf("\nMinimum Total Road Construction Cost = %d\n", totalCost);

    return 0;
}