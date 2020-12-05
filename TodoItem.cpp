#include "TodoItem.h"

TodoItem::TodoItem() { done = false; }

void TodoItem::SetName(string name) { this->name = name; }
void TodoItem::SetContent(string content) { this->content = content; }
void TodoItem::SetPlace(string place) { this->place = place; }
void TodoItem::SetLabel(string label) { this->label = label; }
void TodoItem::SetKind(int kind) { this->kind = kind; }

void TodoItem::SetTime(Date date) { todoTime = date; }
void TodoItem::SetWarnTime(int warnTime) { this->warnTime = warnTime; }
void TodoItem::SetLevel(int level) { this->level = level; }
void TodoItem::MarkAsDone(bool done) { this->done = done; }

int TodoItem::GetLevel() { return level; }

int TodoItem::GetKind() { return kind; }

string TodoItem::GetName() { return name; }

string TodoItem::GetContent() { return content; }

string TodoItem::GetPlace() { return place; }

string TodoItem::GetLabel() { return label; }

Date TodoItem::GetTime() { return todoTime; }

int TodoItem::GetWarnTime() { return warnTime; }

bool TodoItem::HaveDone() { return done; }

bool TodoItem::operator<(const TodoItem &b) const {
  return todoTime < b.todoTime;
}
