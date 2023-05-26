#ifndef CARPROJECT_LIB_GUI_INCLUDE_REGISTRATIONWINDOW_H_
#define CARPROJECT_LIB_GUI_INCLUDE_REGISTRATIONWINDOW_H_

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QObject>
#include <QMouseEvent>
#include <QString>
#include <QByteArray>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPalette>
#include <QFontDatabase>
#include <QFontMetrics>

class RegistrationWindow : public QWidget {
Q_OBJECT
public:
    explicit RegistrationWindow(QWidget *parent);
    void mousePressEvent(QMouseEvent *event) override;
public slots:
    void registerUser();
    void showLoginWindow();
signals:
    void changeToLoginWindow();
private:
    QWidget registration_widget_;
    QWidget success_widget_;
    QVBoxLayout vertical_box_layout_;
    QVBoxLayout vertical_success_box_layout_;
    QFormLayout form_layout_;
    QLineEdit user_name_input_;
    QLineEdit login_input_;
    QLineEdit password_input_;
    QLineEdit again_password_input_;
    QLabel success_label_;
    QLabel user_name_label_;
    QLabel login_label_;
    QLabel password_label_;
    QLabel again_password_label_;
    QLabel error_label_;
    QLabel name_label_;
    QPushButton success_button_;
    QPushButton login_button_;
    QPushButton register_button_;
};

#endif //CARPROJECT_LIB_GUI_INCLUDE_REGISTRATIONWINDOW_H_
