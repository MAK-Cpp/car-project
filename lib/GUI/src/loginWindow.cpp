#include "loginWindow.h"
#include <iostream>

void loginWindow::showUserWindow() {
    if (login_input_.text() == "root" && password_input_.text() == "1234") {
        this->hide();
        login_input_.clear();
        emit changeWindow();
    }
    password_input_.clear();

}

loginWindow::loginWindow(QWidget *parent, int w, int h)
    : QWidget(parent)
    , layout_(this)
    , login_button_("login"){
    this->setFixedSize(w / 4, h / 3);
    layout_.addWidget(&login_input_);
    layout_.addWidget(&password_input_);
    layout_.addWidget(&login_button_);
    this->move((w - this->width()) / 2, (h - this->height()) / 2);


    password_input_.setEchoMode(QLineEdit::Password);
    QObject::connect(&login_button_, SIGNAL(clicked()), this, SLOT(showUserWindow()));
    QObject::connect(&login_input_, SIGNAL(returnPressed()), &password_input_, SLOT(setFocus()));
    QObject::connect(&password_input_, SIGNAL(returnPressed()), &login_button_, SIGNAL(clicked()));
}


void loginWindow::mousePressEvent ( QMouseEvent * event ) {
//    std::cout << "CHECK!\n";
    if (event->button() == Qt::LeftButton) {
        this->setFocus();
    }
}

