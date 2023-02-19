#include "shell.h"
#include <ssh/sshconnection.h>
#include <ssh/sshremoteprocess.h>
#include <iostream>

using namespace QSsh;

Shell::Shell(QWidget *parent) : QMainWindow(parent),
                                m_console(new Console)
{
  setCentralWidget(m_console);
  QSsh::SshConnectionParameters parameters;
  parameters.setHost("10.168.1.121");
  parameters.setUserName("yuliyang");
  parameters.setPassword("root");
  parameters.setPort(22);
  parameters.timeout = 30;
  parameters.authenticationType
    = QSsh::SshConnectionParameters::SshConnectionParameters::AuthenticationTypeTryAllPasswordBasedMethods;
  m_connection = new SshConnection(parameters);
  connect(m_console, &Console::getData, this, &Shell::writeData);
  connect(m_connection, &SshConnection::connected, this, &Shell::handleConnected);
  connect(m_connection, &SshConnection::dataAvailable, this, &Shell::handleShellMessage);
  connect(m_connection, &SshConnection::error, this, &Shell::handleConnectionError);
  m_connection->connectToHost();
}

Shell::~Shell()
{
  delete m_connection;
}

void Shell::writeData(const QByteArray &data) {
  m_shell->write(data);
}

void Shell::handleShellMessage(const QString &message)
{
  const QByteArray data = message.toUtf8();
  m_console->putData(data);
}

void Shell::handleConnected()
{
  m_shell = m_connection->createRemoteShell();
  connect(m_shell.data(), &SshRemoteProcess::started, this, &Shell::handleShellStarted);
  connect(m_shell.data(), &SshRemoteProcess::readyReadStandardOutput,this, &Shell::handleRemoteStdout);
  connect(m_shell.data(), &SshRemoteProcess::readyReadStandardError,this, &Shell::handleRemoteStderr);
  connect(m_shell.data(), &SshRemoteProcess::closed, this, &Shell::handleChannelClosed);
  m_shell->start();
}

void Shell::handleShellStarted()
{
}
void Shell::handleRemoteStdout()
{
  m_console->putData(m_shell->readAllStandardOutput());
}
void Shell::handleRemoteStderr()
{
  qDebug() << m_shell->readAllStandardError().data();
}
void Shell::handleChannelClosed(int exitStatus)
{
}
void Shell::handleConnectionError()
{
}
