// Interprocess Communication (IPC) using Shared Memory

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

void writeData()
{
    printf("WRITER process is executing...\n");
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);

    if (shmid == -1)
    {
        perror("shmget failed");
        exit(1);
    }

    char *shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    printf("Write Data: ");
    fgets(shm_ptr, SHM_SIZE, stdin);

    printf("Data written to shared memory: %s\n", shm_ptr);

    shmdt(shm_ptr);
}

void readData()
{
    printf("READER process is executing...\n");
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666);

    if (shmid == -1)
    {
        perror("shmget failed");
        exit(1);
    }

    char *shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    printf("Data read from shared memory: %s\n", shm_ptr);

    shmdt(shm_ptr);

    shmctl(shmid, IPC_RMID, NULL);
}

int main()
{
    writeData();
    readData();
    return 0;
}
