#include "Doctor_SubDepartment.h"

// 新增记录，测试用
bool Doctor_SubDepartment::CreateDoctor_SubDepartment(string &doc_id, string &apa_id)
{
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    // 插入记录

    // 返回值
    SQLRETURN ret;  
    // sql预编译语句
    string SQL = "INSERT INTO medical.Doctor_SubDepartment (doc_id, apa_id) VALUES (?, ?)";
    SQLPrepare(stmt, (SQLCHAR*)SQL.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)doc_id.c_str(), 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)apa_id.c_str(), 0, NULL);
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

// 获取某子科室中的医生id列表
vector<string> Doctor_SubDepartment::GetDoctorid(string &apa_id)
{
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    // 进行查找

    // 返回值
    SQLRETURN ret;  
    // sql预编译语句
    string SQL = "SELECT doc_id FROM medical.Doctor_SubDepartment WHERE apa_id = ?";
    SQLPrepare(stmt, (SQLCHAR*)SQL.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)apa_id.c_str(), 0, NULL);
    
    // 执行语句
    ret = SQLExecute(stmt);

    // 查找失败
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        vector<string> error;
        error.push_back("Failed");
        return error;
    }

    // 获取结果
    vector<string> res;
    while (SQL_SUCCEEDED(SQLFetch(stmt)))
    {
        SQLCHAR doc_id_[256];
        SQLGetData(stmt, 1, SQL_CHAR, doc_id_, sizeof(doc_id_), NULL);
        res.push_back((const char*)doc_id_);
    }

    DisconnectDB(env, dbc, stmt);

    return res;
}

// 获取医生的子科室id
string Doctor_SubDepartment::GetSubDepartmentid(string &doc_id)
{
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    // 进行查找

    // 返回值
    SQLRETURN ret;  
    // sql预编译语句
    string SQL = "SELECT apa_id FROM medical.Doctor_SubDepartment WHERE doc_id = ?";
    SQLPrepare(stmt, (SQLCHAR*)SQL.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)doc_id.c_str(), 0, NULL);
    
    // 执行语句
    ret = SQLExecute(stmt);

    // 获取结果
    
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