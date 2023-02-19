#include "shell.h"
#include <ssh/sshconnection.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Shell shell;
    shell.show();
    return app.exec();
}