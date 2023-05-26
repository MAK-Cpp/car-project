#include "loginWindow.h"
#include "GeneralDB.h"

#include <iostream>

void loginWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->setFocus();
    }
}

loginWindow::loginWindow(QWidget *parent)
    : QWidget(parent), vertical_box_layout_(this), login_button_("Войти"), register_button_("Первый раз? Регистрация"),
      login_("Имя пользователя:"), password_("Пароль:"), name_(parent->windowTitle()) {

    this->setFixedSize(parent->width(), parent->height());

    int font_id = QFontDatabase::addApplicationFont(PROJECT_SOURCE_DIR "/fonts/brushscriptmtrusbyme_italic.otf");
    QString font_family = QFontDatabase::applicationFontFamilies(font_id).at(0);
    name_.setFont(QFont(font_family, 80));

    QPalette error_text_color;
    error_text_color.setColor(QPalette::WindowText, Qt::red);
    error_.setPalette(error_text_color);

//    login_input_.setFixedWidth(this->width() / 5);
//    password_input_.setFixedWidth(this->width() / 5);


    form_layout_.addRow(&login_, &login_input_);
    form_layout_.addRow(&password_, &password_input_);
    form_layout_.setFormAlignment(Qt::AlignCenter | Qt::AlignTop);

    vertical_box_layout_.addWidget(&name_);
    vertical_box_layout_.addStretch(1);
    vertical_box_layout_.addWidget(&error_);
    vertical_box_layout_.addLayout(&form_layout_);
    vertical_box_layout_.addWidget(&login_button_);
    vertical_box_layout_.addWidget(&register_button_);
    vertical_box_layout_.addStretch(2);

    vertical_box_layout_.setAlignment(&name_, Qt::AlignCenter | Qt::AlignTop);
    vertical_box_layout_.setAlignment(&form_layout_, Qt::AlignCenter);
    vertical_box_layout_.setAlignment(&error_, Qt::AlignCenter);
    vertical_box_layout_.setAlignment(&login_button_, Qt::AlignCenter | Qt::AlignTop);
    vertical_box_layout_.setAlignment(&register_button_, Qt::AlignCenter | Qt::AlignTop);

    login_button_.setFixedWidth(this->width() / 3);
//    login_button_.setFixedHeight(this->width() / 20);
    register_button_.setFixedWidth(this->width() / 3);
//    register_button_.setFixedHeight(this->width() / 20);


    password_input_.setEchoMode(QLineEdit::Password);

    QObject::connect(&login_input_, SIGNAL(returnPressed()), &password_input_, SLOT(setFocus()));
    QObject::connect(&password_input_, SIGNAL(returnPressed()), &login_button_, SIGNAL(clicked()));

    QObject::connect(&login_button_, SIGNAL(clicked()), this, SLOT(showUserWindow()));
    QObject::connect(&register_button_, SIGNAL(clicked()), this, SLOT(showRegistrationWindow()));
}



void loginWindow::showUserWindow() {
    if(login_input_.text().isEmpty() || password_input_.text().isEmpty()) {
        error_.setText("Ошибка: логин или пароль не могут быть пустыми!");
        password_input_.clear();
        return;
    }
    switch (GeneralDB::check_user(login_input_.text(), password_input_.text())) {
        case access::NONE: {
            error_.setText("Ошибка: неправильный логин или пароль!");
            break;
        }
        case access::USER: {
            error_.clear();
            break;
        }
        case access::ROOT: {
            error_.clear();
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

void loginWindow::showRegistrationWindow() {
    login_input_.clear();
    password_input_.clear();
    error_.clear();
    this->hide();
    emit changeToRegistrationWindow();
}
