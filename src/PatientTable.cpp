#include"PatientTable.h"

PatientTable::PatientTable()
{
    ID_list = new vector<string>();
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    ConnectDB(env, dbc, stmt);
    SQLCHAR sql[] = "select id from medical.patient";
    SQLRETURN ret;
    ret = SQLExecDirect(stmt, (SQLCHAR*)sql, SQL_NTS);
    if (!SQL_SUCCEEDED(ret))
    {
        cout << "Error querying SQL Server";
        DisconnectDB(env, dbc, stmt);
        return;
    }
    SQLCHAR tmp_id[10000];
    string tmp;
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        SQLGetData(stmt, 1, SQL_C_CHAR, tmp_id, 10000, NULL);
        tmp = (char*)tmp_id;
        ID_list->push_back(tmp);
    }
    DisconnectDB(env, dbc, stmt);
}

PatientTable::~PatientTable()
{
    delete[] ID_list;
}

bool PatientTable::has_id(const string& patient_id)
{
    vector<string>::iterator it;
    for (it = ID_list->begin(); it != ID_list->end(); it++)
    {
        if (*it == patient_id)
        {
            return true;
        }
    }
    return false;
}

string* PatientTable::get_id_by_phone(const string& phone)
{
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    //连接到数据库
    ConnectDB(env, dbc, stmt);
    SQLCHAR patient_id[10000] = {0};
    //根据phone查询
    string sql = "SELECT id FROM medical.patient WHERE phone = ?";
    SQLPrepare(stmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)phone.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error executing query" << endl;
        exit(-1);
    }
    ret = SQLFetch(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "No phone called " + phone << endl;
        return (string*)new string("");
    }
    ret = SQLGetData(stmt, 1, SQL_C_CHAR, patient_id, sizeof(patient_id), NULL);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error getting data" << endl;
        exit(-1);
    }
    //将patient_id字段值转换为string类型
    string res(reinterpret_cast<const char*>(patient_id));
    DisconnectDB(env, dbc, stmt);
    return new string(res);
}

string* PatientTable::get_new_id()
{
    //获取最大的id，然后加1
    string* res = new string();
    int max_id = 0;
    vector<string>::iterator it;
    for (it = ID_list->begin(); it != ID_list->end(); it++)
    {
        int tmp_id = atoi((*it).c_str());
        if (tmp_id > max_id)
        {
            max_id = tmp_id;
        }
    }
    max_id++;
    char tmp[10000];
    sprintf_s(tmp, "%d", max_id);
    *res = tmp;
    return res;
}

string PatientTable::get_attribute(const string& patient_id, const string& attribute_name)
{
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    SQLRETURN ret;  //返回值
    SQLLEN indicator;
    //连接到数据库
    ConnectDB(env, dbc, stmt);
    SQLCHAR attribute[10000];
    //根据attribute_name查询
    string sql = "SELECT " + attribute_name + " FROM medical.patient WHERE id = ?";
    SQLPrepare(stmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)patient_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error executing query" << endl;
        //exit(-1);
    }
    ret = SQLFetch(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error fetching" << endl;
        return "";
        //exit(-1);
    }
    ret = SQLGetData(stmt, 1, SQL_C_CHAR, attribute, sizeof(attribute), &indicator);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error getting data" << endl;
        return "";
        //exit(-1);
    }
    //将attribute字段值转换为string类型
    string res (reinterpret_cast<const char*>(attribute));
    //res = string_to_utf8(res);
    //断开数据库连接
    DisconnectDB(env, dbc, stmt);

    return res;
}

bool PatientTable::set_attribute(const string& patient_id, const string& attribute_name, const string& attribute_value)
{
    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    SQLRETURN ret;  //返回值
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    //根据attribute_name更新
    string sql = "UPDATE medical.patient SET " + attribute_name + " = ? WHERE id = ?";
    SQLPrepare(stmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)attribute_value.c_str(), 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)patient_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error editing" << endl;
        return false;
    }
    //断开数据库连接
    DisconnectDB(env, dbc, stmt);
    return true;
}

bool PatientTable::add_patient(const string& patient_id)
{
    //检查是否已经存在
    if (has_id(patient_id))
    {
        cout << "This patient has already existed!" << endl;
        return false;
    }

    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    SQLRETURN ret;  //返回值
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    //添加患者
    string sql = "INSERT INTO medical.patient (id) VALUES (?)";
    SQLPrepare(stmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)patient_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error adding" << endl;
        return false;
    }
    //断开数据库连接
    DisconnectDB(env, dbc, stmt);
    //在ID_list中添加新的id
    ID_list->push_back(patient_id);
    return true;
}

bool PatientTable::delete_patient(const string& patient_id)
{
    //检查是否存在
    if (!has_id(patient_id))
    {
        cout << "This patient does not exist!" << endl;
        return false;
    }

    SQLHENV env;  //环境句柄
    SQLHDBC dbc;  //连接句柄
    SQLHSTMT stmt;  //语句句柄
    SQLRETURN ret;  //返回值
    //连接到数据库
    ConnectDB(env, dbc, stmt);

    //删除患者
    string sql = "DELETE FROM medical.patient WHERE patient_id = ?";
    SQLPrepare(stmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)patient_id.c_str(), 0, NULL);
    ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        cerr << "Error deleting" << endl;
        return false;
    }
    //断开数据库连接
    DisconnectDB(env, dbc, stmt);
    //在ID_list中删除id
    for (auto it = ID_list->begin(); it != ID_list->end(); it++)
    {
        if (*it == patient_id)
        {
            ID_list->erase(it);
            break;
        }
    }
    return true;
}

PatientLogIn::PatientLogIn(const string& patient_id)
{
    this->id = new string(patient_id);
    //根据id在患者表中查询password
    PatientTable* PT = new PatientTable();
    string pwd = PT->get_attribute(patient_id, "password");
    this->password = new string(pwd);
}

PatientLogIn::~PatientLogIn()
{
    delete id;
    delete password;
}

bool PatientLogIn::login(const string& password)
{
    //检查密码是否正确
    if (this->password->compare(password) == 0)
        return true;
    else
        return false;
}