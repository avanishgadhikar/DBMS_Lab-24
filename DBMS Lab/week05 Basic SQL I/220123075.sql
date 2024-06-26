/*TASK 01: Creating a Database titled 'week05' */
create database week05;
show databases;
/*----xxxx----*/

/*TASK 02: Creating a no constraints table 'T1'*/
use week05;
create table T1(
	name char(20),
    roll_no int,
    cpi float
);
select * from T1;
insert into T1 (name, roll_no, cpi)
	values ('student 01', 270101001, 9.8), 
			('student 02', 270101002, 8.9), 
            ('student 03', 270101003, 7.6);
select * from T1;
update T1 set T1.cpi = 8.1 where T1.name = 'student 03';
select * from T1;
delete from T1 where T1.name = 'student 02';
select * from T1;
/*----xxxx----*/

/*TASK 03: Creating table with primary key constraint*/
use week05;
create table T2(
	name char(20),
    roll_no int ,
    cpi float, 
    primary key(roll_no)
);
select * from T2;
insert into T2 (name, roll_no, cpi)
	values ('student 01', 270101001, 9.8), 
			('student 01', 270101002, 8.9), 
            ('student 03', 270101003, 7.6);
select * from T2;
update T2 set T2.roll_no = 270101002 where T2.name = 'student 01'; 
select * from T2;
/*ERROR THROWN: primary key constaint will not allow 2 students to have the same roll number, but could have the same name as no primary key constraint on name*/
/*----xxxx-----*/

/*TASK 04: creating a table with unique and not null constraints*/
use week05;
create table T3(
	name char(20) not null,
    roll_no int unique key,
    cpi float
);
select * from T3;
insert into T3 (name, roll_no, cpi)
	values (NULL, 270101001, 9.8); 
/*ERROR THROWN: name cannot be null*/
insert into T3 (name, roll_no, cpi)
	values ('student 02', 270101002, 8.9);
insert into T3 (name, roll_no, cpi)
	values ('student 03', 270101002, 7.6);
/*ERROR THROWN: unique key constraint on roll_no*/
select * from T3;
update T3 set T3.name = null;
/*ERROR THROWN: This would not be executed as name has a 'NOT NULL' constraint.*/
delete from T3 where T3.name = 'student 02';
select * from T3;
/*Last line executes successfully.*/
/*----xxxx----*/

/*TASK 05: Creating table 'T4' to demonstrate 'Data Quality Issues'*/
use week05;
create table T4(
	name char(20),
    roll_no int primary key, 
    cpi float default 0.0
);
insert into T4 (name, roll_no)
	values (NULL, 270101001);
insert into T4 (name, roll_no, cpi)
	values (NULL, 270101002, 8.9);
    select * from T4;
insert into T4 (name, roll_no, cpi)
	values ('student 03', 270101002, -7.6);
select * from T4;
/*ERROR THROWN: This insert statement is not working because there is a primary key constraint on roll_no and 270101002 already exists.*/
insert into T4 (name, roll_no, cpi)
	values ('student 03', 270101003, 8.2);
select * from T4;/*Executes Successfully*/
/*'Errors Thrown' have been mentioned after the statement itself, all other statements are executed.*/
/*----xxxx----*/

/*TASK 06: Initial Good Table is demonstrated using table 'T5'*/
use week05;
create table T5(
	name char(20) not null, 
    roll_no int primary key,
    cpi float default 0.0
);
insert into T5 (name, roll_no)
	values (null, 270101001);
select * from T5;
/*ERROR THROWN: Name has 'Not Null' constraint, which is violated*/
insert into T5 (name, roll_no, cpi)
	values ('student 01', 270101001, 9.6);
select * from T5;
insert into T5 (name, roll_no, cpi)
	values ('student 02', 270101002, 8.2);
select * from T5;
insert into T5 (name, roll_no, cpi)
	values ('student 02', 270101003, 7.6);
select * from T5;
insert into T5 (name, roll_no, cpi)
	values ('student 03', 270101003, 7.2);
select * from T5;
/*ERROR THROWN: roll_no already contains entry 270101003, hence primary key error*/
insert into T5 (name, roll_no)
	values ('student 04', 270101004);
select * from T5;
/*'Error Thrown' comments specify erroneous queries. All other are executed.*/
/*----xxxx----*/

/*TASK 07: Demonstrating the alteration of tables using table T6.*/
use week05;
create table T6(
	name char(20),
    roll_no int, 
    cpi float
);
insert into T6 (name, roll_no, cpi)
	values ('student 01', 270101001, 9.6);
select * from T6;
insert into T6 (name, roll_no, cpi)
	values ('student 02', 270101001, 9.4);
select * from T6;
insert into T6 (name, roll_no, cpi)
	values ('student 03', 270101001, 9.2);
select * from T6;
alter table T6 add constraint primary key(roll_no);
 /*ERROR THROWN: Primary Key constraint cannot be added to a set of attributes which contain duplicate values.*/
alter table T6 add column sem int default 1;
insert into T6 (name, roll_no, cpi, sem)
	values ('student 03', 270101002, 9.2, 3);
select * from T6;
insert into T6 (name, roll_no, cpi)
	values ('student 03', 270101001, 9.2);
select * from T6;
alter table T6 drop roll_no;
select * from T6;
/*All non-erroneous tasks completed successfully.*/
/*---xxxx---*/


