#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqlucode.h>
#include <string>
#include <chrono>
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#include "json.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cerr;


//通过odbc连接数据库
void ConnectDB(SQLHENV& env, SQLHDBC& dbc, SQLHSTMT& stmt);

//断开数据库连接
void DisconnectDB(SQLHENV& env, SQLHDBC& dbc, SQLHSTMT& stmt);

//字符串转utf8编码
string string_to_utf8(const string& str);
