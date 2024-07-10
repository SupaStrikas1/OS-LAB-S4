// FCFS CPU Scheduling Algorithm

#include <stdio.h>

void findAvgT(int processes[], int n, int bt[], int at[], int wt[], int tat[])
{
    int total_wt = 0, total_tat = 0;

    printf("\nProcesses\tArrival Time\tBurst Time\tTurn-Around Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i], at[i], bt[i], tat[i], wt[i]);
    }

    printf("\nAverage waiting time = %.2f\n", (float)total_wt / (float)n);
    printf("Average turn around time = %.2f\n", (float)total_tat / (float)n);
}

void fcfs(int processes[], int n, int bt[], int at[])
{
    int completed = 0, time = at[0], tat[n], wt[n];

    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time)
            {
                time += bt[i];
                tat[i] = time - at[i];
                wt[i] = tat[i] - bt[i];
                completed++;
            }
            else
            {
                time = at[i];
                time += bt[i];
                tat[i] = time - at[i];
                wt[i] = tat[i] - bt[i];
                completed++;
            }
        }
    }

    findAvgT(processes, n, bt, at, wt, tat);
}

int main()
{
    int n, temp;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burst_time[n];
    int arrival_time[n];

    for (int i = 0; i < n; i++)
    {
        processes[i] = i + 1;
        printf("Enter arrival time and burst time for Process %d: ", i + 1);
        scanf("%d%d", &arrival_time[i], &burst_time[i]);
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arrival_time[j] > arrival_time[j + 1])
            {
                temp = arrival_time[j];
                arrival_time[j] = arrival_time[j + 1];
                arrival_time[j + 1] = temp;

                temp = burst_time[j];
                burst_time[j] = burst_time[j + 1];
                burst_time[j + 1] = temp;

                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    fcfs(processes, n, burst_time, arrival_time);

    return 0;
}
