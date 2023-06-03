#include "database.h"

class SubDepartment_Table{
public:
    std::string* getSubDepartmentName(const std::string subdepartment_id);

    void updateSubDepartmentName(std::string subdepartment_id, std::string subdepartment_name);
    

    std::string* getSubDepartmentInfo(std::string subdepartment_id);

    void updateSubDepartmentInfo(std::string subdepartment_id, std::string subdepartment_info);


    std::string* getSubDepartmentDepartment(std::string subdepartment_id);

    void updateSubDepartmentDepartment(std::string subdepartment_id, std::string department_id);


    std::vector<std::string>* getSubDepartmentList();

    void insertSubDepartment(std::string subdepartment_id, std::string subdepartment_name = "NULL", std::string subdepartment_info = "NULL", std::string department_id = "NULL");

    void deleteSubDepartment(std::string subdepartment_id);

private:
    std::string get(std::string name){
        return "SELECT * FROM SubDepartment WHERE subdepartment_id = '" + name + "';";
    }

    std::string update(std::string name, std::string content, std::string id){
        return "UPDATE SubDepartment SET " + name + " = '" + content + "' WHERE subdepartment_id = '" + id + "';";
    }
    
    std::string del(std::string name){
        return "DELETE FROM SubDepartment WHERE subdepartment_id = '" + name + "';";
    }
    std::string insert(std::string subdepartment_id, std::string subdepartment_name, std::string subdepartment_info, std::string department_id){
        return "INSERT INTO SubDepartment VALUES ('" + subdepartment_id + "', '" + subdepartment_name + "', '" + subdepartment_info + "', '" + department_id + "');";
    }
};