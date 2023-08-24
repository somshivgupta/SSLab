#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char *filename = "question_3.txt";
    
    // Try to open the file with O_RDWR and O_EXCL flags
    int file_descriptor = open(filename, O_CREAT|O_EXCL|O_RDWR);
    
    if (file_descriptor == -1) {
        if (errno == EEXIST) {
            // File already exists, so open without O_EXCL
            file_descriptor = open(filename, O_RDWR);
            if (file_descriptor == -1) {
                perror("Error opening file");
                return 1;
            }
            printf("File opened successfully in read-write mode.\n");
        } else {
            perror("Error opening file");
            return 1;
        }
    } else {
        printf("File opened successfully with read-write mode and O_EXCL flag.\n");
    }
    
    // Perform read-write operations on the file here
    // ...
    
    close(file_descriptor);
    
    return 0;
}
