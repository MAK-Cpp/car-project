#include <iostream>
#include <filesystem>
#include <string>
#include <cmath>

// for DataBase
#include "GeneralDB.h"

// for GUI
#include "QT-config.h"
#include "LoginWindow.h"
#include "UserWindow.h"
#include "RegistrationWindow.h"

int main(int argc, char *argv[]) {
    GeneralDB::init();
    QApplication app(argc, argv);
    QMainWindow main_window;
    main_window.setWindowTitle("КОЛЁСА НА ВРЕМЯ");
//    main_window.setFixedSize(1680, 1050);
//    main_window.setFixedSize(1920, 1080);
    main_window.setFixedSize(800, 600);
    main_window.setPalette(QPalette(QColor::fromRgb(48, 48, 48)));
    main_window.setAutoFillBackground(true);


    LoginWindow login_window(&main_window);
    RegistrationWindow registration_window(&main_window);
    UserWindow user_window(&main_window, GeneralDB::getAllCars());
    UserAccount user_account(&main_window);
    RootWindow root_window(&main_window);


    QObject::connect(&login_window, SIGNAL(changeToUserWindow(uint64_t, access)), &user_window, SLOT(showWithUserID(uint64_t, access)));
    QObject::connect(&login_window, SIGNAL(changeToRegistrationWindow()), &registration_window, SLOT(show()));

    QObject::connect(&registration_window, SIGNAL(changeToLoginWindow()), &login_window, SLOT(show()));

    QObject::connect(&user_window, SIGNAL(changeToLoginWindow()), &login_window, SLOT(show()));
    QObject::connect(&user_window, SIGNAL(changeToUserAccount(uint64_t)), &user_account, SLOT(showUserAccount(uint64_t)));
    QObject::connect(&user_window, SIGNAL(changeToRootWindow()), &root_window, SLOT(show()));

    QObject::connect(&user_account, SIGNAL(returnToUserWindow()), &user_window, SLOT(returScreenFromFullScreen()));

    QObject::connect(&root_window, SIGNAL(addCarToUserWindow(Car)), &user_window, SLOT(addCar(Car)));
    QObject::connect(&root_window, SIGNAL(returnToUserWindow()), &user_window, SLOT(returScreenFromFullScreen()));


    user_window.hide();
    registration_window.hide();
    user_account.hide();
    root_window.hide();
    main_window.show();

    return app.exec();
}


