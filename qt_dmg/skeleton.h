//
// Created by yuliyang on 2023/2/11.
//

#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QFile>
#include <QDir>
#include <QClipboard>
#include <QMouseEvent>
#include <QScreen>
#include <QDir>

#include <iostream>


#include "addbuttondialog.h"
#include "addtabdialog.h"
#include "flowlayout.h"

class commandButton : public QPushButton {

Q_OBJECT

public:
  commandButton(QWidget *parent = nullptr);
  ~commandButton();

  void SetName(const QString& n) {
    name = n;
  }
  void SetCmd(const QString& c) {
    command = c;
  }
  const QString& GetName() {
    return name;
  }

  const QString& GetCmd() {
    return command;
  }
  void setFlowLayout(FlowLayout *layout) {
    flowLayout = layout;
  }
private:
  FlowLayout *flowLayout;
  QString name;
  QString command;
private slots:
  void showmenu(QPoint pos);
  void editButton();
  void deleteButton();
  void onclicked();
};

class commandTab : public QTabWidget {

Q_OBJECT

public:
  commandTab(QWidget *parent = nullptr);
  ~commandTab();
  QString name;
  void SetName(const QString& n) {
    name = n;
  }
private slots:
  void showmenu(QPoint pos);
  void rename();
  void remove();
};

class MyWidget : public QWidget {

Q_OBJECT

public:
  MyWidget(const QJsonArray& buttons, QWidget *parent = nullptr);
private:
  FlowLayout *flowLayout;
private slots:
  void showmenu(QPoint pos);
  void addbutton();
};

class Skeleton : public QMainWindow {

Q_OBJECT

public:
  Skeleton(QWidget *parent = nullptr);
  void addTab();
  void save();
  void pin();

private slots:

private:
  commandTab* tabs;
  QJsonDocument config_doc;
  bool pined;
  QString dir;
  QString config_path;
};

