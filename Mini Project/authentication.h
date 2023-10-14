#ifndef AUTHENTICATION
#define AUTHENTICATION
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "./Record.h"

int Auth_of_Admin(const char* UserId, const char* password){
    const char* fileName="Admin.txt";
    int fd=open(fileName,O_RDONLY,0666);
    if(fd==-1){
        printf("Unable to authenticate admin\n");
        return -1;
    }
    struct admin chk_admin;
    while(read(fd,&chk_admin,sizeof(chk_admin))>0){
        if(strcmp(chk_admin.user_id,UserId)==0 &&
           strcmp(chk_admin.pass, password)==0){
            return 1;
           }
    }
    return 0;
}

int Auth_of_Facu(const char* inputFacUID,
                      const char* inputPassword){
    const char* fname="Faculty.txt";
    int fd=open(fname,O_RDONLY,0666);
    if(fd==-1){
        printf("Unable to authenticate faculty\n");
        return -1;
    }
    struct facu facultychk;
    while(read(fd,&facultychk,sizeof(facultychk))>0){
        if(strcmp(facultychk.faculty_ID,inputFacUID)==0 &&
           strcmp(facultychk.pass,inputPassword)==0){
            return 1;
           }
    }
    return 0;
}

int Auth_of_Stud(const char* roll,
                      const char* password){
    const char* fname="Student.txt";
    int fd=open(fname,O_RDONLY,0666);
    if(fd==-1){
        printf("Unable to authenticate student\n");
        return -1;
    }
    struct stud chk_stud;
    while(read(fd,&chk_stud,sizeof(chk_stud))>0){
        if(strcmp(chk_stud.rollno, roll)==0 &&
           strcmp(chk_stud.password,password)==0 &&
           chk_stud.status==1){
            return 1;
           }
    }
    return 0;
}

#endif
