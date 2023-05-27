#include "CarCardWindow.h"
#include <iostream>
#include <filesystem>

CarCardWindow::CarCardWindow(QWidget *parent, const Car& car)
    : QWidget(parent),
      rent_button_(this),
      full_screen_(parent->parentWidget()),
      close_full_screen_("Вернуться", &full_screen_) {
    this->setFixedSize(this->parentWidget()->size() * 0.4);
    full_screen_.setFixedSize(parent->size());
    full_screen_.hide();
    rent_button_.setFixedSize(this->size());
    std::string full_image_path = std::string{PROJECT_SOURCE_DIR} + "/imgs/" + car.picture_path.toUtf8().data();
    if (!exists(std::filesystem::path(full_image_path)) ||
        std::filesystem::is_directory(full_image_path) ||
        std::filesystem::path(full_image_path).extension() != ".png") {
        std::cout << "ERROR";
        exit(-1);
    }
    rent_button_.setIcon(QIcon(QPixmap(QString(full_image_path.c_str()))));
    rent_button_.setIconSize(this->size());

    QObject::connect(&rent_button_, SIGNAL(clicked()), this, SLOT(openFullScreen()));
    QObject::connect(&close_full_screen_, SIGNAL(clicked()), this, SLOT(closeFullScreen()));
}

void CarCardWindow::openFullScreen() {
    this->parentWidget()->hide();
    full_screen_.show();
}

void CarCardWindow::closeFullScreen() {
    this->parentWidget()->show();
    full_screen_.hide();
}
//CarCardWindow::CarCardWindow(const CarCardWindow &other) {
//    full_screen_ =
//}
