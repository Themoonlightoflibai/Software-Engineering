#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include "database.h"


using namespace std;

class PatientTable
{
private:
    //患者id列表
    string* ID_list;

public:
    PatientTable();
    ~PatientTable();

    int has_id(const string& patient_id);

    string* get_attribute(const string& patient_id, const string& attribute_name);

    void set_attribute(const string& patient_id, const string& attribute_name, const string& attribute_value);

    void add_patient(const string& patient_id);

    void delete_patient(const string& patient_id);
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