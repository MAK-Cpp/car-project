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

#include "LoginWindow.h"
#include "UserWindow.h"
#include "RegistrationWindow.h"
#include "GeneralDB.h"

int main(int argc, char *argv[]) {
    GeneralDB::init();
    QApplication app(argc, argv);
    QMainWindow main_window;
    main_window.setWindowTitle("КОЛЁСА НА ВРЕМЯ");
    main_window.setFixedSize(800, 600);

    loginWindow login_window(&main_window);
    RegistrationWindow registration_window(&main_window);
    userWindow second_window(&main_window);

    QObject::connect(&login_window, SIGNAL(changeToUserWindow()), &second_window, SLOT(show()));
    QObject::connect(&login_window, SIGNAL(changeToRegistrationWindow()), &registration_window, SLOT(show()));

    QObject::connect(&registration_window, SIGNAL(changeToLoginWindow()), &login_window, SLOT(show()));

    QPushButton breturn("Return", &second_window);
    breturn.setFont(QFont("Comic sans", 18, QFont::Bold));
    breturn.setGeometry(100, 200, 100, 200);
    QObject::connect(&breturn, SIGNAL(clicked()), &second_window, SLOT(hide()));
    QObject::connect(&breturn, SIGNAL(clicked()), &login_window, SLOT(show()));

    second_window.hide();
    registration_window.hide();
    main_window.show();


    return app.exec();
}


