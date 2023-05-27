#include "UserWindow.h"

UserWindow::UserWindow(QMainWindow *parent, const std::vector<Car> &cars)
    : QWidget(parent),
      scroll_area_(this),
      buttons_container_(&scroll_area_) {

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
    horisontal_layout_->addWidget(&search_container_);

    search_container_.setPalette(QPalette(QPalette::Window, Qt::darkGray));
    search_container_.setAutoFillBackground(true);

    scroll_area_.setFixedWidth(this->width());
    scroll_area_.setFixedHeight(this->height() * 0.9);
    buttons_container_.setFixedWidth(this->width());


    for (int i = 0; i < cars.size(); ++i) {
        grid_layout_->addWidget(new CarCardWindow(this, cars[i]), (i >> 1), (i & 1));
    }
    grid_layout_->setVerticalSpacing(this->height() / 20);

    buttons_container_.setLayout(grid_layout_);

    scroll_area_.setWidget(&buttons_container_);
    scroll_area_.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}
