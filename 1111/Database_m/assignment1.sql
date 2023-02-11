CREATE DATABASE Assignment1;
USE Assignment1;
CREATE TABLE employee(
    employee_name varchar(50) primary key,
    street varchar(50),
    city varchar(50)
    );
 CREATE TABLE company(
     company_name varchar(50),
     city varchar(50),
     primary key(company_name)
     );
     CREATE TABLE works(
         employee_name varchar(50),
         company_name varchar(50),
         salary decimal(8,2),
         primary key (employee_name,company_name),/*composite key*/
         FOREIGN key(company_name) REFERENCES company(company_name),
         FOREIGN key (employee_name) REFERENCES employee(employee_name)
         );
CREATE TABLE manages(
    employee_name varchar(50),
    manager_name varchar(50),
    PRIMARY key (employee_name,manager_name),
    FOREIGN key (employee_name) REFERENCES employee(employee_name),
    FOREIGN key (manager_name) REFERENCES employee(employee_name)
    );

INSERT INTO employee(employee_name,street,city)
VALUES
('Z','XX','AA'),
('Y','YY','CC'),
('X','CX','FF'),
('W','WX','AA');

INSERT INTO `company` (`company_name`, `city`) VALUES
('A', 'AA'),
('B', 'BB'),
('C', 'CC'),
('D', 'DD');

INSERT INTO works(employee_name,company_name,salary)
VALUES
('W','A',10000),
('X','B',150000),
('Y','C',200000),
('Z','C',120000);

A
SELECT employee.employee_name,street,city ,works.company_name,works.salary
FROM employee,works
WHERE employee.employee_name = works.employee_name and works.company_name = 'C' and works.salary>10000;

B
SELECT employee.employee_name
FROM works,company,employee
WHERE employee.employee_name=works.employee_name and company.company_name=works.company_name and employee.city=company.city;

D
SELECT employee.employee_name
FROM employee,works
WHERE employee.employee_name=works.employee_name and works.company_name!='C';

E
SELECT employee.employee_name
FROM employee,works
WHERE employee.employee_name=works.employee_name and salary>(SELECT MAX(salary) FROM works WHERE works.company_name='A');

F
SELECT employee.employee_name
FROM employee,works
WHERE employee.employee_name=works.employee_name and salary>(SELECT MAX(salary) FROM works WHERE works.company_name='A');

G
SELECT employee.employee_name
FROM employee,works
WHERE employee.employee_name=works.employee_name and salary>(SELECT AVG(salary) FROM works WHERE works.company_name='A');


H
SELECT company_name
FROM works
GROUP by company_name
HAVING SUM(salary)=(SELECT MIN(total)
                    FROM (SELECT company_name,SUM(salary) AS total
                          FROM works GROUP by company_name) As tmp);