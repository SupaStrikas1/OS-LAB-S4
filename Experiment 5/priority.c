// Priority CPU Scheduling Algorithm

#include <stdio.h>

void findAvgT(int processes[], int n, int bt[], int at[], int p[], int wt[], int tat[])
{
    int total_wt = 0, total_tat = 0;

    printf("\nProcesses\tArrival Time\tBurst Time\tPriority\tTurn-Around Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i], at[i], bt[i], p[i], tat[i], wt[i]);
    }

    printf("\nAverage waiting time = %.2f\n", (float)total_wt / (float)n);
    printf("Average turn around time = %.2f\n", (float)total_tat / (float)n);
}

void priority(int processes[], int n, int bt[], int at[], int p[])
{
    int completed = 0, time = 0, minm = 10000, shortest = 0;
    int check = 0;
    int r_p[n], wt[n], tat[n];

    for (int i = 0; i < n; i++)
        r_p[i] = p[i];

    while (completed != n)
    {
        for (int j = 0; j < n; j++)
        {
            if ((at[j] <= time) && (r_p[j] < minm) && r_p[j] > 0)
            {
                minm = r_p[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0)
        {
            time++;
            continue;
        }

        time += bt[shortest];
        tat[shortest] = time - at[shortest];
        wt[shortest] = tat[shortest] - bt[shortest];
        completed++;
        r_p[shortest] = 0;
        minm = 10000;
        check = 0;
    }

    findAvgT(processes, n, bt, at, p, wt, tat);
}

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burst_time[n];
    int arrival_time[n];
    int priorityArr[n];

    for (int i = 0; i < n; i++)
    {
        processes[i] = i + 1;
        printf("Enter arrival time, burst time and priority for Process %d: ", i + 1);
        scanf("%d%d%d", &arrival_time[i], &burst_time[i], &priorityArr[i]);
    }

    priority(processes, n, burst_time, arrival_time, priorityArr);

    return 0;
}
