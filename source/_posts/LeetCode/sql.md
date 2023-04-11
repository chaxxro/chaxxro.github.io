---
toc:
  enable: true
  number: false
  max_depth: 3
title: sql
date: 2023-04-11 20:47:27
tags: SQL
categories: SQL
---

## 最晚入职员工所有信息

```sql
CREATE TABLE `employees` (
`emp_no` int(11) NOT NULL,  -- '员工编号'
`birth_date` date NOT NULL,
`first_name` varchar(14) NOT NULL,
`last_name` varchar(16) NOT NULL,
`gender` char(1) NOT NULL,
`hire_date` date NOT NULL,
PRIMARY KEY (`emp_no`));

select * from employees where hire_date = (
    select max(hire_date) from employees
);

select * from employees order by hire_date desc limit 1;

# 入职时间倒数第三的员工所有信息
select * from employees order by hire_date desc limit 1 offset 2;
```

## 各个部门当前领导当前薪水和部门

```sql
CREATE TABLE `salaries` (
`emp_no` int(11) NOT NULL, -- '员工编号',
`salary` int(11) NOT NULL,
`from_date` date NOT NULL,
`to_date` date NOT NULL,
PRIMARY KEY (`emp_no`,`from_date`));

CREATE TABLE `dept_manager` (
`dept_no` char(4) NOT NULL, -- '部门编号'
`emp_no` int(11) NOT NULL, --  '员工编号'
`to_date` date NOT NULL,
PRIMARY KEY (`emp_no`,`dept_no`));

select a.*, b.dept_no from salaries a left join dept_manager b 
on a.from_date = b.from_date
where a.from_date = '9999-01-01' order by a.emp_no; 
```

## 所有员工入职时薪水情况

```sql
CREATE TABLE `employees` (
`emp_no` int(11) NOT NULL,
`birth_date` date NOT NULL,
`first_name` varchar(14) NOT NULL,
`last_name` varchar(16) NOT NULL,
`gender` char(1) NOT NULL,
`hire_date` date NOT NULL,
PRIMARY KEY (`emp_no`));

CREATE TABLE `salaries` (
`emp_no` int(11) NOT NULL,
`salary` int(11) NOT NULL,
`from_date` date NOT NULL,
`to_date` date NOT NULL,
PRIMARY KEY (`emp_no`,`from_date`));

select emp_no, salary from salaries
group by emp_no having salary <= min(salary)
order by emp_no desc;

select a.emp_no, b.salary from employees a, salaries b
where a.emp_no = b.emp_no and a.hire_date = b.from_date
order by a.emp_no desc;
```

## 薪水变动超过 15 次的员工

```sql
CREATE TABLE `salaries` (
`emp_no` int(11) NOT NULL,
`salary` int(11) NOT NULL,
`from_date` date NOT NULL,
`to_date` date NOT NULL,
PRIMARY KEY (`emp_no`,`from_date`));

select emp_no, count(emp_no) t from salaries
group by emp_no having count(emp_no) > 15;

# 所有员工当前薪水情况
select distinct salary from salaries
where to_date = '9999-01-01'
order by salary desc;
```

## 获取员工的经理

```sql
CREATE TABLE `dept_emp` (
`emp_no` int(11) NOT NULL, -- '所有的员工编号'
`dept_no` char(4) NOT NULL, -- '部门编号'
`from_date` date NOT NULL,
`to_date` date NOT NULL,
PRIMARY KEY (`emp_no`,`dept_no`));

CREATE TABLE `dept_manager` (
`dept_no` char(4) NOT NULL, -- '部门编号'
`emp_no` int(11) NOT NULL, -- '经理编号'
`from_date` date NOT NULL,
`to_date` date NOT NULL,
PRIMARY KEY (`emp_no`,`dept_no`));

select a.emp_no, b.emp_no manager_no from
dept_emp a, dept_manager b
where b.to_date = '9999-01-01' 
and a.dept_no = b.dept_no
and a.emp_no != b.emp_no;

select a.emp_no, b.emp_no manager_no from
dept_emp a inner join dept_manager b
on a.dept_no = b.dept_no
where b.to_date = '9999-01-01' 
and a.emp_no != b.emp_no;
```