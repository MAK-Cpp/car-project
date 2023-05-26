#include "registrationWindow.h"
#include <iostream>

registrationWindow::registrationWindow(QWidget *parent)
    : QWidget(parent),
      vertical_box_layout_(this),
      name_(parent->windowTitle()),
      user_name_("Введите имя:"),
      login_("Введите логин:"),
      password_("Введите пароль:"),
      again_password_("Введите пароль еще раз:"),
      login_button_("Уже есть аккаунт? Войти."),
      register_button_("Зарегистрироваться") {
    this->setFixedSize(parent->width(), parent->height());

    int font_id = QFontDatabase::addApplicationFont(PROJECT_SOURCE_DIR "/fonts/brushscriptmtrusbyme_italic.otf");
    QString font_family = QFontDatabase::applicationFontFamilies(font_id).at(0);
    name_.setFont(QFont(font_family, 80));

    QPalette error_text_color;
    error_text_color.setColor(QPalette::WindowText, Qt::red);
    error_.setPalette(error_text_color);

    form_layout_.addRow(&user_name_, &user_name_input_);
    form_layout_.addRow(&login_, &login_input_);
    form_layout_.addRow(&password_, &password_input_);
    form_layout_.addRow(&again_password_, &again_password_input_);
    form_layout_.setFormAlignment(Qt::AlignCenter | Qt::AlignTop);

    vertical_box_layout_.addWidget(&name_);
    vertical_box_layout_.addStretch(1);
    vertical_box_layout_.addWidget(&error_);
    vertical_box_layout_.addLayout(&form_layout_);
    vertical_box_layout_.addWidget(&register_button_);
    vertical_box_layout_.addWidget(&login_button_);
    vertical_box_layout_.addStretch(2);

    vertical_box_layout_.setAlignment(&name_, Qt::AlignCenter | Qt::AlignTop);
    vertical_box_layout_.setAlignment(&form_layout_, Qt::AlignLeft);
    vertical_box_layout_.setAlignment(&error_, Qt::AlignCenter);
    vertical_box_layout_.setAlignment(&login_button_, Qt::AlignCenter | Qt::AlignTop);
    vertical_box_layout_.setAlignment(&register_button_, Qt::AlignCenter | Qt::AlignTop);

    login_button_.setFixedWidth(this->width() / 3);
    register_button_.setFixedWidth(this->width() / 3);

    password_input_.setEchoMode(QLineEdit::Password);
    again_password_input_.setEchoMode(QLineEdit::Password);

    QObject::connect(&login_button_, SIGNAL(clicked()), this, SLOT(showLoginWindow()));
}

void registrationWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->setFocus();
    }
}

void registrationWindow::registerUser() {

}
void registrationWindow::showLoginWindow() {
    user_name_input_.clear();
    login_input_.clear();
    password_input_.clear();
    again_password_input_.clear();
    error_.clear();
    this->hide();
    emit changeToLoginWindow();
}

