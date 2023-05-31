#include "CarCardWindow.h"
#include <iostream>
#include <filesystem>
#include <exception>

CarCardWindow::CarCardWindow(const QWidget *parent, const Car &car)
    : QWidget(const_cast<QWidget*>(parent)),
      rent_button_(this),
      full_screen_(parent->parentWidget()),
      close_full_screen_("Вернуться", &full_screen_),
      car_name_((car.name + "\n" + car.town).c_str()),
      car_id_{car.car_id} {
    this->setFixedSize(this->parentWidget()->size() * 0.4);
    this->setLayout(&vertical_layout_);

    full_screen_.setFixedSize(parent->size());
    full_screen_.setLayout(&grid_layout_);
    full_screen_.hide();

    rent_button_.setFixedSize(this->size());
    std::string full_image_path = std::string{PROJECT_SOURCE_DIR} + "/imgs/" + car.picture_path;
    if (!exists(std::filesystem::path(full_image_path)) ||
        std::filesystem::is_directory(full_image_path) ||
        std::filesystem::path(full_image_path).extension() != ".png") {
        throw std::filesystem::filesystem_error(full_image_path + " CANNOT BE OPENED!", std::error_code());
    }
    car_image_pixmap_ = *new QPixmap(QString(full_image_path.c_str()));
    rent_button_.setIcon(QIcon(car_image_pixmap_.scaled(
        this->size() * (static_cast<double>(car_image_pixmap_.width()) / this->width()))));
    rent_button_.setIconSize(this->size());

    full_screen_.setPixmap(car_image_pixmap_.scaled(full_screen_.size()));
    grid_layout_.setContentsMargins(0, 0, 0, 0);
    grid_layout_.setVerticalSpacing(0);
    grid_layout_.setSpacing(0);
    close_full_screen_.setFont(QFont(close_full_screen_.font().family(), 14));
    close_full_screen_.setStyleSheet("background-color: rgba(220, 20, 60, 1.0); border: none;");
    full_description_ = new QLabel(("Марка: " + car.brand +
        "\nРасход топлива: " + std::to_string(car.consumption) +
        "\nВместимость: " + std::to_string(car.capacity) +
        "\nТопливо: " + car.fuel +
        "\nЦена (за 1 день): " + std::to_string(static_cast<int>(car.price * price_coefficient.at(car.town).first)) + " " + price_coefficient.at(car.town).second).c_str());
    full_description_->setStyleSheet("background-color: rgba(0, 0, 0, 0.8); color: rgba(255, 255, 255, 1.0);");
    full_description_->setFont(QFont(full_description_->font().family(), 30));
    grid_layout_.addWidget(full_description_);
    grid_layout_.setAlignment(full_description_, Qt::AlignCenter);
    QPushButton *full_rent_button = new QPushButton("Арендовать!");
    full_rent_button->setFixedWidth(parent->width() / 2);
    full_rent_button->setStyleSheet("background-color: rgba(46, 204, 113, 1.0); border: none;");
    full_rent_button->setFont(QFont(full_rent_button->font().family(), 40));
    grid_layout_.addWidget(full_rent_button);
    grid_layout_.setAlignment(full_rent_button, Qt::AlignHCenter);

    vertical_layout_.addWidget(&car_name_);
    vertical_layout_.setAlignment(&car_name_, Qt::AlignLeft | Qt::AlignBottom);
    vertical_layout_.setContentsMargins(0, 0, 0, 0);

    car_name_.setStyleSheet("background-color: rgba(0, 0, 0, 0.8);");
    car_name_.setAlignment(Qt::AlignCenter);
    car_name_.setFixedWidth(this->width());
    car_name_.setFixedHeight(this->height() * 0.2);
    car_name_.setFont(QFont("Comic Sans", 18));

    QObject::connect(&rent_button_, SIGNAL(clicked()), this, SLOT(openFullScreen()));
    QObject::connect(&close_full_screen_, SIGNAL(clicked()), this, SLOT(closeFullScreen()));
}

CarCardWindow::CarCardWindow(const CarCardWindow &other)
    : QWidget(other.parentWidget()),
      rent_button_(this),
      full_screen_(other.parentWidget()->parentWidget()),
      close_full_screen_("Вернуться", &full_screen_),
      car_id_{other.car_id_} {
    this->setFixedSize(this->parentWidget()->size() * 0.4);
    this->setLayout(&vertical_layout_);

    car_name_.setText(other.car_name_.text());

    full_screen_.setFixedSize(other.parentWidget()->size());
    full_screen_.setLayout(&grid_layout_);
    full_screen_.hide();

    rent_button_.setFixedSize(this->size());
    car_image_pixmap_ = other.car_image_pixmap_;
    rent_button_.setIcon(QIcon(car_image_pixmap_.scaled(
        this->size() * (static_cast<double>(car_image_pixmap_.width()) / this->width()))));
    rent_button_.setIconSize(this->size());

    full_screen_.setPixmap(car_image_pixmap_.scaled(full_screen_.size()));
    grid_layout_.setContentsMargins(0, 0, 0, 0);
    grid_layout_.setVerticalSpacing(0);
    grid_layout_.setSpacing(0);
    close_full_screen_.setFont(QFont(close_full_screen_.font().family(), 14));
    close_full_screen_.setStyleSheet("background-color: rgba(220, 20, 60, 1.0); border: none;");
    full_description_ = new QLabel(other.full_description_->text());
    full_description_->setStyleSheet("background-color: rgba(0, 0, 0, 0.8); color: rgba(255, 255, 255, 1.0);");
    full_description_->setFont(QFont(full_description_->font().family(), 30));
    grid_layout_.addWidget(full_description_);
    grid_layout_.setAlignment(full_description_, Qt::AlignCenter);
    QPushButton *full_rent_button = new QPushButton("Арендовать!");
    full_rent_button->setFixedWidth(other.parentWidget()->width() / 2);
    full_rent_button->setStyleSheet("background-color: rgba(46, 204, 113, 1.0); border: none;");
    full_rent_button->setFont(QFont(full_rent_button->font().family(), 40));
    grid_layout_.addWidget(full_rent_button);
    grid_layout_.setAlignment(full_rent_button, Qt::AlignHCenter);

    vertical_layout_.addWidget(&car_name_);
    vertical_layout_.setAlignment(&car_name_, Qt::AlignLeft | Qt::AlignBottom);
    vertical_layout_.setContentsMargins(0, 0, 0, 0);

    car_name_.setStyleSheet("background-color: rgba(0, 0, 0, 0.8);");
    car_name_.setAlignment(Qt::AlignCenter);
    car_name_.setFixedWidth(this->width());
    car_name_.setFixedHeight(this->height() * 0.2);
    car_name_.setFont(QFont("Comic Sans", 18));

    QObject::connect(&rent_button_, SIGNAL(clicked()), this, SLOT(openFullScreen()));
    QObject::connect(&close_full_screen_, SIGNAL(clicked()), this, SLOT(closeFullScreen()));
    QObject::connect(full_rent_button, SIGNAL(clicked()), this, SIGNAL(makeRent()));
}

CarCardWindow& CarCardWindow::operator=(const CarCardWindow& other) {
    this->setParent(other.parentWidget());
    full_screen_.setParent(other.parentWidget()->parentWidget());
    car_id_ = other.car_id_;

    this->setFixedSize(this->parentWidget()->size() * 0.4);
    this->setLayout(&vertical_layout_);

    car_name_.setText(other.car_name_.text());

    full_screen_.setFixedSize(other.parentWidget()->size());
    full_screen_.setLayout(&grid_layout_);
    full_screen_.hide();

    rent_button_.setFixedSize(this->size());
    car_image_pixmap_ = other.car_image_pixmap_;
    rent_button_.setIcon(QIcon(car_image_pixmap_.scaled(
        this->size() * (static_cast<double>(car_image_pixmap_.width()) / this->width()))));
    rent_button_.setIconSize(this->size());

    full_screen_.setPixmap(car_image_pixmap_.scaled(full_screen_.size()));
    grid_layout_.setContentsMargins(0, 0, 0, 0);
    grid_layout_.setVerticalSpacing(0);
    grid_layout_.setSpacing(0);
    close_full_screen_.setFont(QFont(close_full_screen_.font().family(), 14));
    close_full_screen_.setStyleSheet("background-color: rgba(220, 20, 60, 1.0); border: none;");
    full_description_ = new QLabel(other.full_description_->text());
    full_description_->setStyleSheet("background-color: rgba(0, 0, 0, 0.8); color: rgba(255, 255, 255, 1.0);");
    full_description_->setFont(QFont(full_description_->font().family(), 30));
    grid_layout_.addWidget(full_description_);
    grid_layout_.setAlignment(full_description_, Qt::AlignCenter);
    QPushButton *full_rent_button = new QPushButton("Арендовать!");
    full_rent_button->setFixedWidth(other.parentWidget()->width() / 2);
    full_rent_button->setStyleSheet("background-color: rgba(46, 204, 113, 1.0); border: none;");
    full_rent_button->setFont(QFont(full_rent_button->font().family(), 40));
    grid_layout_.addWidget(full_rent_button);
    grid_layout_.setAlignment(full_rent_button, Qt::AlignHCenter);

    vertical_layout_.addWidget(&car_name_);
    vertical_layout_.setAlignment(&car_name_, Qt::AlignLeft | Qt::AlignBottom);
    vertical_layout_.setContentsMargins(0, 0, 0, 0);

    car_name_.setStyleSheet("background-color: rgba(0, 0, 0, 0.8);");
    car_name_.setAlignment(Qt::AlignCenter);
    car_name_.setFixedWidth(this->width());
    car_name_.setFixedHeight(this->height() * 0.2);
    car_name_.setFont(QFont("Comic Sans", 18));

    QObject::connect(&rent_button_, SIGNAL(clicked()), this, SLOT(openFullScreen()));
    QObject::connect(&close_full_screen_, SIGNAL(clicked()), this, SLOT(closeFullScreen()));

    return *this;
}

void CarCardWindow::openFullScreen() {
    full_screen_.show();
    emit showFullScreen();
}

void CarCardWindow::closeFullScreen() {
    full_screen_.hide();
    emit hideFullScreen();
}

uint64_t CarCardWindow::car_id() const {
    return car_id_;
}

