#include <iostream>
#include <filesystem>
#include <string>
#include <cmath>

// for SQL
#include "sqlite3.h"

#include "QT-config.h"
#include "LoginWindow.h"
#include "UserWindow.h"
#include "RegistrationWindow.h"
#include "GeneralDB.h"
#include "CarCardWindow.h"

int main(int argc, char *argv[]) {
    GeneralDB::init();
    QApplication app(argc, argv);
    QMainWindow main_window;
    main_window.setWindowTitle("КОЛЁСА НА ВРЕМЯ");
//    main_window.setFixedSize(1680, 1050);
//    main_window.setFixedSize(1920, 1080);
    main_window.setFixedSize(800, 600);

    Car check_car("0", "Mercedes", "49.99", "20", "35", "95", "image.png", "saint-petersburg");



    LoginWindow login_window(&main_window);
    RegistrationWindow registration_window(&main_window);
    UserWindow second_window(&main_window, {check_car, check_car, check_car, check_car, check_car, check_car, check_car, check_car, check_car});

    QObject::connect(&login_window, SIGNAL(changeToUserWindow()), &second_window, SLOT(show()));
    QObject::connect(&login_window, SIGNAL(changeToRegistrationWindow()), &registration_window, SLOT(show()));

    QObject::connect(&registration_window, SIGNAL(changeToLoginWindow()), &login_window, SLOT(show()));


    second_window.hide();
    registration_window.hide();
    main_window.show();


    return app.exec();
}


