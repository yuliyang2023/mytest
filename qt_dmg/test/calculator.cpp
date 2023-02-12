#include <QWidget>

class Calculator : public QWidget {

public:
  Calculator(QWidget *parent = nullptr);
  void onBtnClicked();
private:
  std::atomic<bool> pined;
  Qt::WindowFlags old;
};

#include <QGridLayout>
#include <QPushButton>

#include <QGuiApplication>
#include <QClipboard>
void Calculator::onBtnClicked() {
  QClipboard *clipboard = QGuiApplication::clipboard();

  QPushButton* button = qobject_cast<QPushButton*>(sender());
  if( button != NULL )
  {
    clipboard->setText(button->text());
  }


  pined = !pined;
  if (pined) {

  } else {

  }
}

Calculator::Calculator(QWidget *parent)
  : QWidget(parent), pined(false) {

  auto *grid = new QGridLayout(this);
  grid->setSpacing(2);

  QVector<QString> values({ "7", "8", "9", "/",
                            "4", "5", "6", "*",
                            "1", "2", "3", "-",
                            "0", ".", "=", "+"
                          });

  int pos = 0;

  for (int i=0; i<4; i++) {
    for (int j=0; j<4; j++) {
      auto *btn = new QPushButton(values[pos], this);
      connect(btn, &QPushButton::clicked, this, &Calculator::onBtnClicked);
//      btn->setFixedSize(40, 40);
      grid->addWidget(btn, i, j);
      pos++;
    }
  }

  setLayout(grid);
}

#include <QApplication>

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  Calculator window;
  window.setWindowFlags(Qt::WindowStaysOnTopHint);
  window.setWindowTitle("Calculator");
  window.show();

  return app.exec();
}