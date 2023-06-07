#include "Registration.h"
#include <stdlib.h>
#include <time.h>

// 添加挂号记录
string Registration::AddRegistration(string &pat_id, string &apa_id)
{
    
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    // 插入记录

    // 返回值
    SQLRETURN ret;  
    // 生成随机id
    long long id_ = rand();
    string id = std::to_string(id_);    
    // sql预编译语句
    string SQL = "INSERT INTO medical.Registration (pat_id, apa_id, id) VALUES (?, ?, ?)";
    SQLPrepare(stmt, (SQLCHAR*)SQL.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)pat_id.c_str(), 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)apa_id.c_str(), 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)id.c_str(), 0, NULL);
    // 执行语句并获得返回结果
    ret = SQLExecute(stmt);
    DisconnectDB(env, dbc, stmt);
    // SQL语句返回结果为失败
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        return "Failed";
    }
    return id;
}
// 删除挂号记录
bool Registration::DeleteRegistration(string &id)
{
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    // 删除记录

    // 返回值
    SQLRETURN ret;  
    // sql预编译语句
    string SQL = "DELETE FROM medical.Registration WHERE id = ?";
    SQLPrepare(stmt, (SQLCHAR*)SQL.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)id.c_str(), 0, NULL);
    
    // 执行语句并获得返回结果
    ret = SQLExecute(stmt);
    DisconnectDB(env, dbc, stmt);
    // SQL语句返回结果为失败
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        return false;
    }
    return true;
}

// 根据患者id查找子科室id
string Registration::GetSubDepartmentId(string &pat_id)
{
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    // 删除记录

    // 返回值
    SQLRETURN ret;  
    // sql预编译语句
    string SQL = "SELECT apa_id FROM medical.Registration WHERE pat_id = ?";
    SQLPrepare(stmt, (SQLCHAR*)SQL.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)pat_id.c_str(), 0, NULL);
    
    // 执行语句并获得返回结果
    ret = SQLExecute(stmt);
    
    // SQL语句返回结果为失败
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        return "Failed";
    }
    SQLCHAR apa_id_[256];
    if (SQL_SUCCEEDED(SQLFetch(stmt)))
    {
        SQLGetData(stmt, 1, SQL_CHAR, apa_id_, sizeof(apa_id_), NULL);
    }
    
    string res((const char*)apa_id_);

    DisconnectDB(env, dbc, stmt);

    return res;
}
