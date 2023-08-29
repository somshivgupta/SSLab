#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

void read_lock(int lock_r);
void write_lock(int lock_r);

struct student {
    int roll_no;
    int marks;
};

void main() {
    int fd = open("file18.txt", O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
		perror("file");
		exit(1);
	}
    struct student inp1 = {1, 10};
    struct student inp2 = {2, 20};
    struct student inp3 = {3, 30};

    write(fd, &inp1, sizeof(struct student));
    write(fd, &inp2, sizeof(struct student));
    write(fd, &inp3, sizeof(struct student));

    close(fd);

    fd=open("file18.txt", O_RDONLY);
    if (fd < 0) {
		perror("file");
		exit(1);
	}
    struct student std;
    read(fd, &std, sizeof(struct student));
    printf("Roll No. : %d \n", std.roll_no);
    printf("Marks : %d \n \n", std.marks);

    read(fd, &std, sizeof(struct student));
    printf("Roll No. : %d \n", std.roll_no);
    printf("Marks : %d \n \n", std.marks);

    read(fd, &std, sizeof(struct student));
    printf("Roll No. : %d \n", std.roll_no);
    printf("Marks : %d \n \n", std.marks);

    int lock_r;
    int choice;
    lseek(fd, 0, SEEK_CUR);
    printf("Select record you want to lock: ");
    scanf("%d", &lock_r);
    close(fd);
    if(lock_r < 1 || lock_r > 3) exit(1);
    printf("Select type of lock: \nRead (1)\nWrite (2) \nChoice: ");
    scanf("%d", &choice);
    if(choice == 1) {
        read_lock(lock_r);
        exit(1);
    }
    else if(choice == 2) {
        write_lock(lock_r);
        exit(1);
    }
    else {
        printf("Wrong choice!");
    }
    close(fd);

}

void read_lock(int lock_r) {
    int fd=open("file18.txt", O_RDONLY);
    struct student std;
    lseek(fd, (lock_r - 1) * sizeof(struct student), SEEK_CUR);
    read(fd, &std, sizeof(struct student));
    printf("Roll No: %d \nMarks : %d \n", std.roll_no, std.marks);
    close(fd);
    fd=open("file18.txt", O_RDWR);
    if(fd < 0) perror("file");
    struct flock lock;
    lock.l_type=F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start =  ( lock_r - 1 ) * sizeof(struct student);
    lock.l_len = sizeof(struct student);
    printf("Waiting to acquire lock on record %d \n", std.roll_no);
    fcntl(fd, F_SETLKW, &lock);
    printf("Acquired lock on record %d \n", std.roll_no);
    printf("Press return to exit...\n");
    getchar();
    getchar();
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    printf("Exited critical section...\n");
}

void write_lock(int lock_r) {
    int fd=open("file18.txt", O_RDONLY);
    if(fd < 0) perror("file");
    struct student std;
    lseek(fd, ( lock_r  - 1) * sizeof(struct student), SEEK_CUR);
    read(fd, &std, sizeof(struct student));
    printf("Roll No: %d \nMarks : %d \n", std.roll_no, std.marks);
    close(fd);
    fd=open("file18.txt", O_RDWR);
    if(fd < 0) perror("file");
    struct flock lock;
    lseek(fd, ( lock_r  - 1) * sizeof(struct student), SEEK_CUR);
    lock.l_type=F_RDLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start=(lock_r - 1) * sizeof(struct student);
    lock.l_len = sizeof(struct student);
    printf("Waiting to acquire lock on record %d \n", std.roll_no);
    lock.l_type=F_WRLCK;
    int r=fcntl(fd, F_SETLKW, &lock);
    if(r < 0) perror("lock");
    printf("Acquired lock on record %d \n", std.roll_no);
    printf("You selected to write on this record. \nEnter new marks: ");
    int marks;
    scanf("%d", &marks);
    std.marks=marks;
    lseek(fd, -1 * sizeof(struct student), SEEK_CUR);
    write(fd, &std, sizeof(struct student));
    printf("Press return to exit...\n");
    getchar();
    getchar();
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    printf("Exited critical section...\n");
}
