#include "addbuttondialog.h"
#include <QtWidgets>
AddButtonDialog::AddButtonDialog(QWidget *parent)
    : QDialog(parent),
      nameText(new QLineEdit),
      cmdText(new QTextEdit)
{
    auto nameLabel = new QLabel(tr("名称"));
    auto cmdLabel = new QLabel(tr("命令"));
    auto okButton = new QPushButton(tr("确定"));
    auto cancelButton = new QPushButton(tr("取消"));

    auto gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);
    gLayout->addWidget(nameLabel, 0, 0);
    gLayout->addWidget(nameText, 0, 1);

    gLayout->addWidget(cmdLabel, 1, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(cmdText, 1, 1, Qt::AlignLeft);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("新增命令"));
}

QString AddButtonDialog::name() const
{
    return nameText->text();
}

QString AddButtonDialog::cmd() const
{
    return cmdText->toPlainText();
}

void AddButtonDialog::editcmd(const QString &name, const QString &address)
{
    nameText->setText(name);
    cmdText->setPlainText(address);
}
