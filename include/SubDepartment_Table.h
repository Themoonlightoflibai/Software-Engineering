#pragma once
#include <string>

class SubDepartment_Table {
public:
    std::string getSubDepartmentName(const std::string subdepartment_id);

    void updateSubDepartmentName(std::string subdepartment_id, std::string subdepartment_name);


    std::string getSubDepartmentInfo(std::string subdepartment_id);

    void updateSubDepartmentInfo(std::string subdepartment_id, std::string subdepartment_info);


    std::string getSubDepartmentDepartment(std::string subdepartment_id);

    void updateSubDepartmentDepartment(std::string subdepartment_id, std::string department_id);


    //std::vector<std::string>* getSubDepartmentList();

    void insertSubDepartment(std::string subdepartment_id, std::string subdepartment_name = "NULL", std::string subdepartment_info = "NULL", std::string department_id = "NULL");

    void deleteSubDepartment(std::string subdepartment_id);

};