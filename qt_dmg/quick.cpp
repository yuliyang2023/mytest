#include "skeleton.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Skeleton window;
  window.resize(450, 350);
  window.setWindowTitle("快速命令");
  window.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Window | Qt::FramelessWindowHint);
  window.show();
  return app.exec();
}