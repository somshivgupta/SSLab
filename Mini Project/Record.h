#ifndef RECORD
#define RECORD

struct course{
	char course_code[100];
	char course_name[100];
	char faculty_name[100];
	char faculty_ID[100];
	int credits;
	int student_enrolled;
	int max_stud_allow;
	int status;
};

struct stud {
	char name[1000];
	char rollno[1000];
	char email[1000];
	char password[1000];
	int status;
	struct course course_enroll;
};

struct admin{
	char user_id[100];
	char pass[100];
};

struct facu{
	char name[100];
	char faculty_ID[100];
	char pass[100];
	struct course course_taught;
};

#endif
