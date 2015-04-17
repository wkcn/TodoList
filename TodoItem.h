#ifndef TODOITEM_H
#define TODOITEM_H
#include "Defines.h"

class TodoItem{
protected:
    string name;    //Todo名称
    string content;
    string place;
    string label;   //标签
    int kind;       //类型：事件(0),任务(1)
    int level;      //重要与紧急程度
    Date todoTime;  //Todo时间
    bool done;
    int warnTime;   //提醒时间，单位为（分）
public:
    TodoItem();
    void SetName(string name);
    void SetContent(string content);
    void SetPlace(string place);
    void SetLabel(string label);
    void SetKind(int kind);
    void SetTime(Date date);
    void SetWarnTime(int warnTime);
    void SetLevel(int level);
    void MarkAsDone(bool done);

    string GetName();
    string GetContent();
    string GetPlace();
    string GetLabel();
    int GetKind();
    int GetLevel();

    Date GetTime();
    int GetWarnTime();
    bool HaveDone();

    bool operator < (const TodoItem &b) const;
    //string GetKind();
};

#endif // TODOITEM_H
