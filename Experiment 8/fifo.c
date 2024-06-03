#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_REFERENCES 50

bool isPageInFrame(int page, int frames[], int numFrames)
{
    for (int i = 0; i < numFrames; i++)
    {
        if (frames[i] == page)
        {
            return true;
        }
    }
    return false;
}

int findReplacementIndex(int nextIndex, int numFrames)
{
    return nextIndex % numFrames;
}

void fifoPageReplacement(int pages[], int numPages, int numFrames)
{
    int frames[MAX_FRAMES];
    int nextIndex = 0;
    int pageFaults = 0;

    for (int i = 0; i < numFrames; i++)
    {
        frames[i] = -1;
    }

    for (int i = 0; i < numPages; i++)
    {
        int page = pages[i];

        if (!isPageInFrame(page, frames, numFrames))
        {
            int replaceIndex = findReplacementIndex(nextIndex, numFrames);
            frames[replaceIndex] = page;
            nextIndex++;
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
        else
        {
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
        }
    }

    printf("\n\nTotal page faults: %d\n", pageFaults);
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

    fifoPageReplacement(pages, numPages, numFrames);

    return 0;
}