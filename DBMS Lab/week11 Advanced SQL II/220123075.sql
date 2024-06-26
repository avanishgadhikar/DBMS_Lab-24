-- Task 01: Create a database named week11
CREATE DATABASE IF NOT EXISTS week11;
USE week11;

-- Task 01: 1. Declare session variables and prepare statements to create tables
SET @create_sailors_table := 'CREATE TABLE IF NOT EXISTS sailor_name (sid INT AUTO_INCREMENT, name VARCHAR(20), PRIMARY KEY (sid))';
PREPARE create_sailors FROM @create_sailors_table;
EXECUTE create_sailors;

SET @create_boats_table := 'CREATE TABLE IF NOT EXISTS boat_name (bid INT AUTO_INCREMENT, name VARCHAR(20), PRIMARY KEY (bid))';
PREPARE create_boats FROM @create_boats_table;
EXECUTE create_boats;

SET @create_boat_color_table := 'CREATE TABLE IF NOT EXISTS boat_color (bid INT AUTO_INCREMENT, color VARCHAR(20), PRIMARY KEY (bid))';
PREPARE create_boat_color FROM @create_boat_color_table;
EXECUTE create_boat_color;

SET @create_sailor := 'CREATE TABLE IF NOT EXISTS sailor (sid INT AUTO_INCREMENT, name VARCHAR(20), age INT, rating INT, PRIMARY KEY (sid))';
PREPARE create_sailor FROM @create_sailor;
EXECUTE create_sailor;

SET @create_boats := 'CREATE TABLE IF NOT EXISTS boats (bid INT AUTO_INCREMENT, name VARCHAR(20), color VARCHAR(20), PRIMARY KEY (bid))';
PREPARE create_boats FROM @create_boats;
EXECUTE create_boats;

SET @create_reserves := 'CREATE TABLE IF NOT EXISTS reserves (bid INT , sid INT, date date)';
PREPARE create_reserves FROM @create_reserves;
EXECUTE create_reserves;

-- Task 01: 3. Create stored procedure to populate sailor table
DELIMITER //
CREATE PROCEDURE populate_sailors()
BEGIN
    DECLARE i INT DEFAULT 0;
    WHILE i < 500 DO
        INSERT INTO sailor
        (name) SELECT name FROM sailor_name ORDER BY RAND() LIMIT 1;
        UPDATE sailor SET age = FLOOR(RAND() * (65 - 18 + 1)) + 18, rating = FLOOR(RAND() * (10 - 1 + 1)) + 1 WHERE sid = LAST_INSERT_ID();
        SET i = i + 1;
    END WHILE;
END //

DELIMITER ;

CALL populate_sailors();

-- Task 01: 4. Create stored procedure to populate boats table
DELIMITER //
CREATE PROCEDURE populate_boats()
BEGIN
    DECLARE i INT DEFAULT 0;
    WHILE i < 50 DO
        INSERT INTO boats (name) SELECT name FROM boat_name ORDER BY RAND() LIMIT 1;
        UPDATE boats set color =( SELECT color FROM boat_color ORDER BY RAND() LIMIT 1) where bid = last_insert_id();
        -- INSERT INTO boats (name, color) SELECT b.name, bc.color FROM boats b, boat_color bc WHERE b.bid = LAST_INSERT_ID() AND bc.bid = LAST_INSERT_ID();
        SET i = i + 1;
    END WHILE;
END //

DELIMITER ;

CALL populate_boats();



DELIMITER //

CREATE PROCEDURE populate_reserves()
BEGIN
    DECLARE i INT DEFAULT 0;
    WHILE i < 5000 DO
        INSERT INTO reserves (sid, bid, date) SELECT FLOOR(RAND() * (SELECT MAX(sid) FROM sailor) + 1), FLOOR(RAND() * (SELECT MAX(bid) FROM boats) + 1), generate_random_date() FROM dual;
        SET i = i + 1;
    END WHILE;
END //

DELIMITER ;

DELIMITER //
CREATE FUNCTION generate_random_date()
RETURNS DATE deterministic
BEGIN
    DECLARE dd INT;
    DECLARE mm INT;
    SET mm = FLOOR(RAND() * 12) + 1;
    IF mm = 2 THEN
        SET dd = FLOOR(RAND() * 28) + 1;
    ELSEIF mm IN (4, 6, 9, 11) THEN
        SET dd = FLOOR(RAND() * 30) + 1;
    ELSE
        SET dd = FLOOR(RAND() * 31) + 1;
    END IF;
    RETURN CONCAT('2024-', LPAD(mm, 2, '0'), '-', LPAD(dd, 2, '0'));
END //

DELIMITER ;



CALL populate_reserves();

-- Task 01: 9. Create stored function to generate random date
CREATE FUNCTION gen_date()
	



-- Task 01: 10. Create stored procedure to retrieve boat color by sailor id
DELIMITER //

CREATE PROCEDURE get_boat_color_by_sailor_id(IN sailor_id INT, OUT boat_color VARCHAR(20))
BEGIN
    SELECT color INTO boat_color
    FROM reserves natural join boats
    WHERE reserves.sid = sailor_id
    LIMIT 1;
END //

DELIMITER ;

-- Task 01: 11. Create stored procedure to return cumulative rating of sailors who reserved boats on Sundays
DELIMITER //

CREATE PROCEDURE get_cumulative_rating_on_sundays(OUT cumulative_rating INT)
BEGIN
    SELECT SUM(s.rating) INTO cumulative_rating
    FROM reserves as r JOIN sailors as s ON r.sid = s.sid
    WHERE DAYNAME(r.date) = 'Sunday';
END //

DELIMITER ;

-- Task 01: 12. Create stored function to convert rating into letter grade
DELIMITER //

CREATE FUNCTION rating_to_grade(rating INT) 
RETURNS VARCHAR(2) deterministic
BEGIN
	declare grade varchar(2);
    CASE rating
        WHEN 1 THEN RETURN 'F';
        WHEN 2 THEN RETURN 'F';
        WHEN 3 THEN RETURN 'F';
        WHEN 4 THEN RETURN 'DD';
        WHEN 5 THEN RETURN 'CD';
        WHEN 6 THEN RETURN 'CC';
        WHEN 7 THEN RETURN 'BC';
        WHEN 8 THEN RETURN 'BB';
        WHEN 9 THEN RETURN 'AB';
        WHEN 10 THEN RETURN 'AA';
    END CASE;
    return grade;
END //

DELIMITER ;

-- Task 01: 13. Query Formulation.
select sid,rating,rating_to_grade(rating) from sailor;
