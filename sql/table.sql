
drop DATABASE medical;
create DATABASE medical;
use  medical;
CREATE TABLE patient (
    id VARCHAR(255) PRIMARY KEY,
    name VARCHAR(255),
    img VARCHAR(255),
    description VARCHAR(255),
    gender VARCHAR(255),
    link VARCHAR(255),
    phone VARCHAR(255),
    ethnicity VARCHAR(255),
    ID_card VARCHAR(255),
    password VARCHAR(255)
);

CREATE TABLE doctor(
    id VARCHAR(255) PRIMARY KEY,
    name VARCHAR(255),
    img VARCHAR(255),
    gender VARCHAR(255),
    title VARCHAR(255),
    introcuction VARCHAR(255),
    patient VARCHAR(255),
    phone VARCHAR(255),
    password VARCHAR(255)
);

CREATE TABLE Department(
    id VARCHAR(255) PRIMARY KEY,
    name VARCHAR(255),
    info VARCHAR(255)
);

CREATE TABLE SubDepartment(
    id VARCHAR(255) PRIMARY KEY,
    name VARCHAR(255),
    info VARCHAR(255),
    apa_id VARCHAR(255),
    FOREIGN KEY (apa_id) REFERENCES Department(id)
);


CREATE TABLE registration(
    id VARCHAR(255) PRIMARY KEY,
    patient_id VARCHAR(255),
    apa_id VARCHAR(255),
    FOREIGN KEY (patient_id) REFERENCES patient(id),
    FOREIGN KEY (apa_id) REFERENCES SubDepartment(id)
);

CREATE TABLE doctor_subdepartment(
    doc_id VARCHAR(255) PRIMARY KEY,
    apa_id VARCHAR(255),
    FOREIGN KEY (doc_id) REFERENCES doctor(id),
    FOREIGN KEY (apa_id) REFERENCES SubDepartment(id)
);

CREATE TABLE appointment(
    pat_id VARCHAR(255),
    doc_id VARCHAR(255),
    app_time VARCHAR(255),
    info VARCHAR(255),
    app_id VARCHAR(255),
    primary key (pat_id, doc_id),
    FOREIGN KEY (pat_id) REFERENCES patient(id),
    FOREIGN KEY (doc_id) REFERENCES doctor(id),
    FOREIGN KEY (app_id) REFERENCES registration(id)
);

CREATE TABLE schdeule(
    doc_id VARCHAR(255),
    doc_schedule VARCHAR(255),
    rest INT,
    total INT,
    primary key (doc_id, doc_schedule),
    FOREIGN KEY (doc_id) REFERENCES doctor(id)
);
insert into medical.doctor values('22156335','李四','http://dummyimage.com/400x400','1','主治医师','毕业于北京大学医学院，擅长脑部肿瘤手术','335568','18888888888','123456');
#SELECT * FROM medical.doctor ;
update medical.doctor set patient = '335568,559863' where id='22156335';
#SELECT * FROM medical.doctor ;
insert into medical.patient values('335568','张三','http://dummyimage.com/400x400','小臂骨裂','1','http://dummy.com/400','18888888888','汉族','52688436586422482203','123456');
update medical.patient set phone = '16666666666' where id='335568';
insert into medical.Department values('99853','骨科','骨骼相关疾病');
insert into medical.SubDepartment values('58866','骨科处置室','处置相关骨骼手术','99853');
insert into medical.registration values('99853','335568','58866');
#SELECT * FROM medical.registration ;
insert into medical.appointment values('335568','22156335','202308061','复查','99853');
insert into medical.schdeule values('22156335', '2023-06-01,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-01,2',30,30);
insert into medical.schdeule values('22156335', '2023-06-02,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-02,2',30,30);
insert into medical.schdeule values('22156335', '2023-06-03,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-03,2',30,30);
insert into medical.schdeule values('22156335', '2023-06-04,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-04,2',30,30);
insert into medical.schdeule values('22156335', '2023-06-05,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-05,2',30,30);
insert into medical.schdeule values('22156335', '2023-06-06,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-06,2',30,30);
insert into medical.schdeule values('22156335', '2023-06-07,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-07,2',30,30);
insert into medical.schdeule values('22156335', '2023-06-08,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-08,2',30,30);
insert into medical.schdeule values('22156335', '2023-06-09,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-09,2',30,30);
insert into medical.schdeule values('22156335', '2023-06-10,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-10,2',30,30);
insert into medical.schdeule values('22156335', '2023-06-11,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-11,2',30,30);
insert into medical.schdeule values('22156335', '2023-06-12,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-12,2',30,30);
insert into medical.schdeule values('22156335', '2023-06-13,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-13,2',30,30);
insert into medical.schdeule values('22156335', '2023-06-14,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-14,2',30,30);
insert into medical.schdeule values('22156335', '2023-06-15,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-15,2',30,30);
insert into medical.schdeule values('22156335', '2023-06-16,1',30,30);
insert into medical.schdeule values('22156335', '2023-06-16,2',30,30);
SELECT * FROM medical.patient ;
SELECT id FROM medical.patient WHERE phone = '18888888888';