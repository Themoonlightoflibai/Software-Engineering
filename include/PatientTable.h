#pragma once
#include "database.h"


class PatientTable
{
private:
    //患者id列表
    vector<string>* ID_list;

public:
    PatientTable();
    ~PatientTable();

    bool has_id(const string& patient_id);

    string* get_id_by_phone(const string& phone);

    string* get_new_id();

    string get_attribute(const string& patient_id, const string& attribute_name);

    bool set_attribute(const string& patient_id, const string& attribute_name, const string& attribute_value);

    bool add_patient(const string& patient_id);

    bool delete_patient(const string& patient_id);
};

class PatientLogIn
{
private:
    string* id;
    string* password;

public:
    PatientLogIn(const string& patient_id);
    ~PatientLogIn();

    bool login(const string& password);

};