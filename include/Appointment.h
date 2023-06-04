#pragma once
#include "Mydatabase.h"

// 预约表的类定义
class Appointment {
    public:
        // 默认构造函数
        //Appointment(){}
        // 添加预约记录
        bool AddAppointment(string &pat_id, string &doc_id, string &info, string &time, string &id);
        // 删除预约记录
        bool DeleteAppointment(string &id);
        // 根据患者id查找预约记录
        vector<string> FindPatientAppointment(string &pat_id);
        // 根据医生id查找预约记录
        vector<vector<string>> FindDoctorAppointment(string &doc_id);
        // 根据时间查找患者名单
        vector<string> FindPatientAtTime(string &time);
        //~Appointment();
};