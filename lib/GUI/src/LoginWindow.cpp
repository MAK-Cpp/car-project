#include "LoginWindow.h"
#include "GeneralDB.h"

#include <iostream>

void LoginWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->setFocus();
    }
}

LoginWindow::LoginWindow(QMainWindow *parent)
    : QWidget(parent), vertical_box_layout_(this), login_button_("Войти"), register_button_("Первый раз? Регистрация"),
      login_label_("Имя пользователя:"), password_label_("Пароль:"), name_label_(parent->windowTitle()) {

    this->setFixedSize(parent->width(), parent->height());

    name_label_.setFont(QFont(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(
        PROJECT_SOURCE_DIR "/fonts/brushscriptmtrusbyme_italic.otf")).at(0), 60));

    QPalette error_text_color;
    error_text_color.setColor(QPalette::WindowText, Qt::red);
    error_label_.setPalette(error_text_color);


    form_layout_.addRow(&login_label_, &login_input_);
    form_layout_.addRow(&password_label_, &password_input_);
    form_layout_.setFormAlignment(Qt::AlignCenter | Qt::AlignTop);

    vertical_box_layout_.addWidget(&name_label_);
    vertical_box_layout_.addStretch(1);
    vertical_box_layout_.addWidget(&error_label_);
    vertical_box_layout_.addLayout(&form_layout_);
    vertical_box_layout_.addWidget(&login_button_);
    vertical_box_layout_.addWidget(&register_button_);
    vertical_box_layout_.addStretch(2);

    vertical_box_layout_.setAlignment(&name_label_, Qt::AlignCenter | Qt::AlignTop);
    vertical_box_layout_.setAlignment(&form_layout_, Qt::AlignCenter);
    vertical_box_layout_.setAlignment(&error_label_, Qt::AlignCenter);
    vertical_box_layout_.setAlignment(&login_button_, Qt::AlignCenter | Qt::AlignTop);
    vertical_box_layout_.setAlignment(&register_button_, Qt::AlignCenter | Qt::AlignTop);

    login_button_.setFixedWidth(this->width() / 3);
    register_button_.setFixedWidth(this->width() / 3);


    password_input_.setEchoMode(QLineEdit::Password);

    QObject::connect(&login_input_, SIGNAL(returnPressed()), &password_input_, SLOT(setFocus()));
    QObject::connect(&password_input_, SIGNAL(returnPressed()), &login_button_, SIGNAL(clicked()));

    QObject::connect(&login_button_, SIGNAL(clicked()), this, SLOT(showUserWindow()));
    QObject::connect(&register_button_, SIGNAL(clicked()), this, SLOT(showRegistrationWindow()));
}



void LoginWindow::showUserWindow() {
    if(login_input_.text().isEmpty() || password_input_.text().isEmpty()) {
        error_label_.setText("Ошибка: логин или пароль не могут быть пустыми!");
        password_input_.clear();
        return;
    }
    std::pair<int, access> reg = GeneralDB::check_user(login_input_.text(), password_input_.text());
    switch (reg.second) {
        case access::NONE: {
            error_label_.setText("Ошибка: неправильный логин или пароль!");
            break;
        }
        case access::USER: {
            error_label_.clear();
            this->hide();
            login_input_.clear();
            emit changeToUserWindow(reg.first, access::USER);
            break;
        }
        case access::ROOT: {
            error_label_.clear();
            this->hide();
            login_input_.clear();
            emit changeToUserWindow(reg.first, access::ROOT);
            break;
        }
        default: {
            break;
        }
    }
    password_input_.clear();

}

void LoginWindow::showRegistrationWindow() {
    login_input_.clear();
    password_input_.clear();
    error_label_.clear();
    this->hide();
    emit changeToRegistrationWindow();
}
