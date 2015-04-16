#ifndef PA_H
#define PA_H
#include "Defines.h"
#include "TodoItem.h"

class Event : private TodoItem{
public:
	string GetKind();
};

class Task : private TodoItem{
public:
	string GetKind();
};

class PA{
public:
	PA(string name);
    ~PA();
    void AddTodo(TodoItem item);
    void RemoveTodo(int id,int viewYear,int viewMonth);
	void RemoveTodo(int id,int count, int viewYear, int viewMonth);
	void RemoveTodo(set<int> ids, int viewYear, int viewMonth);
    void ChangeTodo(TodoItem item,int id);
	void ListTodos();
    int GetListSize(int viewYear,int viewMonth);
    TodoItem &GetItem(int id,int viewYear,int viewMonth);
    void MarkAsDone(int id,int viewYear,int viewMonth,bool done);

	string GetName();
private:
	string name;
    set<int> changedList; //记录修改项目的id
    map<int,vector<TodoItem>* > itemsList; //使用一个日期到TodoItem列表的映射
    void TextOut(ostream &os,const string &s);
    string TextIn(istream &is);
    int GetTextRows(const string &s);
private:
    int GetDateID(int viewYear,int viewMonth);
    void LoadData(int viewYear,int viewMonth);
    void SaveData();
};
#endif
