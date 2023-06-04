#include "Department_Table.h"
#include "myDatabase.h"
#include <assert.h>


std::string Department_Table::getDepartmentName(std::string department_id) {
    std::string result;
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLLEN indicator;
    //连接数据库
    ConnectDB(env, dbc, stmt);
    //执行查询
    ret = SQLPrepare(stmt, (SQLCHAR*)"SELECT * FROM medical.Department WHERE id  = ?;", SQL_NTS);


    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    assert(ret != SQL_NEED_DATA);

    if (SQLFetch(stmt) != SQL_SUCCESS) {
        std::cerr << "Error fetching data" << std::endl;
    }

    SQLCHAR buffer[512];
    //获取查询结果第一行第二列的数据

    ret = SQLGetData(stmt, 2, SQL_C_CHAR, buffer, sizeof(buffer), &indicator);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        if (indicator == SQL_NULL_DATA) {
            std::cout << "No data found" << std::endl;
        }
        else {
            // 数据不为NULL，存储在buffer中. 则直接转换为string
            std::string str(reinterpret_cast<const char*>(buffer));
            result = str;
        }
    }
    else {
        // 检索数据失败
        std::cerr << "Error fetching data" << std::endl;
    }
    //断开数据库连接
    DisconnectDB(env, dbc, stmt);
    return result;
}

std::string Department_Table::getDepartmentInfo(std::string department_id) {
    std::string result;
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLLEN indicator;
    //连接数据库
    ConnectDB(env, dbc, stmt);
    //执行查询
    ret = SQLPrepare(stmt, (SQLCHAR*)"SELECT * FROM medical.Department WHERE id  = ?;", SQL_NTS);


    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    assert(ret != SQL_NEED_DATA);

    if (SQLFetch(stmt) != SQL_SUCCESS) {
        std::cerr << "Error fetching data" << std::endl;
    }

    SQLCHAR buffer[512];
    //获取查询结果第一行第三列的数据

    ret = SQLGetData(stmt, 3, SQL_C_CHAR, buffer, sizeof(buffer), &indicator);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        if (indicator == SQL_NULL_DATA) {
            std::cout << "No data found" << std::endl;
        }
        else {
            // 数据不为NULL，存储在buffer中. 则直接转换为string
            std::string str(reinterpret_cast<const char*>(buffer));
            result = str;
        }
    }
    else {
        // 检索数据失败
        std::cerr << "Error fetching data" << std::endl;
    }
    //断开数据库连接
    DisconnectDB(env, dbc, stmt);
    return result;
}

bool Department_Table::updateDepartmentName(std::string department_id, std::string department_name) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    //连接数据库
    ConnectDB(env, dbc, stmt);
    //执行更新
    ret = SQLPrepare(stmt, (SQLCHAR*)"UPDATE medical.Department SET name = ? WHERE id = ?;", SQL_NTS);

    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_name.c_str(), 0, NULL);
    ret = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);

    if (ret != SQL_SUCCESS) {
        std::cerr << "Error updating data" << std::endl;
        return FALSE;
    }
    //断开数据库连接
    DisconnectDB(env, dbc, stmt);
    return TRUE;
}

bool Department_Table::updateDepartmentInfo(std::string department_id, std::string department_info) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    //连接数据库
    ConnectDB(env, dbc, stmt);
    //执行更新
    ret = SQLPrepare(stmt, (SQLCHAR*)"UPDATE medical.Department SET info = ? WHERE id = ?;", SQL_NTS);

    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_info.c_str(), 0, NULL);
    ret = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);

    if (ret != SQL_SUCCESS) {
        std::cerr << "Error updating data" << std::endl;
        return FALSE;
    }
    //断开数据库连接
    DisconnectDB(env, dbc, stmt);
    return TRUE;
}

bool Department_Table::insertDepartment(std::string department_id, std::string department_name , std::string department_info ) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    //连接数据库
    ConnectDB(env, dbc, stmt);
    //执行插入
    ret = SQLPrepare(stmt, (SQLCHAR*)"INSERT INTO medical.Department VALUES (?, ?, ?);", SQL_NTS);


    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_id.c_str(), 0, NULL);
    ret = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_name.c_str(), 0, NULL);
    ret = SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_info.c_str(), 0, NULL);


    ret = SQLExecute(stmt);

    assert(ret != SQL_NEED_DATA);
    assert(ret != SQL_INVALID_HANDLE);
    assert(ret != SQL_ERROR);

    if (ret != SQL_SUCCESS) {
        std::cerr << "Error inserting data" << std::endl;
        return FALSE;
    }

    //断开数据库连接
    DisconnectDB(env, dbc, stmt);
    return TRUE;
}

bool Department_Table::deleteDepartment(std::string department_id) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    //连接数据库
    ConnectDB(env, dbc, stmt);
    //执行删除
    ret = SQLPrepare(stmt, (SQLCHAR*)"DELETE FROM SubDepartment WHERE id = ?;", SQL_NTS);


    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_id.c_str(), 0, NULL);

    ret = SQLExecute(stmt);

    if (ret != SQL_SUCCESS) {
        std::cerr << "Error updating data" << std::endl;
        return FALSE;
    }

    //断开数据库连接
    DisconnectDB(env, dbc, stmt);
    return TRUE;
}

std::vector<std::string>* Department_Table::getDepartmentList() {
    std::vector<std::string>* list = new std::vector<std::string>;
    
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLLEN indicator;
    //连接数据库
    ConnectDB(env, dbc, stmt);
    //执行查询
    ret = SQLPrepare(stmt, (SQLCHAR*)"SELECT * FROM medical.Department;", SQL_NTS);

    ret = SQLExecute(stmt);

    while (SQLFetch(stmt) != SQL_NO_DATA) {
        SQLCHAR buffer[512];
        ret = SQLGetData(stmt, 2, SQL_C_CHAR, buffer, sizeof(buffer), &indicator);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            if (indicator == SQL_NULL_DATA) {
                std::cout << "No data found" << std::endl;
            }
            else {
                // 数据不为NULL，存储在buffer中. 则直接转换为string
                std::string *temp = new std::string(reinterpret_cast<const char*>(buffer));
                list->push_back(*temp);
                
            }
        }
        else {
            // 检索数据失败
            std::cerr << "Error fetching data" << std::endl;
            return nullptr;
        }
    }
    //断开数据库连接
    DisconnectDB(env, dbc, stmt);
    return list;
}