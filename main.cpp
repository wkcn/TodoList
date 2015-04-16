#include "TodoList.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TodoList w;
    w.show();

    return a.exec();
}
