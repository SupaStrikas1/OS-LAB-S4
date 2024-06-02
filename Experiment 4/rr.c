// Round-Robin CPU Scheduling Algorithm

#include <stdio.h>

void findAvgT(int processes[], int n, int bt[], int at[], int wt[], int tat[])
{
    int total_wt = 0, total_tat = 0;

    printf("\nProcesses\tArrival Time\tBurst Time\tTurn-Around Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i], at[i], bt[i], tat[i], wt[i]);
    }

    printf("\nAverage waiting time = %.2f\n", (float)total_wt / (float)n);
    printf("Average turn around time = %.2f\n", (float)total_tat / (float)n);
}

void roundRobin(int processes[], int n, int bt[], int at[], int quantum)
{
    int r_bt[n], wt[n], tat[n];
    for (int i = 0; i < n; i++)
        r_bt[i] = bt[i];

    int time = 0, completed = 0;
    while (completed != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (r_bt[i] > 0)
            {
                if (r_bt[i] > quantum && at[i] <= time)
                {
                    time += quantum;
                    r_bt[i] -= quantum;
                }
                else if (at[i] <= time)
                {
                    time += r_bt[i];
                    tat[i] = time - at[i];
                    wt[i] = tat[i] - bt[i];
                    r_bt[i] = 0;
                    completed++;
                }
                else
                {
                    time++;
                }
            }
        }
    }

    findAvgT(processes, n, bt, at, wt, tat);

}

int main()
{
    int n, quantum;

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

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    roundRobin(processes, n, burst_time, arrival_time, quantum);

    return 0;
}
