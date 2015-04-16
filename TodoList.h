#ifndef TODOLIST_H
#define TODOLIST_H

#include "Defines.h"
#include "PA.h"

namespace Ui {
class TodoList;
}

class TodoList : public QMainWindow
{
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
    enum WINSTATE{
        LIST,EDIT,DETAIL
    };
    enum VIEWSTATE{
        ALL,UNDONE,WARN
    };

    bool ValidIndex();
    void HideWindows(bool hidden);
    void ChangeState(WINSTATE state);
    void MoveIndex(int id,int x);
    void SetWarnText(int position);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    Ui::TodoList *ui;
    QPixmap boxes[4];
    QPixmap checkPic,line,circle,selectBox;
    WINSTATE state;
    VIEWSTATE viewState;
    int warnAniTime;
    int moveY,oldMoveY;
    int oldMoveX;
    PA pa;
    Date viewDate;
    int indexID[128];
    int indexPosX[128];
    int indexSize;
    int selectIndex;
    bool mouseList[64];
    int mouseCount;
    int mouseTime;
    int selectID;
    int pressX,pressY;
    bool mousePre;
    int waitTime;
	int lastDateY;
	int deleteIndex;
    QFont font,sFont,dateFont;

    const int maxMoveAniFrame = 60;
    const double maxMoveAniAngle = acos(-1) / 180.0 * 120;
    int moveAniFrame;
    int moveAniTarget,moveAniSource;
    double moveAniA; //正弦函数幅度
    double dmoveY; //浮点数Y坐标
};

#endif // TODOLIST_H
