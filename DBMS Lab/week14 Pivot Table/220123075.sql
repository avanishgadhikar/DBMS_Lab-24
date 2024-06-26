-- Question 1: 
-- Task 01. Creating Database week14
drop database if exists week14;
create database week14;
use week14;
-- x.

-- Task 02. Creating necessary tables.
create table location (
	location_id int primary key,
    city char(10), 
    state char(2), 
    country char(20)
);

create table product (
	product_id int primary key, 
    product_name char(10), 
    category char(20), 
    price int
);

create table sale (
	product_id int, 
    time_id int, 
    location_id int, 
    sales int, 
    primary key (product_id, time_id, location_id)
);

-- x.

-- Task 03. Populating the tables.
-- location table: 
insert into location values(1, 'Madison', 'WI', 'USA');
insert into location values(2, 'Fresno', 'CA', 'USA');
insert into location values(5, 'Chennai', 'TN', 'India');

-- product table:
insert into product values(11, 'Lee Jeans', 'Apparel', 25);
insert into product values(12, 'Zord', 'Toys', 18);
insert into product values(13, 'Biro Pen', 'Stationery', 2);

-- sale table:
insert into sale values(11, 1995, 1, 25);
insert into sale values(11, 1996, 1, 8);
insert into sale values(11, 1997, 1, 15);
insert into sale values(12, 1995, 1, 30);
insert into sale values(12, 1996, 1, 20);
insert into sale values(12, 1997, 1, 50);
insert into sale values(13, 1995, 1, 8);
insert into sale values(13, 1996, 1, 10);
insert into sale values(13, 1997, 1, 10);
insert into sale values(11, 1995, 2, 35);
insert into sale values(11, 1996, 2, 22);
insert into sale values(11, 1997, 2, 10);
insert into sale values(12, 1995, 2, 26);
insert into sale values(12, 1996, 2, 45);
insert into sale values(12, 1997, 2, 20);
insert into sale values(13, 1995, 2, 20);
insert into sale values(13, 1996, 2, 40);
insert into sale values(13, 1997, 2, 5);

select * from location;
select * from product;
select * from sale;

-- x.

-- Task 04: Building a pivot table.
-- a. Constructing pivot table year_state_01-
drop table if exists year_state_01;
create table year_state_01 (
	year char(10),
	WI int, 
    CA int, 
    Total int
);

insert into year_state_01 values(
	'1995',
	(select sum(sales) from sale natural join product natural join location where time_id = 1995 and state = 'WI'),
    (select sum(sales) from sale natural join product natural join location where time_id = 1995 and state = 'CA'),
    (select sum(sales) from sale natural join product natural join location where time_id = 1995 and (state = 'WI' or state = 'CA'))
);
insert into year_state_01 values(
	'1996',
	(select sum(sales) from sale natural join product natural join location where time_id = 1996 and state = 'WI'),
    (select sum(sales) from sale natural join product natural join location where time_id = 1996 and state = 'CA'),
    (select sum(sales) from sale natural join product natural join location where time_id = 1996 and (state = 'WI' or state = 'CA'))
);
insert into year_state_01 values(
	'1997',
	(select sum(sales) from sale natural join product natural join location where time_id = 1997 and state = 'WI'),
    (select sum(sales) from sale natural join product natural join location where time_id = 1997 and state = 'CA'),
    (select sum(sales) from sale natural join product natural join location where time_id = 1997 and (state = 'WI' or state = 'CA'))
);
insert into year_state_01 values(
	'Total',
	(select sum(sales) from sale natural join product natural join location where (time_id = 1995 or time_id = 1996 or time_id = 1997) and state = 'WI'),
    (select sum(sales) from sale natural join product natural join location where (time_id = 1995 or time_id = 1996 or time_id = 1997) and state = 'CA'),
    (select sum(sales) from sale natural join product natural join location)
);

select * from year_state_01;

-- b. Creating a pivot table year_state_02:
drop table if exists year_state_02_01;
create table year_state_02_01 
select 
	time_id as year, 
    sum(case when location.state = 'WI' then sale.sales else 0 end) as 'WI', 
    sum(case when location.state = 'CA' then sale.sales else 0 end) as 'CA'
from sale natural join product natural join location
group by time_id ;
select * from year_state_02_01;

drop table if exists year_state_02_02;
create table year_state_02_02 
select 
    sum(case when location.state = 'WI' or location.state = 'CA' then sale.sales else 0 end) as 'Total'
from sale natural join product natural join location
group by time_id ;
select * from year_state_02_02;

drop table if exists year_state_02_03; 
create table year_state_02_03 
select  
    sum(case when location.state = 'WI' then sale.sales else 0 end) as 'WI', 
    sum(case when location.state = 'CA' then sale.sales else 0 end) as 'CA'
from sale natural join product natural join location;
select * from year_state_02_03;

drop table if exists year_state_02_04;
create table year_state_02_04 
select 
    sum(case when location.state = 'WI' or location.state = 'CA' then sale.sales else 0 end) as 'Total'
from sale natural join product natural join location;
select * from year_state_02_04;

-- c. Creating a table year_state_03- 
drop table if exists year_state_03;
create table year_state_03 
select 
	time_id as year, 
    sum(case when location.state = 'WI' then sale.sales else 0 end) as 'WI', 
    sum(case when location.state = 'CA' then sale.sales else 0 end) as 'CA', 
    sum(sales) as 'Total'
from sale natural join product natural join location
group by time_id 
union
select 
	'Total' as year, 
    sum(case when location.state = 'WI' then sale.sales else 0 end) as 'WI', 
    sum(case when location.state = 'CA' then sale.sales else 0 end) as 'CA', 
    sum(sales) as 'Total'
from sale natural join product natural join location;
select * from year_state_03;

-- d. Creating a pivot table with rollup.
drop table if exists year_state_04;
create table year_state_04 
select 
	if(grouping(time_id), 'Total', time_id)as year, 
    sum(case when location.state = 'WI' then sale.sales else 0 end) as 'WI', 
    sum(case when location.state = 'CA' then sale.sales else 0 end) as 'CA',
    sum(sales) as 'Total'
from sale join location on location.location_id = sale.location_id
group by sale.time_id with rollup;
select * from year_state_04;

-- XXX --