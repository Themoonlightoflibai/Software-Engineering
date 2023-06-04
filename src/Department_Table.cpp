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
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ�в�ѯ
    ret = SQLPrepare(stmt, (SQLCHAR*)"SELECT * FROM medical.Department WHERE id  = ?;", SQL_NTS);


    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    assert(ret != SQL_NEED_DATA);

    if (SQLFetch(stmt) != SQL_SUCCESS) {
        std::cerr << "Error fetching data" << std::endl;
    }

    SQLCHAR buffer[512];
    //��ȡ��ѯ�����һ�еڶ��е�����

    ret = SQLGetData(stmt, 2, SQL_C_CHAR, buffer, sizeof(buffer), &indicator);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        if (indicator == SQL_NULL_DATA) {
            std::cout << "No data found" << std::endl;
        }
        else {
            // ���ݲ�ΪNULL���洢��buffer��. ��ֱ��ת��Ϊstring
            std::string str(reinterpret_cast<const char*>(buffer));
            result = str;
        }
    }
    else {
        // ��������ʧ��
        std::cerr << "Error fetching data" << std::endl;
    }
    //�Ͽ����ݿ�����
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
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ�в�ѯ
    ret = SQLPrepare(stmt, (SQLCHAR*)"SELECT * FROM medical.Department WHERE id  = ?;", SQL_NTS);


    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    assert(ret != SQL_NEED_DATA);

    if (SQLFetch(stmt) != SQL_SUCCESS) {
        std::cerr << "Error fetching data" << std::endl;
    }

    SQLCHAR buffer[512];
    //��ȡ��ѯ�����һ�е����е�����

    ret = SQLGetData(stmt, 3, SQL_C_CHAR, buffer, sizeof(buffer), &indicator);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        if (indicator == SQL_NULL_DATA) {
            std::cout << "No data found" << std::endl;
        }
        else {
            // ���ݲ�ΪNULL���洢��buffer��. ��ֱ��ת��Ϊstring
            std::string str(reinterpret_cast<const char*>(buffer));
            result = str;
        }
    }
    else {
        // ��������ʧ��
        std::cerr << "Error fetching data" << std::endl;
    }
    //�Ͽ����ݿ�����
    DisconnectDB(env, dbc, stmt);
    return result;
}

bool Department_Table::updateDepartmentName(std::string department_id, std::string department_name) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ�и���
    ret = SQLPrepare(stmt, (SQLCHAR*)"UPDATE medical.Department SET name = ? WHERE id = ?;", SQL_NTS);

    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_name.c_str(), 0, NULL);
    ret = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);

    if (ret != SQL_SUCCESS) {
        std::cerr << "Error updating data" << std::endl;
        return FALSE;
    }
    //�Ͽ����ݿ�����
    DisconnectDB(env, dbc, stmt);
    return TRUE;
}

bool Department_Table::updateDepartmentInfo(std::string department_id, std::string department_info) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ�и���
    ret = SQLPrepare(stmt, (SQLCHAR*)"UPDATE medical.Department SET info = ? WHERE id = ?;", SQL_NTS);

    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_info.c_str(), 0, NULL);
    ret = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);

    if (ret != SQL_SUCCESS) {
        std::cerr << "Error updating data" << std::endl;
        return FALSE;
    }
    //�Ͽ����ݿ�����
    DisconnectDB(env, dbc, stmt);
    return TRUE;
}

bool Department_Table::insertDepartment(std::string department_id, std::string department_name , std::string department_info ) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ�в���
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

    //�Ͽ����ݿ�����
    DisconnectDB(env, dbc, stmt);
    return TRUE;
}

bool Department_Table::deleteDepartment(std::string department_id) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ��ɾ��
    ret = SQLPrepare(stmt, (SQLCHAR*)"DELETE FROM SubDepartment WHERE id = ?;", SQL_NTS);


    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_id.c_str(), 0, NULL);

    ret = SQLExecute(stmt);

    if (ret != SQL_SUCCESS) {
        std::cerr << "Error updating data" << std::endl;
        return FALSE;
    }

    //�Ͽ����ݿ�����
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
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ�в�ѯ
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
                // ���ݲ�ΪNULL���洢��buffer��. ��ֱ��ת��Ϊstring
                std::string *temp = new std::string(reinterpret_cast<const char*>(buffer));
                list->push_back(*temp);
                
            }
        }
        else {
            // ��������ʧ��
            std::cerr << "Error fetching data" << std::endl;
            return nullptr;
        }
    }
    //�Ͽ����ݿ�����
    DisconnectDB(env, dbc, stmt);
    return list;
}