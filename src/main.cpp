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

    Car check_car("0", "benz", "49.99", "20", "35", "95", "image.png", "saint-petersburg", "white", "Mercedes");

    Car a("2", "Bentley Bentayga First Edition" , "59000" "4.0", "550.0", "бензин", "Bentley", "Bentley_Bentayga_First_Edition.png", "Москва", "черный", "bentley");
    Car b("3", "Bentley Continental GT W12", "65000", "6.0", "635.0", "бензин", "Bentley_Continental_GT_W12.png", "Москва", "синий", "bentley");
    Car c("4", "BMW X5 M-SPORT", "18900", "3.0", "340.0", "бензин", "BMW_X5_M-SPORT.png", "Минск", "черный", "bmw");
    Car d("5", "BMW X7 M-SPORT", "21000", "3.0", "249.0", "дизель", "BMW_X7_M-SPORT.png", "Москва", "черный", "bmw");
    Car e("6", "BMW X6 M-SPORT", "20000", "3.0", "249.0", "дизель", "BMW_X6_M-SPORT.png", "Москва", "черный", "bmw");



    LoginWindow login_window(&main_window);
    RegistrationWindow registration_window(&main_window);
    UserWindow user_window(&main_window, {check_car, a, b, c, d, e});

    QObject::connect(&login_window, SIGNAL(changeToUserWindow()), &user_window, SLOT(show()));
    QObject::connect(&login_window, SIGNAL(changeToRegistrationWindow()), &registration_window, SLOT(show()));

    QObject::connect(&registration_window, SIGNAL(changeToLoginWindow()), &login_window, SLOT(show()));

    QObject::connect(&user_window, SIGNAL(changeToLoginWindow()), &login_window, SLOT(show()));

    user_window.hide();
    registration_window.hide();
    main_window.show();


    return app.exec();
}


