#pragma once
#include "Mydatabase.h"

// 医生-子科室的类定义
class Doctor_SubDepartment {
    public:
        // 默认构造函数
        //Doctor_SubDepartment(){}
        // 新增记录，测试用
        bool CreateDoctor_SubDepartment(string &doc_id, string &apa_id);
        // 获取某子科室中的医生id列表
        vector<string> GetDoctorid(string &apa_id);
        // 获取医生的子科室id
        string GetSubDepartmentid(string &doc_id);
        //~Doctor_SubDepartment();
};
