#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    struct stat file_info;

    if (stat(filename, &file_info) == -1) {
        perror("Error");
        return 1;
    }

    printf("File Information for: %s\n", filename);
    printf("a. Inode: %ld\n", (long)file_info.st_ino);
    printf("b. Number of Hard Links: %ld\n", (long)file_info.st_nlink);
    printf("c. UID: %d\n", file_info.st_uid);

    struct passwd *pwd = getpwuid(file_info.st_uid);
    if (pwd != NULL) {
        printf("   Username: %s\n", pwd->pw_name);
    } else {
        printf("   Username not found\n");
    }

    printf("d. GID: %d\n", file_info.st_gid);

    struct group *grp = getgrgid(file_info.st_gid);
    if (grp != NULL) {
        printf("   Group Name: %s\n", grp->gr_name);
    } else {
        printf("   Group Name not found\n");
    }

    printf("e. Size: %ld bytes\n", (long)file_info.st_size);
    printf("f. Block Size: %ld bytes\n", (long)file_info.st_blksize);
    printf("g. Number of Blocks: %ld\n", (long)file_info.st_blocks);

    printf("h. Time of Last Access: %s", ctime(&file_info.st_atime));
    printf("i. Time of Last Modification: %s", ctime(&file_info.st_mtime));
    printf("j. Time of Last Change: %s", ctime(&file_info.st_ctime));

    return 0;
}

