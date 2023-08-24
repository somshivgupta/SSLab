#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open the file in read-write mode
    int fd = open("test_ques_10.txt", O_RDWR | O_CREAT);
    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    }

    // Write 10 bytes to the file
    char data1[] = "abcdefghij";
    int bytes_written1 = write(fd, data1, sizeof(data1));
    if (bytes_written1 == -1) {
        perror("Error writing to the file");
        close(fd);
        return 1;
    }

    // Move the file pointer by 10 bytes using lseek
    printf("%d", SEEK_CUR);
    printf("\n");
    int seek_offset = lseek(fd, 10, SEEK_CUR);
    printf("Pointer of this is: %d", seek_offset);
    if (seek_offset == -1) {
        perror("Error seeking in the file");
        close(fd);
        return 1;
    }

    // Write another 10 bytes to the file
    char data2[] = "0123456789";
    int bytes_written2 = write(fd, data2, sizeof(data2));
    if (bytes_written2 == -1) {
        perror("Error writing to the file");
        close(fd);
        return 1;
    }

    // Close the file
    close(fd);
    return 0;
}

