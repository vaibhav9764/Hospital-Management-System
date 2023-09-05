CREATE DATABASE hospitalmanagement;

use hospitalmanagement;

CREATE TABLE users( 
    username Varchar(20), 
    password varchar(20) 
);

INSERT INTO users (username, password) VALUES ('admin', 'admin');

CREATE TABLE appointment(
    doctor varchar(20),
    patientname varchar(20),
    time varchar(20),
    age varchar(10),
    contactno varchar(20),
    symptoms varchar(30)
);

INSERT INTO appointment(doctor, patientname, time, age, contactno, symptoms) VALUES ('Dr. Waqar', 'Raj', '10:30 AM', '28', '9945367281', 'cough');
INSERT INTO appointment(doctor, patientname, time, age, contactno, symptoms) VALUES ('Dr. Shankar', 'Rana', '1:30 PM', '18', '9945367281', 'fever');
INSERT INTO appointment(doctor, patientname, time, age, contactno, symptoms) VALUES ('Dr. Krishna', 'Rahul', '9 AM', '38', '9945367281', 'mild fever');
INSERT INTO appointment(doctor, patientname, time, age, contactno, symptoms) VALUES ('Dr. Roy', 'Ravi', '1 PM', '28', '9945367281', 'cough');

CREATE TABLE staff(
    name varchar(20),
    age  varchar(10),
    salary varchar(50),
    contactno varchar(20),
    position varchar(40)
);

INSERT INTO staff(name, age, salary, contactno, position) VALUES ('Vikram Raj', '33', '20000', '9934627721', 'dispensor');