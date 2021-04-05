<div align = "center">第四章第五章SQL作业</div>

 <div align = "center">班级： 计科1905  姓名：殷绍轩  学号： 2018010636 </div>



![img](file:////tmp/wps-franktudor/ksohtml/wps4Pi67z.png)   

 

 

 

 

 

1. 在SQL Server或MY SQL数据库SERVER上，建立自己的数据库，比如”张三DB”。

```sql
CREATE DATABASE myDB;
```



2. 在自己已经建立的数据库上，按照课堂派上传的” 建库、表及第5章数据插入语句.txt”文件, 建立学生表(Student)、课程表(Course)、选课表(Course)三个表。

   ```sql
   CREATE TABLE Student (
   Sno CHAR(10) PRIMARY KEY,
   Sname VARCHAR(30) NOT NULL,
   Ssex CHAR(2),
   Sage INT,
   Sdept VARCHAR(20),
   check (Ssex ='男' OR Ssex ='女'),
   check (Sage >=10 AND Sage <=60)
   )
   
   CREATE TABLE Course (
   Cno CHAR(4) PRIMARY KEY,
   Cname VARCHAR(20) NOT NULL,
   Credit INT NOT NULL,
   Semester INT NOT NULL,
   Ctype VARCHAR(10) NOT NULL
   )
   
   CREATE TABLE SC (
   Sno CHAR(10) NOT NULL,
   Cno CHAR(4) NOT NULL,
   Grade TINYINT,
   check (Grade >=0 and Grade <=100),
   PRIMARY KEY (Sno, Cno),
   FOREIGN KEY (Sno) REFERENCES Student (Sno),
   FOREIGN KEY (Cno) REFERENCES Course (Cno)
   )
   ```

   

3. 按照课堂派上传的” 建库、表及第5章数据插入语句.txt”文件, 为学生表(Student)、课程表(Course)、选课表(SC)三个表插入(录入)一些基本数据。

   ```sql
   insert into Student values('2018111001','李勇','男',21,'计算机系');
   insert into Student values('2018111002','刘晨','男',20,'计算机系');
   insert into Student values('2018211003','王敏','女',20,'计算机系');
   insert into Student values('2018211004','张小红','女',19,'计算机系');
   insert into Student values('2018211001','张立','男',20,'信息管理系');
   insert into Student values('2018211002','吴宾','女',19,'信息管理系');
   insert into Student values('2018311004','张海','男',20,'通信工程系');
   insert into Student values('2018311001','钱小平','女',21,'通信工程系');
   insert into Student values('2018311002','王大力','男',20,'通信工程系');
   insert into Student values('2018311003','张姗姗','女',19,'通信工程系');
   
   insert into Course values('C001','高等数学',4,1,'必修');
   insert into Course values('C002','大学英语',3,1,'必修');
   insert into Course values('C003','大学英语',3,2,'必修');
   insert into Course values('C004','计算机文化学',2,2,'选修');
   insert into Course values('C005','VB',2,3,'选修');
   insert into Course values('C006','数据库系统原理与应用',4,5,'必修');
   insert into Course values('C007','数据结构',4,4,'必修');
   insert into Course values('C008','计算机网络',4,4,'必修');
   
   insert into SC values('2018111001','C001',96);
   insert into SC values('2018111001','C002',80);
   insert into SC values('2018111001','C003',84);
   insert into SC values('2018111001','C005',62);
   insert into SC values('2018111002','C001',92);
   insert into SC values('2018111002','C002',90);
   insert into SC values('2018111002','C004',84);
   insert into SC values('2018111002','C001',76);
   insert into SC values('2018111002','C004',85);
   insert into SC values('2018111002','C005',73);
   insert into SC values('2018111002','C007',NULL);
   insert into SC values('2018211003','C001',50);
   insert into SC values('2018211003','C004',80);
   insert into SC values('2018311001','C001',55);
   insert into SC values('2018311001','C004',80);
   insert into SC values('2018311001','C007',NULL);
   insert into SC values('2018311003','C004',78);
   insert into SC values('2018311003','C005',65);
   insert into SC values('2018311003','C007',NULL);
   ```

   

在以上三个表的基础上，完成下列查询：

4. 查询计算机系年龄在20~23岁之间的的学生信息。

   ```sql
    SELECT * FROM Student WHERE Sdept='计算机系' and Sage>=20 and Sage<=23;
   ```

   

5. 查询计算机系的学生的姓名、性别和年龄信息。

   ```sql
   SELECT Sname 姓名,Ssex 性别,Sage 年龄 FROM Student WHERE Sdept='计算机系';
   ```

   

6. 查询所有课程类型为“必修”的课程名、开设学期、学分。

   ```sql
   SELECT Cname 课程名, Semester 开设学期, Credit 学分 FROM Course WHERE Ctype='必修';
   ```

   

7. 查询张三所学必修课程的总学分。(需要用到表的连接、SUM集合函数)

   ```sql
   SELECT Sname, SUM(Credit) 必修总学分 FROM Student INNER JOIN SC ON (SC.Sno=Student.Sno) INNER JOIN Course ON (Course.Cno=SC.Cno) WHERE Sname='李勇' AND Ctype='必修';
   /*用李勇代替*/
   ```

8. 查询姓名为张三的学生所学的专业。

   ```sql
   SELECT Sname, Sdept FROM Student WHERE Sname='李勇';/*没有张三用李勇代替*/
   
   ```

   

9. 查询所有姓张、姓李、姓王的学生信息。

   ```sql
   SELECT * FROM Student WHERE Sname LIKE '李%' OR Sname LIKE '张%' OR Sname LIKE '王%';
   ```

   

10. 查询学生张三所学的“数据库”课程的考试成绩。(需要用到表的连接、LIKE)

    ```sql
    SELECT Sname,Cname,Grade FROM Student JOIN SC ON(SC.Sno=Student.Sno) JOIN Course ON (Course.Cno=SC.Cno) WHERE Sname='李勇';/*用李勇代替张三*/
    
    ```

    

11. 查询张三所选修的所有课程性质为“必修”的课程名称。

    ```sql
    SELECT Sname,Cname,Ctype FROM Student JOIN SC ON (SC.Sno=Student.Sno) JOIN Course ON (Course.Cno=SC.Cno) WHERE Sname='李勇' AND Ctype='必修';/*用李勇代替张三*/
    ```

    

12. 查询所有学习了“数据库”课程的学生学号、考试成绩，并按照考试成绩从大到小排序。

    ```sql
    SELECT Student.Sno,Grade FROM Course JOIN SC ON (SC.Cno=Course.Cno) JOIN Student ON (Student.Sno=SC.Sno) order by Grade desc;
    ```

    

13. 查询计算机系学生的年龄，并按年龄从小到大排序。

    ```sql
    SELECT Sname,Sage FROM Student ORDER BY Sage asc;
    ```

    

14. 查询每个专业的学生总数，要求列出专业名称和每个专业的学生总数。

    ```sql
     SELECT Sdept,COUNT(Sdept) FROM Student GROUP BY Sdept;
    ```

    

15. 查询“计算机系”和“通信工程系”两个专业的学生总数，要求列出专业名称和这两个专业的学生总数。

    ```sql
    SELECT Sdept,COUNT(Sdept) FROM Student WHERE Sdept='计算机系' OR Sdept='通信工程系' GROUP BY Sdept;
    ```

    

16. 计算课程号为“C001”的课程考试最高分、最低分、平均分。

    ```sql
    SELECT Course.Cno,MAX(Grade) 最高分, MIN(Grade) 最低分, AVG(Grade) FROM SC CROSS JOIN Course ON (Course.Cno=SC.Cno) WHERE Course.Cno='C001';
    ```

    

17. 大家还可以自己编点题目练习SQL语句。(这个自己做主吧，尽量把各种语句和使用方式都练习到。)

Create  table  teacher(

Tno char(8)  PRIMARY KEY,

TEL CHAR(11),

 

………

Check TEL LIKE ‘[1-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]’

)