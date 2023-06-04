#include "Appointment.h"

// 添加预约记录
bool Appointment::AddAppointment(string &pat_id, string &doc_id, string &info, string &time, string &id)
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
    string SQL = "INSERT INTO medical.Appointment (pat_id, doc_id, info, apa_time, id) VALUES (?, ?, ?, ?, ?)";
    SQLPrepare(stmt, (SQLCHAR*)SQL.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)pat_id.c_str(), 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)doc_id.c_str(), 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)info.c_str(), 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)time.c_str(), 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)id.c_str(), 0, NULL);
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

// 根据挂号id删除预约记录
bool Appointment::DeleteAppointment(string &id)
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
    string SQL = "DELETE FROM medical.Appointment WHERE id = ?";
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

// 根据患者id查找预约记录
vector<string> Appointment::FindPatientAppointment(string &pat_id)
{
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    // 返回值
    SQLRETURN ret;  
    // sql预编译语句
    string SQL = "SELECT * FROM medical.Appointment WHERE pat_id = ?";
    SQLPrepare(stmt, (SQLCHAR*)SQL.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)pat_id.c_str(), 0, NULL);
    
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
    if (SQL_SUCCEEDED(SQLFetch(stmt)))
    {
        SQLCHAR pat_id_[256];
        SQLGetData(stmt, 1, SQL_C_CHAR, pat_id_, sizeof(pat_id_), NULL);
        res.push_back((const char*)pat_id_);
        SQLCHAR doc_id_[256];
        SQLGetData(stmt, 2, SQL_C_CHAR, doc_id_, sizeof(doc_id_), NULL);
        res.push_back((const char*)doc_id_);
        SQLCHAR info_[256];
        SQLGetData(stmt, 3, SQL_C_CHAR, info_, sizeof(info_), NULL);
        res.push_back((const char*)info_);
        SQLCHAR time_[256];
        SQLGetData(stmt, 4, SQL_C_CHAR, time_, sizeof(time_), NULL);
        res.push_back((const char*)time_);
        SQLCHAR id_[256];
        SQLGetData(stmt, 5, SQL_C_CHAR, id_, sizeof(id_), NULL);
        res.push_back((const char*)id_);
    }
    
    DisconnectDB(env, dbc, stmt);

    return res;
}

// 根据医生id查找预约记录
vector<vector<string>> Appointment::FindDoctorAppointment(string &doc_id)
{
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    // 返回值
    SQLRETURN ret;  
    // sql预编译语句
    string SQL = "SELECT * FROM medical.Appointment WHERE doc_id = ?";
    SQLPrepare(stmt, (SQLCHAR*)SQL.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)doc_id.c_str(), 0, NULL);
    
    // 执行语句
    ret = SQLExecute(stmt);
    // 查找失败
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        vector<vector<string>> error_;
        vector<string> error;
        error.push_back("Failed");
        error_.push_back(error);
        return error_;
    }
    
    // 获取结果
    vector<vector<string>> res_;
    while (SQL_SUCCEEDED(SQLFetch(stmt)))
    {
        // 保存预约单内容
        vector<string> res;
        SQLCHAR pat_id_[256];
        SQLGetData(stmt, 1, SQL_C_CHAR, pat_id_, sizeof(pat_id_), NULL);
        res.push_back((const char*)pat_id_);
        SQLCHAR doc_id_[256];
        SQLGetData(stmt, 2, SQL_C_CHAR, doc_id_, sizeof(doc_id_), NULL);
        res.push_back((const char*)doc_id_);
        SQLCHAR info_[256];
        SQLGetData(stmt, 3, SQL_C_CHAR, info_, sizeof(info_), NULL);
        res.push_back((const char*)info_);
        SQLCHAR time_[256];
        SQLGetData(stmt, 4, SQL_C_CHAR, time_, sizeof(time_), NULL);
        res.push_back((const char*)time_);
        SQLCHAR id_[256];
        SQLGetData(stmt, 5, SQL_C_CHAR, id_, sizeof(id_), NULL);
        res.push_back((const char*)id_);
        // 将该预约加入到结果集中
        res_.push_back(res);
    }
    

    DisconnectDB(env, dbc, stmt);

    return res_;
}

// 根据时间查找患者名单
vector<string> Appointment::FindPatientAtTime(string &time)
{
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    // 返回值
    SQLRETURN ret;  
    // sql预编译语句
    string SQL = "SELECT pat_id FROM medical.Appointment WHERE apa_time = ?";
    SQLPrepare(stmt, (SQLCHAR*)SQL.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)time.c_str(), 0, NULL);
    
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
        SQLCHAR pat_id_[256];
        SQLGetData(stmt, 1, SQL_CHAR, pat_id_, sizeof(pat_id_), NULL);
        res.push_back((const char*)pat_id_);
    }

    DisconnectDB(env, dbc, stmt);

    return res;
}
