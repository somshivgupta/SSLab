#ifndef FUNCTION
#define FUNCTION

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include "./Record.h"

int add_student(struct stud add_stud) {
	const char* filename = "Student.txt";
	printf("File Open\n");	
	int fd = open(filename, O_WRONLY|O_APPEND,0666);
	if(fd == -1) {
		printf("Error while Adding Student");
		return -1;
	}
	printf("Exected\n");
	write(fd, &add_stud, sizeof(add_stud));
	return 0;
}

int add_faculty(struct facu add_fac) {
	const char* filename = "Faculty.txt";
	int fd = open(filename, O_CREAT|O_WRONLY|O_APPEND,0666);
	if(fd == -1) {
		perror("Error while Adding Faculty");
		return 0;
	}
	
	write(fd, &add_fac, sizeof(add_fac));
	return 0;
}

int add_Course(struct course add_cou) {
	const char* filename = "Course.txt";
	int fd = open(filename, O_WRONLY|O_APPEND,0666);
	if(fd == -1) {
		perror("Error while Adding Course");
		return 0;
	}
	
	write(fd, &add_cou, sizeof(add_cou));
	return 0;
}

int modify_status_student(struct stud upd_stud){
    struct stud buff_stud;
    const char* fileName="Student.txt";
    int fd=open(fileName, O_WRONLY,0666);
    if(fd == -1){
        printf("Error changing status of Student\n");
        return 0;
    }
    int fd2 = read(fd,&buff_stud,sizeof(buff_stud));
    while(fd2 != -1){
        if(strcmp(buff_stud.rollno,upd_stud.rollno)==0){
            lseek(fd,-1*sizeof(buff_stud),SEEK_CUR);
            write(fd,&upd_stud,sizeof(upd_stud));
            return 1;
        }
    }
    return 0;
}


int searchStudent(const char* inp_roll) {
	const char* fname = "Student.txt";
	int fd = open(fname, O_RDONLY|O_CREAT, 0666);
	if(fd == -1) {
		printf("Not able to open a file");
		return -1;
	}
	
	struct stud chk_stu;
	while(read(fd, &chk_stu, sizeof(chk_stu)) > 0) {
		int s1 = strcmp(chk_stu.rollno, inp_roll);
		if(s1 == 0) {
			//duplicate exists
			return 0;
		}
	}
	
	return 1;
}

int searchFaculty(const char* input_ID){
    const char* fname="Faculty.txt";
    int fd = open(fname,O_RDONLY|O_CREAT,0666);
    if(fd ==-1) {
        printf("Unable to access Faculty database\n");
        return -1;
    }
    
    struct facu chk_facul;
    while(read(fd, &chk_facul, sizeof(chk_facul))>0){
    	int s1 = strcmp(chk_facul.faculty_ID,input_ID);
        if(s1 == 0){
            //duplicate exists
            return 0;
        }
    }
    //no duplicate exists
    return 1;
}

int searchActiveCourse(const char* inputCourseCode){
    const char* fileName="Courses.txt";
    int fd=open(fileName,O_RDONLY|O_CREAT,0666);
    if(fd==-1){
        printf("Unable to access Course database\n");
        return -1;
    }
    struct course chk_cour;
    while(read(fd, &chk_cour, sizeof(chk_cour))>0){
        if(strcmp(chk_cour.course_code,inputCourseCode)==0 &&
            chk_cour.status==1){
            //duplicate exists
            return 0;
        }
    }
    //no duplicate exists
    return 1;
}
			
int modify_status_facilty(struct facu upd_facul){
    struct facu buff_facul;
    const char* fileName="Faculty.txt";
    int fd=open(fileName, O_WRONLY,0666);
    if(fd == -1){
        printf("Error changing status of faculty\n");
        return 0;
    }
    
    while(read(fd,&buff_facul,sizeof(buff_facul)) > 0){
        if(strcmp(buff_facul.faculty_ID,upd_facul.faculty_ID)==0){
            lseek(fd,-1*sizeof(buff_facul),SEEK_CUR);
            write(fd, &upd_facul ,sizeof(upd_facul));
            return 1;
        }
    }
    return 0;
}

int removeCourse(const char* rmv_cur) {
	struct course cour;
	const char* filename = "Course.txt";
	int fd = open(filename, O_RDWR,0666);
	if(fd == -1) {
		printf("Error While Removing Course\n");
		return 0;
	}
	
	while(read(fd, &cour, sizeof(cour)) > 0) {
		int sc = strcmp(cour.course_code, rmv_cur);
		if(sc == 0) {
			cour.status = 0;
			lseek(fd, -1*sizeof(cour),SEEK_CUR);
			write(fd, &rmv_cur, sizeof(rmv_cur));
			return 1;
		}
	}
	
	return 0;
}

#endif
