//
// Created by yuliyang on 2023/2/12.
//

#include "addtabdialog.h"
#include <QtWidgets>
AddTabDialog::AddTabDialog(QWidget *parent)
  : QDialog(parent),
    nameText(new QLineEdit)
{
  auto nameLabel = new QLabel(tr("名称"));
  auto okButton = new QPushButton(tr("确定"));
  auto cancelButton = new QPushButton(tr("取消"));

  auto gLayout = new QGridLayout;
  gLayout->setColumnStretch(1, 2);
  gLayout->addWidget(nameLabel, 0, 0);
  gLayout->addWidget(nameText, 0, 1);

  auto buttonLayout = new QHBoxLayout;
  buttonLayout->addWidget(okButton);
  buttonLayout->addWidget(cancelButton);

  gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

  auto mainLayout = new QVBoxLayout;
  mainLayout->addLayout(gLayout);
  setLayout(mainLayout);

  connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
  connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

  setWindowTitle(tr("新建文件夹"));
}

QString AddTabDialog::name() const
{
  return nameText->text();
}
