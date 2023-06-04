#include"database.h"
#include <fstream>
#include <sstream>

using namespace std;

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
    vector<string> patient_id_list = doctor_table.get_patient_list(doctor_id);

    Json::Value Root;
    Json::StyledWriter sw;

    for(int i=0;i<patient_id_list.size();i++)
    {
        Root["patients"][i]["id"]=Json::Value(patient_id_list[i]);
        Root["patients"][i]["img"]=Json::Value(patient_table.get_attribute(patient_id_list[i],"img"));
        Root["patients"][i]["name"]=Json::Value(patient_table.get_attribute(patient_id_list[i],"name"));
        Root["patients"][i]["description"]=Json::Value(patient_table.get_attribute(patient_id_list[i],"description"));
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
    vector<string> patient_list = appointment_table.FindPatientAtTime(date,time_id);//////////????

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

void get_doctor_data(int doctor_id)
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
    string tokon = "";
    bool flag = doctor_table.set_string_attribute(doctor_id, type, content);//flag为1代表操作成功
    if (flag==1) tokon="200 OK";
    else tokon = "500 Internal Server Error, code 1000";

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

void get_timetable(int doctor_id)
{
    Schedule schedule_table;

    Json::Value Root;
    Json::StyledWriter sw;

    Root["timetable"]["周一"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,"周一上午")!=0));
    Root["timetable"]["周一"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,"周一下午")!=0));
    Root["timetable"]["周二"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,"周二上午")!=0));
    Root["timetable"]["周二"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,"周二下午")!=0));
    Root["timetable"]["周三"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,"周三上午")!=0));
    Root["timetable"]["周三"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,"周三下午")!=0));
    Root["timetable"]["周四"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,"周四上午")!=0));
    Root["timetable"]["周四"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,"周四下午")!=0));
    Root["timetable"]["周五"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,"周五上午")!=0));
    Root["timetable"]["周五"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,"周五下午")!=0));
    Root["timetable"]["周六"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,"周六上午")!=0));
    Root["timetable"]["周六"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,"周六下午")!=0));
    Root["timetable"]["周日"]["1"]=Json::Value(bool(schedule_table.GetRest(doctor_id,"周日上午")!=0));
    Root["timetable"]["周日"]["2"]=Json::Value(bool(schedule_table.GetRest(doctor_id,"周日下午")!=0));

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
  Patient_Table patient_table=patient_table.NewPatientTable();//初始化更新患者表，这个类应该是结构体指针链表的形式吧
  string password_tmp=patient_table.SearchPasswordByPhone(phone);//如果未注册，返回""空字符串
  
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
  Patient_Table patient_table=patient_table.NewPatientTable();//初始化更新患者表，这个类应该是结构体指针链表的形式吧
  string password_tmp=patient_table.SearchPasswordByPhone(phone);//如果未注册，返回""空字符串
  
  string token="";
  if(password_tmp=="")//手机号未被注册
  {
    token=patient_table.AddNewPatient(phone,password,name,id_number,gender,ethnicity);//添加成功，返回string"200 OK"，否则返回""
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
  Patient_Table patient_table=patient_table.NewPatientTable();//初始化更新患者表，这个类应该是结构体指针链表的形式吧
  string password_tmp=patient_table.SearchPasswordByPhone(phone);//如果未注册，返回""空字符串
  
  string token="";
  if(password_tmp=="")//未注册，返回 403 Forbidden，code 1001
  token="403 Forbidden, code 1001";
  else if(password_tmp!=old_password)//旧密码错误 - 返回 403 Forbidden，code 1002
  token="403 Forbidden, code 1002";
  else //修改密码
  {
    patient_table.UpdatePasswordByPhone(phone,new_password);
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
  Department_Table department_table=department_table.NewDepartmentTable();//初始化更新科室表，这个类应该是结构体指针链表的形式吧
  vector<department> department_list=department_table.GetDepartmentList();//出错的话返回空vector
  Json::Value Root;
  Json::StyledWriter sw;
  
  string token="";
  if(department_list.size()==0)//出现错误 - 返回 500 Internal Server Error，code 1000
  token="500 Internal Server Error, code 1000";
  else
  token="200 OK";
  Root["token"]=Json::Value(token);

  for(int i=0;i<department_list.size();i++)
  {
    Root["data"][i]["id"]=Json::Value(department_list[i]->id);
    Root["data"][i]["name"]=Json::Value(department_list[i]->name);
  }
  
  ofstream os;
  os.open("demo.json", std::ios::out | std::ios::trunc);
  if (!os.is_open())
    cout << "error:can not find or create the file which named \" demo.json\"." << endl;
  os << sw.write(Root);
  os.close();

  return;
}

void get_department_details(int department_id)
{
  Department_Table department_table=department_table.NewDepartmentTable();//初始化更新科室表，这个类应该是结构体指针链表的形式吧
  string name=department_table.GetNameByID(department_id);//id不存在的话，返回""
  string token="";
  string description="";
  vector<department> subdepartment_list;
  Json::Value Root;
  Json::StyledWriter sw;
  if(name=="")//id不存在,- 返回 400 Bad Request，code 1005
  {
    token="400 Bad Request, code 1005";
  }
  else
  {
    description=department_table.GetDescriptionByID(department_id);
    subdepartment_list=department_table.GetSublistByID(department_id);//出错的话返回空vector
    if(subdepartment_list.size()==0)//出现错误 - 返回 500 Internal Server Error，code 1000
    token="500 Internal Server Error, code 1000";
    else
    token="200 OK";
  }

  Root["token"]=Json::Value(token);
  if(name!="")//科室id存在
  {
    Root["description"]=Json::Value(description);
    for(int i=0;i<subdepartment_list.size();i++)
    {
      Root["sub_departs"][i]["id"]=subdepartment_list[i]->id;
      Root["sub_departs"][i]["name"]=subdepartment_list[i]->name;
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
  Doctor_Table doctor_table=doctor_table.NewDoctorTable();//初始化更新医生表，这个类应该是结构体指针链表的形式吧
  vector<doctor> doctor_list=doctor_table.GetDoctorList();//出错的话返回空vector
  string token;
  Json::Value Root;
  Json::StyledWriter sw;
  if(doctor_list.size()==0)//出现错误 - 返回 500 Internal Server Error，code 1000
    token="500 Internal Server Error, code 1000";
  else
    token="200 OK";
  Root["token"]=Json::Value(token);
  for(int i=0;i<doctor_list.size();i++)
  {
    Root["doctors"][i]["id"]=Json::Value(doctor_list[i]->id);
    Root["doctors"][i]["name"]=Json::Value(doctor_list[i]->name);
    Root["doctors"][i]["sub_departs_id"]=Json::Value(doctor_list[i]->sub_depart_id);
    Root["doctors"][i]["sub_depart_name"]=Json::Value(doctor_list[i]->sub_depart_name);
    Root["doctors"][i]["description"]=Json::Value(doctor_list[i]->description);
    for(int j=0;j<14;j++)
    {
      Root["doctors"][i]["schedule"][j]["capacity"]=Json::Value(doctor_list[i]->schedule[2*j]);
      Root["doctors"][i]["schedule"][j]["remain"]=Json::Value(doctor_list[i]->schedule[2*j+1]);
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
//获取失败应该如何返回？？
void get_subdepartment_doctor_list(string subdepartment_id)
{
    SubDepartment subdepartment;
    DoctorTable doctortable;
    Schedule schedule;

    vector<string> doctor_list = subdepartment.GetDoctorid(subdepartment_id);
    Json::Value Root;

    for(int i = 0;i < doctor_list.size();i++)
    {
        Json::Value doctor;
        doctor["id"] = Json::Value(doctor_list[i]);
        string* doctor_name = doctortable.get_string_attribute(doctor_list[i],"name");        //string* 会不会改
        doctor["name"] = Json::Value(doctor_name[0]);
        for(int i = 0;i < 14;i++)
        {
            Json::Value time_schedule;
            string time;                                                     //不知道怎么获取时间,姑且先这么写
            int capacity = schedule.GetTotal(doctor_list[i],time);
            int rest = schedule.GetRest(doctor_list[i],time);
            time_schedule["capacity"] = Json::Value(capacity);
            time_schedule["remain"] = Json::Value(rest);
            doctor["schedule"].append(time_schedule);
        }
        string* doctor_description = doctortable.get_string_attribute(doctor_list[i],"introduction");
        doctor["description"] = Json::Value(doctor_description[0]);
        doctor["image_url"] = "...";                                         //姑且先空着
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
    int isin = doctortable.has_id(doctor_id);
    bool success;
    string id;                                                                        //不知道怎么获取
    if(isin)
    {
        string time;                                                                  //姑且这么写
        int rest = schedule.GetRest(doctor_id,time);
        if(rest > 0)
        {
            string * info = patienttable.get_attribute(patient_id,"link");              // string*
            success = appointment.AddAppointment(patient_id,doctor_id,info[0],time,id);
        }
    }
    Json::Value Root;
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

void cancel_appointment(std::string appointment_id)
{
    Appointment appointment;
    appointment.DeleteAppointment(appointment_id);                        //需要判断预约是否存在吗？
}

void get_patient_data(std::string patient_id)                 
{
    PatientTable patienttable;

    int isin = patienttable.has_id(patient_id);
    if(isin)
    {
        Json::Value Root;
        string* name = patienttable.get_attribute(patient_id,"name");          //string*
        Root["name"] = Json::Value(name[0]);
        string* gender = patienttable.get_attribute(patient_id,"gender");
        Root["gender"] = Json::Value(gender[0]);
        string* ethnicity = patienttable.get_attribute(patient_id,"ethnicity");
        Root["ethnicity"] = Json::Value(ethnicity[0]);
        string* IDcard = patienttable.get_attribute(patient_id,"IDcard");
        Root["id_number"] = Json::Value(IDcard[0]);
        string* phone = patienttable.get_attribute(patient_id,"phone");
        Root["phone"] = Json::Value(phone[0]);

        Json::StyledWriter sw;
        std::ofstream os;

        os.open("demo.json", std::ios::out | std::ios::trunc);
        if (!os.is_open())
            cout << "error:can not find or create the file which named \" demo.json\"." << endl;
        os << sw.write(Root);
        os.close();
    }
}
void modify_patient_data(std::string patient_id, std::string name, std::string gender, std::string ethnicity, std::string id_number, std::string phone_number)
{
    PatientTable patienttable;

    int isin = patienttable.has_id(patient_id);
    if(isin)
    {
        patienttable.set_attribute(patient_id,"name",name);
        patienttable.set_attribute(patient_id,"gender",gender);
        patienttable.set_attribute(patient_id,"ethnicity",ethnicity);
        patienttable.set_attribute(patient_id,"IDcard",id_number);
        patienttable.set_attribute(patient_id,"phone",phone_number);
    }
}