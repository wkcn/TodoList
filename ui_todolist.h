/********************************************************************************
** Form generated from reading UI file 'todolist.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TODOLIST_H
#define UI_TODOLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TodoList
{
public:
    QWidget *centralWidget;
    QLabel *titleBox;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QDateTimeEdit *dateTimeEdit;
    QTextEdit *contentBox;
    QComboBox *comboBox;
    QLineEdit *nameBox;
    QLineEdit *placeBox;
    QLineEdit *labelBox;
    QSlider *horizontalSlider;
    QLabel *warningBox;
    QPushButton *addTodo;
    QPushButton *confirmButton;

    void setupUi(QMainWindow *TodoList)
    {
        if (TodoList->objectName().isEmpty())
            TodoList->setObjectName(QStringLiteral("TodoList"));
        TodoList->resize(420, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(42);
        sizePolicy.setVerticalStretch(60);
        sizePolicy.setHeightForWidth(TodoList->sizePolicy().hasHeightForWidth());
        TodoList->setSizePolicy(sizePolicy);
        TodoList->setMinimumSize(QSize(420, 600));
        TodoList->setMaximumSize(QSize(420, 600));
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font.setBold(true);
        font.setWeight(75);
        TodoList->setFont(font);
        TodoList->setMouseTracking(false);
        QIcon icon;
        icon.addFile(QStringLiteral("mypa.ico"), QSize(), QIcon::Normal, QIcon::Off);
        TodoList->setWindowIcon(icon);
        TodoList->setAnimated(false);
        centralWidget = new QWidget(TodoList);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        titleBox = new QLabel(centralWidget);
        titleBox->setObjectName(QStringLiteral("titleBox"));
        titleBox->setGeometry(QRect(0, 0, 420, 50));
        titleBox->setFont(font);
        titleBox->setScaledContents(false);
        titleBox->setAlignment(Qt::AlignCenter);
        radioButton_1 = new QRadioButton(centralWidget);
        radioButton_1->setObjectName(QStringLiteral("radioButton_1"));
        radioButton_1->setGeometry(QRect(50, 80, 101, 16));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setWeight(75);
        radioButton_1->setFont(font1);
        radioButton_2 = new QRadioButton(centralWidget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(50, 100, 101, 16));
        radioButton_3 = new QRadioButton(centralWidget);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(220, 80, 101, 16));
        radioButton_4 = new QRadioButton(centralWidget);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(220, 100, 101, 16));
        radioButton_4->setChecked(true);
        dateTimeEdit = new QDateTimeEdit(centralWidget);
        dateTimeEdit->setObjectName(QStringLiteral("dateTimeEdit"));
        dateTimeEdit->setGeometry(QRect(0, 150, 421, 31));
        QFont font2;
        font2.setPointSize(10);
        dateTimeEdit->setFont(font2);
        dateTimeEdit->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(0, 0, 0)));
        dateTimeEdit->setCalendarPopup(true);
        dateTimeEdit->setTimeSpec(Qt::LocalTime);
        contentBox = new QTextEdit(centralWidget);
        contentBox->setObjectName(QStringLiteral("contentBox"));
        contentBox->setGeometry(QRect(0, 270, 421, 291));
        QFont font3;
        font3.setPointSize(12);
        contentBox->setFont(font3);
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(358, 80, 51, 22));
        nameBox = new QLineEdit(centralWidget);
        nameBox->setObjectName(QStringLiteral("nameBox"));
        nameBox->setGeometry(QRect(0, 0, 421, 61));
        QFont font4;
        font4.setPointSize(28);
        nameBox->setFont(font4);
        placeBox = new QLineEdit(centralWidget);
        placeBox->setObjectName(QStringLiteral("placeBox"));
        placeBox->setGeometry(QRect(0, 190, 421, 31));
        placeBox->setFont(font2);
        labelBox = new QLineEdit(centralWidget);
        labelBox->setObjectName(QStringLiteral("labelBox"));
        labelBox->setGeometry(QRect(0, 230, 421, 31));
        labelBox->setFont(font2);
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 127, 401, 22));
        horizontalSlider->setMaximum(864);
        horizontalSlider->setPageStep(1);
        horizontalSlider->setValue(0);
        horizontalSlider->setOrientation(Qt::Horizontal);
        warningBox = new QLabel(centralWidget);
        warningBox->setObjectName(QStringLiteral("warningBox"));
        warningBox->setGeometry(QRect(10, 117, 401, 20));
        warningBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        addTodo = new QPushButton(centralWidget);
        addTodo->setObjectName(QStringLiteral("addTodo"));
        addTodo->setEnabled(true);
        addTodo->setGeometry(QRect(380, 6, 40, 40));
        QFont font5;
        font5.setPointSize(26);
        addTodo->setFont(font5);
        addTodo->setFlat(true);
        confirmButton = new QPushButton(centralWidget);
        confirmButton->setObjectName(QStringLiteral("confirmButton"));
        confirmButton->setGeometry(QRect(0, 560, 421, 40));
        QFont font6;
        font6.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font6.setPointSize(20);
        confirmButton->setFont(font6);
        confirmButton->setAutoDefault(false);
        confirmButton->setDefault(false);
        confirmButton->setFlat(true);
        TodoList->setCentralWidget(centralWidget);
        warningBox->raise();
        titleBox->raise();
        radioButton_1->raise();
        radioButton_2->raise();
        radioButton_3->raise();
        radioButton_4->raise();
        dateTimeEdit->raise();
        contentBox->raise();
        comboBox->raise();
        nameBox->raise();
        placeBox->raise();
        labelBox->raise();
        horizontalSlider->raise();
        confirmButton->raise();
        addTodo->raise();

        retranslateUi(TodoList);

        QMetaObject::connectSlotsByName(TodoList);
    } // setupUi

    void retranslateUi(QMainWindow *TodoList)
    {
        TodoList->setWindowTitle(QApplication::translate("TodoList", "\346\210\221\347\232\204\344\270\200\345\244\251", "TodoList"));
        titleBox->setText(QApplication::translate("TodoList", "<html><head/><body><p><span style=\" font-size:20pt; color:#00cdff;\">2015/4 - \345\205\250\351\203\250</span></p></body></html>", 0));
        radioButton_1->setText(QApplication::translate("TodoList", "\345\276\210\351\207\215\350\246\201-\345\276\210\347\264\247\346\200\245", 0));
        radioButton_2->setText(QApplication::translate("TodoList", "\344\270\215\351\207\215\350\246\201-\345\276\210\347\264\247\346\200\245", 0));
        radioButton_3->setText(QApplication::translate("TodoList", "\345\276\210\351\207\215\350\246\201-\344\270\215\347\264\247\346\200\245", 0));
        radioButton_4->setText(QApplication::translate("TodoList", "\344\270\215\351\207\215\350\246\201-\344\270\215\347\264\247\346\200\245", 0));
        contentBox->setPlaceholderText(QApplication::translate("TodoList", "\345\206\205\345\256\271\357\274\232", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("TodoList", "\344\272\213\344\273\266", 0)
         << QApplication::translate("TodoList", "\344\273\273\345\212\241", 0)
        );
        nameBox->setPlaceholderText(QApplication::translate("TodoList", "\350\257\267\350\276\223\345\205\245\345\276\205\345\212\236\344\272\213\351\241\271", 0));
        placeBox->setPlaceholderText(QApplication::translate("TodoList", "\345\234\260\347\202\271\357\274\232", 0));
        labelBox->setPlaceholderText(QApplication::translate("TodoList", "\346\240\207\347\255\276\357\274\232", 0));
        warningBox->setText(QApplication::translate("TodoList", "\344\270\215\346\217\220\351\206\222", 0));
        addTodo->setText(QApplication::translate("TodoList", "+", 0));
        confirmButton->setText(QApplication::translate("TodoList", "\346\267\273\345\212\240", 0));
    } // retranslateUi

};

namespace Ui {
    class TodoList: public Ui_TodoList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TODOLIST_H
