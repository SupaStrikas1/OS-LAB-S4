// FCFS Disk Scheduling Algorithm

#include <stdio.h>
#include <stdlib.h>

int FCFS(int requests[], int numRequests, int initialHeadPosition)
{
    int totalHeadMovement = 0;
    int currentHeadPosition = initialHeadPosition;

    for (int i = 0; i < numRequests; i++)
    {
        totalHeadMovement += abs(requests[i] - currentHeadPosition);
        currentHeadPosition = requests[i];
    }

    return totalHeadMovement;
}

int main()
{
    int numRequests, initialHeadPosition;

    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    int requests[numRequests];

    printf("Enter the disk requests:\n");
    for (int i = 0; i < numRequests; i++)
    {
        scanf("%d", &requests[i]);
    }

    printf("\nEnter the initial head position: ");
    scanf("%d", &initialHeadPosition);

    int totalHeadMovement = FCFS(requests, numRequests, initialHeadPosition);

    printf("\nTotal head movement: %d\n", totalHeadMovement);

    return 0;
}
