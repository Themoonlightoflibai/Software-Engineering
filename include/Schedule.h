#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include "database.h"

using namespace std;
// 排班表的类定义
class Schedule {
    public:
        // 默认构造函数
        Schedule();
        // 构造函数
        bool CreateSchedule(string &doc_id, string &time, int &rest, int &total);
        // 修改排班, change始终等于1，choice---1为取消，2为增加
        bool ChangeRest(string &doc_id, string &time, int &change, int &choice);
        // 获取余量
        int GetRest(string &doc_id, string &time);
        // 获取总量
        int GetTotal(string &doc_id, string &time);
};