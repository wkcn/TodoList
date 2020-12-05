#ifndef PA_H
#define PA_H
#include "Defines.h"
#include "TodoItem.h"

//以下Event和Task两个类继承于TodoItem,但是没有使用
class Event : private TodoItem {
 public:
  string GetKind();
};

class Task : private TodoItem {
 public:
  string GetKind();
};

class PA {
 public:
  PA(string name);
  ~PA();
  void AddTodo(TodoItem item);
  void RemoveTodo(int id, int viewYear, int viewMonth);
  void RemoveTodo(int id, int count, int viewYear, int viewMonth);
  void RemoveTodo(set<int> ids, int viewYear, int viewMonth);
  void ChangeTodo(TodoItem item, int id, int viewYear, int viewMonth);

  void ListTodos();
  int GetListSize(int viewYear, int viewMonth);
  TodoItem &GetItem(int id, int viewYear, int viewMonth);

  void MarkAsDone(int id, int viewYear, int viewMonth, bool done);

  string GetName();

 private:
  string name;                             //用户名称
  set<int> changedList;                    //记录修改项目的id
  map<int, vector<TodoItem> *> itemsList;  //使用一个日期int到TodoItem列表的映射
 private:
  int GetDateID(int viewYear, int viewMonth);  //将日期转换为int

  void TextOut(ostream &os, const string &s);  //写入多行string
  string TextIn(istream &is);                  //读入多行string
  int GetTextRows(const string &s);            //判断string占用行数

  void LoadData(int viewYear, int viewMonth);
  void SaveData();
};
#endif
