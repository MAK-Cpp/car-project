#include "RegistrationWindow.h"
#include "GeneralDB.h"
#include <iostream>

RegistrationWindow::RegistrationWindow(QMainWindow *parent)
    : QWidget(parent),
      registration_widget_(this),
      success_widget_(this),
      vertical_box_layout_(&registration_widget_),
      vertical_success_box_layout_(&success_widget_),
      name_label_(parent->windowTitle()),
      success_label_("Вы успешно зарегистрировались! Теперь можете войти в аккаунт:"),
      success_button_("Вернуться"),
      user_name_label_("Введите имя:"),
      login_label_("Введите логин:"),
      password_label_("Введите пароль:"),
      again_password_label_("Введите пароль еще раз:"),
      login_button_("Уже есть аккаунт? Войти."),
      register_button_("Зарегистрироваться") {

    this->setFixedSize(parent->width(), parent->height());
    registration_widget_.setFixedSize(this->width(), this->height());
    success_widget_.setFixedSize(this->width(), this->height());

    name_label_.setFont(QFont(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(
        PROJECT_SOURCE_DIR "/fonts/brushscriptmtrusbyme_italic.otf")).at(0), 60));

    QPalette error_text_color;
    error_text_color.setColor(QPalette::WindowText, Qt::red);
    error_label_.setPalette(error_text_color);

    vertical_success_box_layout_.addStretch(1);
    vertical_success_box_layout_.addWidget(&success_label_);
    vertical_success_box_layout_.addWidget(&success_button_);
    vertical_success_box_layout_.addStretch(1);
    vertical_success_box_layout_.setAlignment(&success_label_, Qt::AlignCenter | Qt::AlignTop);
    vertical_success_box_layout_.setAlignment(&success_button_, Qt::AlignCenter);
    success_widget_.hide();

    form_layout_.addRow(&user_name_label_, &user_name_input_);
    form_layout_.addRow(&login_label_, &login_input_);
    form_layout_.addRow(&password_label_, &password_input_);
    form_layout_.addRow(&again_password_label_, &again_password_input_);

    vertical_box_layout_.addWidget(&name_label_);
    vertical_box_layout_.addStretch(1);
    vertical_box_layout_.addWidget(&error_label_);
    vertical_box_layout_.addLayout(&form_layout_);
    vertical_box_layout_.addWidget(&register_button_);
    vertical_box_layout_.addWidget(&login_button_);
    vertical_box_layout_.addStretch(2);

    vertical_box_layout_.setAlignment(&name_label_, Qt::AlignCenter | Qt::AlignTop);
    vertical_box_layout_.setAlignment(&form_layout_, Qt::AlignLeft);
    vertical_box_layout_.setAlignment(&error_label_, Qt::AlignCenter);
    vertical_box_layout_.setAlignment(&register_button_, Qt::AlignCenter | Qt::AlignTop);
    vertical_box_layout_.setAlignment(&login_button_, Qt::AlignCenter | Qt::AlignTop);

    login_button_.setFixedWidth(this->width() / 3);
    register_button_.setFixedWidth(this->width() / 3);
    success_button_.setFixedWidth(this->width() / 3);

    password_input_.setEchoMode(QLineEdit::Password);
    again_password_input_.setEchoMode(QLineEdit::Password);

    QObject::connect(&user_name_input_, SIGNAL(returnPressed()), &login_input_, SLOT(setFocus()));
    QObject::connect(&login_input_, SIGNAL(returnPressed()), &password_input_, SLOT(setFocus()));
    QObject::connect(&password_input_, SIGNAL(returnPressed()), &again_password_input_, SLOT(setFocus()));
    QObject::connect(&again_password_input_, SIGNAL(returnPressed()), &register_button_, SIGNAL(clicked()));

    QObject::connect(&register_button_, SIGNAL(clicked()), this, SLOT(registerUser()));
    QObject::connect(&login_button_, SIGNAL(clicked()), this, SLOT(showLoginWindow()));
    QObject::connect(&success_button_, SIGNAL(clicked()), this, SLOT(showLoginWindow()));

}

void RegistrationWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->setFocus();
    }
}

void RegistrationWindow::registerUser() {
    if (user_name_input_.text().isEmpty() ||
        login_input_.text().isEmpty() ||
        password_input_.text().isEmpty() ||
        again_password_input_.text().isEmpty()) {
        error_label_.setText("Ошибка: необходимо заполнить все поля!");
    } else if (password_input_.text() != again_password_input_.text()) {
        error_label_.setText("Ошибка: пароли не совпадают, попробуйте ещё раз.");
    } else {
        reg_const registration_status = GeneralDB::register_user(user_name_input_.text(), login_input_.text(), password_input_.text());
        if (registration_status == reg_const::NONE) {
            error_label_.setText("Ошибка: аккаунт с таким логином уже существует, выберите другой.");
        } else {
            success_widget_.show();
            registration_widget_.hide();
            login_input_.clear();
            user_name_input_.clear();
        }
    }
    password_input_.clear();
    again_password_input_.clear();
}
void RegistrationWindow::showLoginWindow() {
    user_name_input_.clear();
    login_input_.clear();
    password_input_.clear();
    again_password_input_.clear();
    error_label_.clear();

    success_widget_.hide();
    registration_widget_.show();
    this->hide();

    emit changeToLoginWindow();
}

