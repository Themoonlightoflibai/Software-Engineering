#include "myDatabase.h"

//using namespace std;

//通过odbc连接数据库
void ConnectDB(SQLHENV& env, SQLHDBC& dbc, SQLHSTMT& stmt)
{
    SQLRETURN ret;  //返回值

    //分配数据库环境句柄
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        std::cerr << "Error allocating environment handle" << std::endl;
        exit(-1);
    }
    //设置环境属性
    ret = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        std::cerr << "Error setting environment attribute" << std::endl;
        exit(-1);
    }
    //分配数据库连接句柄
    ret = SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        std::cerr << "Error allocating connection handle" << std::endl;
        exit(-1);
    }
    //连接数据库
    ret = SQLConnect(dbc, (SQLCHAR*)"MySQL", SQL_NTS, (SQLCHAR*)"root", SQL_NTS, (SQLCHAR*)"zmz269613", SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        std::cout << ret << std::endl;
        std::cerr << "Error connecting to database" << std::endl;
        exit(-1);
    }
    //分配语句句柄
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        std::cerr << "Error allocating statement handle" << std::endl;
        exit(-1);
    }
}

//断开数据库连接
void DisconnectDB(SQLHENV& env, SQLHDBC& dbc, SQLHSTMT& stmt)
{
    SQLRETURN ret;  //返回值

    //释放语句句柄
    ret = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        std::cerr << "Error freeing statement handle" << std::endl;
        exit(-1);
    }
    //断开数据库连接
    ret = SQLDisconnect(dbc);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        std::cerr << "Error disconnecting from database" << std::endl;
        exit(-1);
    }
    //释放连接句柄
    ret = SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        std::cerr << "Error freeing connection handle" << std::endl;
        exit(-1);
    }
    //释放环境句柄
    ret = SQLFreeHandle(SQL_HANDLE_ENV, env);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        std::cerr << "Error freeing environment handle" << std::endl;
        exit(-1);
    }
}

