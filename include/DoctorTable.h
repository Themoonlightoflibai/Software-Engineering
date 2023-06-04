#pragma once
#include "database.h"


//定义医生表类
class DoctorTable
{
private:
    //医生id列表
    vector<string>* ID_list;

public:
    DoctorTable();
    ~DoctorTable();

    //判断医生id是否存在于表中
    bool has_id(const string& doctor_id);

    vector<string>* get_doctor_list();

    string get_string_attribute(const string& doctor_id, const string& attribute_name);
    //int get_gender(const string& doctor_id);
    //根据医生id获取患者id
    vector<string>* get_patient_list(const string& doctor_id);

    bool set_string_attribute(const string& doctor_id, const string& attribute_name, const string& attribute_value);
    
    //新增医生
    bool add_doctor(const std:: string& doctor_id);
    //删除医生
    bool delete_doctor(const std:: string& doctor_id);

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