create database assignment2;
use DATABASE assignment2
CREATE table book(
    book_name varchar(50),
    author varchar(50),
    price int,
    quantity INT
);
CREATE table customer (
    Cust_id int ,
    Cust_name varchar(50),
    Addr varchar(50),
    ph_no varchar(50),
    pan_no varchar(50)
);

INSERT INTO `book` (`book_name`, `author`, `price`, `quantity`) VALUES
('dbms', 'rahim', 300, 40),
('dc', 'azom', 500, 20),
('compiler', 'subir', 100, 80),
('nm', 'alom', 500, 50);


INSERT INTO `customer` (`Cust_id`, `Cust_name`, `Addr`, `ph_no`, `pan_no`) VALUES
(1, 'tania', 'raj', '01727738440', '0004'),
(2, 'sultana', 'puthia', '01303148500', '1234'),
(3, 'anni', 'tetulia', '01714879742', '9876');


A
TRUNCATE TABLE customer;


B 
SELECT author
FROM book
WHERE price=200;

C 
SELECT author
FROM book
WHERE price BETWEEN 175 and 250;

D 
SELECT author
FROM book
WHERE author LIKE 'a%';
#% means zero or any number
#_ means one
#exact 5 or any charcter then oi songkhok underscore(_)



  2...
  CREATE TABLE `mark_details` (
  `reg_no` int,
  `mark1` int,
  `mark2` int,
  `mark3` int,
  `total` int,
  foreign key (reg_no) references stu_details(reg_no)
) 

CREATE TABLE `stu_details` (
  `reg_no` int primary key,
  `stu_name` varchar(50),
  `DOB` varchar(50),
  `address` varchar(50),
  `city` varchar(50)
) 


A 

SELECT stu_name FROM stu_details;

B 
SELECT stu_name FROM stu_details
WHERE city = 'puthis';

C 
DROP TABLE stu_details;