#include "skeleton.h"

commandTab::commandTab(QWidget *parent)
  : QTabWidget(parent) {
  setStyleSheet(
    "QTabWidget::tab-bar { alignment: left;}");
  this->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(customContextMenuRequested(QPoint)),
          this, SLOT(showmenu(QPoint)));
}

commandTab::~commandTab() {
  qDebug() << __func__ << name;
}

void commandTab::rename() {
  AddTabDialog aDialog;
  aDialog.setWindowTitle(tr("重命名"));
  aDialog.move(aDialog.screen()->availableGeometry().topLeft() + QPoint(20, 20));
  if (aDialog.exec()) {
    const QString newName = aDialog.name();
    this->setTabText(this->currentIndex(), newName);
  }
}

void commandTab::remove() {
  this->removeTab(this->currentIndex());
}

void commandTab::showmenu(QPoint pos) {
  QMenu contextMenu(tr("按钮菜单"), this);
  QAction action1("重命名", this);
  QAction action2("删除", this);
  connect(&action1, SIGNAL(triggered()), this, SLOT(rename()));
  connect(&action2, SIGNAL(triggered()), this, SLOT(remove()));
  contextMenu.addAction(&action1);
  contextMenu.addAction(&action2);
  contextMenu.exec(mapToGlobal(pos));
}

void commandButton::onclicked() {
  QClipboard *clipboard = QGuiApplication::clipboard();
  clipboard->setText(command);
}

commandButton::commandButton(QWidget *parent)
  : QPushButton(parent) {
  this->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(customContextMenuRequested(QPoint)),
          this, SLOT(showmenu(QPoint)));
  connect(this, &QPushButton::clicked, this, &commandButton::onclicked);
}

commandButton::~commandButton() {
  qDebug() << __func__ << name << "" << command;
}

void commandButton::editButton() {
  qDebug() << __func__;
  AddButtonDialog aDialog;
  aDialog.setWindowTitle(tr("编辑命令"));
  aDialog.editcmd(name, command);
  aDialog.move(aDialog.screen()->availableGeometry().topLeft() + QPoint(20, 20));
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
  aDialog.move(aDialog.screen()->availableGeometry().topLeft() + QPoint(20, 20));
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

MyWidget::MyWidget(const QJsonArray& buttons, QWidget *parent)
  : QWidget(parent) {
  flowLayout = new FlowLayout;
  this->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(customContextMenuRequested(QPoint)),
          this, SLOT(showmenu(QPoint)));
  for (int i=0; i < buttons.count(); i++) {
    QJsonObject bt = buttons.at(i).toObject();
    for (auto iter = bt.begin(); iter != bt.end(); iter++) {
      commandButton* bt = new commandButton();
      bt->SetName(iter.key());
      bt->SetCmd(iter.value().toString());
      bt->setText(iter.key());
      bt->setFlowLayout(flowLayout);
      flowLayout->addWidget(bt);
    }
  }
  setLayout(flowLayout);
}

void Skeleton::addTab() {
  qDebug() << "新建分类";
  AddTabDialog aDialog;
  aDialog.setWindowTitle(tr("新建分类"));
  aDialog.move(aDialog.screen()->availableGeometry().topLeft() + QPoint(20, 20));
  if (aDialog.exec()) {
    const QString newName = aDialog.name();
    if (!newName.isEmpty()) {
      QJsonArray buttons;
      MyWidget* tab = new MyWidget(buttons, this);
      tabs->addTab(tab, newName);
    }
  }
}

void Skeleton::mousePressEvent(QMouseEvent *event) {
  m_nMouseClick_X_Coordinate = event->x();
  m_nMouseClick_Y_Coordinate = event->y();
}

void Skeleton::mouseMoveEvent(QMouseEvent *event) {
  move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

void Skeleton::save() {
  qDebug() << __func__;
  QJsonArray config;
  for (int i = 0; i < tabs->count(); i++) {
    MyWidget* widget = static_cast<MyWidget*>(tabs->widget(i));
    QString tab = tabs->tabText(i);
    QList<commandButton *> widgets = widget->findChildren<commandButton *>();
    QJsonArray list;
    foreach(commandButton *w, widgets) {
      qDebug() << w->GetName() << "=" << w->GetCmd();
      QJsonObject item;
      item[w->GetName()] = w->GetCmd();
      list.append(item);
    }
    QJsonObject tag_config;
    tag_config[tab] = list;
    config.append(tag_config);
  }
  QJsonDocument doc;
  doc.setArray(config);
  QFile file(QDir::homePath() + "/.quickcmd.json");
  if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    statusBar()->showMessage("写入配置文件失败: " + QDir::homePath() + "/.quickcmd.json", 2000);
  } else {
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream << doc.toJson();
  }
  file.close();
  statusBar()->showMessage("保存配置文件成功: " + QDir::homePath() + "/.quickcmd.json", 2000);
}

Skeleton::Skeleton(QWidget *parent)
  : QMainWindow(parent) {
  QJsonParseError jsonError;
  QFile config_file;
  config_file.setFileName(QDir::homePath() + "/.quickcmd.json");
  if(!config_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    statusBar()->showMessage("打开配置文件失败:" + config_file.errorString(), 2000);
  } else {
    QString str = config_file.readAll();
    config_file.close();
    config_doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !config_doc.isNull()) {
      statusBar()->showMessage("解析JSON失败:" + jsonError.errorString(), 2000);
    }
  }

  QPixmap newpix("new.png");
  QPixmap openpix("open.png");
  QPixmap quitpix("quit.png");
  QPixmap savepix("save.png");
  QToolBar *toolbar = new QToolBar();
  addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolbar);
  toolbar->setMovable(false);
  toolbar->addAction(QIcon(newpix), "New", this, &Skeleton::addTab);
  toolbar->addSeparator();
  QAction *save = toolbar->addAction(QIcon(savepix),"保存", this, &Skeleton::save);
  QAction *quit2 = toolbar->addAction(QIcon(quitpix),"退出");
  connect(quit2, &QAction::triggered, qApp, &QApplication::quit);
  tabs = new commandTab(this);
  QJsonArray config_list = config_doc.array();
  for (int i = 0; i < config_list.count(); i++) {
    QJsonObject tag_conf = config_list.at(i).toObject();
    for (auto iter = tag_conf.begin(); iter != tag_conf.end(); iter++) {
      QString tag_name = iter.key();
      QJsonArray buttonlist = iter.value().toArray();
      MyWidget* t = new MyWidget(buttonlist, this);
      tabs->addTab(t, tag_name);
    }
  }
  setCentralWidget(tabs);
  statusBar()->showMessage("Ready", 2000);
}
