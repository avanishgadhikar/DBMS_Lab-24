-- Task 01: Creating Database.
create database week09;
show databases;

-- Task 02: Creating Database Tables. 
use week09;
create table sailors(
	sid int primary key,
    sname char(50),
    rating int,
    age decimal(3, 1)
);

use week09;
create table boats(
	bid int primary key,
    bname char(50),
    bcolor char (50)
);

use week09;
create table reserves(
	sid int references sailors(sid),
    bid int references boats(bid), 
    day char(50),
    primary key(sid, bid, day)
);

-- Task 03: Populating Table. 
use week09;
insert into sailors values 
(22, 'Dustin', 7, 45),
(29, 'Brutus', 1, 33), 
(31, 'Lubber', 8, 55.5),
(32, 'Andy', 8, 25.5),
(58, 'Rusty', 10, 35), 
(64, 'Horatio', 7, 35), 
(71, 'Zorba', 10, 16), 
(74, 'Horatio', 9, 35), 
(85, 'Art', 3, 25.5), 
(95, 'Bob', 3, 63.5);
select * from sailors;

use week09;
insert into boats values
(101, 'Interlake', 'blue'), 
(102, 'Interlake', 'red'), 
(103, 'Clipper', 'green'), 
(104, 'Marine', 'red');
select * from boats;

use week09; 
insert into reserves values
(22, 101, '1998-10-10'),
(22, 102, '1998-10-10'), 
(22, 103, '1998-10-08'),
(22, 104, '1998-10-07'), 
(31, 102, '1998-11-10'), 
(31, 103, '1998-11-06'), 
(31, 104, '1998-11-12'), 
(64, 101, '1998-09-05'), 
(64, 102, '1998-09-08'), 
(74, 102, '1998-09-08');
select * from reserves;

-- Task 04: Creating Views. 
-- Task 04.a updatable: 
create view v1 as (select sid, rating from sailors);
insert into v1 values (91, 7), (92, 8), (93, 9), (94, 10), (22, 8); -- ERROR only for entry with 22 as primary key violated!
update v1 set v1.rating = 8 where (v1.sid = 91);
delete from v1 where v1.sid = 91;
select * from v1;
-- Successful Run!

-- Task 04.b updatable:
create view v2 as (select * from boats where boats.bcolor = 'green'); 
insert into v2 values (205, 'River Mania', 'green'), (206, 'green-bird', 'green'), (207, 'blue-warriors', 'blue');
select * from v2;
select * from boats; -- Blue visible in boats but not in view.

create view v3 as (select * from boats where boats.bcolor = 'green') with check option; 
insert into v3 values (207, 'blue-warriors', 'blue');
select * from v3;
select * from boats; -- Blue not visible in boats as well!

-- Task 04.c updatable: 
create view v4 as (select sid, rating, bid, bname from sailors, boats);
insert into v4(sid, rating) values (80, 8);
insert into v4(bid, bname) values (105, 'Lucky Lake');
update v4 set v4.bname = 'Jumper' where v4.bid = 101;
update v4 set v4.bname = 'Interlake' where v4.bid = 101;
select * from v4;
select * from sailors, boats;
-- All Run Successfully!

-- Task 04.a Not Updatable:

drop view v5;
create view v5 as 
(
select sailors.sid as sid, sname, rating, boats.bid as bid, bname
from sailors, boats, (select sailors.sid as sid, boats.bid as bid, max(rating) as max_ratingR
		from sailors, boats, reserves
        where sailors.sid = reserves.sid and boats.bid = reserves.bid) as a
where boats.bid = a.bid and sailors.sid = a.sid and rating = a.max_ratingR
group by sid
);
select * from v5;
insert into v5(sid, sname, rating) values (80, 'best sailor', 10); -- ERROR Thrown.
update v5 set v5.sid = -9 where v5.sid = 74; -- ERROR Thrown.
delete from v5 where v5.sid = 74; -- ERROR as deletion cannot takew place from Join views.
update v5 set v5.bname = 'Can I get updated?' where v5.bid = 102; -- ERROR Thrown as aggregated views cannot be updated.

-- Task 04.b Not Updatable:
create view v6 as 
(select distinct(sailors.rating) as rating
from sailors);
select * from v6;
insert into v6(rating) values (2); -- ERROR
update v6 set v6.rating = -7 where v6.rating = 7; -- ERROR
delete from v6 where v6.rating = 7;

-- Task 04.c Not Updatable:
create view v7 as 
(select boats.bid as bid, bname, bcolor, sa.rating as rating, sa.age as age
from boats, reserves, sailors as sa, sailors as sb
where boats.bid = reserves.bid and sa.sid = reserves.sid and sa.rating = sb.rating);
insert into v7(sid, sname, rating, age) values (80, 'budding sailor', 10, 25); -- ERROR Thrown Target table not insertable into. 
update v7 set v7.rating = 6 where v7.rating  = 8; -- ERROR Thrown!
delete from v7 where v7.rating = 7; -- ERROR Thrown!

-- Task 04.d Not Updatable:
create view v8 as 
(select boats.bid as bid, bname, bcolor, sa.rating as rating, sa.age as age
from boats, reserves, sailors as sa, sailors as sb
where boats.bid = reserves.bid and sa.sid = reserves.sid and sa.rating = sb.rating
having sa.age > 36);
select bid, bname, bcolor, rating, age from v8;
insert into v8(sid, sname, rating, age) values (80, 'budding sailor', 10, 25); -- ERROR Thrown Target table not insertable into. 
update v8 set v8.rating = 6 where v8.rating  = 8;
delete from v8 where v8.rating = 7;

-- Task 04.e Not Updatable:
create view v9 as 
(select sailors.sid as sid, sname, boats.bid as bid, bcolor
from sailors, boats, reserves
where reserves.sid = sailors.sid and boats.bid = reserves.bid and boats.bcolor = 'blue')
union
(select sailors.sid as sid, sname, boats.bid as bid, bcolor
from sailors, boats, reserves
where reserves.sid = sailors.sid and boats.bid = reserves.bid and boats.bcolor = 'green');
select * from v9;
insert into v9(sid, rating) values (81, 9); -- ERROR Thrown!
update v9 set v9.sid = 9 where v9.sid = 22; -- ERROR Thrown!
delete from v9 where v9.sid = 22; -- ERROR Thrown!

-- Task 04 View Using Views
create view v10 as(select rating from v1);
insert into v10 values (7), (8), (9), (10), (8); -- ERROR as underlying table deos not have a default value.
select * from v10;
update v10 set v10.rating = 9 where v10.rating = 8;
delete from v10 where v10.rating = 10;

create view v11 as(
select sid, bname, day
from reserves, v2
where v2.bid = reserves.bid
);
select * from v11;

-- Task 04 Effect of Altering Original Tables On Views:
alter table sailors change column rating rting int;
select * from v1;
select * from v4;
select * from v5;
select * from v6;
select * from v8;
select * from v10;

alter table sailors change column rting rating int;
select * from v1;
select * from v4;
select * from v5;
select * from v6;
select * from v8;
select * from v10;

delete rating from sailors;
select * from v1;
select * from v4;
select * from v5;
select * from v6;
select * from v8;
select * from v10;

-- Task 04 Type Conversion:
create table sailors_1(
	sid int primary key,
    sname char(50),
    rating int,
    age decimal(3, 1)
);

use week09;
create table boats_1(
	bid int primary key,
    bname char(50),
    bcolor char (50)
);

use week09;
create table reserves_1(
	sid int references sailors(sid),
    bid int references boats(bid), 
    day char(50),
    primary key(sid, bid, day)
);

-- Task 03: Populating Table. 
use week09;
insert into sailors_1 values 
(22, 'Dustin', 7, 45),
(29, 'Brutus', 1, 33), 
(31, 'Lubber', 8, 55.5),
(32, 'Andy', 8, 25.5),
(58, 'Rusty', 10, 35), 
(64, 'Horatio', 7, 35), 
(71, 'Zorba', 10, 16), 
(74, 'Horatio', 9, 35), 
(85, 'Art', 3, 25.5), 
(95, 'Bob', 3, 63.5);
select * from sailors_1;

use week09;
insert into boats_1 values
(101, 'Interlake', 'blue'), 
(102, 'Interlake', 'red'), 
(103, 'Clipper', 'green'), 
(104, 'Marine', 'red');
select * from boats_1;

use week09; 
insert into reserves_1 values
(22, 101, '1998-10-10'),
(22, 102, '1998-10-10'), 
(22, 103, '1998-10-08'),
(22, 104, '1998-10-07'), 
(31, 102, '1998-11-10'), 
(31, 103, '1998-11-06'), 
(31, 104, '1998-11-12'), 
(64, 101, '1998-09-05'), 
(64, 102, '1998-09-08'), 
(74, 102, '1998-09-08');
select * from reserves_1;

alter table sailors_1 modify sid smallint;
alter table boats modify bid char(3);
alter table boats modify bcolor char(5);
select * from boats_1;
select * from sailors_1;

-- END! -- 