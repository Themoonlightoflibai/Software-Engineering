#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <windows.h>
#include "database.h"

using namespace std;
//定义医生表类
class DoctorTable
{
private:
    //医生id列表
    string* ID_list;

public:
    DoctorTable();
    ~DoctorTable();

    //判断医生id是否存在于表中
    int has_id(const string& doctor_id);

    string* get_string_attribute(const string& doctor_id, const string& attribute_name);
    //根据医生id获取患者id
    string* get_patient_list(const string& doctor_id);

    void set_string_attribute(const string& doctor_id, const string& attribute_name, const string& attribute_value);
    
    //新增医生
    void add_doctor(const std:: string& doctor_id);
    //删除医生
    void delete_doctor(const std:: string& doctor_id);

};


//定义医生登录类
class DoctorLogIn
{
private:
    string* id;
    string* password;

public:
    DoctorLogIn(const string& doctor_id);
    ~DoctorLogIn();

    bool login(const string& password);

};