#pragma once
#include<string>


class Department_Table {
public:
    std::string getDepartmentName(std::string department_id);

    void updateDepartmentName(std::string department_id, std::string department_name);

    std::string getDepartmentInfo(std::string department_id);

    void updateDepartmentInfo(std::string department_id, std::string department_info);

    //std::vector<std::string>* getDepartmentList();

    void insertDepartment(std::string department_id, std::string department_name = "NULL", std::string department_info = "NULL");

    void deleteDepartment(std::string department_id);
};