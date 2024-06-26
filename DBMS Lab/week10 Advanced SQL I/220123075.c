#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
static char *host="localhost";
static char *user="root";
static char *pass="root@123";
static char *db=NULL;
static unsigned int port=0;
static char *socket =NULL;
static unsigned int flags=0;
 
int main(){


//TASK 01: 
MYSQL *conn; //TASK 01.1: pointer to hold the information about the database connection.
conn=mysql_init(NULL);//TASK 01.2: intialising the pointer.
if(!(mysql_real_connect(conn,host,user,pass,NULL,0,NULL,0))){
	fprintf(stderr,"Error: %s [%d]\n",mysql_error(conn),mysql_errno(conn));
	exit(1);
}//TASK 01.3: using mysql_real_connect() function.

if (mysql_query(conn, "CREATE DATABASE week10")) {
        fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        return 1;
}//TASK 01.4: Creating databse titled week10.
//TASK 01 completed.


//TASK 02:
if (mysql_query(conn, "USE week10")) {
        fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        return 1;
}
if (mysql_query(conn, "CREATE TABLE student18(name char(100), roll_number char(10), primary key(roll_number))")) {
        fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        return 1;
}//TASK 02.1: Creating table student18.

if (mysql_query(conn, "CREATE TABLE course18(semester int, cid char(7), name char(100), l int, t int, p int, c int, primary key(cid))")) {
        fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        return 1;
}// TASK 02.2: Creating table course18.

if (mysql_query(conn, "CREATE TABLE grade18(roll_number char(10), cid char(7), letter_grade char(2), primary key(roll_number, cid))")) {
        fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        return 1;
}//TASK 02.3: Creating table grade18.

if (mysql_query(conn, "CREATE TABLE curriculum(dept char(3), number int, cid char(7))")) {
        fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        return 1;
}//TASK 02.4: Creating table curriculum.
//TASK 02 completed.


//TASK 03:
//TASK 03.1: Populating student18.
char file_path1 [200];
strcpy(file_path1, "student18.csv");
FILE* fptr1 = fopen(file_path1, "r");
for(int i = 0; i < 158; i++){
	char name[101];
	char roll_number[11];
	char query[100];
	strcpy(query, "INSERT INTO student18 VALUES ('");
	fscanf(fptr1, "%101[^,],%11[^\n]\n", name, roll_number);	
	strcat(query, name);
	strcat(query, "', '");
	strcat(query, roll_number);
	strcat(query, "')");
	//printf("%s\n", query);
	if (mysql_query(conn,query)){
        fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        return 1;
	}
}
fclose(fptr1);

//TASK 03.2: Populating course18.
char file_path2 [200];
strcpy(file_path2, "course18.csv");
FILE* fptr2 = fopen(file_path2, "r");
for(int i = 0; i < 63; i++){
	char sem[2];
	char cid [8];
	char name [101];
	char l[3];
	char t[3];
	char p[3];
	char c[3];
	fscanf(fptr2, "%2[^,],%8[^,],%101[^,],%3[^,],%3[^,],%3[^,],%3[^\n]\n", sem, cid, name, l, t, p, c);
	char query[1000];
	strcpy(query, "INSERT INTO course18 VALUES (");
	strcat(query, sem);
	strcat(query, ", '");
	strcat(query, cid);
	strcat(query, "', '");
	strcat(query, name);
	strcat(query, "', ");
	strcat(query, l);
	strcat(query, ", ");
	strcat(query, t);
	strcat(query, ", ");
	strcat(query, p);
	strcat(query, ", ");
	strcat(query, c);
	strcat(query, ") ");
	if (mysql_query(conn,query)){
        fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        return 1;
	}
}
fclose(fptr2);

//TASK 03.3: Populating grade18.
char file_path3 [200];
strcpy(file_path3, "grade18.csv");
FILE* fptr3 = fopen(file_path3, "r");
for(int i = 0; i < 9954; i++){
	char lg [2];
	char cid [8];
	char roll_number[11];
	fscanf(fptr3, "%11[^,],%8[^,],%3[^\n]\n", roll_number, cid, lg);
	char query[1000];
	strcpy(query, "INSERT INTO grade18 VALUES ('");
	strcat(query, roll_number);
	strcat(query, "', '");
	strcat(query, cid);
	strcat(query, "', '");
	strcat(query, lg);
	strcat(query, "')");
	if (mysql_query(conn,query)){
        fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        return 1;
	}
}
fclose(fptr3);

//TASK 03.4: Populating curriculum.
char file_path4 [200];
strcpy(file_path4, "curriculum.csv");
FILE* fptr4 = fopen(file_path4, "r");
for(int i = 0; i < 68; i++){
	char dept [4];
	char number [2];
	char cid[8];
	fscanf(fptr4, "%4[^,],%2[^,],%8[^\n]\n", dept, number, cid);
	char query[1000];
	strcpy(query, "INSERT INTO curriculum VALUES ('");
	strcat(query, dept);
	strcat(query, "', ");
	strcat(query, number);
	strcat(query, ", '");
	strcat(query, cid);
	strcat(query, "')");
	if (mysql_query(conn,query)){
        fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        return 1;
	}
}
fclose(fptr4);
//TASK 03 completed.
//TASK 04: 
//TASK 04.1:
MYSQL_RES *res; 
if (mysql_query(conn, "SELECT * FROM student18")){
  	fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
    return 1;
}
res = mysql_store_result(conn);
MYSQL_ROW row;
printf("name\t\troll_number\n");
while(row = mysql_fetch_row(res)){
	printf("%s\t\t%s\n", row[0], row[1]);
}

//TASK 04.2:
if (mysql_query(conn, "SELECT * FROM course18")){
  	fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
    return 1;
}
res = mysql_store_result(conn);
printf("semester\t\tcid\t\tname\t\tl\t\tt\t\tp\t\tc\n");
while(row = mysql_fetch_row(res)){
	printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
}

//TASK 04.3:
if (mysql_query(conn, "SELECT * FROM grade18")){
  	fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
    return 1;
}
res = mysql_store_result(conn);
printf("roll_number\t\tcid\t\tletter_grade\n");
while(row = mysql_fetch_row(res)){
	printf("%s\t\t%s\t\t%s\n", row[0], row[1], row[2]);
}

//TASK 04.4:
if (mysql_query(conn, "SELECT * FROM curriculum")){
  	fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
    return 1;
}
res = mysql_store_result(conn);
printf("dept\t\tnumber\t\tcid\n");
while(row = mysql_fetch_row(res)){
	printf("%s\t\t%s\t\t%s\n", row[0], row[1], row[2]);
}

//TASK 04.5:
//compute_spi
int check = 1;
while(check){
	printf("Enter 1 to search SPI for a roll number or 0 skip task!\n");
	scanf("%d", &check);
	char roll[10];
	char sem[2];
	printf("Enter roll number and sem number\n");
	scanf("%s", roll);
	scanf("%s", sem);
	char query [1000];
	strcpy(query, "select letter_grade, c from grade18, course18 where grade18.cid = course18.cid and roll_number = '");
	strcpy(query, roll);
	strcpy(query, "' and grade18.semester = ");
	strcpy(query, sem);
	if (mysql_query(conn, query)){
	  	fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	res = mysql_store_result(conn);
	int tot_cred = 0;
	int recd = 0;
	while(row = mysql_fetch_row(res)){
		int credit;
		credit = (int)(row[0] - '0');
		tot_cred += credit;
		int grade;
		if(!strcmp(res[1], "AA") || !strcmp(row[1], "AS")){
			grade = 10;
		}else if(!strcmp(row[1], "AB")){
			grade = 9;
		}else if(!strcmp(row[1], "BB")){
			grade = 8;
		}else if(!strcmp(row[1], "BC")){
			grade = 7;
		}else if(!strcmp(row[1], "CC")){
			grade = 6;
		}else if(!strcmp(row[1], "CD")){
			grade = 5;
		}else if(!strcmp(row[1], "DD")){
			grade = 4;
		}else{
			grade = 0;
		}
		recd += (grade*credit);
	}
	float spi = recd/tot_cred;
	printf("SPI of %s for sem: %s is %.2f\n", roll, sem, spi);
}

//TASK 04.6:
//compute_cpi
check = 1;
while(check){
	printf("Enter 1 to search CPI for a roll number or 0 skip task!\n");
	scanf("%d", &check);
	printf("Enter roll number\n");
	scanf("%s", roll);
	int i = 0;
	char sem[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
	while(i <= 7){
		strcpy(query,"");
		strcpy(query, "select letter_grade, c from grade18, course18 where grade18.cid = course18.cid and roll_number = '");
		strcpy(query, roll);
		strcpy(query, "'and grade18.semester <= ");
		strcpy(query, sem[i]);
		if (mysql_query(conn, query)){
		  	fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
			return 1;
		}
		res = mysql_store_result(conn);
		tot_cred = 0;
		recd = 0;
		while(row = mysql_fetch_row(res)){
			int credit;
			credit = (int)(row[0] - '0');
			tot_cred += credit;
			int grade;
			if(!strcmp(row[1], "AA") || !strcmp(row[1], "AS")){
				grade = 10;
			}else if(!strcmp(row[1], "AB")){
				grade = 9;
			}else if(!strcmp(row[1], "BB")){
				grade = 8;
			}else if(!strcmp(row[1], "BC")){
				grade = 7;
			}else if(!strcmp(row[1], "CC")){
				grade = 5;
			}else if(!strcmp(row[1], "DD")){
				grade = 4;
			}else{
				grade = 0;
			}
			recd += (grade*credit);
		}
		float cpi = recd/tot_cred;
		printf("CPI of %s for sem %s is %.2f\n", roll, sem[i], cpi);
		i++;
	}
}


//TASK 04.7:


/*
MYSQL_ROW row;
 
mysql_query(conn,"INSERT INTO hehe VALUES (1,'HERO',22.345) ");
mysql_query(conn,"SELECT * FROM hehe ");
res=mysql_store_result(conn);
while(row=mysql_fetch_row(res)){
	printf("%s\t%s\t%s\n", row[0], row[1], row[2]);
}*/
mysql_free_result(res);
mysql_close(conn);
return 0;
}
