// Bankers Algorithm for Deadlock Avoidance.

#include <stdio.h>
#include <stdbool.h>

int isSafeState(int n, int m, int processes[], int avail[], int max[][m], int alloc[][m], int need[][m], int safeSequence[n])
{
    bool finish[n];
    int work[m];

    for (int i = 0; i < m; i++)
    {
        work[i] = avail[i];
    }

    for (int i = 0; i < n; i++)
    {
        finish[i] = false;
    }

    int count = 0;
    while (count < n)
    {
        bool found = false;
        for (int p = 0; p < n; p++)
        {
            if (!finish[p])
            {
                int flag = 1;
                for (int r = 0; r < m; r++)
                {
                    if (need[p][r] > work[r])
                    {
                        flag = 0;
                        break;
                    }
                }

                if (flag == 1)
                {
                    for (int r = 0; r < m; r++)
                    {
                        work[r] += alloc[p][r];
                    }

                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found)
        {
            return 0;
        }
    }

    return 1;
}

void bankerAlgorithm(int n, int m, int processes[], int avail[], int max[][m], int alloc[][m], int need[][m], int safeSequence[n])
{
    if (isSafeState(n, m, processes, avail, max, alloc, need, safeSequence))
    {
        printf("\nSystem is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < n; i++)
        {
            printf(" P%d ", safeSequence[i]);
        }
        printf("\nAllocating Resorces ...\n");
    }
    else
    {
        printf("\nSystem is not in a safe state. Possible deadlock. Cannot Allocate resources.\n");
    }
}

int main()
{
    int n, m;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    int processes[n];
    int avail[m];
    int max[n][m];
    int alloc[n][m];
    int need[n][m];
    int safeSequence[n];

    for (int i = 0; i < n; i++)
    {
        processes[i] = i;
    }

    printf("\nEnter the available resources:\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }

    printf("\nEnter the maximum resource matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter the allocation matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    bankerAlgorithm(n, m, processes, avail, max, alloc, need, safeSequence);

    return 0;
}
