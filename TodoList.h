#ifndef TODOLIST_H
#define TODOLIST_H

#include "Defines.h"
#include "PA.h"

namespace Ui {
class TodoList;
}

class TodoList : public QMainWindow {
  Q_OBJECT

 public:
  explicit TodoList(QWidget *parent = 0);
  void paintEvent(QPaintEvent *);
  ~TodoList();
 private slots:
  void on_addTodo_clicked();
  void timerUpDate();
  void on_horizontalSlider_sliderMoved(int position);
  void on_confirmButton_clicked();

 private:
  //界面类型
  enum WINSTATE { LIST, EDIT, DETAIL };
  //显示列表的类型
  enum VIEWSTATE { ALL, UNDONE, WARN };

  bool ValidIndex();                 //当前所选项目可用
  void HideWindows(bool hidden);     //隐藏编辑界面
  void ChangeState(WINSTATE state);  //更改界面
  void MoveIndex(int id, int x);     //滑动选项（动画）
  void StartAniTimer();
  void StopAniTimer();
  void SetWarnText(int position);
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void wheelEvent(QWheelEvent *);

 private:
  Ui::TodoList *ui;
  QTimer *aniTimer;
  QPixmap boxes[4];
  QPixmap checkPic, line, circle, selectBox;
  WINSTATE state;
  VIEWSTATE viewState;
  PA pa;          // PA类
  Date viewDate;  //当前显示项目的时间段

  //各个项目的参数
  int indexID[128];
  int indexPosX[128];
  int indexSize;
  int selectIndex;
  int deleteIndex;

  //鼠标事件
  bool mouseList[64];
  int mouseCount;
  int mouseTime;
  int selectID;
  int pressX, pressY;
  bool mousePre;

  //动画参数
  int waitTime;
  int warnAniTime;
  int moveY, oldMoveY, oldMoveX;
  int lastDateY;
  const int maxMoveAniFrame = 60;  // C++11 allowed
  const double maxMoveAniAngle = acos(-1) / 180.0 * 120;
  int moveAniFrame;
  int moveAniTarget, moveAniSource;
  double moveAniA;  //正弦函数幅度

  //字体
  QFont font, sFont, dateFont;
};

#endif  // TODOLIST_H
