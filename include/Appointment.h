#include <iostream>
#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <vector>
#include "database.h"

using namespace std;
// 预约表的类定义
class Appointment {
    public:
        // 默认构造函数
        Appointment();
        // 添加预约记录
        bool AddAppointment(string &pat_id, string &doc_id, string &info, string &time, string &id);
        // 删除预约记录
        bool DeleteAppointment(string &id);
        // 根据患者id查找预约记录
        vector<string> FindAppointment(string &pat_id);
};