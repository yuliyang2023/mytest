#pragma once
#include <QObject>
#include <QSharedPointer>
#include <QMainWindow>
#include "console.h"

namespace QSsh {
class SshConnection;
class SshConnectionParameters;
class SshRemoteProcess;
}

QT_BEGIN_NAMESPACE
class QByteArray;
class QFile;
class QString;
QT_END_NAMESPACE

class Shell : public QMainWindow
{
    Q_OBJECT
public:
    explicit Shell(QWidget *parent = nullptr);
    ~Shell();

private:
    Console *m_console = nullptr;
    void handleConnected();
    void handleConnectionError();
    void handleRemoteStdout();
    void handleRemoteStderr();
    void handleShellMessage(const QString &message);
    void handleChannelClosed(int exitStatus);
    void handleShellStarted();
    void writeData(const QByteArray &data);

    QSsh::SshConnection *m_connection;
    QSharedPointer<QSsh::SshRemoteProcess> m_shell;
};
