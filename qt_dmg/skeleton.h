//
// Created by yuliyang on 2023/2/11.
//

#pragma once

#include <QMainWindow>
#include <QApplication>

class MyWidget : public QWidget {

Q_OBJECT

public:
  MyWidget(QWidget *parent = nullptr);

private slots:
  void showmenu(QPoint pos);
  void addbutton();
};

class Skeleton : public QMainWindow {

Q_OBJECT

public:
  Skeleton(QWidget *parent = nullptr);
  void addTab();

private slots:
  void on_tabWidget_currentChanged(int index);

private:
  QTabWidget* tabs;
};

