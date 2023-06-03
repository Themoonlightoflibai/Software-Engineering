#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <vector>
#include "database.h"

using namespace std;
// 子科室的类定义
class SubDepartment {
    public:
        // 默认构造函数
        SubDepartment();
        // 获取某子科室中的医生id列表
        vector<string> GetDoctorid(string &apa_id);
        // 获取医生的子科室id
        string GetSubDepartmentid(string &doc_id);
};
