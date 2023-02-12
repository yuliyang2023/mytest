#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE

//! [0]
class AddButtonDialog : public QDialog
{
    Q_OBJECT

public:
    AddButtonDialog(QWidget *parent = nullptr);

    QString name() const;
    QString cmd() const;
    void editcmd(const QString &name, const QString &cmd);

private:
    QLineEdit *nameText;
    QTextEdit *cmdText;
};

#endif // ADDDIALOG_H
