#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <iostream>
#include <QClipboard>
#include <QAction>

class MyButton : public QWidget {

public:
    MyButton(QWidget *parent = nullptr);
    void fun();
};

void MyButton::fun() {
    std::cout << "xxxxxxx" << std::endl;
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText("qqqqqqq");
}

MyButton::MyButton(QWidget *parent)
        : QWidget(parent) {

//    this->setGeometry(0, 0, 300, 100);
    auto *quitBtn = new QPushButton("Quit", this);
    quitBtn->setGeometry(50, 40, 75, 30);

    connect(quitBtn, &QPushButton::clicked, this, &MyButton::fun);
}

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    MyButton window;

    window.resize(250, 150);
    window.setWindowTitle("QPushButton");
    window.show();

    return app.exec();
}