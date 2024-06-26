#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define int long long int

typedef struct course_i{
	char course_no[10];
	int credits;
}course_i;

typedef struct course_e{
	char course_no[10];
	bool pass;
}course_e;

typedef struct course_enrolled{
	course_e courses[100];
	char semester[100];
	char violation[10][20];
	int no_violations;
}course_enrolled;

typedef struct st_c{
	int roll_no;
	char course_no[10];
	bool pass;
}stc;

typedef struct course_check{
	int total_credits;
	char violation1[100];
	char violation2[100];
	char violation3[100];
	bool status_clear;
}course_check;


typedef struct curriculum{
	course_i c[15];
}sem_wise_course;

typedef struct no_dues{
	int roll_no;
	bool hostel;
	bool department;
	bool ncc;
	bool cos;
	bool nso;
	bool institute;
	bool status_clear;
	char violation[20];
	
}no_dues;

typedef struct disciplinary{
	bool status_clear;
}disciplinary;

typedef struct student{
	int roll_no;
	char name[10];
}student;

int main(){



	//ALL ABOUT NO DUES//
	FILE* f1 ;
	f1 = fopen("no-dues.csv", "r");
	//taking one fgets because first line is column info
	char line[2000];
	fgets(line, 2000, f1);
	int i = 1;
	no_dues n[122];
	
	while(fgets(line, 2000, f1)){
		int  j = 0;
		n[i].roll_no = (line[0] - '0')*100000000 + (line[1] - '0')*10000000 + (line[2] - '0')*1000000 + (line[3] - '0')*100000 + (line[4] - '0')*10000 + (line[5] - '0')*1000 + (line[6] - '0')*100 + (line[7] - '0')*10 + (line[8] - '0');
		j = 10;
		if(line[j] == 'Y'){
			n[i].hostel = 1;
			j = j + 4;
		}else if(line[j] == 'N'){
			n[i].hostel = 0;
			j = j + 3;
			//n[i].violation = "Hostel";
			strcpy(n[i].violation, "Hostel");
		}
		if(line[j] == 'Y'){
			n[i].department = 1;
			j = j + 4;
		}else if(line[j] == 'N'){
			n[i].department = 0;
			j = j + 3;
			//n[i].violation = "Department";
			strcpy(n[i].violation, "Department");
		}
		if(line[j] == 'Y'){
			n[i].ncc = 1;
			j = j + 4;
		}else if(line[j] == 'N'){
			n[i].ncc = 0;
			j = j + 3;
			//n[i].violation = "NCC";
			strcpy(n[i].violation, "NCC");
		}
		if(line[j] == 'Y'){
			n[i].cos = 1;
			j = j + 4;
		}else if(line[j] == 'N'){
			n[i].cos = 0;
			j = j + 3;
			//n[i].violation = "COS";
			strcpy(n[i].violation, "COS");
		}
		if(line[j] == 'Y'){
			n[i].nso = 1;
			j = j + 4;
		}else if(line[j] == 'N'){
			n[i].nso = 0;
			j = j + 3;
			//n[i].violation = "NSO";
			strcpy(n[i].violation, "NSO");
		}
		if(line[j] == 'Y'){
			n[i].institute = 1;
			j = j + 4;
		}else if(line[j] == 'N'){
			n[i].institute = 0;
			j = j + 3;
			//n[i].violation = "Institute";
			strcpy(n[i].violation, "Institute");
		}
		if(n[i].hostel && n[i].department && n[i].ncc && n[i].cos && n[i].nso && n[i].institute){
			n[i].status_clear = 1;
		}else{
			n[i].status_clear = 0;
		}
		i++;
	}
	
    int stu_count = i;
	//printf("%lld\n", i);
	//printf("%s\n", n[5].violation);
	//printf("%d\n", n[5].status_clear);
	fclose(f1);

	
	//ALL ABOUT STUDENT AND NAME//
	
	student stud[122];
	FILE* f2 = fopen("students.csv", "r");
	//ignoring first line of input
	fgets(line, 2000, f2);
	i = 1;
	while(fgets(line, 2000, f2)){
		int  j = 0;
		stud[i].roll_no = (line[0] - '0')*100000000 + (line[1] - '0')*10000000 + (line[2] - '0')*1000000 + (line[3] - '0')*100000 + (line[4] - '0')*10000 + (line[5] - '0')*1000 + (line[6] - '0')*100 + (line[7] - '0')*10 + (line[8] - '0');
		j = 10;
		stud[i].name[j-10] = line[j];j++;
		stud[i].name[j-10] = line[j];j++;
		stud[i].name[j-10] = line[j];j++;
		stud[i].name[j-10] = line[j];j++;
		i++;		
	}
	//printf("%lld-->%s\n", stud[90].roll_no, stud[90].name);
	fclose(f2);
	
	//ALL ABOUT COURSES OFFERED//
	
	FILE* f4 = fopen("curriculum.csv", "r");
	course_i credit_i[64];
	fgets(line, 2000, f4);
	i = 1;
	while(fgets(line, 2000, f4)){
		credit_i[i].course_no[0] = line[0];
		credit_i[i].course_no[1] = line[1];
		credit_i[i].course_no[2] = line[2];
		credit_i[i].course_no[3] = line[3];
		credit_i[i].course_no[4] = line[4];
		credit_i[i].credits = (line[6] - '0');
		i++;
	}
	//printf("%s-->%lld\n", credit_i[7].course_no,credit_i[7].credits); 
	fclose(f4);
	
	/*//ALL ABOUT STUD GRADE RECORD//
	
	FILE* f3 = fopen("grades.csv", "r");
	fgets(line, 2000, f3);
	stc grade_rec [7565];
	course_check cc[122];
	i = 0;
	while(fgets(line, 2000, f3)){
		int r = 0;
		r = (line[0] - '0')*100000000 + (line[1] - '0')*10000000 + (line[2] - '0')*1000000 + (line[3] - '0')*100000 + (line[4] - '0')*10000 + (line[5] - '0')*1000 + (line[6] - '0')*100 + (line[7] - '0')*10 + (line[8] - '0');
		r = r - 270101000;
		int j = 10;
		grade_rec[i].course_no[j-10] = line[j]; j++;
		grade_rec[i].course_no[j-10] = line[j]; j++;
		grade_rec[i].course_no[j-10] = line[j]; j++;
		grade_rec[i].course_no[j-10] = line[j]; j++;
		grade_rec[i].course_no[j-10] = line[j]; j++;j++;
		
		if(line[j] == 'F' || line[j] == 'N'){
			grade_rec[i].pass = 0;
			//cc[r].status_clear = 0;
			if(line[j] == 'F'){
				strcpy(cc[r].violation1, "CORE Course");
			}else if(line[j] == 'N'){
				strcpy(cc[r].violation2, "AUDIT course");
			}
		}
		
		i++;
	}*/
	

	/*//ALL ABOUT GRADES OF STUDENTS//
	FILE* f3 = fopen("grades.csv", "r");
	fgets(line, 2000, f3);
	course_enrolled scr[122];
	int r_prev = 0;
	int r = 0;
	i = 0;
	int v = 0;
	while(fgets(line, 2000, f3)){
		int j = 10;
		printf("%lld\n", r);
		r = (line[0] - '0')*100000000 + (line[1] - '0')*10000000 + (line[2] - '0')*1000000 + (line[3] - '0')*100000 + (line[4] - '0')*10000 + (line[5] - '0')*1000 + (line[6] - '0')*100 + (line[7] - '0')*10 + (line[8] - '0');
		r = r - 270101000;
		if(r != r_prev){
			i = 0;
			v = 0;
			scr[r].no_violations = 0;
		}
		scr[r].courses[i].course_no[0] = line[j]; j++;
		scr[r].courses[i].course_no[1] = line[j]; j++;
		scr[r].courses[i].course_no[2] = line[j]; j++;
		scr[r].courses[i].course_no[3] = line[j]; j++;
		scr[r].courses[i].course_no[4] = line[j]; j++;j++;
		
		/*if(line[j] == 'F' || line[j] == 'N'){
			scr[r].courses[i].pass = 0;
			scr[r].no_violations += 1;
			strcpy(scr[r].violation[v], scr[r].courses[i].course_no);
		}else{
			scr[r].courses[i].pass = 1;
		}//*//*
		
		
	}
	printf("%s-->%d, %s-->%d", scr[10].courses[0].course_no, scr[r].courses[0].pass, scr[10].courses[1].course_no, scr[r].courses[1].pass);
	
	fclose(f3);*/
	
	
	//ALL ABOUT DISCIPLINARY //
	
	FILE* f5 = fopen("disciplinary.csv", "r");
	fgets(line, 2000, f5);
	disciplinary d[122];
	i = 1;
	
	while(fgets(line, 2000, f5)){
		int j = 10;
		if(line[j] == 'N'){
			d[i].status_clear = 1;
		}else{
			d[i].status_clear = 0;
		}
		i++;
	}
	printf("220101080 %d\n", d[80].status_clear);
	fclose(f5);
	
	//CHECKING IF ELIGIBLE//
	
	printf("Enter 1 to give set of roll numbers or 0 for all checking eligibility of all students\n");
	int ch;
	scanf("%lld", &ch);
	if(ch){
		while(1){
			printf("Enter 1 for a request or 0 to terminate the program\n");
			int ch1;
			scanf("%lld", &ch1);
			if(ch1){
				printf("Enter LAST-3 digits of roll number...(upto 121 only)\n");
				int index;
				scanf("%lld", &index);
				printf("%s: \t %lld-\n", stud[index].name, stud[index].roll_no);
				if(d[index].status_clear && n[index].status_clear){
					printf("Eligible\n");
				}else{
					printf("NOT Eligible\n");
					if(!d[index].status_clear){
						printf("Disciplinary Violation\n");
					}
					if(!n[index].status_clear){
						printf("%s\n", n[index].violation);
					}
				}
			}else{
				break;
			}
		}
	}else{
		//all students to be checked.
		for(int index = 1; index <= 121; index++){
				printf("%s: \t %lld-\n", stud[index].name, stud[index].roll_no);
				if(d[index].status_clear && n[index].status_clear){
					printf("Eligible\n");
				}else{
					printf("NOT Eligible\n");
					if(!d[index].status_clear){
						printf("Disciplinary Violation\n");
					}
					if(!n[index].status_clear){
						printf("%s\n", n[index].violation);
					}
				}
		}
	}































	return 0;
}
