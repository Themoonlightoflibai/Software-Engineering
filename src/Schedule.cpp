#include "Schedule.h"

bool Schedule::CreateSchedule(string &doc_id, string &time, int &rest, int &total)
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
    string SQL = "INSERT INTO medical.Schedule (doc_id, doc_time, rest, total) VALUES (?, ?, ?, ?);";
    SQLPrepare(stmt, (SQLCHAR*)SQL.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)doc_id.c_str(), 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)time.c_str(), 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLINTEGER*)&rest, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLINTEGER*)&total, 0, NULL);
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

// 修改排班, change始终等于1，choice---1为取消，2为增加
bool Schedule::ChangeRest(string &doc_id, string &time, int &change, int &choice)
{   
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    SQLRETURN ret;  //返回值

    // 连接到数据库
    ConnectDB(env, dbc, stmt);

    // 进行修改
    string SQL = "UPDATE medical.Schedule SET rest = ? WHERE doc_id = ? AND doc_time = ?;";
    SQLPrepare(stmt, (SQLCHAR*)SQL.c_str(), SQL_NTS);

    // 根据修改类型进行更新
    // 取消预约
    if (choice == 1)
    {
        int rest = GetRest(doc_id, time);
        int total = GetTotal(doc_id, time);
        // 取消预约数量多于现实数量
        if (total < change + rest)
        {
            return false;
        }
        // 取消预约数量合理
        rest += change;
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLINTEGER*)&rest, 0, NULL);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)doc_id.c_str(), 0, NULL);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)time.c_str(), 0, NULL);
    }
    // 增加预约
    if (choice == 2)
    {
        int rest = GetRest(doc_id, time);
        int total = GetTotal(doc_id, time);
        // 增加预约数量多于可预约数量
        if (rest < change)
        {
            return false;
        }
        // 取消预约数量合理
        rest -= change;
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLINTEGER*)&rest, 0, NULL);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)doc_id.c_str(), 0, NULL);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)time.c_str(), 0, NULL);
    }
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

// 获取余量
int Schedule::GetRest(string &doc_id, string time)
{
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    SQLRETURN ret;  //返回值
    SQLLEN indicator;
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    // 进行查询
    string SQL = "SELECT rest FROM medical.Schedule WHERE doc_id = ? AND doc_time = ?;";
    SQLPrepare(stmt, (SQLCHAR*)SQL.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)doc_id.c_str(), 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)time.c_str(), 0, NULL);
    ret = SQLExecute(stmt);

    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        return -1;
    }

    // 获取数据
    SQLINTEGER rest_;
    if (SQL_SUCCEEDED(SQLFetch(stmt)))
    {
        SQLGetData(stmt, 1, SQL_C_SLONG, &rest_, sizeof(rest_), &indicator);
    }
    //断开数据库连接
    DisconnectDB(env, dbc, stmt);

    return rest_;
}
// 获取总量
int Schedule::GetTotal(string &doc_id, string time)
{
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    SQLRETURN ret;  //返回值
    SQLLEN indicator;
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    // 进行查询
    string SQL = "SELECT total FROM medical.Schedule WHERE doc_id = ? AND doc_time = ?;";
    SQLPrepare(stmt, (SQLCHAR*)SQL.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)doc_id.c_str(), 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)time.c_str(), 0, NULL);
    ret = SQLExecute(stmt);

    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        return -1;
    }

    // 获取数据
    SQLINTEGER total_;
    if (SQL_SUCCEEDED(SQLFetch(stmt)))
    {
        SQLGetData(stmt, 1, SQL_C_SLONG, &total_, sizeof(total_), &indicator);
    }
    //断开数据库连接
    DisconnectDB(env, dbc, stmt);

    return total_;
}

// 获取时间
vector<string> Schedule::GetTime(string &doc_id)
{
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    // 返回值
    SQLRETURN ret;  
    // sql预编译语句
    string SQL = "SELECT doc_time FROM medical.Schedule WHERE doc_id = ?;";
    SQLPrepare(stmt, (SQLCHAR*)SQL.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)doc_id.c_str(), 0, NULL);
    
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
        SQLCHAR time_[256];
        SQLGetData(stmt, 1, SQL_C_CHAR, time_, sizeof(time_), NULL);
        res.push_back((const char*)time_);
    }

    DisconnectDB(env, dbc, stmt);

    return res;
}