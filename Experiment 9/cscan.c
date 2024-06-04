// C-SCAN Disk Scheduling Algorithm 

#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int CSCAN(int requests[], int numRequests, int initialHeadPosition, int diskSize)
{
    int totalHeadMovement = 0;
    int currentHeadPosition = initialHeadPosition;
    int requestsLeft[numRequests], requestsRight[numRequests];
    int leftCount = 0, rightCount = 0;

    for (int i = 0; i < numRequests; i++)
    {
        if (requests[i] < initialHeadPosition)
        {
            requestsLeft[leftCount++] = requests[i];
        }
        else
        {
            requestsRight[rightCount++] = requests[i];
        }
    }

    sort(requestsLeft, leftCount);
    sort(requestsRight, rightCount);

    for (int i = 0; i < rightCount; i++)
    {
        totalHeadMovement += abs(requestsRight[i] - currentHeadPosition);
        currentHeadPosition = requestsRight[i];
    }

    if (rightCount > 0)
    {
        totalHeadMovement += (diskSize - 1 - currentHeadPosition);
        currentHeadPosition = 0;
    }

    for (int i = 0; i < leftCount; i++)
    {
        totalHeadMovement += abs(requestsLeft[i] - currentHeadPosition);
        currentHeadPosition = requestsLeft[i];
    }

    return totalHeadMovement;
}

int main()
{
    int numRequests, initialHeadPosition, diskSize;

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

    printf("\nEnter the disk size (number of cylinders): ");
    scanf("%d", &diskSize);

    int totalHeadMovement = CSCAN(requests, numRequests, initialHeadPosition, diskSize);

    printf("\nTotal head movement: %d\n", totalHeadMovement);

    return 0;
}
