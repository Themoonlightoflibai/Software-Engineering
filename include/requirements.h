#include <iostream>
#include <string>
#include <vector>
#include <sql.h>
#include <sqlext.h>
#include "jsoncpp.cpp"

//根据分工完成如下表的类的定义
class Patient_Table;
class Doctor_Table;
class Department_Table;
class subDepartment_Table;
class Registration_Table;
class Appointment_Table;
class Scheduling_Table;
class Docter_subDepartment_Table;

void get_patient_list(int doctor_id);
void get_time_patient_list(std::string date, std::string time_id);
void get_doctor_data(int doctor_id);
void modify_doctor_data(std::string doctor_id, int type, sstd::tring content);
void get_timetable(int doctor_id);
void get_patient_data(std::string patient_id);
void login(std::string username, std::string password);
void signup(std::string username, std::string password, std::string name, std::string id_number, int gender, std::string ethnicity);
void newpwd(std::string username, std::string old_password; std::string new_password);
void get_department_list();
void get_department_details(int department_id);
void get_doctor_list();
void get_subdepartment_doctor_list(int subdepartment_id);
void create_appointment(std::string patient_id, std::string doctor_id, int section);
void cancel_appointment(std::string appointment_id);
void get_patient_data(std::string patient_id);
void modify_patient_data(std::string patient_id, std::string name, int gender, std::string ethnicity, std::string id_number, std::string phone_number);