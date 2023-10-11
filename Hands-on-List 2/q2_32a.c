/*
============================================================================
Name : 32a.c
Author : Som Shiv Gupta
Description : Write a program to implement semaphore to protect any critical section.    
a. rewrite the ticket number creation program using semaphore  
   
Date: 11th Oct, 2023.
============================================================================
*/

#include <sys/ipc.h>   
#include <sys/sem.h>   
#include <sys/types.h> 
#include <sys/stat.h>  
#include <fcntl.h>     
#include <unistd.h>    
#include <stdio.h>     

int main(void)
{
    char *ticketFile = "ticket.txt";    

    int fd = open(ticketFile, O_CREAT | O_RDWR, S_IRWXU);
    if (fd == -1)
    {
        perror("Error while opening the ticket file!");
        return 0;
    }

    union semun
    {
        int val;               
        struct semid_ds *buf;  
        unsigned short *array; 
        struct seminfo *__buf; 
    } sem_set;

    int semKey = ftok(".", 1);
    if (semKey == -1)
    {
        perror("Error while computing key!");
        return 0;
    }

    int sem_id = semget(semKey, 1, 0);
    if (sem_id == -1)
    {
        sem_id = semget(semKey, 1, IPC_CREAT | 0777);
        if (sem_id == -1)
        {
            perror("Error while creating semaphore!");
            return 0;
        }

        sem_set.val = 1; 
        int sem_ctl_s = semctl(sem_id, 0, SETVAL, sem_set);
        if (sem_ctl_s == -1)
        {
            perror("Error while initializing a binary sempahore!");
            _exit(1);
        }
    }

    struct sembuf sema; 
    sema.sem_num = 0;
    sema.sem_flg = 0;

    printf("Press enter to obtain lock on the critical section\n");
    getchar();
   
    sema.sem_op = -1;
    int sema_s = semop(sem_id, &sema, 1);
    if (sema_s == -1)
    {
        perror("Error while operating on semaphore!");
        return 0;
    }
    
    printf("Obtained lock on critical section!\n");
    printf("Now entering critical section!\n");

    int data;
    int reads = read(fd, &data, sizeof(data));
    if (reads == -1)
    {
        perror("Error while reading from ticket file!");
        return 0;
    }
    
    else if (reads == 0) 
        data = 1;
        
    else
    {
        data += 1;
        
        int lseek_off;
        lseek_off = lseek(fd, 0, SEEK_SET);
        if (lseek_off == -1)
        {
            perror("Error while seeking!");
            return 0;
        }
    }

    int writes = write(fd, &data, sizeof(data));
    if (writes == -1)
    {
        perror("Error while writing to ticket file!");
        return 0;
    }

    printf("Your ticker number is: %d\n", data);

    printf("Press enter to exit from critical section!\n");
    getchar();

    sema.sem_op = 1;
    int sem_ops = semop(sem_id, &sema, 1);
    if (sem_ops == -1)
    {
        perror("Error while operating on semaphore!");
        return 0;
    }
    close(fd);
}
