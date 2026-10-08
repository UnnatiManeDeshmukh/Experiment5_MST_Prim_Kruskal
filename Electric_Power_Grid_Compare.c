#include <stdio.h>

#define MAX 20
#define INF 999

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

int prim(int graph[MAX][MAX], int n)
{
    int selected[MAX] = {0};
    int edges = 0;
    int totalCost = 0;
    int min, x = 0, y = 0;
    int i, j;

    selected[0] = 1;

    printf("\n--- Prim's Algorithm ---\n");

    while (edges < n - 1)
    {
        min = INF;

        for (i = 0; i < n; i++)
        {
            if (selected[i])
            {
                for (j = 0; j < n; j++)
                {
                    if (!selected[j] && graph[i][j] < min)
                    {
                        min = graph[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }

        printf("Power Station %d - Power Station %d : Cost = %d\n",
               x + 1, y + 1, min);

        totalCost += min;
        selected[y] = 1;
        edges++;
    }

    printf("Prim's Minimum Cost = %d\n", totalCost);

    return totalCost;
}

int kruskal(int graph[MAX][MAX], int n)
{
    struct Edge edges[MAX * MAX];
    int edgeCount = 0;
    int parent[MAX];
    int selectedEdges = 0;
    int totalCost = 0;
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (graph[i][j] != 0)
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

    printf("\n--- Kruskal's Algorithm ---\n");

    for (i = 0; i < edgeCount && selectedEdges < n - 1; i++)
    {
        int root1 = find(parent, edges[i].source);
        int root2 = find(parent, edges[i].destination);

        if (root1 != root2)
        {
            printf("Power Station %d - Power Station %d : Cost = %d\n",
                   edges[i].source + 1,
                   edges[i].destination + 1,
                   edges[i].cost);

            totalCost += edges[i].cost;
            unionSets(parent, root1, root2);
            selectedEdges++;
        }
    }

    printf("Kruskal's Minimum Cost = %d\n", totalCost);

    return totalCost;
}

int main()
{
    int n, i, j;
    int graph[MAX][MAX];
    int primCost, kruskalCost;

    printf("Enter number of power stations: ");
    scanf("%d", &n);

    printf("\nEnter the power connection cost matrix:\n");
    printf("(Enter 0 if there is no direct connection)\n\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);

            if (graph[i][j] == 0)
                graph[i][j] = INF;
        }
    }

    primCost = prim(graph, n);

    /* Convert diagonal/INF values back for Kruskal */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
                graph[i][j] = 0;
        }
    }

    kruskalCost = kruskal(graph, n);

    printf("\n--- Comparison ---\n");
    printf("Prim's Algorithm Minimum Cost    = %d\n", primCost);
    printf("Kruskal's Algorithm Minimum Cost = %d\n", kruskalCost);

    if (primCost == kruskalCost)
        printf("Both algorithms produce the same minimum cost.\n");
    else
        printf("The minimum costs are different.\n");

    return 0;
}