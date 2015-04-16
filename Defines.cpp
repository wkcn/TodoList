#include "Defines.h"

QDir directoryOf(const QString &subdir){
    QDir dir(QApplication::applicationDirPath());

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug"
            || dir.dirName().toLower() == "release"
            || dir.dirName().toLower() == "bin")
        dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS"){
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
    dir.cd(subdir);
    return dir;
}

QString GetFileDir(QString file){
    return directoryOf("").absoluteFilePath(file);
}

//日期的计算
bool IsLeapYear(int year){
        return (year%400==0||(year%100!=0&&year%4==0));
}
int YearHaveDay(int year){
        if (IsLeapYear(year))return 366;
            return 365;
}
int MonthHaveDay(int month,bool leap){
        if (month==4||month==6||month==9||month==11)return 30;
            if (month==2)return leap?29:28;
                return 31;
}

Date::Date(){
    updated = false;
}

void Date::ToLastMonth(){
    month --;
    if(month <= 0){
        month = 12;
        year --;
    }
    day = min(MonthHaveDay(month,IsLeapYear(year)),day);
    updated = false;
}

void Date::ToNextMonth(){
    month ++;
    if(month > 12){
        month = 1;
        year ++;
    }
    day = min(MonthHaveDay(month,IsLeapYear(year)),day);
    updated = false;
}

Date::Date(int year,int month,int day,int hour,int minute,int second){
    this -> year = year;
    this -> month = month;
    this -> day = day;

    this -> hour = hour;
    this -> minute = minute;
    this -> second = second;
    updated = false;
}

bool Date::operator < (const Date &b) const {
    return GetTime() < b.GetTime();
}

Date GetDate(int offsetHour){
    int t = time(0) + offsetHour * 60 *60;
    Date d;
    d.second = t % 60;
    t /= 60;
    d.minute = t % 60;
    t /= 60;
    d.hour = t % 24;
    t /= 24;
    //从1970年1月1日开始偏移日期
    d.year = 1970;
    d.month = 1;
    d.day = 1;
    int temp;
    while(t>=(temp=YearHaveDay(d.year))){t-=temp;d.year++;}
    while(t>=(temp=MonthHaveDay(d.month,IsLeapYear(d.year)))){t-=temp;d.month++;}
    d.day += t;
    return d;
}

int Date::GetTime() const{
    int count = 0;
    count += second + minute * 60 + hour * 60 * 60 + day * 24 * 60 * 60;
    Date d = *this;
    while(d.month > 1){
        count += MonthHaveDay(d.month,IsLeapYear(d.year)) * 24 * 60 * 60;
        d.month --;
    }
    while(d.year > 1970){
        count += YearHaveDay(d.year) * 24 * 60 * 60;
        d.year --;
    }
    while(d.year < 1970){
        count -= YearHaveDay(d.year) * 24 * 60 * 60;
        d.year ++;
    }
    return count;
}

int Date::operator()(){
    return GetTime();
}

void Date::UpdateDateWeek(){
    int dyear = 1970;
    int dmonth = 1;
    //int dday = 1;
    int dweek = 4;
    while(year > dyear){
        dweek = (dweek + YearHaveDay(dyear))%7;
        dyear ++;
    }
    while(month > dmonth){
        dweek = (dweek + MonthHaveDay(dmonth,IsLeapYear(dyear)))%7;
        dmonth ++;
    }
    dweek = (dweek + day - 1)%7;
    week = dweek;
    updated = true;
}

int Date::GetWeek(){
    if(!updated){
        UpdateDateWeek();
    }
    return week;
}
