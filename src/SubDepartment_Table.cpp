#include "SubDepartment_Table.h"
#include "myDatabase.h"


std::string SubDepartment_Table::getSubDepartmentName(const std::string subdepartment_id) {
    std::string result;
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLLEN indicator;
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ�в�ѯ
    ret = SQLPrepare(stmt, (SQLCHAR*)"SELECT * FROM medical.SubDepartment WHERE id  = ?;", SQL_NTS);


    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)subdepartment_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    //assert(ret != SQL_NEED_DATA);

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

std::string SubDepartment_Table::getSubDepartmentInfo(const std::string subdepartment_id) {
    std::string result;
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLLEN indicator;
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ�в�ѯ
    ret = SQLPrepare(stmt, (SQLCHAR*)"SELECT * FROM medical.SubDepartment WHERE id  = ?;", SQL_NTS);


    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)subdepartment_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    //assert(ret != SQL_NEED_DATA);

    if (SQLFetch(stmt) != SQL_SUCCESS) {
        std::cerr << "Error fetching data" << std::endl;
    }

    SQLCHAR buffer[512];
    //��ȡ��ѯ�����һ�еڶ��е�����

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

std::string SubDepartment_Table::getSubDepartmentDepartment(const std::string subdepartment_id) {
    std::string result;
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLLEN indicator;
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ�в�ѯ
    ret = SQLPrepare(stmt, (SQLCHAR*)"SELECT * FROM medical.SubDepartment WHERE id  = ?;", SQL_NTS);


    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)subdepartment_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    //assert(ret != SQL_NEED_DATA);

    if (SQLFetch(stmt) != SQL_SUCCESS) {
        std::cerr << "Error fetching data" << std::endl;
    }

    SQLCHAR buffer[512];
    //��ȡ��ѯ�����һ�е�4�е�����

    ret = SQLGetData(stmt, 4, SQL_C_CHAR, buffer, sizeof(buffer), &indicator);
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

bool SubDepartment_Table::updateSubDepartmentName(std::string subdepartment_id, std::string subdepartment_name) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ�и���
    ret = SQLPrepare(stmt, (SQLCHAR*)"UPDATE medical.SubDepartment SET name = ? WHERE id = ?;", SQL_NTS);

    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)subdepartment_name.c_str(), 0, NULL);
    ret = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)subdepartment_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);

    if (ret != SQL_SUCCESS) {
        std::cerr << "Error updating data" << std::endl;
        return FALSE;
    }
    //�Ͽ����ݿ�����
    DisconnectDB(env, dbc, stmt);
    return TRUE;
}

bool SubDepartment_Table::updateSubDepartmentInfo(std::string subdepartment_id, std::string subdepartment_info) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ�и���
    ret = SQLPrepare(stmt, (SQLCHAR*)"UPDATE medical.SubDepartment SET info = ? WHERE id = ?;", SQL_NTS);

    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)subdepartment_info.c_str(), 0, NULL);
    ret = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)subdepartment_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);

    if (ret != SQL_SUCCESS) {
        std::cerr << "Error updating data" << std::endl;
        return FALSE;
    }
    //�Ͽ����ݿ�����
    DisconnectDB(env, dbc, stmt);
    return TRUE;
}

bool SubDepartment_Table::updateSubDepartmentDepartment(std::string subdepartment_id, std::string department_id) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ�и���
    ret = SQLPrepare(stmt, (SQLCHAR*)"UPDATE medical.SubDepartment SET apa_id = ? WHERE id = ?;", SQL_NTS);

    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_id.c_str(), 0, NULL);
    ret = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)subdepartment_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);

    if (ret != SQL_SUCCESS) {
        std::cerr << "Error updating data" << std::endl;
        return FALSE;
    }
    //�Ͽ����ݿ�����
    DisconnectDB(env, dbc, stmt);
    return TRUE;
}

bool SubDepartment_Table::insertSubDepartment(std::string subdepartment_id, std::string subdepartment_name, std::string subdepartment_info, std::string department_id) {

    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ�в���
    ret = SQLPrepare(stmt, (SQLCHAR*)"INSERT INTO medical.subDepartment VALUES (?, ?, ?, ?);", SQL_NTS);


    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)subdepartment_id.c_str(), 0, NULL);
    ret = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)subdepartment_name.c_str(), 0, NULL);
    ret = SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)subdepartment_info.c_str(), 0, NULL);
    ret = SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_id.c_str(), 0, NULL);


    ret = SQLExecute(stmt);

    //assert(ret != SQL_NEED_DATA);
    //assert(ret != SQL_INVALID_HANDLE);
    //assert(ret != SQL_ERROR);

    if (ret != SQL_SUCCESS) {
        std::cerr << "Error inserting data" << std::endl;
        return FALSE;
    }

    //�Ͽ����ݿ�����
    DisconnectDB(env, dbc, stmt);
    return TRUE;
}

bool SubDepartment_Table::deleteSubDepartment(std::string subdepartment_id) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ��ɾ��
    ret = SQLPrepare(stmt, (SQLCHAR*)"DELETE FROM SubDepartment WHERE id = ?;", SQL_NTS);


    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)subdepartment_id.c_str(), 0, NULL);

    ret = SQLExecute(stmt);

    if (ret != SQL_SUCCESS) {
        std::cerr << "Error updating data" << std::endl;
        return FALSE;
    }

    //�Ͽ����ݿ�����
    DisconnectDB(env, dbc, stmt);
    return TRUE;
}
std::vector<std::string>* SubDepartment_Table::getSubDepartmentIdByDepatmentId(std::string department_id) {
    std::vector<std::string>* list = new std::vector<std::string>;

    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLLEN indicator;
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ�в�ѯ
    ret = SQLPrepare(stmt, (SQLCHAR*)"SELECT * FROM medical.SubDepartment WHERE apa_id  = ?;", SQL_NTS);

    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)department_id.c_str(), 0, NULL);

    ret = SQLExecute(stmt);
    
    while (SQLFetch(stmt) != SQL_NO_DATA) {
        SQLCHAR buffer[512];
        ret = SQLGetData(stmt, 1, SQL_C_CHAR, buffer, sizeof(buffer), &indicator);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            if (indicator == SQL_NULL_DATA) {
                std::cout << "No data found" << std::endl;
            }
            else {
                // ���ݲ�ΪNULL���洢��buffer��. ��ֱ��ת��Ϊstring
                std::string* temp = new std::string(reinterpret_cast<const char*>(buffer));
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
/*
std::vector<std::string>* SubDepartment_Table::getSubDepartmentList() {
    std::vector<std::string>* result = new std::vector<std::string>;
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLLEN indicator;
    //�������ݿ�
    ConnectDB(env, dbc, stmt);
    //ִ�в�ѯ

    //��һ����Ҫ���ݷ��ص����ݸ�ʽ���жϣ�����ĵ��Ե�ʱ��ʵ��
    ret = SQLExecDirect(stmt, (SQLCHAR*)list(), SQL_NTS);

    if (ret != SQL_SUCCESS) {
        std::cerr << "Error fetching data" << std::endl;
    }

    //�Ͽ����ݿ�����
    DisconnectDB(env, dbc, stmt);
}
*/