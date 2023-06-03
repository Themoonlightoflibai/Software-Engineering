#include <iostream>
#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include "database.h"

using namespace std;
// 挂号表的类定义
class Registration {
    public:
        // 默认构造函数
        Registration();
        // 添加挂号记录
        bool AddRegistration(string &pat_id, string &apa_id, string &id);
        // 删除挂号记录
        bool DeleteRegistration(string &id);
};