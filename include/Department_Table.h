#include "Database.h"


class Department_Table {
public:
    std::string* getDepartmentName(std::string department_id);

    void updateDepartmentName(std::string department_id, std::string department_name);

    std::string* getDepartmentInfo(std::string department_id);

    void updateDepartmentInfo(std::string department_id, std::string department_info);

    std::vector<std::string>* getDepartmentList();

    void insertDepartment(std::string department_id, std::string department_name = "NULL", std::string department_info = "NULL");

    void deleteDepartment(std::string department_id);

private:
    std::string get(std::string name) {
        return "SELECT * FROM Department WHERE department_id = '" + name + "';";
    }

    std::string update(std::string name, std::string content, std::string id) {
        return "UPDATE Department SET " + name + " = '" + content + "' WHERE department_id = '" + id + "';";
    }

    std::string del(std::string name) {
        return "DELETE FROM Department WHERE department_id = '" + name + "';";
    }
};