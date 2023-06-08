#pragma once
#include <string>
#include <vector>

class SubDepartment_Table {
public:
    std::string getSubDepartmentName(const std::string subdepartment_id);

    bool updateSubDepartmentName(std::string subdepartment_id, std::string subdepartment_name);


    std::string getSubDepartmentInfo(std::string subdepartment_id);

    bool updateSubDepartmentInfo(std::string subdepartment_id, std::string subdepartment_info);


    std::string getSubDepartmentDepartment(std::string subdepartment_id);

    bool updateSubDepartmentDepartment(std::string subdepartment_id, std::string department_id);


    //std::vector<std::string>* getSubDepartmentList();
    std::vector<std::string>* getSubDepartmentIdByDepatmentId(std::string department_id);

    bool insertSubDepartment(std::string subdepartment_id, std::string subdepartment_name = "NULL", std::string subdepartment_info = "NULL", std::string department_id = "NULL");

    bool deleteSubDepartment(std::string subdepartment_id);

};