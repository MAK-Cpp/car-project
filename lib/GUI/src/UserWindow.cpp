#include "UserWindow.h"

#include <iostream>

void UserWindow::addNewCarButton(const Car& car, int i, int j) {
    CarCardWindow *another_car = new CarCardWindow(this, car);
    QObject::connect(another_car, SIGNAL(showFullScreen()), this, SLOT(freeScreenForFullScreen()));
    QObject::connect(another_car, SIGNAL(hideFullScreen()), this, SLOT(returScreenFromFullScreen()));
    grid_layout_->addWidget(another_car, i, j);
}

UserWindow::UserWindow(QMainWindow *parent, const std::vector<Car> &cars)
    : QWidget(parent),
      scroll_area_(this),
      buttons_container_(&scroll_area_),
      exit_(&search_container_){

    vertical_layout_ = new QVBoxLayout(nullptr);
    horisontal_layout_ = new QHBoxLayout(nullptr);
    grid_layout_ = new QGridLayout(nullptr);

    vertical_layout_->setContentsMargins(0, 0, 0, 0);
    vertical_layout_->setSpacing(0);

    this->setFixedSize(parent->size());
    this->setLayout(vertical_layout_);

    vertical_layout_->addLayout(horisontal_layout_);
    vertical_layout_->addWidget(&scroll_area_);

    search_container_.setFixedSize(this->width(), this->height() - this->height() * 0.9);
    search_container_.setPalette(QPalette(QPalette::Window, Qt::darkGray));
    search_container_.setAutoFillBackground(true);
    exit_.setFixedSize(search_container_.height() * 0.9, search_container_.height() * 0.9);
    horisontal_layout_->addWidget(&search_container_);
    horisontal_layout_->setAlignment(&exit_, Qt::AlignLeft);


    scroll_area_.setFixedWidth(this->width());
    scroll_area_.setFixedHeight(this->height() * 0.9);
    buttons_container_.setFixedWidth(this->width());

    for (int i = 0; i < cars.size(); ++i) {
        addNewCarButton(cars[i], (i >> 1), (i & 1));
    }
    grid_layout_->setVerticalSpacing(this->height() / 20);

    buttons_container_.setLayout(grid_layout_);

    scroll_area_.setWidget(&buttons_container_);
    scroll_area_.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QObject::connect(&exit_, SIGNAL(clicked()), this, SLOT(returToLoginWindow()));

}
void UserWindow::freeScreenForFullScreen() {
    this->hide();
}
void UserWindow::returScreenFromFullScreen() {
    this->show();
}
void UserWindow::returToLoginWindow() {
    this->hide();
    emit changeToLoginWindow();
}
