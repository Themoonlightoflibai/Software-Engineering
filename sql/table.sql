-- SQLBook: Code
-- Active: 1685814392069@@127.0.0.1@3306
create DATABASE medical;
use  medical;
CREATE TABLE patient (
    id VARCHAR(255) PRIMARY KEY,
    name VARCHAR(255),
    img VARCHAR(255),
    description VARCHAR(255),
    gender INT,
    link VARCHAR(255),
    phone VARCHAR(255),
    ethnicity VARCHAR(255),
    ID_card VARCHAR(255),
    password VARCHAR(255)
);

CREATE TABLE doctortable(
    id VARCHAR(255) PRIMARY KEY,
    name VARCHAR(255),
    img VARCHAR(255),
    gender INT,
    title VARCHAR(255),
    phone VARCHAR(255),
    introcuction VARCHAR(255),
    patient VARCHAR(255),
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


CREATE TABLE Registration(
    id VARCHAR(255),
    pat_id VARCHAR(255),
    apa_id VARCHAR(255),
    primary key (id, pat_id, apa_id)
    # FOREIGN KEY (pat_id) REFERENCES patient(id),
    # FOREIGN KEY (apa_id) REFERENCES SubDepartment(id)
);

CREATE TABLE Doctor_SubDepartment(
    doc_id VARCHAR(255),
    apa_id VARCHAR(255),
    primary key (doc_id, apa_id)
    # FOREIGN KEY (doc_id) REFERENCES doctortable(id),
    # FOREIGN KEY (apa_id) REFERENCES SubDepartment(id)
);

CREATE TABLE Appointment(
    pat_id VARCHAR(255),
    doc_id VARCHAR(255),
    apa_time VARCHAR(255),
    info VARCHAR(255),
    id VARCHAR(255),
    primary key (pat_id, doc_id, id)
    # FOREIGN KEY (pat_id) REFERENCES patient(id),
    # FOREIGN KEY (doc_id) REFERENCES doctortable(id),
    # FOREIGN KEY (id) REFERENCES registration(id)
);

CREATE TABLE Schedule(
    doc_id VARCHAR(255),
    doc_time VARCHAR(255),
    rest INT,
    total INT,
    primary key (doc_id, doc_time)
    # FOREIGN KEY (doc_id) REFERENCES doctortable(id)
);
DEFAULT CHARACTER SET = 'utf8mb4';

