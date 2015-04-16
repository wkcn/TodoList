#ifndef DEFINES_H
#define DEFINES_H

#define _CRT_SECURE_NO_WARNINGS

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QPainter>
#include <QApplication>
#include <QSharedMemory>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QProcess>
#include <QClipboard>
#include <QThread>
#include <QBitmap>

#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sstream>
using namespace std;

QDir directoryOf(const QString &subdir);
QString GetFileDir(QString file);

#pragma execution_character_set("utf-8")

class Date{
public:
    int year,month,day;
    int hour,minute,second;
    Date();
    Date(int year,int month,int day,int hour,int minute,int second = 0);
    void ToLastMonth();
    void ToNextMonth();
    int GetWeek();
    bool operator < (const Date &b) const;
    int GetTime() const;
    int operator ()(); //变换为int形式，即距离1970/1/1的秒数
    //operator string(); //隐式转换
private:
    bool updated;
    int week;
    void UpdateDateWeek();
};

Date GetDate(int offsetHour);

#endif // DEFINES_H
