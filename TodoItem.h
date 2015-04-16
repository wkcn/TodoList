#ifndef TODOITEM_H
#define TODOITEM_H
#include "Defines.h"

class TodoItem{
protected:
    string name;
    string content;
    string place;
    string label; //标签
    int kind;
    int level;
    Date todoTime;
    bool done;
    int warnTime; //提醒时间，单位为（分）
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
