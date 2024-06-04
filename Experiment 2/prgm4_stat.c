// Reading the file status – stat()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

char *formatdatetime(char *str, time_t val)
{
    strftime(str, 36, "%d.%m.%Y %H:%M:%S", localtime(&val));
    return str;
}

void main()
{
    struct stat filestat;
    char file[50];
    char buffer[50];

    printf("Enter file name : ");
    scanf("%s", file);

    if (stat(file, &filestat) == -1)
    {
        printf("Error");
        exit(EXIT_FAILURE);
    }
    printf("\nFile Size: %ld bytes\n", filestat.st_size);
    printf("No. of Links: %ld\n", filestat.st_nlink);
    printf("Time of Last Access: %s\n", formatdatetime(buffer, filestat.st_atime));
    printf("Time of Last Modification: %s\n", formatdatetime(buffer, filestat.st_mtime));
}