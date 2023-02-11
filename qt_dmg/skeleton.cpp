//
// Created by yuliyang on 2023/2/11.
//

#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QTableWidget>
#include <QHBoxLayout>
#include <iostream>
#include "skeleton.h"
#include <QPushButton>

void MyWidget::addbutton() {
  std::cout << __func__ << std::endl;
  auto *quitBtn = new QPushButton("b1", this);
  quitBtn->setStyleSheet("background-color:blue;");
  quitBtn->setMinimumHeight(40);
  quitBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  quitBtn->setMaximumWidth(800);
  quitBtn->setMinimumWidth(300);
}

void MyWidget::showmenu(QPoint pos)
{
  QMenu contextMenu(tr("Context menu"), this);
  QAction action1("新建", this);
  connect(&action1, SIGNAL(triggered()), this, SLOT(addbutton()));
  contextMenu.addAction(&action1);
  contextMenu.exec(mapToGlobal(pos));
}

MyWidget::MyWidget(QWidget *parent)
  : QWidget(parent) {
  this->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(customContextMenuRequested(QPoint)),
          this, SLOT(showmenu(QPoint)));
  auto *layout = new QHBoxLayout(this);
  this->setStyleSheet("background-color:red;");
//  auto *quitBtn = new QPushButton("b1", this);
//  quitBtn->setStyleSheet("background-color:blue;");
//  quitBtn->setMinimumHeight(40);
//  quitBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//  quitBtn->setMaximumWidth(800);
//  quitBtn->setMinimumWidth(300);
//  layout->addWidget(quitBtn);
//  layout->setAlignment(quitBtn, Qt::AlignLeft);  //<-- without this, expanding works fine!
//  layout->setStretchFactor(quitBtn, 1);
//  setLayout(layout);
}

void Skeleton::addTab() {
  std::cout << "add tab" << std::endl;
  MyWidget* b3 = new MyWidget(this);
  tabs->addTab(b3, "apple");
}

void Skeleton::on_tabWidget_currentChanged(int index) {
  std::cout << index << std::endl;
}

Skeleton::Skeleton(QWidget *parent)
  : QMainWindow(parent) {

  QPixmap newpix("new.png");
  QPixmap openpix("open.png");
  QPixmap quitpix("quit.png");

  auto *quit = new QAction("&Quit", this);

  QMenu *file = menuBar()->addMenu("&File");
  file->addAction(quit);

  connect(quit, &QAction::triggered, qApp, &QApplication::quit);

  QToolBar *toolbar = addToolBar("main toolbar");
  toolbar->addAction(QIcon(newpix), "New File", this, &Skeleton::addTab);
  toolbar->addAction(QIcon(openpix), "Open File");
  toolbar->addSeparator();

  QAction *quit2 = toolbar->addAction(QIcon(quitpix),
                                      "Quit Application");
  connect(quit2, &QAction::triggered, qApp, &QApplication::quit);
  tabs = new QTabWidget(this);
  connect(tabs, &QTabWidget::currentChanged, this, &Skeleton::on_tabWidget_currentChanged);
  MyWidget* b1 = new MyWidget(this);
  tabs->addTab(b1, "默认分类");
  tabs->setStyleSheet("background-color:black;");
  setCentralWidget(tabs);
}
