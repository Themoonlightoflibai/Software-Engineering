#pragma once
#include "Mydatabase.h"

// 挂号表的类定义
class Registration {
    public:
        // 默认构造函数
        //Registration(){}
        // 添加挂号记录
        string AddRegistration(string &pat_id, string &apa_id);
        // 删除挂号记录
        bool DeleteRegistration(string &id);
        // 根据患者id查找子科室id
        string GetSubDepartmentId(string &pat_id);
        //~Registration();
};
