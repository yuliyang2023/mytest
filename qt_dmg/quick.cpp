#include "skeleton.h"
#include <singleapplication.h>

int main(int argc, char *argv[]) {
  SingleApplication app(argc, argv);
  Skeleton window;
  if(app.isSecondary()) {
    app.sendMessage( app.arguments().join(' ').toUtf8() );
    return 0;
  } else {
    QObject::connect( &app, &SingleApplication::instanceStarted, [ &window ]() {
      window.raise();
      window.activateWindow();
    });
  }
  window.resize(450, 350);
  window.setWindowTitle("快速命令");
  window.setWindowFlags(Qt::Window);
  window.show();
  return app.exec();
}