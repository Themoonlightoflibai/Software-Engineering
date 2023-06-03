#pragma once
#include <string>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <windows.h>

using namespace std;

//通过odbc连接数据库
void ConnectDB(SQLHENV& env, SQLHDBC& dbc, SQLHSTMT& stmt);

//断开数据库连接
void DisconnectDB(SQLHENV& env, SQLHDBC& dbc, SQLHSTMT& stmt);
