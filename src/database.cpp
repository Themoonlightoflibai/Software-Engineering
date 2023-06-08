#include"database.h"
#include "Appointment.h"
#include "Department_Table.h"
#include "Doctor_SubDepartment.h"
#include "DoctorTable.h"
#include "mydatabase.h"
#include "PatientTable.h"
#include "Registration.h"
#include "Schedule.h"
#include <time.h>
#include "MyDate.h"
#include "SubDepartment_Table.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

using std::string;
using std::ofstream;

//张铭杰
void get_patient_data(std::string patient_id)
{
  PatientTable patient_table;
  Registration registeration;
  Json::Value Root;
  Json::StyledWriter sw;

  Root["id"]=Json::Value(patient_id);
  Root["img"]=Json::Value(patient_table.get_attribute(patient_id,"img"));
  Root["name"]=Json::Value(patient_table.get_attribute(patient_id,"name"));
  Root["gender"]=Json::Value(patient_table.get_attribute(patient_id,"gender"));
  Root["menu"]=Json::Value(registeration.GetSubDepartmentId(patient_id));
  Root["telephone"]=Json::Value(patient_table.get_attribute(patient_id,"phone"));
  Root["information"]=Json::Value(patient_table.get_attribute(patient_id,"description"));

  Write:
  ofstream os;
	os.open("demo.json", std::ios::out | std::ios::trunc);
	if (!os.is_open())
		cout << "error:can not find or create the file which named \" demo.json\"." << endl;
	os << sw.write(Root);
	os.close();
}

void get_patient_list(string doctor_id)
{
    DoctorTable doctor_table;
    PatientTable patient_table;
    vector<string>* patient_id_list = doctor_table.get_patient_list(doctor_id);

    Json::Value Root;
    Json::StyledWriter sw;

    for(int i=0;i<(*patient_id_list).size();i++)
    {
        Root["patients"][i]["id"]=Json::Value((*patient_id_list)[i]);
        Root["patients"][i]["img"]=Json::Value(patient_table.get_attribute((*patient_id_list)[i],"img"));
        Root["patients"][i]["name"]=Json::Value(patient_table.get_attribute((*patient_id_list)[i],"name"));
        Root["patients"][i]["description"]=Json::Value(patient_table.get_attribute((*patient_id_list)[i],"description"));
    }
    ofstream os;

    os.open("demo.json", std::ios::out | std::ios::trunc);
    if (!os.is_open())
        cout << "error:can not find or create the file which named \" demo.json\"." << endl;
    os << sw.write(Root);
    os.close();
}
//////////////
void get_time_patient_list(std::string date, std::string time_id)
{
    Appointment appointment_table;
    PatientTable patient_table;
    std::string time = date + "," + time_id;
    vector<string> patient_list = appointment_table.FindPatientAtTime(time);

    Json::Value Root;
    Json::StyledWriter sw;

    for(int i=0;i<patient_list.size();i++)
    {
        Root["patient"][i]["id"]=Json::Value(patient_list[i]);
        Root["patient"][i]["name"]=Json::Value(patient_table.get_attribute(patient_list[i],"name"));
        Root["patient"][i]["img"]=Json::Value(patient_table.get_attribute(patient_list[i],"img"));
        Root["patient"][i]["description"]=Json::Value(patient_table.get_attribute(patient_list[i],"description"));
    }
    ofstream os;
    os.open("demo.json", std::ios::out | std::ios::trunc);
    if (!os.is_open())
        cout << "error:can not find or create the file which named \" demo.json\"." << endl;
    os << sw.write(Root);
    os.close();
}

void get_doctor_data(string doctor_id)
{
    DoctorTable doctor_table;
    Doctor_SubDepartment subdepartment;
    PatientTable patient_table;
    Registration registeration;

    Json::Value Root;
    Json::StyledWriter sw;
   
    Root["id"]=Json::Value(doctor_id);
    Root["img"]=Json::Value(doctor_table.get_string_attribute(doctor_id, "img"));
    Root["name"]=Json::Value(doctor_table.get_string_attribute(doctor_id, "name"));
    Root["menu"]=Json::Value(subdepartment.GetSubDepartmentid(doctor_id));
    Root["gender"]=Json::Value(doctor_table.get_string_attribute(doctor_id, "gender"));
    Root["title"]=Json::Value(doctor_table.get_string_attribute(doctor_id, "title"));
    Root["introduction"]=Json::Value(doctor_table.get_string_attribute(doctor_id, "introduction"));
    
    Write:
    ofstream os;
    os.open("demo.json", std::ios::out | std::ios::trunc);
    if (!os.is_open())
        cout << "error:can not find or create the file which named \" demo.json\"." << endl;
    os << sw.write(Root);
    os.close();
}

void modify_doctor_data(std::string doctor_id, int type, std::string content)
{
    DoctorTable doctor_table;
    string token = "";

    std::unordered_map<int, string>attribute;
    attribute[1] = "depart";
    attribute[2] = "name";
    attribute[3] = "gender";
    attribute[4] = "title";
    attribute[5] = "phone";
    attribute[6] = "introcuction";

    bool flag = doctor_table.set_string_attribute(doctor_id, attribute[type], content);//flag为1代表操作成功
    if (flag==1) token="200 OK";
    else token = "500 Internal Server Error, code 1000";

    Json::Value Root;
    Json::StyledWriter sw;
    Root["token"]=Json::Value(token);

    ofstream os;
    os.open("demo.json", std::ios::out | std::ios::trunc);
    if (!os.is_open())
        cout << "error:can not find or create the file which named \" demo.json\"." << endl;
    os << sw.write(Root);
    os.close();
    return;
}

void get_timetable(string doctor_id)
{
    Schedule schedule_table;
    std::string middle;
    Json::Value Root;
    Json::StyledWriter sw;

    time_t t = time(0); 
    char tmp[32];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d",localtime(&t)); 
    char weekend[2];
    strftime(weekend, sizeof(weekend), "%w",localtime(&t));
    middle = tmp;

    switch(weekend[0])
    {
        case '1' :  Root["timetable"]["周一"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周一"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周二"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周二"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周三"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周三"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周四"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周四"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周五"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周五"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周六"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周六"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周日"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周日"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    break;
        case '2' :  Root["timetable"]["周二"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周二"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周一"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周一"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    middle = Tomorrow(middle);
                    Root["timetable"]["周三"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周三"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周四"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周四"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周五"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周五"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周六"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周六"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周日"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周日"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    break;
        case '3' :  Root["timetable"]["周三"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周三"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周二"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周二"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周一"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周一"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    middle = Tomorrow(middle);
                    middle = Tomorrow(middle);
                    Root["timetable"]["周四"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周四"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周五"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周五"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周六"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周六"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周日"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周日"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    break;
        case '4' :  Root["timetable"]["周四"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周四"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周三"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周三"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周二"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周二"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周一"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周一"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    middle = Tomorrow(middle);
                    middle = Tomorrow(middle);
                    middle = Tomorrow(middle);
                    Root["timetable"]["周五"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周五"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周六"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周六"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周日"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周日"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    break;
        case '5' :  Root["timetable"]["周五"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周五"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周四"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周四"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周三"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周三"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周二"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周二"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周一"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周一"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    middle = Tomorrow(middle);
                    middle = Tomorrow(middle);
                    middle = Tomorrow(middle);
                    middle = Tomorrow(middle);
                    Root["timetable"]["周六"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周六"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    Root["timetable"]["周日"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周日"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    break;
        case '6' :  Root["timetable"]["周六"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周六"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周五"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周五"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周四"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周四"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周三"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周三"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周二"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周二"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周一"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周一"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Tomorrow(middle);
                    middle = Tomorrow(middle);
                    middle = Tomorrow(middle);
                    middle = Tomorrow(middle);
                    middle = Tomorrow(middle);
                    middle = Tomorrow(middle);
                    Root["timetable"]["周日"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周日"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    break;
        case '7' :  Root["timetable"]["周日"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周日"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周六"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周六"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周五"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周五"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周四"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周四"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周三"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周三"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周二"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周二"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
                    middle = Yesterday(middle);
                    Root["timetable"]["周一"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",1")!=0));
                    Root["timetable"]["周一"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,middle + ",2")!=0));
    }

    ofstream os;
	os.open("demo.json", std::ios::out | std::ios::trunc);
	if (!os.is_open())
		cout << "error:can not find or create the file which named \" demo.json\"." << endl;
	os << sw.write(Root);
	os.close();
}

//郑楚泓
void login(std::string phone, std::string password)
{
  PatientTable patient_table;
  string *patient_id=patient_table.get_id_by_phone(phone);
  string password_tmp=patient_table.get_attribute(*patient_id,"password");//如果未注册，返回""空字符串
  
  string token="";
  if(password_tmp=="")//==运算符重载,未注册，返回 403 Forbidden，code 1001
  token="403 Forbidden, code 1001";
  else if(password_tmp==password)//成功 - 返回 200 OK
  token="200 OK";
  else//密码错误 - 返回 403 Forbidden，code 1002
  token="403 Forbidden, code 1002";

  Json::Value Root;
  Json::StyledWriter sw;
  Root["token"]=Json::Value(token);

  ofstream os;
  os.open("demo.json", std::ios::out | std::ios::trunc);
  if (!os.is_open())
    cout << "error:can not find or create the file which named \" demo.json\"." << endl;
  os << sw.write(Root);
  os.close();
  return;
}

void signup(std::string phone, std::string password, std::string name, std::string id_number, int gender, std::string ethnicity)
{
  PatientTable patient_table;
  string *patient_id=patient_table.get_id_by_phone(phone);
  string password_tmp=patient_table.get_attribute(*patient_id,"password");//如果未注册，返回""空字符串
  
  string token="";
  if(password_tmp=="")//手机号未被注册
  {
    patient_id = patient_table.get_new_id();
    patient_table.add_patient(*patient_id);
    (phone,password,name,id_number,gender,ethnicity);//添加成功，返回string"200 OK"，否则返回""
    patient_table.set_attribute(*patient_id,"phone",phone);
    patient_table.set_attribute(*patient_id,"password",password);
    patient_table.set_attribute(*patient_id,"name",name);
    patient_table.set_attribute(*patient_id,"id_number",id_number);
    patient_table.set_attribute(*patient_id,"gender",std::to_string(gender));
    patient_table.set_attribute(*patient_id,"ethnicity",ethnicity);
    token="200 OK";
  }
  else //手机号已被注册 - 返回 400 Bad Request，code 1003
  {
    token="400 Bad Request, code 1003";
  }

  Json::Value Root;
  Json::StyledWriter sw;
  Root["token"]=Json::Value(token);

  ofstream os;
  os.open("demo.json", std::ios::out | std::ios::trunc);
  if (!os.is_open())
    cout << "error:can not find or create the file which named \" demo.json\"." << endl;
  os << sw.write(Root);
  os.close();

  return;
}

void newpwd(std::string phone, std::string old_password, std::string new_password)
{
  PatientTable patient_table;//初始化更新患者表，这个类应该是结构体指针链表的形式吧
  string *patient_id=patient_table.get_id_by_phone(phone);
  string password_tmp=patient_table.get_attribute(*patient_id,"password");//如果未注册，返回""空字符串
  
  string token="";
  if(password_tmp=="")//未注册，返回 403 Forbidden，code 1001
  token="403 Forbidden, code 1001";
  else if(password_tmp!=old_password)//旧密码错误 - 返回 403 Forbidden，code 1002
  token="403 Forbidden, code 1002";
  else //修改密码
  {
    patient_table.set_attribute(*patient_id,"password",new_password);
    token="200 OK";
  }

  Json::Value Root;
  Json::StyledWriter sw;
  Root["token"]=Json::Value(token);

  ofstream os;
  os.open("demo.json", std::ios::out | std::ios::trunc);
  if (!os.is_open())
    cout << "error:can not find or create the file which named \" demo.json\"." << endl;
  os << sw.write(Root);
  os.close();
  return;
}

void get_department_list()
{
  //用vector来存list
  Department_Table department_table;
  vector<string>* department_list=department_table.getDepartmentList();//出错的话返回NULL
  Json::Value Root;
  Json::StyledWriter sw;

  string id="";
  string name="";
  string token="";
  if(department_list==NULL)//出现错误 - 返回 500 Internal Server Error，code 1000
  token="500 Internal Server Error, code 1000";
  else
  token="200 OK";
  Root["token"]=Json::Value(token);

  for(int i=0;i<(*department_list).size();i++)
  {
    id=(* department_list)[i];
    name=department_table.getDepartmentName(id);
    Root["data"][i]["id"]=Json::Value(id);
    Root["data"][i]["name"]=Json::Value(name);
  }
  
  ofstream os;
  os.open("demo.json", std::ios::out | std::ios::trunc);
  if (!os.is_open())
    cout << "error:can not find or create the file which named \" demo.json\"." << endl;
  os << sw.write(Root);
  os.close();

  return;
}

void get_department_details(string department_id)
{
  Department_Table department_table;
  string name=department_table.getDepartmentName(department_id);//id不存在的话，返回""
  string token="";
  string description="";
  Json::Value Root;
  Json::StyledWriter sw;
  string sub_name="";
  string sub_id="";
  if(name=="")//id不存在,- 返回 400 Bad Request，code 1005
  {
    token="400 Bad Request, code 1005";
    Root["token"]=Json::Value(token);
  }
  else
  {
    description=department_table.getDepartmentInfo(department_id);
    SubDepartment_Table subdepartment_table;
    vector<string>* subdepartment_list=subdepartment_table.getSubDepartmentIdByDepatmentId(department_id);//出错的话返回空vector
    if(subdepartment_list==NULL)//出现错误 - 返回 500 Internal Server Error，code 1000
    token="500 Internal Server Error, code 1000";
    else
    token="200 OK";
    Root["token"]=Json::Value(token);
    Root["description"]=Json::Value(description);
    for(int i=0;i<(*subdepartment_list).size();i++)
    {
      sub_id=(*subdepartment_list)[i];
      sub_name=subdepartment_table.getSubDepartmentName(sub_id);
      Root["sub_departs"][i]["id"]=Json::Value(sub_id);
      Root["sub_departs"][i]["name"]=Json::Value(sub_name);
    }
  }


  ofstream os;
  os.open("demo.json", std::ios::out | std::ios::trunc);
  if (!os.is_open())
    cout << "error:can not find or create the file which named \" demo.json\"." << endl;
  os << sw.write(Root);
  os.close();
  return;
}

void get_doctor_list()
{
  DoctorTable doctor_table;
  vector<string>* doctor_list=doctor_table.get_doctor_list();//出错的话返回NULL
  string token;
  Json::Value Root;
  Json::StyledWriter sw;
  string doctor_id="";
  string doctor_name="";
  string doctor_sub_depart_id="";
  string doctor_sub_depart_name="";
  string doctor_description="";
  int doctor_schedule[28];

  if(doctor_list==NULL)//出现错误 - 返回 500 Internal Server Error，code 1000
    token="500 Internal Server Error, code 1000";
  else
    token="200 OK";
  Root["token"]=Json::Value(token);
  for(int i=0;i<(*doctor_list).size();i++)
  {
    doctor_id=(*doctor_list)[i];
    doctor_name=doctor_table.get_string_attribute(doctor_id,"name");
    doctor_sub_depart_id=doctor_table.get_string_attribute(doctor_id,"doctor_sub_depart_id");
    doctor_sub_depart_name=doctor_table.get_string_attribute(doctor_id,"doctor_sub_depart_name");
    doctor_description=doctor_table.get_string_attribute(doctor_id,"doctor_description");
    Root["doctors"][i]["id"]=Json::Value(doctor_id);
    Root["doctors"][i]["name"]=Json::Value(doctor_name);
    Root["doctors"][i]["sub_departs_id"]=Json::Value(doctor_sub_depart_id);
    Root["doctors"][i]["sub_depart_name"]=Json::Value(doctor_sub_depart_name);
    Root["doctors"][i]["description"]=Json::Value(doctor_description);
    Schedule schedule;
    string time_[14];
    time_t t = time(0); 
    char tmp[32];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d",localtime(&t)); 
    time_[0]=tmp;
    for(int i=1;i<7;i++)
      time_[2*i]=Tomorrow(time_[2*(i-1)]);
    for(int i=0;i<7;i++)
    {
      time_[2*i+1]=time_[2*i]+",2";
      time_[2*i]=time_[2*i]+",1";
    }
    for(int j=0;j<14;j++)
    {
      doctor_schedule[2*j]=schedule.GetTotal(doctor_id,time_[j]);
      doctor_schedule[2*j+1]=schedule.GetRest(doctor_id,time_[j]);
      Root["doctors"][i]["schedule"][j]["capacity"]=Json::Value(doctor_schedule[2*j]);
      Root["doctors"][i]["schedule"][j]["remain"]=Json::Value(doctor_schedule[2*j+1]);
    }
  }

  ofstream os;
  os.open("demo.json", std::ios::out | std::ios::trunc);
  if (!os.is_open())
    cout << "error:can not find or create the file which named \" demo.json\"." << endl;
  os << sw.write(Root);
  os.close();
  return;
}

//朱圣铭
void get_subdepartment_doctor_list(string subdepartment_id)
{
    Doctor_SubDepartment subdepartment;
    DoctorTable doctortable;
    Schedule schedule;
    SubDepartment_Table subdepartment_table;

    vector<string> doctor_list = subdepartment.GetDoctorid(subdepartment_id);
    Json::Value Root;

    if(doctor_list.size() == 0)
    {
        Root["token"] = Json::Value("400 Bad Request，code 1005");
    }
    else
    {
        Root["token"] = Json::Value("200 OK");
    }
    for(int i = 0;i < doctor_list.size();i++)
    {
        Json::Value doctor;
        doctor["id"] = Json::Value(doctor_list[i]);
        string doctor_name = doctortable.get_string_attribute(doctor_list[i],"name");        
        doctor["name"] = Json::Value(doctor_name);

        string time_[14];
        time_t t = time(0);
        char tmp[32];
        strftime(tmp, sizeof(tmp), "%Y-%m-%d",localtime(&t));
        time_[0] = tmp;
        for(int k = 1;k < 7;k++)
            time_[2*k] = Tomorrow(time_[2*(k-1)]);
        for(int k = 0;k < 7;k++)
        {
            time_[2*k+1] = time_[2*k] + ",2";
            time_[2*k] = time_[2*k] + ",1";
        }
        for(int j = 0;j < 14;j++)
        {
            Json::Value time_schedule;
            int capacity = schedule.GetTotal(doctor_list[i],time_[j]);
            int rest = schedule.GetRest(doctor_list[i],time_[j]);
            time_schedule["capacity"] = Json::Value(capacity);
            time_schedule["remain"] = Json::Value(rest);
            doctor["schedule"].append(time_schedule);
        }
        string doctor_description = doctortable.get_string_attribute(doctor_list[i],"introduction");
        doctor["description"] = Json::Value(doctor_description);
        doctor["image_url"] = "...";                                         
        Root["doctors"].append(doctor);
    }
    Json::StyledWriter sw;
    std::ofstream os;

    os.open("demo.json", std::ios::out | std::ios::trunc);
    if (!os.is_open())
        cout << "error:can not find or create the file which named \" demo.json\"." << endl;
    os << sw.write(Root);
    os.close();
}

void create_appointment(std::string patient_id, std::string doctor_id, int section)
{
    DoctorTable doctortable;
    Schedule schedule;
    Appointment appointment;
    PatientTable patienttable;
    Registration reg;
    Doctor_SubDepartment doctor_subdepartment;
    int isin = doctortable.has_id(doctor_id);
    string apa_id = doctor_subdepartment.GetSubDepartmentid(doctor_id);
    string id = reg.AddRegistration(patient_id, apa_id);
    string info = patienttable.get_attribute(patient_id, "description");
    bool success;
    Json::Value Root;                                                                
    if(isin)
    {
        if(section > 14 || section < 1)
        Root["token"] = Json::Value("400 Bad Request，code 1006");
        else
        {
            Root["token"] = Json::Value("200 OK");  
            string time_[14];
            time_t t = time(0);
            char tmp[32];
            strftime(tmp, sizeof(tmp), "%Y-%m-%d",localtime(&t));
            time_[0] = tmp;
            for(int k = 1;k < 7;k++)
                time_[2*k] = Tomorrow(time_[2*(k-1)]);
            for(int k = 0;k < 7;k++)
            {
                time_[2*k+1] = time_[2*k] + ",2";
                time_[2*k] = time_[2*k] + ",1";
            }                                                               
            int rest = schedule.GetRest(doctor_id,time_[section-1]);
            if(rest > 0)
            {
                string  info = patienttable.get_attribute(patient_id,"link");              
                success = appointment.AddAppointment(patient_id,doctor_id, info, time_[section-1], id);
            }
        }
    }
    else
    {
        Root["token"] = Json::Value("400 Bad Request，code 1005");
    }
    
    if(success)
    {
        Root["app_id"] = Json::Value(id);
    }
    else
    {
        Root["app_id"] = Json::Value("-1");
    }
    Json::StyledWriter sw;
    std::ofstream os;

    os.open("demo.json", std::ios::out | std::ios::trunc);
    if (!os.is_open())
        cout << "error:can not find or create the file which named \" demo.json\"." << endl;
    os << sw.write(Root);
    os.close();
}

void cancel_appointment(std::string appointment_id,std::string parent_id)
{
    Appointment appointment;
    Json::Value Root;
    bool flag = appointment.DeleteAppointment(appointment_id);
    if(flag)
    {
        Root["token"] = Json::Value("200 OK");
    }
    else
    {
        Root["token"] = Json::Value("400 Bad Request，code 1005");
    }
    Json::StyledWriter sw;
    std::ofstream os;

    os.open("demo.json", std::ios::out | std::ios::trunc);
    if (!os.is_open())
        cout << "error:can not find or create the file which named \" demo.json\"." << endl;
    os << sw.write(Root);
    os.close();
}

void get_patient_data(std::string patient_id)                 
{
    PatientTable patienttable;
    Json::Value Root;

    bool isin = patienttable.has_id(patient_id);
    if(isin)
    {
        Root["token"] = Json::Value("200 OK");
        string name = patienttable.get_attribute(patient_id,"name");          
        Root["name"] = Json::Value(name);
        string gender = patienttable.get_attribute(patient_id,"gender");
        Root["gender"] = Json::Value(gender);
        string ethnicity = patienttable.get_attribute(patient_id,"ethnicity");
        Root["ethnicity"] = Json::Value(ethnicity);
        string IDcard = patienttable.get_attribute(patient_id,"IDcard");
        Root["id_number"] = Json::Value(IDcard);
        string phone = patienttable.get_attribute(patient_id,"phone");
        Root["phone"] = Json::Value(phone);
    }
    else
    {
        Root["token"] = Json::Value("500 Internal Server Error，code 1000");
    }
    Json::StyledWriter sw;
    std::ofstream os;
    os.open("demo.json", std::ios::out | std::ios::trunc);
    if (!os.is_open())
        cout << "error:can not find or create the file which named \" demo.json\"." << endl;
    os << sw.write(Root);
    os.close();
}
void modify_patient_data(std::string patient_id, std::string name, std::string gender, std::string ethnicity, std::string id_number, std::string phone_number)
{
    PatientTable patienttable;
    Json::Value Root;

    bool isin = patienttable.has_id(patient_id);
    if(isin)
    {
        Root["token"] = Json::Value("200 OK");
        patienttable.set_attribute(patient_id,"name",name);
        patienttable.set_attribute(patient_id,"gender",gender);
        patienttable.set_attribute(patient_id,"ethnicity",ethnicity);
        patienttable.set_attribute(patient_id,"IDcard",id_number);
        patienttable.set_attribute(patient_id,"phone",phone_number);
    }
    else
    {
        Root["token"] = Json::Value("500 Internal Server Error，code 1000");
    }
    Json::StyledWriter sw;
    std::ofstream os;
    os.open("demo.json", std::ios::out | std::ios::trunc);
    if (!os.is_open())
        cout << "error:can not find or create the file which named \" demo.json\"." << endl;
    os << sw.write(Root);
    os.close();
}