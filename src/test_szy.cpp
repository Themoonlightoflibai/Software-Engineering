/*
#include "Appointment.h"
#include "Schedule.h"
#include "Doctor_SubDepartment.h"
#include "Registration.h"

void test()
{
    // 测试Appointment
    
    // 添加预约
    {
        cout << endl; 
        cout << "test Appointment ..." << endl;
        Appointment appointment;
        string pat_id = "1";
        string doc_id = "1";
        string info = "123你好";
        string time = "6-1";
        string id = "1";
        bool res1 = appointment.AddAppointment(pat_id, doc_id, info, time, id);
        string pat_id_ = "2";
        string doc_id_ = "1";
        string info_ = "1234";
        string time_ = "6-1";
        string id_ = "1";
        bool res1_ = appointment.AddAppointment(pat_id_, doc_id_, info_, time_, id_);
        cout << "Appointment added " << res1 << " " << res1_ << endl;

        // 根据患者id查找预约记录
        // TODO: 有乱码
        vector<string> res2 = appointment.FindPatientAppointment(pat_id);
        cout << "Patient Appointment " << res2.back() << endl;

        // 根据医生id查找预约记录
        vector<vector<string>> res3 = appointment.FindDoctorAppointment(doc_id);
        for (auto res3_ : res3)
        {
            for (auto res : res3_)
            {
                cout << res << " ";
            }
            cout << endl;
        }
        
        // 根据时间查找患者名单
        vector<string> res4 = appointment.FindPatientAtTime(time);
        for (string res : res4)
        {
            cout << res << " ";
        }
        cout << endl;

        // 删除预约
        bool res5 = appointment.DeleteAppointment(id);
        cout << "Appointment deleted " << res5 << endl;
    }

    // 测试Schedule
    {
        cout << endl; 
        cout << "test Schedule ..." << endl;
        // 测试插入
        Schedule schedule;
        string doc_id = "1";
        string time = "6-1";
        int rest = 1;
        int total = 1;
        bool res1 = schedule.CreateSchedule(doc_id, time, rest, total);
        cout << "Schedule created " << res1 << endl;

        // 测试修改排班
        int change = 1;
        int choice1 = 1;
        int choice2 = 2;
        // 增加预约
        bool res2 = schedule.ChangeRest(doc_id, time, change, choice2);
        // 取消预约
        bool res3 = schedule.ChangeRest(doc_id, time, change, choice1);
        cout << "Schedule changed " << res2 << " " << res3 << endl;

        // 测试获取余量
        int res4 = schedule.GetRest(doc_id, time);
        cout << "Rest: " << res4 << endl;

        // 测试获取总量
        int res5 = schedule.GetTotal(doc_id, time);
        cout << "Total: " << res5 << endl;

        // 测试获取时间
        vector<string> res6 = schedule.GetTime(doc_id);
        for (auto res : res6)
        {
            cout << res << " ";
        }
        cout << endl;
    }

    // 测试Doctor_SubDepartment
    {
        cout << endl; 
        cout << "test Doctor_SubDepartment ..." << endl;
        Doctor_SubDepartment doc_subdepartment;
        string doc_id = "1";
        string apa_id = "1";
        cout << doc_subdepartment.CreateDoctor_SubDepartment(doc_id, apa_id) << endl;
        

        // 测试获取某子科室中的医生id列表
        vector<string> res1 = doc_subdepartment.GetDoctorid(apa_id);
        for (auto res : res1)
        {
            cout << res << " ";
        }
        cout << endl;

        // 测试获取医生的子科室id
        string res2 = doc_subdepartment.GetSubDepartmentid(doc_id);
        cout << res2 << endl;
    }

    // 测试Registration
    {
        cout << endl; 
        cout << "test Registration ..." << endl;

        // 测试添加挂号记录
        Registration registration;
        string pat_id = "1";
        string apa_id = "1";
        string id = "1";

        bool res1 = registration.AddRegistration(pat_id, apa_id, id);
        cout << "Registration Create " << res1 << endl;

        // 测试根据患者id查找子科室id
        string res2 = registration.GetSubDepartmentId(pat_id);
        cout << "SubDepartment " << res2 << endl;

        // 测试删除挂号记录
        bool res3 = registration.DeleteRegistration(id);
        cout << "Registration Delete " << res3 << endl; 
    }
}
*/