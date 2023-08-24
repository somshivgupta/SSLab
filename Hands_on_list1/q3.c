#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    // File path
    const char *file_path = "question_3.txt";

    // Create the file using creat() system call
    int fd = creat(file_path, 0644); // 0644 gives read and write permissions to the owner, and read permissions to others

    if (fd == -1) {
        perror("Error creating file");
    }

    printf("File created successfully with file descriptor: %d\n", fd);

    // Close the file descriptor
    close(fd);

}

