#include "TodoList.h"
#include "ui_todolist.h"

TodoList::TodoList(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TodoList), pa("WKCN") {
  ui->setupUi(this);

  state = WINSTATE::LIST;

  aniTimer = new QTimer(this);
  connect(aniTimer, SIGNAL(timeout()), this, SLOT(timerUpDate()));

  //设置白色背景
  QPalette palette;
  palette.setBrush(this->backgroundRole(), Qt::white);
  this->setPalette(palette);

  //设置字体
  // QPainter painter;
  font = this->font;  // painter.font();
  font.setPointSize(20);
  sFont = this->font;  // painter.font();
  sFont.setPointSize(15);
  // painter.setFont(font);
  dateFont = this->font;  // painter.font();
  dateFont.setPointSize(9);

//针对linux字体显示过大问题
#if !defined(Q_OS_WIN)
  ui->comboBox->setFont(dateFont);
  ui->radioButton_1->setFont(dateFont);
  ui->radioButton_2->setFont(dateFont);
  ui->radioButton_3->setFont(dateFont);
  ui->radioButton_4->setFont(dateFont);
  ui->warningBox->setFont(dateFont);
#endif

  //"+"，标题蓝色
  QPalette pal;
  pal.setColor(QPalette::ButtonText, QColor(0, 205, 255));
  ui->addTodo->setPalette(pal);
  ui->confirmButton->setPalette(pal);
  ui->titleBox->setFont(font);
  pal.setColor(QPalette::WindowText, QColor(0, 205, 255));
  ui->titleBox->setPalette(pal);

  //读取图片资源
  boxes[0] = QPixmap(GetFileDir("pic//green.png"));
  boxes[1] = QPixmap(GetFileDir("pic//blue.png"));
  boxes[2] = QPixmap(GetFileDir("pic//orange.png"));
  boxes[3] = QPixmap(GetFileDir("pic//red.png"));

  checkPic = QPixmap(GetFileDir("pic//check.png"));
  line = QPixmap(GetFileDir("pic//line.png"));
  circle = QPixmap(GetFileDir("pic//circle.png"));
  selectBox = QPixmap(GetFileDir("pic//box.png"));

  //设置数据
  string title = "我的一天 - " + pa.GetName();
  this->setWindowTitle(QString::fromStdString(title));

  QDateTime dateTime = QDateTime::currentDateTime();
  QDate qdate = dateTime.date();
  viewDate = Date(qdate.year(), qdate.month(), qdate.day(), 0, 0);

  viewState = VIEWSTATE::ALL;
  ChangeState(WINSTATE::LIST);

  moveAniFrame = 0;
  HideWindows(true);

  StartAniTimer();
}
TodoList::~TodoList() {
  // pa的保存由PA的析构函数完成，因此这里不用额外写
  delete ui;
}

void TodoList::StartAniTimer() {
  if (!aniTimer->isActive()) {
    aniTimer->start(10);  // FPS 100
  }
}

void TodoList::StopAniTimer() {
  if (aniTimer->isActive()) {
    aniTimer->stop();
  }
}

void TodoList::timerUpDate() {
  this->update();
  //以下为动画处理
  bool updated = false;
  if (warnAniTime > 0) {
    warnAniTime--;
    ui->nameBox->move(sin(warnAniTime) * 10, 0);
    updated = true;
  }
  if (mouseTime > 0) {
    mouseTime--;
    updated = true;
  } else {
    mouseCount = 0;
  }
  if (moveAniFrame <= maxMoveAniFrame) {
    moveAniA = (moveAniTarget - moveAniSource) / sin(maxMoveAniAngle);
    moveY = moveAniSource + moveAniA * sin(maxMoveAniAngle * 1.0 /
                                           maxMoveAniFrame * moveAniFrame);
    moveAniFrame++;
    updated = true;
  }
  //滑动动画
  int i = 0;
  while (i < indexSize) {
    if (indexPosX[i] > 375 && deleteIndex == -1) {
      //上面判断为-1是为了避免批量删除时出现覆盖index情况
      deleteIndex = i;
      i++;
      continue;
    }
    if (i != selectIndex || !mousePre) {
      int u = indexPosX[i] * 0.92;
      indexPosX[i] = u;
      if (u > 0)
        updated = true;
    }
    i++;
  }
  if (!updated) {
    StopAniTimer();
  }
}

void TodoList::HideWindows(bool hidden) {
  ui->comboBox->setHidden(hidden);
  ui->contentBox->setHidden(hidden);
  ui->dateTimeEdit->setHidden(hidden);
  ui->horizontalSlider->setHidden(hidden);
  ui->labelBox->setHidden(hidden);
  ui->nameBox->setHidden(hidden);
  ui->placeBox->setHidden(hidden);
  ui->radioButton_1->setHidden(hidden);
  ui->radioButton_2->setHidden(hidden);
  ui->radioButton_3->setHidden(hidden);
  ui->radioButton_4->setHidden(hidden);
  ui->warningBox->setHidden(hidden);
  ui->confirmButton->setHidden(hidden);

  ui->comboBox->setEnabled(!hidden);
  ui->contentBox->setEnabled(!hidden);
  ui->dateTimeEdit->setEnabled(!hidden);
  ui->horizontalSlider->setEnabled(!hidden);
  ui->labelBox->setEnabled(!hidden);
  ui->nameBox->setEnabled(!hidden);
  ui->placeBox->setEnabled(!hidden);
  ui->radioButton_1->setEnabled(!hidden);
  ui->radioButton_2->setEnabled(!hidden);
  ui->radioButton_3->setEnabled(!hidden);
  ui->radioButton_4->setEnabled(!hidden);
  ui->warningBox->setEnabled(!hidden);
  ui->confirmButton->setEnabled(!hidden);

  ui->titleBox->setEnabled(hidden);
  ui->titleBox->setHidden(!hidden);
  // ui->addTodo->setHidden(!hidden);
}

bool TodoList::ValidIndex() {
  return selectIndex < indexSize && selectIndex >= 0 && mousePre;
}

void TodoList::MoveIndex(int id, int x) {
  int kid = indexID[id];
  indexPosX[id] = x;
  if (kid == -1) {
    id++;
    for (; id < indexSize; id++) {
      kid = indexID[id];
      if (kid == -1) break;
      indexPosX[id] = x;
    }
  }
}

void TodoList::mouseReleaseEvent(QMouseEvent *event) {
  int x = event->globalPos().x() - this->pos().x();
  int y = event->globalPos().y() - this->pos().y();
  moveY = oldMoveY + y - pressY;
  selectIndex = (y - moveY - 95) / 80;
  if (ValidIndex()) {
    MoveIndex(selectIndex, oldMoveX + x - pressX);
  }
  moveAniSource = moveY;
  moveAniFrame = 0;
  mousePre = false;

  moveAniTarget = (moveY / 80 + ((moveY % 80) / 80.0 >= 0.5)) *
                  80;  //找到最接近80的倍数的值
  if (moveY > 0) moveAniTarget = 0;

  // lastDateY = (-80 * indexSize) + 0;

  if (moveY < lastDateY) moveAniTarget = lastDateY;

  if (deleteIndex != -1 && deleteIndex < indexSize) {
    // deleteIndex 为选中项目id，要和事件id区分！
    int id = indexID[deleteIndex];  //对应时间的paid
    int validID = -1;
    int count = 0;
    if (id == -1) {
      //批量删除todolist
      for (int i = deleteIndex + 1; i < indexSize && indexID[i] != -1; i++) {
        if (validID == -1) validID = indexID[i];
        count++;
      }
    } else {
      //删除单个Todo
      count = 1;
      validID = id;
    }
    indexSize -= count;
    for (int i = deleteIndex; i < indexSize; i++) {
      indexID[i] = indexID[i + count];
      indexPosX[i] = indexPosX[i + count];
    }
    pa.RemoveTodo(validID, count, viewDate.year, viewDate.month);
    deleteIndex = -1;
  }
  StartAniTimer();
}

void TodoList::mouseMoveEvent(QMouseEvent *event) {
  int x = event->globalPos().x() - this->pos().x();
  int y = event->globalPos().y() - this->pos().y();
  moveY = oldMoveY + y - pressY;
  selectIndex = (y - moveY - 95) / 80;
  if (ValidIndex()) {
    MoveIndex(selectIndex, oldMoveX + x - pressX);
  }
  StartAniTimer();
}

void TodoList::mousePressEvent(QMouseEvent *event) {
  int x = event->globalPos().x() - this->pos().x();
  int y = event->globalPos().y() - this->pos().y();
  pressX = x;
  pressY = y;
  oldMoveY = moveY;
  mousePre = true;

  if (y < 76 && (x >= 68 && x <= 105)) {
    viewDate.ToLastMonth();
    ChangeState(WINSTATE::LIST);
  }
  if (y < 76 && (x >= 318 && x <= 355)) {
    viewDate.ToNextMonth();
    ChangeState(WINSTATE::LIST);
  }
  // qDebug("%d %d",x,y);
  if (y < 76 && (x >= 255 && x <= 320)) {
    viewState = VIEWSTATE((int(viewState) + 1) % 3);
    ChangeState(WINSTATE::LIST);
  }
  mouseList[mouseCount++] = event->button() == Qt::LeftButton;
  mouseTime = 20;

  //以下把y转为绘制画面的相对坐标
  //相对选择项目的坐标
  int sy = y - moveY;
  selectIndex = (sy - 95) / 80;

  if (ValidIndex()) oldMoveX = indexPosX[selectIndex];

  if (ValidIndex() && indexID[selectIndex] != -1) {
    int id = indexID[selectIndex];
    int viewYear = viewDate.year;
    int viewMonth = viewDate.month;
    TodoItem &item = pa.GetItem(id, viewYear, viewMonth);
    int offset = selectIndex * 80;
    if (85 <= x && x <= 120 && 110 + offset <= sy && sy <= 140 + offset) {
      pa.MarkAsDone(id, viewYear, viewMonth, !item.HaveDone());
    }
    if (mouseCount >= 2 && mouseList[0] && mouseList[1]) {
      //跳转到添加新Todo界面
      ui->nameBox->setText(QString::fromStdString(item.GetName()));
      switch (item.GetLevel()) {
        case 0:
          ui->radioButton_4->setChecked(true);
          break;
        case 1:
          ui->radioButton_2->setChecked(true);
          break;
        case 2:
          ui->radioButton_3->setChecked(true);
          break;
        case 3:
          ui->radioButton_1->setChecked(true);
          break;
      }
      ui->horizontalSlider->setValue(item.GetWarnTime() / 5);
      SetWarnText(ui->horizontalSlider->value());
      Date date = item.GetTime();
      QDate qdate(date.year, date.month, date.day);
      QTime qtime(date.hour, date.minute);
      ui->dateTimeEdit->setDateTime(QDateTime(qdate, qtime));
      ui->placeBox->setText(QString::fromStdString(item.GetPlace()));
      ui->labelBox->setText(QString::fromStdString(item.GetLabel()));
      ui->contentBox->setText(QString::fromStdString(item.GetContent()));
      ui->comboBox->setCurrentIndex(item.GetKind());

      selectID = id;
      ChangeState(WINSTATE::DETAIL);

      mouseCount = 0;
    }
    if (mouseCount >= 2 && !mouseList[0] && !mouseList[1]) {
      pa.RemoveTodo(id, viewYear, viewMonth);
      mouseCount = 0;
    }
  }
  StartAniTimer();
}

void TodoList::wheelEvent(QWheelEvent *event) {
  int dy = event->angleDelta().y();
  moveY += dy / 5;
  StartAniTimer();
}

void TodoList::paintEvent(QPaintEvent *) {
  QPainter painter;
  painter.begin(this);

  if (state == WINSTATE::LIST) {
    //标题名称的临时变量
    char temp[128];
    string text;
    text += "<  ";
    int viewYear = viewDate.year;
    int viewMonth = viewDate.month;

    string viewType = "全部";
    string nullText = "出去玩吧 ≥▽≤";
    if (viewState == VIEWSTATE::UNDONE) {
      viewType = "未完成";
      nullText = "出去玩吧 ^o^";
    } else {
      if (viewState == VIEWSTATE::WARN) {
        viewType = "提醒";
        nullText = "没有提醒 ~";
      }
    }

    sprintf(temp, "%d/%.2d - %s", viewYear, viewMonth, viewType.c_str());
    text += temp;
    text += "  >";

    ui->titleBox->setText(QString::fromStdString(text));

    int posX = 16, posY = 60;
    posY += moveY;
    int paintX = 0, paintY = 0;

    //用于显示具体日期，这里将同一天的事件归为一类
    int lastDay = 0;

    bool haveTodo = false;
    bool first = true;
    indexSize = 0;
    int todoSize = pa.GetListSize(viewYear, viewMonth);

    QDateTime qDateTime = QDateTime::currentDateTime();
    QDate qDate = qDateTime.date();
    QTime qTime = qDateTime.time();
    Date nowDate(qDate.year(), qDate.month(), qDate.day(), qTime.hour(),
                 qTime.minute(), qTime.second());

    for (int i = 0; i < todoSize; i++) {
      paintX = indexPosX[indexSize];
      TodoItem &item = pa.GetItem(i, viewYear, viewMonth);
      Date date = item.GetTime();

      if (viewState == VIEWSTATE::UNDONE) {
        if (item.HaveDone()) continue;
      } else if (viewState == VIEWSTATE::WARN) {
        int warnTime = item.GetWarnTime();
        if (warnTime == 0 || date.GetTime() - nowDate.GetTime() > warnTime) {
          continue;
        }
      }
      // if(date.month != viewMonth || date.year != viewYear)continue;

      haveTodo = true;

      if (date.day != lastDay) {
        lastDay = date.day;
        //优化渲染效率
        if (posY + 59 + paintY + 50 > 0) {
          //绘制时间文字
          painter.setPen(QPen(Qt::gray));
          painter.setFont(sFont);
          char dateText[128];
          static string weekStr[7] = {"日", "一", "二", "三", "四", "五", "六"};
          sprintf(dateText, "%d年%.2d月%.2d日 星期%s   +", date.year,
                  date.month, date.day, weekStr[date.GetWeek()].c_str());
          painter.drawText(posX + 80 + paintX, posY - 21 + paintY, 343, 70,
                           Qt::AlignBottom, QString::fromStdString(dateText));
          painter.setPen(QPen(Qt::black));

          if (!first)
            painter.drawPixmap(posX + 26, posY - 40 + paintY, 8, 60,
                               line);  //圆圈上方线条

          painter.drawPixmap(posX + 9 + paintX, posY + 20 + paintY, 40, 40,
                             circle);
          char dayText[4];
          sprintf(dayText, "%.2d", date.day);
          painter.drawText(posX + 16 + paintX, posY + 14 + paintY, 40, 40,
                           Qt::AlignBottom, QString::fromStdString(dayText));

          painter.drawPixmap(posX + 26, posY + 59 + paintY, 8, 50,
                             line);  //圆圈下方线条
        }

        first = false;

        if (indexSize < 128) indexID[indexSize++] = -1;

        paintY += 80;
      }

      paintX = indexPosX[indexSize];

      if (posY - 26 + paintY + 70 > 0) {
        //绘制圆点上下直线
        painter.drawPixmap(posX + 26, posY + 20 + paintY, 8, 10,
                           line);  //圆点上方
        painter.drawPixmap(posX + 26, posY + 36 + paintY, 8, 65,
                           line);  //圆点下方
        // Todo框
        painter.drawPixmap(posX + 23 + paintX, posY + paintY, 343, 70,
                           boxes[item.GetLevel()]);

        //勾Todo　Havedone
        if (item.HaveDone())
          painter.drawPixmap(posX + 68 + paintX, posY + paintY + 22, 25, 25,
                             checkPic);

        //绘制Todo名称
        painter.setPen(QPen(Qt::black));
        painter.setFont(font);
        painter.drawText(posX + 113 + paintX, posY - 21 + paintY, 343, 70,
                         Qt::AlignBottom,
                         QString::fromStdString(item.GetName()));

        //左侧Todo时间
        painter.setPen(QPen(Qt::gray));
        painter.setFont(dateFont);
        char dateText[16];
        sprintf(dateText, "%.2d:%.2d", date.hour, date.minute);
        painter.drawText(posX - 12 + paintX, posY - 26 + paintY, 343, 70,
                         Qt::AlignBottom, QString::fromStdString(dateText));
      }

      if (indexSize < 128) indexID[indexSize++] = i;  //记录对应todo的id号

      paintY += 80;
      //强行停止渲染
      if (posY + 20 + paintY > 600) break;
    }

    lastDateY = -(paintY);

    if (!haveTodo) {
      painter.setPen(QPen(Qt::gray));
      painter.setFont(font);
      painter.drawText(posX + 100, posY - 21, 400, 70, Qt::AlignBottom,
                       QString::fromStdString(nullText));
    }
  }
  painter.end();
}

void TodoList::on_addTodo_clicked() {
  switch (state) {
    case WINSTATE::LIST:
      //跳转到添加新Todo界面
      ui->nameBox->clear();
      ui->radioButton_4->setChecked(true);
      ui->horizontalSlider->setValue(0);
      ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
      ui->placeBox->clear();
      ui->labelBox->clear();
      ui->contentBox->clear();
      ui->comboBox->setCurrentIndex(0);

      ChangeState(WINSTATE::EDIT);
      break;
    default:
      //从添加界面切换到显示界面
      ChangeState(WINSTATE::LIST);
  }
}

void TodoList::ChangeState(WINSTATE state) {
  this->state = state;
  // viewState = VIEWSTATE::ALL;
  indexSize = 0;
  selectIndex = 0;
  indexSize = 0;
  indexPosX[0] = 0;
  deleteIndex = -1;

  warnAniTime = 0;
  waitTime = 0;
  moveY = oldMoveY = 0;
  oldMoveX = 0;
  lastDateY = 0;

  mouseCount = 0;
  mouseTime = 0;
  pressX = pressY = 0;
  mousePre = false;

  switch (state) {
    case WINSTATE::EDIT:
      ui->addTodo->setText("x");
      HideWindows(false);
      ui->confirmButton->setText("添加");
      break;
    case WINSTATE::DETAIL:
      ui->addTodo->setText("x");
      HideWindows(false);
      ui->confirmButton->setText("修改");
      break;
    case WINSTATE::LIST:
      ui->addTodo->setText("+");
      HideWindows(true);
      indexPosX[7] = -1600;
      for (int j = 6; j >= 0; j--)
        indexPosX[j] = indexPosX[j + 1] * 0.68;  //第一次的进入动画
      for (int i = 8; i < 128; i++) indexPosX[i] = 0;
      moveY = 0;
      moveAniFrame = 0;
      break;
  }
  StartAniTimer();
}

void TodoList::SetWarnText(int position) {
  if (position == 0) {
    ui->warningBox->setText("不提醒");
    return;
  }
  position *= 5;
  stringstream ss;
  ss << "提前";
  int day, hour, minute;
  day = position / 60 / 24;
  position -= 60 * 24 * day;
  hour = position / 60;
  position -= 60 * hour;
  minute = position;
  if (day > 0) ss << day << "天";
  if (hour > 0) ss << hour << "小时";
  if (minute > 0) ss << minute << "分提示";
  QString str = QString::fromStdString(ss.str());
  ui->warningBox->setText(str);
}

void TodoList::on_horizontalSlider_sliderMoved(int position) {
  SetWarnText(position);
}

void TodoList::on_confirmButton_clicked() {
  QString name = ui->nameBox->text();
  if (name.size() == 0) {
    warnAniTime = 30;
    return;
  }

  TodoItem item;

  item.SetName(name.toStdString());
  item.SetPlace(ui->placeBox->text().toStdString());
  item.SetContent(ui->contentBox->toPlainText().toStdString());
  item.SetLabel(ui->labelBox->text().toStdString());

  item.SetKind(ui->comboBox->currentIndex());

  QDateTime dateTime = ui->dateTimeEdit->dateTime();
  QDate date = dateTime.date();
  QTime ti = dateTime.time();
  item.SetTime(
      Date(date.year(), date.month(), date.day(), ti.hour(), ti.minute()));
  item.SetWarnTime(ui->horizontalSlider->value() * 5);  //以分为单位

  int level = 0;
  if (ui->radioButton_1->isChecked()) level = 3;
  if (ui->radioButton_2->isChecked()) level = 1;
  if (ui->radioButton_3->isChecked()) level = 2;
  if (ui->radioButton_4->isChecked()) level = 0;
  item.SetLevel(level);

  if (state == WINSTATE::EDIT) {
    pa.AddTodo(item);
  } else if (state == WINSTATE::DETAIL) {
    pa.ChangeTodo(item, selectID, viewDate.year, viewDate.month);
  }

  ChangeState(WINSTATE::LIST);
}
