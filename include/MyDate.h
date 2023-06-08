#include<iostream>
#include <string>
#include<time.h>
using namespace std;
struct date{
    int month;
    int day;
    int year;
};

//结构体转成string
string Date2String(struct date d)
{
    string s="1900-01-01";
    //cout<<s<<endl;
    s[0]=d.year/1000+'0';
    //cout<<s<<endl;
    s[1]=(d.year/100)%10+'0';
    s[2]=(d.year/10)%10+'0';
    s[3]=d.year%10+'0';
    s[5]=(d.month/10)%10+'0';
    s[6]=d.month%10+'0';
    s[8]=(d.day/10)%10+'0';
    s[9]=d.day%10+'0';
    //cout<<s<<endl;
    return s;
}
//反过来
struct date String2Date(string s)
{
    struct date d;
    int t1,t2,t3;
    t1=t2=t3=0;
    t1=(s[0]-'0')*1000+(s[1]-'0')*100+(s[2]-'0')*10+(s[3]-'0');
    t2=(s[5]-'0')*10+(s[6]-'0');
    t3=(s[8]-'0')*10+(s[9]-'0');
    d.year=t1;
    d.month=t2;
    d.day=t3;
    return d;
}
//判断闰年
bool isLeap(struct date d)
{
    bool leap = 0;
    if((d.year %4==0 && d.year %100 !=0) || d.year%400 == 0){
        leap = 1;
    }
    return leap;
}
//这个月有多少天
int number0fDays(struct date d)
{
    int days;
    const int daysPerMOnth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(d.month == 2 && isLeap(d)){
        days = 29;
    }else{
        days = daysPerMOnth[d.month-1];
    }
    return days;
}
//输入结构体返回明天的结构体
struct date TomorrowByDate(struct date today)
{
    struct date tomorrow;
    if(today.day != number0fDays(today)){
        tomorrow.day = today.day+1;
        tomorrow.month = today.month;
        tomorrow.year = today.year;
    }
    else if(today.month == 12){
        tomorrow.day = 1;
        tomorrow.month = 1;
        tomorrow.year = today.year+1;
    }
    else{
        tomorrow.day = 1;
        tomorrow.month = today.month + 1;
        tomorrow.year = today.year;
    }
    return tomorrow;
}
//输入今天返回明天
string Tomorrow(string today)
{
    string tomorrow;
    struct date d1=String2Date(today);
    struct date d2=TomorrowByDate(d1);
    tomorrow=Date2String(d2);
    return tomorrow;
}
//输入结构体返回昨天结构体
struct date YesterdayByDate(struct date today)
{
    struct date yesterday;
    if(today.day != 1){
        yesterday.day = today.day-1;
        yesterday.month = today.month;
        yesterday.year = today.year;
    }
    else if(today.month == 1){
        yesterday.day = 31;
        yesterday.month = 12;
        yesterday.year = today.year-1;
    }
    else{
        struct date inter_date;
        inter_date.day = 1;
        inter_date.month = today.month -1;
        inter_date.year = today.year;
        yesterday.day = number0fDays(inter_date);
        yesterday.month = today.month - 1;
        yesterday.year = today.year;
    }
    return yesterday;
}
//输入今天返回昨天
string Yesterday(string today)
{
    string yesterday;
    struct date d1=String2Date(today);
    struct date d2=YesterdayByDate(d1);
    yesterday=Date2String(d2);
    return yesterday;
}