#include"DoctorTable.h"


DoctorTable::DoctorTable()
{
    ID_list = new vector<string>();
    SQLCHAR tmp_id[10000];
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    SQLRETURN ret;  //返回值
    //连接到数据库
    ConnectDB(env, dbc, stmt);
    SQLCHAR sql[] = "select id from medical.doctor";
    ret = SQLExecDirect(stmt, (SQLCHAR*)sql, SQL_NTS);
    if (!SQL_SUCCEEDED(ret))
    {
        cout << "Error querying SQL Server";
        DisconnectDB(env, dbc, stmt);
        return;
    }
    int i = 0;
    string tmp;
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        SQLGetData(stmt, 1, SQL_C_CHAR, tmp_id, 10000, NULL);
        tmp = (char*)tmp_id;
        ID_list->push_back(tmp);
    }
    DisconnectDB(env, dbc, stmt);
}

DoctorTable::~DoctorTable()
{
    delete[] ID_list;
}

bool DoctorTable::has_id(const string& doctor_id)
{
    vector<string>::iterator it;
    for (it = ID_list->begin(); it != ID_list->end(); it++)
    {
        if (*it == doctor_id)
        {
            return true;
        }
    }
    return false;
}

vector<string>* DoctorTable::get_doctor_list()
{
    return ID_list;
}


string DoctorTable:: get_string_attribute(const string& doctor_id, const string& attribute_name)
{
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    SQLRETURN ret;  //返回值
    SQLLEN indicator;
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    //string res;
    SQLCHAR attribute[2048];
    //根据attribute_name查询
    string sql = "SELECT " + attribute_name + " FROM medical.doctor WHERE id = ?";
    SQLPrepare(stmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)doctor_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error executing query" << endl;
        exit(-1);
    }
    ret = SQLFetch(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error fetching results" << endl;
        exit(-1);
    }
    ret = SQLGetData(stmt, 1, SQL_C_CHAR, attribute, sizeof(attribute), &indicator);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error getting data" << endl;
        exit(-1);
    }
    string res(reinterpret_cast<const char*>(attribute));
    //res = string_to_utf8(res);
    //将attribute字段值转换为string类型
    //res = (const char*)attribute;
    //断开数据库连接
    DisconnectDB(env, dbc, stmt);
    return res;
}

bool DoctorTable::set_string_attribute(const string& doctor_id, const string& attribute_name, const string& attribute_value)
{
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    SQLRETURN ret;  //返回值
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    //根据attribute_name更新
    string sql = "UPDATE medical.doctor SET " + attribute_name + " = ? WHERE id = ?";
    SQLPrepare(stmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)attribute_value.c_str(), 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)doctor_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error executing edition" << endl;
        return false;
    }

    //断开数据库连接
    DisconnectDB(env, dbc, stmt);
    return true;
}

bool DoctorTable::add_doctor(const string& doctor_id)
{
    //检查是否已经存在
    if (has_id(doctor_id))
    {
        cout << "This doctor has already existed!" << endl;
        return false;
    }

    //连接到数据库
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    SQLRETURN ret;  //返回值
    ConnectDB(env, dbc, stmt);

    //插入新的患者
    string sql = "INSERT INTO medical.doctor(id) VALUES(?)";
    SQLPrepare(stmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)doctor_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error executing insertion" << endl;
        return false;
    }

    //断开数据库连接
    DisconnectDB(env, dbc, stmt);
    //在ID_list中添加新的id
    ID_list->push_back(doctor_id);

    return true;
}


bool DoctorTable::delete_doctor(const string& doctor_id)
{
    //检查是否已经存在
    if (!has_id(doctor_id))
    {
        cout << "This doctor does not exist!" << endl;
        return false;
    }

    //连接到数据库
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    SQLRETURN ret;  //返回值
    ConnectDB(env, dbc, stmt);

    //删除患者
    string sql = "DELETE FROM medical.doctor WHERE id = ?";
    SQLPrepare(stmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)doctor_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error executing deletion" << endl;
        return false;
    }

    //断开数据库连接
    DisconnectDB(env, dbc, stmt);
    //在ID_list中删除id
    for (auto it = ID_list->begin(); it != ID_list->end(); it++)
    {
        if (*it == doctor_id)
        {
            ID_list->erase(it);
            break;
        }
    }
    return true;
}

vector<string>* DoctorTable:: get_patient_list(const string& doctor_id)//多值属性查询
{
    //检查是否已经存在
    if (!has_id(doctor_id))
    {
        cout << "This doctor does not exist!" << endl;
        return NULL;
    }

    //连接到数据库
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    SQLRETURN ret;  //返回值
    ConnectDB(env, dbc, stmt);

    vector<string>* res = new vector<string>();
    SQLCHAR patient_id[10000];
    //根据doctor_id查询
    string sql = "SELECT patient FROM medical.doctor WHERE id = ?";
    SQLPrepare(stmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)doctor_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error executing query" << endl;
        exit(-1);
    }
    SQLGetData(stmt, 1, SQL_C_CHAR, patient_id, sizeof(patient_id), NULL);
    //将patient_id字段值转换为string类型
    int i = 0;
    string tmp = "";
    while (patient_id[i] != '\0')
    {
        if (patient_id[i] == ';')
        {
            res->push_back(tmp);
            tmp = "";
        }
        else
        {
            tmp += patient_id[i];
        }
        i++;
    }

    //断开数据库连接
    DisconnectDB(env, dbc, stmt);

    return res;
}


//实现医生登录类
DoctorLogIn::DoctorLogIn(const string& doctor_id)
{
    this->id = new string(doctor_id);
    //根据id在医生表中查询password
    DoctorTable* DT = new DoctorTable();
    string pwd = DT->get_string_attribute(doctor_id, "password");
    this->password = &pwd;
}

DoctorLogIn::~DoctorLogIn()
{
    delete this->id;
    delete this->password;
}

bool DoctorLogIn::login(const string& password)
{
    if (password == *this->password)
        return true;
    else
        return false;
}