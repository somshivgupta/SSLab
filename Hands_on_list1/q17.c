#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main() {
  struct flock lock;
  int fd=open("fl.txt", O_RDWR);
  if(fd==-1){
    perror("Error");
    return 1;
  }
  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = 0;
  int buf;
  lock.l_type=F_RDLCK;
  printf("Read lock set\n");
  fcntl(fd, F_SETLKW, &lock);
  int r=read(fd, &buf, sizeof(int));
  if(r==-1){
    perror("Unable to read");
    return 1;
  }
  lseek(fd, -4, SEEK_CUR);
  printf("Read ticket no: %d\n", buf);
  buf++;
  lock.l_type=F_WRLCK;
  fcntl(fd, F_SETLKW, &lock);
  printf("Write lock set\n");
  int wv = write(fd, &buf, sizeof(int));
  if(wv ==-1){
    perror("Error in writing");
    return 1;
  }
  lseek(fd, -4, SEEK_CUR);
  int rv = read(fd, &buf, sizeof(int));
  if(rv==-1){
    perror("Unable to Read");
    return 1;
  }
  printf("Read after writing: %d\n", buf);
  printf("Press return to unlock...");
  getchar();
  lock.l_type=F_UNLCK;
  fcntl(fd, F_SETLKW, &lock);
  close(fd);
  return 0;
}
