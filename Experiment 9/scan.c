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

int SCAN(int requests[], int numRequests, int initialHeadPosition, int diskSize, int direction)
{
    int totalHeadMovement = 0;
    int currentHeadPosition = initialHeadPosition;
    int requestsLeft[numRequests], requestsRight[numRequests];
    int leftCount = 0, rightCount = 0;

    if (direction == 0)
    {
        requestsLeft[leftCount++] = 0;
    }
    else
    {
        requestsRight[rightCount++] = diskSize - 1;
    }

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

    int flag = 2;
    while (flag--)
    {

        if (direction == 0)
        {
            for (int i = leftCount - 1; i >= 0; i--)
            {
                totalHeadMovement += abs(requestsLeft[i] - currentHeadPosition);
                currentHeadPosition = requestsLeft[i];
            }
            direction = 1;
        }

        else
        {
            for (int i = 0; i < rightCount; i++)
            {
                totalHeadMovement += abs(requestsRight[i] - currentHeadPosition);
                currentHeadPosition = requestsRight[i];
            }
            direction = 0;
        }
    }
    return totalHeadMovement;
}

int main()
{
    int numRequests, initialHeadPosition, diskSize, direction = 0;

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

    int totalHeadMovement = SCAN(requests, numRequests, initialHeadPosition, diskSize, direction);

    printf("\nTotal head movement: %d\n", totalHeadMovement);

    return 0;
}
