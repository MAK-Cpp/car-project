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
#include "GeneralDB.h"

int main(int argc, char *argv[]) {
    GeneralDB::init();
    QApplication app(argc, argv);
    QMainWindow main_window;
    main_window.setFixedSize(800, 600);

    loginWindow window(&main_window, main_window.width(), main_window.height());

    userWindow second_window(main_window.width(), main_window.height(), &main_window);

    QObject::connect(&window, SIGNAL(changeToUserWindow()), &second_window, SLOT(show()));

    QPushButton breturn("Return", &second_window);
    breturn.setFont(QFont("Comic sans", 18, QFont::Bold));
    breturn.setGeometry(100, 200, 100, 200);
    QObject::connect(&breturn, SIGNAL(clicked()), &second_window, SLOT(hide()));
    QObject::connect(&breturn, SIGNAL(clicked()), &window, SLOT(update()));
    QObject::connect(&breturn, SIGNAL(clicked()), &window, SLOT(show()));

    main_window.show();
    second_window.hide();

    return app.exec();
}


