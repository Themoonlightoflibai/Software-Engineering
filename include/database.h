#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqlucode.h>
#include <string>
#include <chrono>
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#include "json.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cerr;


//通过odbc连接数据库
void ConnectDB(SQLHENV& env, SQLHDBC& dbc, SQLHSTMT& stmt);

//断开数据库连接
void DisconnectDB(SQLHENV& env, SQLHDBC& dbc, SQLHSTMT& stmt);

void doctor_get_patient_data(std::string patient_id);

void get_patient_list(string doctor_id);

void get_time_patient_list(std::string date, std::string time_id);

void get_doctor_data(string doctor_id);

void modify_doctor_data(std::string doctor_id, int type, std::string content);

void get_timetable(string doctor_id);

void login(std::string phone, std::string password);

void signup(std::string phone, std::string password, std::string name, std::string id_number, int gender, std::string ethnicity);

void newpwd(std::string phone, std::string old_password, std::string new_password);

void get_department_list();

void get_department_details(string department_id);

void get_doctor_list();

void get_subdepartment_doctor_list(string subdepartment_id);

void create_appointment(std::string patient_id, std::string doctor_id, int section);

void cancel_appointment(std::string appointment_id, std::string parent_id);

void patient_get_patient_data(std::string patient_id);

void modify_patient_data(std::string patient_id, std::string name, std::string gender, std::string ethnicity, std::string id_number, std::string phone_number);


