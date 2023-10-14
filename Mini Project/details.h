#ifndef DETAILS
#define DETAILS

#include<stdio.h>
#include "./head.h"
#include "./Record.h"
#include "./functions.h"
#include "./authentication.h"

#define ADMIN_LOGOUT "Logging Out"
#define buffsz 100000


bool admin_details(int fd);
bool prof_details(int fd);
bool student_details(int fd);

bool admin_details(int fd) {
		int writeBytes, readBytes;
		char readb[1000], writeb[1000];
		while(1) {
			char input_name[100];
			char input_pass[100];
			
			char *userid = "Enter UserId:";
			writeBytes = write(fd, userid, strlen(userid));
			
			readBytes = read(fd, input_name, sizeof(input_name));
			if(readBytes == -1) {
				perror("Error while reading");
				return false;
			}
			
			char *password = "Enter Password:";
			writeBytes = write(fd, password, strlen(password));
			
			readBytes = read(fd, input_pass, sizeof(input_pass));
			if(readBytes == -1) {
				perror("Error while reading");
				return false;
			}
			
			int valid_bit = Auth_of_Admin(input_name, input_pass);
			if(valid_bit == 0) {
				char* msg = "The Credential are not valid\n";
				write(fd, msg, strlen(msg));
				return false;
			}
			
			strcat(writeb, "\n");
			strcat(writeb, ADMIN);
			
			writeBytes = write(fd, writeb, strlen(writeb));
			if(writeBytes == -1) {
				perror("Error while choosing the credential!");
				return false;
			}
			 
			int choice;
			readBytes = read(fd, readb, sizeof(readb));
			if(writeBytes == -1) {
				perror("Error while choosing the credential!");
				return false;
			}
			 
			choice = atoi(readb); 
			
			 
			if(choice == 1) {
		       		struct stud add_s;
		       		
		       		//write student name
		       		char* msg="Enter student name:";
		       		writeBytes = write(fd,msg,strlen(msg));

		       		//read student name		    		
		       		read(fd, &add_s.name, sizeof(add_s.name));               
		            
		       		//write student rollno
		       		msg="Enter student rollno:";
		       		write(fd,msg,strlen(msg));

		       		//read student rollno
		       		read(fd,&add_s.rollno,sizeof(add_s.rollno));

		       		//write student emailID
		       		msg="Enter student emailID:";
		       		write(fd,msg,strlen(msg));

		       		//read student emailID
		       		read(fd,&add_s.email,sizeof(add_s.email));

		       		//write student password
		       		msg="Enter student password:";
		       		write(fd,msg,strlen(msg));

		      		//read student password
		       		read(fd,&add_s.password,sizeof(add_s.password));
		       		 
		       		int check = searchStudent(add_s.rollno);
		            
		       		if(check == -1) {
		            	//Not able to access
		           	 break;
		        	}
		        
		      		else if(check == 0){
		                	//Entry Already Present
		                	break;

		         	}
		         
		         	else if(check == 1){
		                	//unique entry
		                	
		                	int addStudentEntry = add_student(add_s);
		                	//write addStudentEntry
		                	if(addStudentEntry==-1) {
		                		msg="Student not added successfully!";
		                    		write(fd,msg,strlen(msg));
		                    		break;
		                	}
		                
		               	 	else {
		                		//write student added successfully!!!
		                    		msg="Student added successfully!";
		                    		write(fd,msg,strlen(msg));
		                 	}

		            	}
		            
		            
		           	else {
		           		break;
		          	 }
		            
                   }
                   
                   else if(choice == 2) {
		            //write input rollnumber
		            
		            char* msg="Input Rollnumber of student to update\n";
		            write(fd, msg, strlen(msg));
		            char roll_no[100];
		            read(fd, roll_no, sizeof(roll_no));
		            

		            int check = searchStudent(roll_no);

		            if(check == -1) {
		                //unable to access database
		                break;
		            }
		            else if(check == 0) {
		                //duplicate entry
		                int updateNamePass;

		                //write nam/pass
		                msg="What you want to update Name or Password\n"
		                    "1. Name\n"
		                    "2. Password\n";
		                write(fd, msg, strlen(msg));

		                //read namepass value
		                int choosen_value;
		                read(fd, &choosen_value, sizeof(int));

		                if(choosen_value == 1) {
		                    //update Name
		                    struct stud update_name;
		                    int fd = open("Student.txt", O_RDWR, 0666);
		                    while(read(fd, &update_name, sizeof(update_name))>0){
		                        if(strcmp(update_name.rollno, roll_no)==0){
		                            //write msg to enter new name
		                            msg="Enter new name\n";
		                            write(fd, msg, strlen(msg));

		                            //read new name
		                            read(fd, update_name.name, sizeof(update_name.name));
		                            
		                            lseek(fd, -1*sizeof(update_name), SEEK_CUR);
		                            write(fd, &update_name, sizeof(update_name));

		                            //write msg updation successful
		                            msg="Name has been updated\n";
		                            write(fd, msg, strlen(msg));
		                            break;
		                        }
		                    }  

		                }
		                
		                else if(choosen_value == 2) {
		                    //update password
		                    struct stud update_password;
		                    int fd = open("Student.txt", O_RDONLY, 0666);
		                    while(read(fd, &update_password, sizeof(update_password))>0){
		                        if(strcmp(update_password.rollno, roll_no)==0){
		                            //write msg to enter new password
		                            msg="Enter new password\n";
		                            write(fd, msg, strlen(msg));

		                            //read new password
		         read(fd, update_password.password, sizeof(update_password.password));
		         
		                            lseek(fd, -1*sizeof(update_password), SEEK_CUR);
		                            write(fd, &update_password, sizeof(update_password));

		                            //write msg updation successful
		                            msg="Name has been updated\n";
		                            write(fd, msg, strlen(msg));
		                            break;
		                        }
		                    }
		                }
		                
		                else {
		                    break;
		                }

		            }
		            
		            else if(check == 1) {
		                //unique entry
		                msg="No such student exist\n";

		                //write student not found
		                write(fd, msg, strlen(msg));
		                break;
		            }
		            
		            else{
		                break;
		            }
		            
                   }
                   
                   else if(choice == 3) {
                   	struct facu add_f;
                   	
                   	char* msg = "Enter the faculty name:";
                   	write(fd, msg, strlen(msg));
                   	
                   	read(fd, add_f.name, sizeof(add_f.name)); 
                   	
                   	msg = "Enter the faculty UID:";
                   	write(fd, msg, strlen(msg));
                   	
                   	read(fd, add_f.faculty_ID, sizeof(add_f.faculty_ID));
                   	
                   	msg = "Enter the faculty password:";
                   	write(fd, msg, strlen(msg));
                   	
                   	read(fd, add_f.pass, sizeof(add_f.pass));
                   	
                   	int check = searchStudent(add_f.faculty_ID);

		       	//write checker
		       	//write(fd,&check,sizeof(int));
		            
		       	if(check==-1){
		            //Not able to access
		            break;
		        }
		        
		      	else if(check==0){
		                //Entry Already Present
		                break;
		        }
		         
		        else if(check==1){
		               //unique entry
		               int addfacultyEntry = add_faculty(add_f);
		               //write addStudentEntry
		                
		               if(addfacultyEntry==-1){
		                    	break;
		                }
		                
		                else{
		                    //write student added successfully!!!
		                    msg="Facuilty added successfully!";
		                    write(fd,msg,strlen(msg));
		                    break;
		                }

		            }
		            
		           else {
		           	break;
		           }
		     }
		    
		  
		  else if(choice == 4) {
	
                    //write input FacultyID
                    char* msg="Enter the faculty_ID to update\n";
                    write(fd, msg, strlen(msg));
                    char input_ID[100];
                    //read Student UID
                    read(fd,input_ID,sizeof(input_ID));

                    int check = searchFaculty(input_ID);                   

                    if(check ==-1){
                        //unable to access database
                        break;
                    }
                    else if(check == 0){
                        //duplicate entry
                        int updateNamePass;
                        
                        msg="Do you want to update Name or Password\n"
                            "1. Name\n"
                            "2. Password\n";
                        write(fd, msg, strlen(msg));
                       
                        char ch[100];
                        read(fd, ch ,sizeof(ch));
                        int choosen_value = atoi(ch);
                        printf("%d", choosen_value);
                        //read namepass value

                        if(choosen_value == 1)
                        {
                            //update Name
                            struct facu update_name;
                            int fd = open("Faculty.txt",O_RDWR,0666);
                            while(read(fd, &update_name, sizeof(update_name))>0){
                                if(strcmp(update_name.faculty_ID,input_ID)==0){
                                    //write msg to enter new name
                                    msg="Enter new name\n";
                                    write(fd, msg, strlen(msg));
                                    read(fd, update_name.name, sizeof(update_name.name));

                                    lseek(fd, -1*sizeof(update_name), SEEK_CUR);
                                    write(fd, &update_name, sizeof(update_name));

                                    //write msg updation successful
                                    msg="Name has been updated\n";
                                    write(fd,msg,strlen(msg));
                                    break;
                                }
                                
                            }   

                        }
                        
                        else if(choosen_value == 2){
                            //update password
                            struct facu update_password;
                            int fd = open("Faculty.txt",O_RDONLY,0666);
                            while(read(fd, &update_password,sizeof(update_password))>0){
                                if(strcmp(update_password.pass, input_ID)==0){
                                    //write msg to enter new password
                                    msg="Enter new password\n";
                                    write(fd, msg, strlen(msg));

                                    //read new password
                                    read(fd, update_password.pass, sizeof(update_password.pass));
                                    lseek(fd, -1*sizeof(update_password), SEEK_CUR);
                                    write(fd, &update_password, sizeof(update_password));

                                    //write msg updation successful
                                    msg="Name has been updated\n";
                                    write(fd, msg, strlen(msg));
                                    break;
                                }
                            }
                            
                        }
                        
                        else{
                            break;
                        }

                    }
                    
                    else if(check == 1){
                        //unique entry
                        msg="No such Faculty exist\n";

                        //write student not found
                        write(fd,msg,strlen(msg));                        
                        break;
                    }
                    
                    else
                    {
                        break;
                    }

		  }
		  
		  else if(choice == 5) {
		     	    struct stud acti_stu;
		            //write Student UID
		            char* msg="Enter Student rollno\n";
		            write(fd,msg,strlen(msg));
		            //write Student UID

		            //read Student UID
		            read(fd,&acti_stu.rollno,sizeof(acti_stu.rollno));

		            int check = searchStudent(acti_stu.rollno);

		            if(check == -1){
		                //unable to access database
		                break;
		            }
		            
		            else if(check == 0){
		                //duplicate entry
		                acti_stu.status=1;
		                //update status in database
		                modify_status_student(acti_stu);
		                msg="Student status activated\n";

		                //write student msg
		                write(fd,msg,strlen(msg));
		                //write student msg
		                break;

		            }
		            else if(check == 1){
		                //unique entry
		                msg="No such student exist\n";
		                write(fd,msg,strlen(msg));
		                
		                break;
		            }
		            
		            else
		            {
		                break;
		            }
			
		  }
		  
		  else if(choice == 6) {
		  	    struct stud blk_std;
		            //write Student UID
		            char* msg="Enter Student rollno\n";
		            write(fd, msg, strlen(msg));

		            //read Student UID
		            read(fd,&blk_std.rollno,sizeof(blk_std.rollno));

		            int check = searchStudent(blk_std.rollno);

		            if(check == -1){
		                //unable to access database
		                break;
		            }
		            
		            else if(check == 0){
		                //duplicate entry
		                blk_std.status=0;
		                //update status in database
		                modify_status_student(blk_std);
		                
		                msg="Student status deactivated\n";

		                //write student msg
		                write(fd,msg,strlen(msg));
		               

		            }
		            
		            else if(check == 1){
		                //unique entry
		                msg="No such student exist\n";

		                //write student not found
		                write(fd,msg,strlen(msg));
		                break;
		            }
		            
		            else
		                break;
		}	  
		 
		 
		else if(choice == 7) { 
			 char* msg = "Enter Your Roll no!";
			 write(fd, msg, strlen(msg));
			 
			 char inputrollno[1000];
			 read(fd, inputrollno, sizeof(inputrollno));
			 
			 const char* fname = "Student.txt";
			 int fd1 = open(fname, O_RDONLY|O_CREAT, 0666);
			 
			 if(fd1 == -1) {
			 	perror("Not able to access the Student database");
			 	return 0;
			 }
			 
			 struct stud chk_stud;
			 char data[8000];
			 while(read(fd1, &chk_stud, sizeof(struct stud)) > 0) {
			 	if(strcmp(chk_stud.rollno, inputrollno) == 0) {
			 		snprintf(data, sizeof(data), " .....................Student Details Are.......................\nName = %s\nRoll_no = %s\nEmail_ID = %s\nStatus = %d\n", chk_stud.name, chk_stud.rollno, chk_stud.email, chk_stud.status);
			 		write(fd, data, strlen(data));
			 	}
			 }
		}
		
		else if(choice == 8) { 
			 char* msg = "Enter Faculty ID!";
			 write(fd, msg, strlen(msg));
			 
			 char inputfacultyid[1000];
			 read(fd, inputfacultyid, sizeof(inputfacultyid));
			 
			 const char* fname = "Faculty.txt";
			 int fd1 = open(fname, O_RDONLY|O_CREAT, 0666);
			 
			 if(fd1 == -1) {
			 	perror("Not able to access the Faculty in database");
			 	return 0;
			 }
			 
			 struct facu chk_fac;
			 char data[8000];
			 while(read(fd1, &chk_fac, sizeof(struct facu)) > 0) {
			 	if(strcmp(chk_fac.faculty_ID, inputfacultyid) == 0) {
			 		snprintf(data, sizeof(data), "...................Faculty Details Are.........................\nName = %s\nFaculty ID = %s\n", chk_fac.name, chk_fac.faculty_ID);
			 		write(fd, data, strlen(data));
			 		
			 	}
			 }
		}
		
		else if(choice == 9)
		{
                    char* msg = "Logged out from Admin\n";
                    write(fd, msg, sizeof(msg));
                    break;
                }
                
                else
                {
                    printf("You have choosen wrong option\n");
                    break;
                 }
			
	}
		
}

bool prof_details(int fd) {
	int writeBytes, readBytes;
	char readb[1000], writeb[1000];
	while(1) {
		char input_facu_id[100];
		char input_pass[100];
			
		char *facuid = "Enter Faculty_Id:";
		writeBytes = write(fd, facuid, strlen(facuid));
			
		readBytes = read(fd, input_facu_id, sizeof(input_facu_id));
		if(readBytes == -1) {
			perror("Error while reading");
			return false;
		}
			
		char *password = "Enter Password:";
		writeBytes = write(fd, password, strlen(password));
			
		readBytes = read(fd, input_pass, sizeof(input_pass));
		if(readBytes == -1) {
			perror("Error while reading");
			return false;
		}
			
		int valid_bit = Auth_of_Facu(input_facu_id, input_pass);
		if(valid_bit == 0) {
			printf("The Credential are not valid\n");
			return false;
		}
			
		strcat(writeb, "\n");
		strcat(writeb, FACULTY);
			
		writeBytes = write(fd, writeb, strlen(writeb));
		if(writeBytes == -1) {
			perror("Error while choosing the credential!");
			return false;
		}
			 
		int choice;
		readBytes = read(fd, readb, sizeof(readb));
		if(writeBytes == -1) {
			perror("Error while choosing the credential!");
			return false;
		}
		 
		choice = atoi(readb); 
		
		if(choice == 1) {
		    struct course add_cour;
                    //write course code
                    char* msg="Enter course code\n";
                    write(fd, msg, strlen(msg));

                    //read course code
                    read(fd,&add_cour.course_code,sizeof(add_cour.course_code));

                    //write course name
                    msg="Enter course name\n";
                    write(fd, msg, strlen(msg));

                    //read course name
                    read(fd, &add_cour.course_name, sizeof(add_cour.course_name));

                    //add facUID
                    strcpy(add_cour.faculty_ID, input_facu_id);

                    //write course credits
                    msg="Enter course credits\n";
                    write(fd, msg, strlen(msg));

                    //read course credits
                    read(fd, &add_cour.credits, sizeof(add_cour.credits));

                    //current students enrolled
                    add_cour.student_enrolled=0;

                    //write course maxStudentsAllowed
                    msg="Enter maximum Students allowed\n";
                    write(fd, msg, strlen(msg));

                    //read course maxStudentsAllowed
                    read(fd,&add_cour.max_stud_allow,sizeof(add_cour.max_stud_allow));

                    //is course active
                    add_cour.status = 1;
                    
                    int check = searchActiveCourse(add_cour.course_code);

                    if(check == -1){
                        break;
                    }
                    else if(check == 0){
                        //duplicate entry
                        break;
                    }
                    else if(check == 1){
                        //course not present

                        //write course entry
                        int add_cour_entry = add_Course(add_cour);

                        if(add_cour_entry==-1){
                            break;
                        }
                        else{
                            //write course added successfully!!!
                            msg="Course added successfully!!!\n";
                            write(fd, msg, strlen(msg));
                        }
                    }
                    
                    else
                    {
                    	break;
                    }
               }
               
               else if(choice == 2) {
               	    //remove course
                    //ask for course_code
                    char rmv_cour[100];

                    //write course code
                    char* msg="Enter course code\n";
                    write(fd, msg, strlen(msg));

                    //read course code
                    read(fd, &rmv_cour, sizeof(rmv_cour));

                    int check = searchActiveCourse(rmv_cour);

                    if(check == -1)
                    {
                        //unable to access
                        break;
                    }
                    else if(check == 0)
                    {
                        removeCourse(rmv_cour);

			//write course remove msg
                        msg="Course has been removed\n";
                        write(fd, msg, strlen(msg));
                        strcat(writeb, "\n");
                        
                    }
                    
                    else if(check == 1)
                    {
                        break;
                    }
                    
                    else
                    {
                        break;
                    }
              }
              
              else if(choice == 3) {
		    //view enrollments
                    //sendmsg for input 
                    char* msg="Enter course code";
                    write(fd, msg, strlen(msg));

                    //read input coursecode
                    char input_code[100];
                    read(fd, &input_code, sizeof(input_code));

                    int check = searchActiveCourse(input_code);

                    if(check == -1){
                        //unable to access
                        break;
                    }
                    
                    else if(check == 0)
                    {
                        //display 
                        //send message
                        msg="Number of current students are:\n";
                        write(fd, &msg, sizeof(msg));
                        //send message

                        //write value
                        int active_stud = getStudentCount(input_code);
                        printf("%d\n", active_stud);
                        write(fd, &active_stud, sizeof(active_stud));
                    }
                    
                    else if(check == 1)
                    {
                        //course does not exist
                        break;
                    }
                    
                    else
                    {
                        break;
                    }
               }
               
               else if(choice == 4) {
               		//password change
		        struct facu update_pass;
		        int fd = open("Faculty.txt",O_RDWR,0666);
		        while(read(fd,&update_pass,sizeof(update_pass))>0){
		             if(strcmp(update_pass.faculty_ID,input_facu_id)==0){
		                  //write msg to enter new password
		                  char* msg="Enter new password\n";
		                  write(fd,msg,strlen(msg));
		                    
		                  //read new password
		                  read(fd,update_pass.pass,sizeof(update_pass.name));
		                  
		                  lseek(fd,-1*sizeof(update_pass),SEEK_CUR);
		                  write(fd, &update_pass, sizeof(update_pass));

		                  //write msg updation successful
		                  msg="Password has been updated\n";
		                  write(fd, msg, strlen(msg));
		              }
		         }
		}
		
		else if(choice==5)
		{
		       char *msg = "Faculty Logged out\n";
		       write(fd, msg, strlen(msg)); 
		       
		}
		
		else
		{
		       char *msg = "You have choosen wrong option\n";
		       write(fd, msg, strlen(msg)); 
		       
		}
         }
}

/*bool stud_details(int fd) {
	int writeBytes, readBytes;
	char readb[1000], writeb[1000];
	while(1) {
		char input_rollno[100];
		char input_pass[100];
			
		char *roll = "Enter Student Roll no:";
		writeBytes = write(fd, roll, strlen(roll));
			
		readBytes = read(fd, input_rollno, sizeof(input_rollno));
		if(readBytes == -1) {
			perror("Error while reading");
			return false;
		}
			
		char *password = "Enter Student Password:";
		writeBytes = write(fd, password, strlen(password));
			
		readBytes = read(fd, input_pass, sizeof(input_pass));
		if(readBytes == -1) {
			perror("Error while reading");
			return false;
		}
			
		/*int valid_bit = Auth_of_Facu(input_name, input_pass);
		if(valid_bit == 0) {
			printf("The Credential are not valid\n");
			return false;
		}
			
		strcat(writeb, "\n");
		strcat(writeb, STUDENT);
			
		writeBytes = write(fd, writeb, strlen(writeb));
		if(writeBytes == -1) {
			perror("Error while choosing the credential!");
			return false;
		}
			 
		int choice;
		readBytes = read(fd, readb, sizeof(readb));
		if(writeBytes == -1) {
			perror("Error while choosing the credential!");
			return false;
		}
		 
		choice = atoi(readb); 
		
		if(choice == 1) {
			    char enroll_course[100];
		            //write course code
		            char* msg="Enter course code to enroll\n";
		            write(fd, msg, strlen(msg));

		            //read course code
		            read(fd, &enroll_course, sizeof(enroll_course));


		            int check = searchActiveCourse(enroll_course);

		            if(check == -1){
		                //unable to access course database
		                break;
		            }
		            else if(check == 0){   
		                //course exists
		                int status=enrollInActiveCourse(enroll_course,input_rollno);
		                
		                if(status==-1){
		                    break;
		                }
		                else if(status==1){
		                    //student is enrolled in course successfully

		                    break;
		                }
		                else if(status==0){
		                    //one of condition fails
		                    break;
		                }
		                else
		                {
		                    break;
		                }
		                break;
		            }
		            else if(check == 1){
		                //course does not exist
		                break;
		            }
		            else{
		                break;
		            }
                 }
                 
                 else if(choice == 2) {
                 	    //unenroll student
		            char unEnrollInCourse[100];

		            //write course code
		            char* msg="Enter course code\n";
		            write(fd,msg,strlen(msg));
		            //write course code

		            //read course code
		            read(fd,&unEnrollInCourse,sizeof(unEnrollInCourse));


		            int check = searchActiveCourse(unEnrollInCourse);
		             
		            if(check == -1){
		                //unable to access database
		                break;
		            }
		            else if(check == 0){
		                //course exists
		                int unenrollStatus=unenrollInActiveCourse(unEnrollInCourse,input_rollno);
		                //write unenrollStatus
		                write(fd, &unenrollStatus, sizeof(int));
		                if(unenrollStatus==-1){
		                    //error
		                    break;
		                }
		                else if(unenrollStatus==1){
		                    //success
		                    
		                }
		                else if(unenrollStatus==0){
		                    //failed
		                    break;
		                }
		                else{
		                    break;
		                }
		                
		            }
		            else if(check == 1){
		                //course does not exist
		                break;
		            }
		            else
		            {
		                break;
		            }
		 }
		 
		 else if(choice == 3) {
		 	//view enrolled courses
                    	//stores data from students in courses
                    	char viewCourseDetails[buffsz];

                    	viewEnrolledCourses(input_rollno, viewCourseDetails);
                    
                    	//write view course details
                    	write(fd,&viewCourseDetails,buffsz);
                }
                
                else if(choice == 4) {
                	    struct stud updateThisPassword;
		            int fd=open("Student.txt",O_RDWR,0666);
		            while(read(fd,&updateThisPassword,sizeof(updateThisPassword))>0){
		                if(strcmp(updateThisPassword.rollno,input_rollno)==0){
		                    //write msg to enter new password
		                    char* msg="Enter new password\n";
		                    write(fd,msg,strlen(msg));
		                    //write msg to enter new password


		                    //read new password
		                    read(fd,updateThisPassword.password,sizeof(updateThisPassword.name));
		                    //read new password
		                    lseek(fd,-1*sizeof(updateThisPassword),SEEK_CUR);
		                    write(fd,&updateThisPassword,sizeof(updateThisPassword));


		                    //write msg updation successful
		                    msg="Password has been updated\n";
		                    write(fd, msg, strlen(msg));
		                    break;
		                }
		           }
		}
		
		else if(choice == 5) {
			char* msg = "Student is Logged Out!\n";
			write(fd, msg, strlen(msg));
			return false;
		}
		
		else {
			char* msg = "You entered wrong choice\n";
			write(fd, msg, strlen(msg));
			return false;
		}
		
		
	}
}*/
				
#endif
