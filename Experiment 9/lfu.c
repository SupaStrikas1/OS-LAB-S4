// LFU Page Replacement Algorithm

#include <stdio.h>
#include <limits.h>

#define MAX_FRAMES 10
#define MAX_REFERENCES 50

int isPageInFrame(int page, int frames[], int numFrames)
{
    for (int i = 0; i < numFrames; i++)
    {
        if (frames[i] == page)
        {
            return i;
        }
    }
    return -1;
}

int findLFU(int freq[], int time[], int numFrames)
{
    int minFreq = INT_MAX;
    int minTime = INT_MAX;
    int pos = -1;

    for (int i = 0; i < numFrames; i++)
    {
        if (freq[i] < minFreq || (freq[i] == minFreq && time[i] < minTime))
        {
            minFreq = freq[i];
            minTime = time[i];
            pos = i;
        }
    }
    return pos;
}

void lfuPageReplacement(int pages[], int numPages, int numFrames)
{
    int frames[MAX_FRAMES];
    int freq[MAX_FRAMES];
    int time[MAX_FRAMES];
    int pageFaults = 0, currentTime = 0;

    for (int i = 0; i < numFrames; i++)
    {
        frames[i] = -1;
        freq[i] = 0;
        time[i] = 0;
    }

    for (int i = 0; i < numPages; i++)
    {
        int page = pages[i];
        int index = isPageInFrame(page, frames, numFrames);

        if (index == -1)
        {
            int replaceIndex = findLFU(freq, time, numFrames);
            frames[replaceIndex] = page;
            freq[replaceIndex] = 1;
            time[replaceIndex] = currentTime++;
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
            freq[index]++;
            time[index] = currentTime++;
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

    lfuPageReplacement(pages, numPages, numFrames);

    return 0;
}
