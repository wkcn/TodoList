#ifndef DEFINES_H
#define DEFINES_H

#define _CRT_SECURE_NO_WARNINGS

#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
//#include <QMessageBox>
#include <QApplication>
#include <QPainter>
#include <QTimer>
//#include <QSharedMemory>
//#include <QDesktopWidget>
#include <QMouseEvent>
//#include <QProcess>
//#include <QClipboard>
//#include <QThread>
//#include <QBitmap>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

QDir directoryOf(const QString &subdir);
QString GetFileDir(QString file);

// Windows编码
#if defined(WIN32)
#pragma execution_character_set("utf-8")
#endif

class Date {
 public:
  int year, month, day;
  int hour, minute, second;
  int intTime;  // int类型的time,为了配合<重载，只能让其public

  Date();
  Date(int year, int month, int day, int hour, int minute, int second = 0);

  int GetWeek();
  int GetTime();

  void ToLastMonth();
  void ToNextMonth();

  void Update();
  bool operator<(const Date &b) const;
  int operator()();  //变换为int形式，即距离1970/1/1的秒数
 private:
  int week;  // 0代表星期天
  bool updated;
};

//得到当前日期
Date GetDate(int offsetHour);

#endif  // DEFINES_H
