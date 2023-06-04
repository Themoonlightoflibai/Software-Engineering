#include "database.h"

using namespace std;

//通过odbc连接数据库
void ConnectDB(SQLHENV& env, SQLHDBC& dbc, SQLHSTMT& stmt)
{
    SQLRETURN ret;  //返回值

    //分配数据库环境句柄
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error allocating environment handle" << endl;
        exit(-1);
    }
    //设置环境属性
    ret = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error setting environment attribute" << endl;
        exit(-1);
    }
    //分配数据库连接句柄
    ret = SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error allocating connection handle" << endl;
        exit(-1);
    }
    //连接数据库
    ret = SQLConnect(dbc, (SQLCHAR*)"test1", SQL_NTS, (SQLCHAR*)"root", SQL_NTS, (SQLCHAR*)"121602", SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error connecting to database" << endl;
        exit(-1);
    }
    //分配语句句柄
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error allocating statement handle" << endl;
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
        cerr << "Error freeing statement handle" << endl;
        exit(-1);
    }
    //断开数据库连接
    ret = SQLDisconnect(dbc);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error disconnecting from database" << endl;
        exit(-1);
    }
    //释放连接句柄
    ret = SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error freeing connection handle" << endl;
        exit(-1);
    }
    //释放环境句柄
    ret = SQLFreeHandle(SQL_HANDLE_ENV, env);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error freeing environment handle" << endl;
        exit(-1);
    }
}


string string_to_utf8(const string& str)
{
    int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
 
    wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
    ZeroMemory(pwBuf, nwLen * 2 + 2);
 
    ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
 
    int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
 
    char * pBuf = new char[nLen + 1];
    ZeroMemory(pBuf, nLen + 1);
 
    ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
 
    std::string retStr(pBuf);
 
    delete[]pwBuf;
    delete[]pBuf;
 
    pwBuf = NULL;
    pBuf = NULL;
 
    return retStr;
}
