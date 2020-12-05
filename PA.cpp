#include "PA.h"

PA::PA(string name) { this->name = name; }

int PA::GetDateID(int viewYear, int viewMonth) {
  return viewYear * 100 + viewMonth;
}

void PA::AddTodo(TodoItem item) {
  Date date = item.GetTime();
  int dateID = GetDateID(date.year, date.month);
  changedList.insert(dateID);
  if (!itemsList.count(dateID)) itemsList[dateID] = new vector<TodoItem>;
  vector<TodoItem> *items = itemsList[dateID];
  items->push_back(item);
  sort(items->rbegin(), items->rend());  //进行逆序排序
}

void PA::RemoveTodo(int id, int viewYear, int viewMonth) {
  RemoveTodo(id, 1, viewYear, viewMonth);
}

void PA::RemoveTodo(int id, int count, int viewYear, int viewMonth) {
  int dateID = GetDateID(viewYear, viewMonth);
  changedList.insert(dateID);
  vector<TodoItem> *items = itemsList[dateID];
  vector<TodoItem>::iterator iter = items->begin();
  (*items).erase(iter + id, iter + id + count);
}

void PA::RemoveTodo(set<int> ids, int viewYear, int viewMonth) {
  set<int>::iterator iter = ids.begin();
  viewYear;
  viewMonth;
  //该功能暂时没有实现
}

void PA::ChangeTodo(TodoItem item, int id, int viewYear, int viewMonth) {
  Date date = item.GetTime();
  int dateID = GetDateID(date.year, date.month);

  changedList.insert(dateID);
  RemoveTodo(id, viewYear, viewMonth);
  AddTodo(item);
}

void PA::ListTodos() {
  //因为有图形化界面，所以不使用该函数
  /*
      printf("----------Personal Assistant----------\n");
      printf("ID\tName\tTime\tPlace\tLabel\t");
      for(int i = 0;i < items.size();i++){
              TodoItem &todo = items[i];
              if(!todo.HaveDone()){
                      printf("ID");
              }
  }*/
}

void PA::MarkAsDone(int id, int viewYear, int viewMonth, bool done) {
  int dateID = GetDateID(viewYear, viewMonth);
  changedList.insert(dateID);
  vector<TodoItem> *items = itemsList[dateID];
  (*items)[id].MarkAsDone(done);
}

int PA::GetTextRows(const string &s) {
  int r = 1;
  for (auto c : s) {
    if (c == '\n') r++;
  }
  return r;
}

void PA::TextOut(ostream &os, const string &s) {
  os << GetTextRows(s) << endl;
  os << s << endl;
}

string PA::TextIn(istream &is) {
  int r;
  is >> r;
  string buf;
  char c;
  // windows中以\r\n换行,linux中以\n换行~
  c = is.get();
  if (c == '\r') c = is.get();  // jump end sign
  while (!is.eof()) {
    c = is.get();
    if (c == '\r') c = is.get();  // jump end sign
    if (c == '\n') {
      r--;
      if (r <= 0) {
        break;
      }
    }
    buf += c;
  }

  if (buf.size() > 0 && buf[buf.size() - 1] == '\n') buf.pop_back();
  return buf;
}

void PA::LoadData(int viewYear, int viewMonth) {
  int dateID = GetDateID(viewYear, viewMonth);
  //当该日期未读取时，新建或读取相应数据
  if (!itemsList.count(dateID)) {
    itemsList[dateID] = new vector<TodoItem>;

    char fileName[64];
    sprintf(fileName, "data//%d.txt", dateID);
    ifstream fin(fileName);
    if (fin) {
      int n;
      fin >> n;
      while (n--) {
        TodoItem item;
        item.SetName(TextIn(fin));
        item.SetLabel(TextIn(fin));
        int level;
        fin >> level;
        item.SetLevel(level);
        Date date;
        fin >> date.year >> date.month >> date.day >> date.hour >> date.minute;
        date.Update();  //更新int时间！
        item.SetTime(date);
        item.SetPlace(TextIn(fin));
        item.SetContent(TextIn(fin));
        int temp;
        fin >> temp;
        item.MarkAsDone(bool(temp));
        fin >> temp;
        item.SetKind(temp);
        fin >> temp;
        item.SetWarnTime(temp);
        AddTodo(item);
      }
      fin.close();
    }
  }
}

void PA::SaveData() {
  QString folder = GetFileDir("data");
  QDir dir(folder);
  if (!dir.exists()) {
    dir.mkdir(folder);
  }
  //之所以这样直接保存，是为了方便查看
  for (int id : changedList) {
    char fileName[64];
    sprintf(fileName, "data//%d.txt", id);
    ofstream fout(fileName);
    vector<TodoItem> *adr = itemsList[id];
    fout << (*adr).size() << endl;
    for (auto con : (*adr)) {
      // auto &con = *adr;
      TextOut(fout, con.GetName());
      TextOut(fout, con.GetLabel());
      fout << con.GetLevel() << endl;
      Date date = con.GetTime();
      fout << date.year << " " << date.month << " " << date.day << " "
           << date.hour << " " << date.minute << endl;
      TextOut(fout, con.GetPlace());
      TextOut(fout, con.GetContent());
      fout << con.HaveDone() << " " << con.GetKind() << " " << con.GetWarnTime()
           << endl;
    }
    fout.close();
  }
}

string PA::GetName() { return name; }

int PA::GetListSize(int viewYear, int viewMonth) {
  LoadData(viewYear, viewMonth);
  vector<TodoItem> *items = itemsList[GetDateID(viewYear, viewMonth)];
  return int(items->size());
}

TodoItem &PA::GetItem(int id, int viewYear, int viewMonth) {
  LoadData(viewYear, viewMonth);
  vector<TodoItem> *items = itemsList[GetDateID(viewYear, viewMonth)];
  return (*items)[id];
}

PA::~PA() { SaveData(); }
