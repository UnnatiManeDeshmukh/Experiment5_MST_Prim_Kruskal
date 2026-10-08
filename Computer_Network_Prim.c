#include <stdio.h>

#define INF 999

int main()
{
    int n, i, j;
    int graph[20][20];
    int selected[20] = {0};
    int edges = 0, totalCost = 0;
    int min, x = 0, y = 0;

    printf("Enter number of computers: ");
    scanf("%d", &n);

    printf("\nEnter the cost matrix:\n");
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

    selected[0] = 1;

    printf("\nMinimum Cost Spanning Tree using Prim's Algorithm:\n");

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

        printf("Computer %d - Computer %d : Cable Cost = %d\n",
               x + 1, y + 1, min);

        totalCost += min;
        selected[y] = 1;
        edges++;
    }

    printf("\nMinimum Total Cable Cost = %d\n", totalCost);

    return 0;
}