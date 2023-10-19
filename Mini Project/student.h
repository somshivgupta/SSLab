#include <stdio.h>	// Import for `printf` & `perror` functions
#include <stdlib.h>	// Import for `atoi` function
#include <string.h>	// Import for string functions
#include <unistd.h>	// Import for `fork`, `fcntl`, `read`, `write`, `lseek, `_exit` functions
#include <fcntl.h>	// Import for `fcntl` functions
#include <sys/types.h>	// Import for `socket`, `bind`, `listen`, `accept`, `fork`, `lseek` functions
#include <errno.h>	// Import for `errno` variable
#include <sys/socket.h>	// Import for `socket`, `bind`, `listen`, `accept` functions
#include <netinet/in.h>	// Import for `sockaddr_in` stucture
#include <stdbool.h>
#include "./constant.h"
#include "./default.h"
#include "../Structures/courseStudent.h"
#include "../Structures/student.h"
#include "../Structures/course.h"
#include "../Structures/faculty.h"

#ifndef STUDENT_FUNCTIONS
#define STUDENT_FUNCITONS

bool offeringCoursesToStudent(int sockfd);
bool addStudentCourses(int sockfd,int studentID);
bool dropCourse(int sockfd, int studentID);
bool enrolledCourse(int sockfd,int student);
bool changeStudentPassword(int sockfd,int studentID);

bool studentHandler(int sockfd)
{
	int studentID;
	if((studentID = loginHandler(2,sockfd)) != -1)
	{
		if(studentID == -99)
		{
			// If Username or password didnt match
			printf("\n Data not found !! -99\n");
			write(sockfd, LOGOUT, strlen(LOGOUT));
			return false;
				
		}
		printf("\nInto student.h\n");
		int readBytes, writeBytes;			// Number of bytes written to / read from the socket 
		char readBuffer[1024], writeBuffer[1024];	// Buffer for reading from / writing to the client 
		bzero(writeBuffer, sizeof(writeBuffer));
		strcpy(writeBuffer,"Welcome Student!!");
		
		while(1)
		{
			strcat(writeBuffer, "\n");
			strcat(writeBuffer, STUDENT_MENU);
			writeBytes = write(sockfd, writeBuffer, strlen(writeBuffer));
			if (writeBytes == -1)
			{
				perror("Error while writing STUDENT_MENU to client!");
				return false;
			}
			
			bzero(writeBuffer, sizeof(writeBuffer));
			
			readBytes = read(sockfd, readBuffer, sizeof(readBuffer));
			if (readBytes == -1)
			{
				perror("Error while reading client's choice for ADMIN_MENU");
				return false;
			}
			
			int choice = atoi(readBuffer);
			printf("\n Student Choice is %d",choice);
			switch(choice)
			{
				case 1:
					offeringCoursesToStudent(sockfd);
					break;
				case 2:
					addStudentCourses(sockfd, studentID);
					break;
				case 3:
					dropCourse(sockfd, studentID);
					break;
				case 4:
					enrolledCourse(sockfd, studentID);
					break;
				case 5:
					changeStudentPassword(sockfd, studentID);
					break;
				default:
					writeBytes = write(sockfd, LOGOUT, strlen(LOGOUT));
                			return false;
			}
		}
	}
	else
	{
		// Student LOGIN FAILED
        	return false;
	}
	return true;
}

// ---------------------------------------------------------------------------------------------
// ------------------------------ OFFERS COURSES -----------------------------------------------
// ---------------------------------------------------------------------------------------------
bool offeringCoursesToStudent(int sockfd)
{
	ssize_t readBytes, writeBytes;
	char readBuffer[1000], writeBuffer[1000];
	char temp[1000];
	
	struct Course course;
	
	int courseFD = open(COURSE_FILE, O_RDONLY);
	if(courseFD == -1)
	{
		// course File doesn't exist
		bzero(writeBuffer, sizeof(writeBuffer));
		strcpy(writeBuffer, ID_DOESNT_EXIT);
		strcat(writeBuffer, "^");
		writeBytes = write(sockfd, writeBuffer, strlen(writeBuffer));
		if (writeBytes == -1)
		{
		    perror("Error while writing ID_DOESNT_EXIT message to client!");
		    return false;
		}
		readBytes = read(sockfd, readBuffer, sizeof(readBuffer)); // Dummy read
		return false;
	}
	
	// Getting lock
	struct flock lock = {F_RDLCK, SEEK_SET, 0, 0, getpid()};
	int lockstatus = fcntl(courseFD, F_SETLKW, &lock);
	if (lockstatus == -1)
    	{
        	perror("Error while obtaining read lock on the course file!");
        	return false;
    	}
    	bzero(temp, sizeof(temp));
    	strcat(temp, "You can choose :\n");
    	while(read(courseFD, &course, sizeof(struct Course)) > 0)
    	{
    		char t[500];
    		bzero(t,sizeof(t));
    		sprintf(t,"ID : %d\nCourse Name : %s\nCourse Credit : %d\n",course.id,course.name,course.credit);
    		strcat(temp,t);
    	}
    	strcat(temp,"\n\nYou'll now be redirected to the main menu...^");
    	
//-------------------------------------------------------------------------------------
//---------------------- PRINTING COURSE DATA------------------------------------------
//-------------------------------------------------------------------------------------
	
	writeBytes = write(sockfd, temp, strlen(temp));
    	if (writeBytes == -1)
    	{
        	perror("Error writing course name to client!");
        	return false;
    	}
	
    	readBytes = read(sockfd, readBuffer, sizeof(readBuffer)); // Dummy read
    	return true;
    	
}

// ---------------------------------------------------------------------------------------------
// ---------------------------- ADD COURSES ----------------------------------------------------
// ---------------------------------------------------------------------------------------------
bool addStudentCourses(int sockfd, int studentID)
{
	int readBytes, writeBytes;
	char readBuffer[1024], writeBuffer[1024];
	int t = 0;
	
	struct courseStudent coursestudent;
	coursestudent.studentID = studentID;
	struct Course oldcourse, newCourse, course;
	off_t offset;
	
	//-----------------------------------------------------------------
	//-------------------------------- MENU ---------------------------
	//-----------------------------------------------------------------
	writeBytes = write(sockfd, STUDENT_ADD_COURSE_MENU, strlen(STUDENT_ADD_COURSE_MENU));
	if (writeBytes == -1)
	{
		perror("Error while writing STUDENT_ADD_COURSE_MENU message to client!");
		return false;
	}
	bzero(readBuffer, sizeof(readBuffer));
	readBytes = read(sockfd, readBuffer, sizeof(readBuffer));
	if (readBytes == -1)
	{
		perror("Error while reading student ID from client!");
		return false;
	}
	
	int choice = atoi(readBuffer);
	
	int courseFD = open(COURSE_FILE, O_RDWR);
	if(courseFD == -1)
	{
		perror("Error in opening course file for Add course");
		return false;
	}
	struct flock lock = {F_WRLCK, SEEK_SET, 0, 0, getpid()};
	
	int lockstatus = fcntl(courseFD, F_SETLKW, &lock);
	if(lockstatus == -1)
	{
		perror("Error while obtaining read lock");
		return -1;
	}
	else
		printf("\n Read laock on course is acquired\n");
	while(read(courseFD, &course, sizeof(struct Course)) > 0)
	{
		printf("\nCourse ID : %d\n",course.id);
		if(course.id == choice)
		{
			t = 1;
			lock.l_type = F_UNLCK;
			lockstatus = fcntl(courseFD, F_SETLKW, &lock);
			if(lockstatus == -1)
			{
				perror("Error while obtaining read lock");
				return -1;
			}
			else
				printf("\nRead lock on course is released!!\n");
			break;
		}
	}
	if(t == 1)
	{
		printf("\nCourse ID found!!\n");
			
			
			int courseStudentFD = open(COURSE_STUDENT_FILE, O_CREAT | O_APPEND | O_WRONLY, 0666);
			if(courseStudentFD == -1)
			{
				perror("Error while creating/opening COURSE STUDENT file");
				lock.l_type = F_UNLCK;
				lockstatus = fcntl(courseFD, F_SETLK, &lock);
				return -1;
			}
			
			coursestudent.courseID = choice;
			coursestudent.studentID = studentID;
			printf("\nStuden ID is %d.\n",studentID);
			
			writeBytes = write(courseStudentFD, &coursestudent, sizeof(coursestudent));
			if (writeBytes == -1)
			{
				perror("Error while writing Student record to file!");
				lock.l_type = F_UNLCK;
				lockstatus = fcntl(courseFD, F_SETLK, &lock);
				return false;
			}
			close(courseStudentFD);
			
			writeBytes = write(sockfd, STUDENT_MOD_SUCCESS, strlen(STUDENT_MOD_SUCCESS));
			if (writeBytes == -1)
			{
				perror("Error while writing STUDENT_MOD_SUCCESS message to client!");
				return false;
			}
			
			readBytes = read(sockfd, readBuffer, sizeof(readBuffer)); // Dummy read
			
			// Update enrolled count
			course.enrolledStudent = course.enrolledStudent + 1;
			// -----Update Course data ---------
			
	}
	else if(t == 0)
	{
		printf("\nInvalid Course ID\n");
	}
}

// ---------------------------------------------------------------------------------------------
// ----------------------- READ ENROLLED COURSES -----------------------------------------------
// ---------------------------------------------------------------------------------------------
bool enrolledCourse(int sockfd,int studentID)
{
	int readBytes, writeBytes;
	char readBuffer[1024], writeBuffer[1024];
	
	struct courseStudent coursestudent;
	printf("\nInside enrolled course.\n");
	
	int courseStudentFD = open(COURSE_STUDENT_FILE, O_RDONLY);
	if(courseStudentFD == -1)
	{
		perror("Error while openeing course student file");
		return false;
	}
	
	struct flock lock = {F_RDLCK, SEEK_SET, 0, 0, getpid()};
	int lockstatus = fcntl(courseStudentFD, F_SETLK, &lock);
	if(lockstatus == -1)
	{
		perror("Error while obtaining read lock on the course student file!");
		return false;
	}
	else
		printf("\nRead lock for enrolled course is acquired!!\n");
		
	char data[1024];
	bzero(data,sizeof(data));
	strcat(data,"You are enrolled in :\n");
	while(read(courseStudentFD, &coursestudent, sizeof(struct courseStudent)) > 0)
	{
		if(coursestudent.studentID == studentID)
		{
			char temp[500];
			bzero(temp,sizeof(temp));
			sprintf(temp,"ID: %d\n",coursestudent.courseID);
			strcat(data,temp);
		}
	}
	lock.l_type = F_UNLCK;
	lockstatus = fcntl(courseStudentFD, F_SETLK, &lock);
	if(lockstatus == -1)
	{
		perror("Error while releasing read lock on the course student file!");
		return false;
	}
	else
		printf("\nRead lock for enrolled course is released!!\n");
	strcat(data,"\n\nYou'll now be redirected to the main menu...^");
	
	// --------- Printing data
	writeBytes = write(sockfd, data, strlen(data));
    	if (writeBytes == -1)
    	{
        	perror("Error writing course name to client!");
        	return false;
    	}	

    	readBytes = read(sockfd, readBuffer, sizeof(readBuffer)); // Dummy read
    	return true;
}

// ---------------------------------------------------------------------------------------------
// ---------------------------- CHANGE PASSWORD ------------------------------------------------
// ---------------------------------------------------------------------------------------------
bool changeStudentPassword(int sockfd,int studentID)
{
	int readBytes, writeBytes;
	char readBuffer[1024], writeBuffer[1024];
	
	struct Student student;
	printf("\nInsidee changePassword for student\n");
	off_t offset;
	int lockstatus;
	
	int studentFD = open(STUDENT_FILE, O_RDONLY);
	if(studentFD == -1)
	{
		perror("Error while openeing student file");
		return false;
	}
	lseek(studentFD,0,SEEK_SET);
	offset = lseek(studentFD, studentID * sizeof(struct Student), SEEK_SET);
	if (errno == EINVAL)
	{
		// student record doesn't exist
		bzero(writeBuffer, sizeof(writeBuffer));
		strcpy(writeBuffer, ID_DOESNT_EXIT);
		strcat(writeBuffer, "^");
		writeBytes = write(sockfd, writeBuffer, strlen(writeBuffer));
		if (writeBytes == -1)
		{
		    perror("Error while writing ID_DOESNT_EXIT message to client!");
		    return false;
		}
		readBytes = read(sockfd, readBuffer, sizeof(readBuffer)); // Dummy read
		return false;
		}
	else if (offset == -1)
	{
		perror("Error while seeking to required student record!");
		return false;
	}
	
	
	//-----------------------------------------------------------------
	//----------------------LOCK REQUIRED DATA-------------------------
	//-----------------------------------------------------------------
	struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct Student), getpid()};
	lockstatus = fcntl(studentFD, F_SETLKW, &lock);
	if(lockstatus == -1)
	{
		perror("Error while obtaining read lock on the student file!");
        	return false;
	}
	readBytes = read(studentFD, &student, sizeof(struct Student));
	lock.l_type = F_UNLCK;
	fcntl(studentFD, F_SETLK, &lock);
	if (readBytes == -1)
	{
		perror("Error reading student record from file!");
		return false;
	}
	close(studentFD);
	printf("\nStudent password is %s\n",student.password);
	//-----------------------------------------------------------------
	//---------------------- CHANGE PASSWORD --------------------------
	//-----------------------------------------------------------------
	bzero(writeBuffer, sizeof(writeBuffer));
	writeBytes = write(sockfd, CHANGE_PASSWORD, strlen(CHANGE_PASSWORD));
	if (writeBytes == -1)
	{
		perror("Error while writing CHANGE_PASSWORD message to client!");
		return false;
	}
	bzero(readBuffer, sizeof(readBuffer));
	readBytes = read(sockfd, readBuffer, sizeof(readBuffer));
	if (readBytes == -1)
	{
		perror("Error while reading  updated password of course from client!");
		return false;
	}
	
	char hashedPassword[1000];
	strcpy(student.password, crypt(readBuffer, "MK"));
	printf("\nPassword is %s\n",student.password);
	
	// --------------------------Writing back --------------------------------
	studentFD = open(STUDENT_FILE, O_WRONLY);
	if(studentFD == -1)
	{
		perror("Error while opening student file");
        	return false;
	}
	lseek(studentFD,0,SEEK_SET);
	offset = lseek(studentFD, studentID * sizeof(struct Student), SEEK_SET);
	if(offset == -1)
	{
		perror("Error while seeking to required student record");
		return false;
	}
	
	lock.l_type = F_WRLCK;
	lock.l_start = offset;
	lockstatus = fcntl(studentFD, F_SETLK, &lock);
	if(lockstatus == -1)
	{
		perror("Error while obtaining write lock on student record");
		return false;
	}
	
	writeBytes = write(studentFD, &student, sizeof(struct Student));
	lock.l_type = F_UNLCK;
	fcntl(studentFD, F_SETLK, &lock);
	if(writeBytes == -1)
	{
		perror("Error while writing update to student file");
		return false;
	}
	
	
	close(studentFD);
	
	writeBytes = write(sockfd, STUDENT_MOD_SUCCESS, strlen(STUDENT_MOD_SUCCESS));
	if (writeBytes == -1)
	{
		perror("Error while writing STUDENT_MOD_SUCCESS message to client!");
		return false;
	}
	
	readBytes = read(sockfd, readBuffer, sizeof(readBuffer)); // Dummy read
}

// ---------------------------------------------------------------------------------------------
// ---------------------------- Remove Course --------------------------------------------------
// ---------------------------------------------------------------------------------------------
bool dropCourse(int sockfd, int studentID)
{
	int readBytes, writeBytes;
	char readBuffer[1024], writeBuffer[1024];
	
	struct courseStudent coursestudent;
	
	//-----------------------------------------------------------------
	//--------------------------- COURSE ID ---------------------------
	//-----------------------------------------------------------------
	writeBytes = write(sockfd, FACULTY_MOD_COURSE_ID, strlen(FACULTY_MOD_COURSE_ID));
	if (writeBytes == -1)
	{
		perror("Error while writing FACULTY_MOD_COURSE_ID message to client!");
		return false;
	}
	
	bzero(readBuffer, sizeof(readBuffer));
	readBytes = read(sockfd, readBuffer, sizeof(readBuffer));
	if (readBytes == -1)
	{
		perror("Error while reading faculty ID from client!");
		return false;
	}
	
	int courseID = atoi(readBuffer);
	printf("\nUser want to drop %d course\n",courseID);
	
	int courseStudentFD = open(COURSE_STUDENT_FILE, O_RDWR);
	if(courseStudentFD == -1)
	{
		// Course-student file doesnt exist
		bzero(writeBuffer, sizeof(writeBuffer));
		strcpy(writeBuffer, ID_DOESNT_EXIT);
		strcat(writeBuffer, "^");
		writeBytes = write(sockfd, writeBuffer, strlen(writeBuffer));
		if (writeBytes == -1)
		{
		    perror("Error while writing ID_DOESNT_EXIT message to client!");
		    return false;
		}
		readBytes = read(sockfd, readBuffer, sizeof(readBuffer)); // Dummy read
		return false;
	}
	
	//-----------------------------------------------------------------
	//----------------- LOCK REQUIRED FOR WRITE -----------------------
	//-----------------------------------------------------------------
	struct flock lock = {F_WRLCK, SEEK_SET, 0, 0, getpid()};
	int lockstatus;
	
	if(courseStudentFD != -1)
	{
		printf("\nInside Delete course-student\n");
		lockstatus = fcntl(courseStudentFD, F_SETLK, &lock);
		if(lockstatus == -1)
		{
			perror("Error while obtaining write lock (remove) on the course-student file!");
			return false;
		}
		else
			printf("\nWrite lock for remove in course-student file\n");
		
		while(read(courseStudentFD, &coursestudent, sizeof(struct courseStudent)) > 0)
		{
			if(coursestudent.courseID == courseID && coursestudent.studentID == studentID)
			{
				printf("\nMatch found : course-student delete\n");
				while(readBytes = read(courseStudentFD, &coursestudent, sizeof(struct courseStudent)) > 0)
				{
					printf("\nCourse ID : %d\n",coursestudent.courseID);
					lseek(courseStudentFD, -2 * sizeof(struct courseStudent), SEEK_CUR);
					write(courseStudentFD, &coursestudent, sizeof(struct courseStudent));
					lseek(courseStudentFD, sizeof(struct courseStudent),SEEK_CUR);
				}
				if(readBytes == 0)
				{
					printf("\nU deleted last data\n");
					lseek(courseStudentFD, -1 * sizeof(struct courseStudent),SEEK_CUR);
					ftruncate(courseStudentFD, lseek(courseStudentFD, 0, SEEK_CUR));
				}
				break;
			}
		}
		lock.l_type = F_UNLCK;
		lockstatus = fcntl(courseStudentFD, F_SETLK, &lock);
		if(lockstatus == -1)
		{
			perror("Error while releasing write lock (remove) on the course-student file!");
			return false;
		}
		else
			printf("\nWrite lock re for remove on course-student\n");
	}
	
	writeBytes = write(sockfd, ADMIN_MOD_SUCCESS, strlen(ADMIN_MOD_SUCCESS));
	if(writeBytes == -1)
	{
		perror("Error while  ADMIN_MOD_SUCCESS");
		return false;
	}
	
	readBytes = read(sockfd, readBuffer, sizeof(readBuffer)); // Dummy read

    	return true;	
}

#endif
