#include "loginWindow.h"
#include "database_action.h"

#include <iostream>

void loginWindow::showUserWindow() {
    switch (check_user(login_input_.text(), password_input_.text())) {
        case access::NONE: {
            error_.setText("Ошибка: неправильный логин или пароль!");
            break;
        }
        case access::USER: {
            error_.setText("");
            break;
        }
        case access::ROOT: {
            error_.setText("");
            this->hide();
            login_input_.clear();
            emit changeToUserWindow();
            break;
        }
        default: {
            break;
        }
    }
    password_input_.clear();

}

loginWindow::loginWindow(QWidget *parent, int w, int h)
    : QWidget(parent), box_layout_(this), login_button_("Войти"), register_button_("Первый раз? Регистрация"),
      login_("Имя пользователя:"), password_("Пароль:"), name_("КОЛЁСА НА ВРЕМЯ") {

    this->setFixedSize(w, h);

    name_.setFont(QFont("brush script mt", 80));

    QPalette error_text_color;
    error_text_color.setColor(QPalette::WindowText, Qt::red);

    error_.setPalette(error_text_color);

    form_layout_.addRow(&login_, &login_input_);
    form_layout_.addRow(&password_, &password_input_);

    box_layout_.addWidget(&name_);
    box_layout_.addStretch(1);
    box_layout_.addWidget(&error_);
    box_layout_.addLayout(&form_layout_);
    box_layout_.addWidget(&login_button_);
    box_layout_.addWidget(&register_button_);
    box_layout_.addStretch(2);

    box_layout_.setAlignment(&name_, Qt::AlignCenter | Qt::AlignTop);
    box_layout_.setAlignment(&form_layout_, Qt::AlignLeft);
    box_layout_.setAlignment(&error_, Qt::AlignCenter);
    box_layout_.setAlignment(&login_button_, Qt::AlignCenter | Qt::AlignTop);
    box_layout_.setAlignment(&register_button_, Qt::AlignCenter | Qt::AlignTop);

    login_button_.setFixedWidth(this->width() / 3);
    register_button_.setFixedWidth(this->width() / 3);

    password_input_.setEchoMode(QLineEdit::Password);
    QObject::connect(&login_button_, SIGNAL(clicked()), this, SLOT(showUserWindow()));
    QObject::connect(&login_input_, SIGNAL(returnPressed()), &password_input_, SLOT(setFocus()));
    QObject::connect(&password_input_, SIGNAL(returnPressed()), &login_button_, SIGNAL(clicked()));
}

void loginWindow::mousePressEvent(QMouseEvent *event) {
//    std::cout << "CHECK!\n";
    if (event->button() == Qt::LeftButton) {
        this->setFocus();
    }
}

