#ifndef CARPROJECT_LIB_GUI_INCLUDE_LOGINWINDOW_H_
#define CARPROJECT_LIB_GUI_INCLUDE_LOGINWINDOW_H_

#include "QT-config.h"
#include "GeneralDB.h"
#include <string>


class LoginWindow : public QWidget {
    Q_OBJECT
public:
    explicit LoginWindow(QMainWindow* parent);
    void mousePressEvent ( QMouseEvent * event ) override;
public slots:
    void showUserWindow();
    void showRegistrationWindow();
signals:
    void changeToUserWindow(uint64_t, access);
    void changeToRegistrationWindow();
private:
    QVBoxLayout vertical_box_layout_;
    QFormLayout form_layout_;
    QLineEdit login_input_;
    QLineEdit password_input_;
    QLabel login_label_;
    QLabel password_label_;
    QLabel error_label_;
    QLabel name_label_;
    QPushButton login_button_;
    QPushButton register_button_;
};

#endif //CARPROJECT_LIB_GUI_INCLUDE_LOGINWINDOW_H_
