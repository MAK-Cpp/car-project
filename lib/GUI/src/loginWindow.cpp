#include "loginWindow.h"
#include "UserDB.h"

#include <iostream>

void loginWindow::showUserWindow() {
    switch (UserDB::check_user(login_input_.text(), password_input_.text())) {
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
    : QWidget(parent), vertical_box_layout_(this), login_button_("Войти"), register_button_("Первый раз? Регистрация"),
      login_("Имя пользователя:"), password_("Пароль:"), name_("КОЛЁСА НА ВРЕМЯ") {

    this->setFixedSize(w, h);

    int font_id = QFontDatabase::addApplicationFont(PROJECT_SOURCE_DIR "/fonts/brushscriptmtrusbyme_italic.otf");
    QString font_family = QFontDatabase::applicationFontFamilies(font_id).at(0);

    name_.setFont(QFont(font_family, 80));

    QPalette error_text_color;
    error_text_color.setColor(QPalette::WindowText, Qt::red);

    error_.setPalette(error_text_color);

    form_layout_.addRow(&login_, &login_input_);
    form_layout_.addRow(&password_, &password_input_);

    vertical_box_layout_.addWidget(&name_);
    vertical_box_layout_.addStretch(1);
    vertical_box_layout_.addWidget(&error_);
    vertical_box_layout_.addLayout(&form_layout_);
    vertical_box_layout_.addWidget(&login_button_);
    vertical_box_layout_.addWidget(&register_button_);
    vertical_box_layout_.addStretch(2);

    vertical_box_layout_.setAlignment(&name_, Qt::AlignCenter | Qt::AlignTop);
    vertical_box_layout_.setAlignment(&form_layout_, Qt::AlignLeft);
    vertical_box_layout_.setAlignment(&error_, Qt::AlignCenter);
    vertical_box_layout_.setAlignment(&login_button_, Qt::AlignCenter | Qt::AlignTop);
    vertical_box_layout_.setAlignment(&register_button_, Qt::AlignCenter | Qt::AlignTop);

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

