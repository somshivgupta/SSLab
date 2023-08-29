#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main() {
    int fd;
    char buffer[256];

    // Open a file for reading and writing
    fd = open("ques16_file.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Perform write locking
    struct flock lock;
    lock.l_type = F_WRLCK;    // Write lock
    lock.l_whence = SEEK_SET; // Start from the beginning of the file
    lock.l_start = 0;         // Start locking from the beginning
    lock.l_len = 0;           // Lock the entire file

    // Attempt to acquire the write lock
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl write lock");
        exit(EXIT_FAILURE);
    }

    printf("Write lock acquired. Press Enter to release it.\n");
    getchar(); // Wait for user input

    // Release the write lock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl unlock");
        exit(EXIT_FAILURE);
    }
    printf("Write lock released.\n");

    // Perform read locking
    lock.l_type = F_RDLCK; // Read lock

    // Attempt to acquire the read lock
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl read lock");
        exit(EXIT_FAILURE);
    }

    printf("Read lock acquired. Press Enter to release it.\n");
    getchar(); // Wait for user input

    // Release the read lock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl unlock");
        exit(EXIT_FAILURE);
    }
    printf("Read lock released.\n");

    close(fd);
    return 0;
}
