#pragma once
#include<string>
#include <vector>


class Department_Table {
public:
    std::string getDepartmentName(std::string department_id);

    bool updateDepartmentName(std::string department_id, std::string department_name);

    std::string getDepartmentInfo(std::string department_id);

    bool updateDepartmentInfo(std::string department_id, std::string department_info);

    std::vector<std::string>* getDepartmentList();

    bool insertDepartment(std::string department_id, std::string department_name = "NULL", std::string department_info = "NULL");

    bool deleteDepartment(std::string department_id);
};