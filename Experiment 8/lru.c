#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10 
#define MAX_REFERENCES 50 

int frames[MAX_FRAMES];  
int counter[MAX_FRAMES]; 

int findLRU()
{
    int max = counter[0];
    int lru_frame = 0;

    for (int i = 1; i < MAX_FRAMES; i++)
    {
        if (counter[i] > max)
        {
            max = counter[i];
            lru_frame = i;
        }
    }

    return lru_frame;
}

void lruPageReplacement(int pages[], int numPages, int numFrames)
{
    int pageFaults = 0;

    for (int i = 0; i < numFrames; i++)
    {
        frames[i] = -1; 
        counter[i] = 0; 
    }

    for (int i = 0; i < numPages; i++)
    {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < numFrames; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                printf("\nPage %d - Page Hit. Frames: ", page);
                for (int j = 0; j < numFrames; j++)
                {
                    if (frames[j] != -1)
                    {
                        printf("%d ", frames[j]);
                    }
                    else
                    {
                        printf("- ");
                    }
                }
                break;
            }
        }

        if (!found)
        {
            int lru_frame = findLRU();
            frames[lru_frame] = page;
            counter[lru_frame] = 0;
            pageFaults++;
            printf("\nPage %d - Page Fault. Frames: ", page);
            for (int j = 0; j < numFrames; j++)
            {
                if (frames[j] != -1)
                {
                    printf("%d ", frames[j]);
                }
                else
                {
                    printf("- ");
                }
            }
        }

        for (int j = 0; j < numFrames; j++)
        {
            counter[j]++;
        }

        for (int j = 0; j < numFrames; j++)
        {
            if (frames[j] == page)
            {
                counter[j] = 0;
                break;
            }
        }
    }

    printf("\n\nTotal Page Faults: %d\n", pageFaults);
}

int main()
{
    int numFrames, numPages;
    int pages[MAX_REFERENCES];

    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    printf("Enter the number of page references: ");
    scanf("%d", &numPages);

    printf("Enter the page references:\n");
    for (int i = 0; i < numPages; i++)
    {
        scanf("%d", &pages[i]);
    }

    lruPageReplacement(pages, numPages, numFrames);

    return 0;
}
