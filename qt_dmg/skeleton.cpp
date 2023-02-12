#include "skeleton.h"

commandButton::commandButton(QWidget *parent)
  : QPushButton(parent) {
  this->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(customContextMenuRequested(QPoint)),
          this, SLOT(showmenu(QPoint)));
}

commandButton::~commandButton() {
  qDebug() << __func__ << name << "" << command;
}

void commandButton::editButton() {
  qDebug() << __func__;
  AddButtonDialog aDialog;
  aDialog.setWindowTitle(tr("编辑命令"));
  aDialog.editcmd(name, command);
  if (aDialog.exec()) {
    const QString newName = aDialog.name();
    const QString newCmd = aDialog.cmd();
    name = newName;
    command = newCmd;
    setText(newName);
  }
}

void commandButton::deleteButton() {
  qDebug() << __func__;
  setParent(nullptr);
  flowLayout->removeWidget(this);
  deleteLater();
}

void commandButton::showmenu(QPoint pos) {
  QMenu contextMenu(tr("按钮菜单"), this);
  QAction action1("修改", this);
  QAction action2("删除", this);
  connect(&action1, SIGNAL(triggered()), this, SLOT(editButton()));
  connect(&action2, SIGNAL(triggered()), this, SLOT(deleteButton()));
  contextMenu.addAction(&action1);
  contextMenu.addAction(&action2);
  contextMenu.exec(mapToGlobal(pos));
}

void MyWidget::addbutton() {
  qDebug() << __func__;
  AddButtonDialog aDialog;
  aDialog.setWindowTitle(tr("新增命令"));
  if (aDialog.exec()) {
    const QString newName = aDialog.name();
    const QString newCmd = aDialog.cmd();
    commandButton* bt = new commandButton();
    bt->SetName(newName);
    bt->SetCmd(newCmd);
    bt->setText(newName);
    bt->setFlowLayout(flowLayout);
    flowLayout->addWidget(bt);
  }
}

void MyWidget::showmenu(QPoint pos)
{
  QMenu contextMenu(tr("Tab菜单"), this);
  QAction action1("新建命令", this);
  connect(&action1, SIGNAL(triggered()), this, SLOT(addbutton()));
  contextMenu.addAction(&action1);
  contextMenu.exec(mapToGlobal(pos));
}

MyWidget::MyWidget(QWidget *parent)
  : QWidget(parent) {
  flowLayout = new FlowLayout;
  this->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(customContextMenuRequested(QPoint)),
          this, SLOT(showmenu(QPoint)));
  setLayout(flowLayout);
}

void Skeleton::addTab() {
  qDebug() << "新建文件夹";
  AddTabDialog aDialog;
  aDialog.setWindowTitle(tr("新建文件夹"));
  if (aDialog.exec()) {
    const QString newName = aDialog.name();
    if (!newName.isEmpty()) {
      MyWidget* b = new MyWidget(this);
      tabs->addTab(b, newName);
    }
  }
}

void Skeleton::on_tabWidget_currentChanged(int index) {
  qDebug() << index;
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
  toolbar->addAction(QIcon(newpix), "新建文件夹", this, &Skeleton::addTab);
  toolbar->addAction(QIcon(openpix), "打开配置文件");
  toolbar->addSeparator();

  QAction *quit2 = toolbar->addAction(QIcon(quitpix),"退出");
  connect(quit2, &QAction::triggered, qApp, &QApplication::quit);
  tabs = new QTabWidget(this);
  connect(tabs, &QTabWidget::currentChanged, this, &Skeleton::on_tabWidget_currentChanged);
  MyWidget* b1 = new MyWidget(this);
  tabs->addTab(b1, "默认分类");
  setCentralWidget(tabs);
}
