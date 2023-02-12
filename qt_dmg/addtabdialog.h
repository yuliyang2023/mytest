//
// Created by yuliyang on 2023/2/12.
//

#ifndef UNTITLED1_ADDTABDIALOG_H
#define UNTITLED1_ADDTABDIALOG_H


#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE

class AddTabDialog : public QDialog
{
Q_OBJECT

public:
  AddTabDialog(QWidget *parent = nullptr);
  QString name() const;

private:
  QLineEdit *nameText;
};

#endif //UNTITLED1_ADDTABDIALOG_H
