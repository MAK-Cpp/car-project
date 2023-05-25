#include <iostream>
#include <filesystem>
#include <string>

// for SQL
#include "sqlite3.h"

#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>

#include "loginWindow.h"
#include "userWindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow main_window;
    main_window.setFixedSize(800, 600);


    loginWindow window(&main_window);


    userWindow second_window(800, 600, &main_window);

    QObject::connect(&window, SIGNAL(changeWindow()), &second_window, SLOT(show()));


    // загружаем изображение в QPixmap
    QPixmap pixmap(PROJECT_SOURCE_DIR "/imgs/image.png");




//    quit.setIcon(QIcon(pixmap));
//    quit.setIconSize(QSize(400, 600));
//    quit.setStyleSheet("background-image: url(" PROJECT_SOURCE_DIR "/imgs/image.png" ");");

    QPushButton breturn("Return", &second_window);
    breturn.resize(100, 200);
    breturn.setFont(QFont("Times", 18, QFont::Bold));
    breturn.setGeometry(100, 200, 100, 200);
    QObject::connect(&breturn, SIGNAL(clicked()), &second_window, SLOT(hide()));
    QObject::connect(&breturn, SIGNAL(clicked()), &window, SLOT(update()));
    QObject::connect(&breturn, SIGNAL(clicked()), &window, SLOT(show()));

    main_window.show();
    second_window.hide();

    return app.exec();
}

