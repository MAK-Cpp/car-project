#include "RootWindow.h"

#include <iostream>
#include <filesystem>

RootWindow::RootWindow(QMainWindow *parent) : QWidget(parent) {
//    this->setFixedSize(parent->size());
    QVBoxLayout *vertical_layout = new QVBoxLayout();
    picture_path_button_ = new QPushButton("ВЫБЕРИТЕ ПУТЬ");
    QObject::connect(picture_path_button_, SIGNAL(clicked()), this, SLOT(searchPicture()));

    name_line_edit_ = new QLineEdit();
    price_line_edit_ = new QLineEdit();
    consumption_line_edit_ = new QLineEdit();
    capacity_line_edit_ = new QLineEdit();
    fuel_line_edit_ = new QLineEdit();
    town_combo_box_ = new QComboBox();
    town_combo_box_->insertItem(0, "ВЫБЕРИТЕ ГОРОД");
    int id = 1;
    for (auto x : price_coefficient) {
        town_combo_box_->insertItem(id, x.first.c_str());
        id++;
    }
    color_line_edit_ = new QLineEdit();
    brand_line_edit_ = new QLineEdit();

    vertical_layout->addWidget(new QLabel("Название машины:"));
    vertical_layout->addWidget(name_line_edit_);
    vertical_layout->addWidget(new QLabel("Стоимость за аренду (в рублях):"));
    vertical_layout->addWidget(price_line_edit_);
    vertical_layout->addWidget(new QLabel("Сколько машина потребляет:"));
    vertical_layout->addWidget(consumption_line_edit_);
    vertical_layout->addWidget(new QLabel("Вместимость автомобиля (в литрах):"));
    vertical_layout->addWidget(capacity_line_edit_);
    vertical_layout->addWidget(new QLabel("Тип топлива:"));
    vertical_layout->addWidget(fuel_line_edit_);
    vertical_layout->addWidget(new QLabel("Выберите файл изображения машины:"));
    vertical_layout->addWidget(picture_path_button_);
    vertical_layout->addWidget(new QLabel("Город, в котором можно арендовать машину:"));
    vertical_layout->addWidget(town_combo_box_);
    vertical_layout->addWidget(new QLabel("Цвет машины: "));
    vertical_layout->addWidget(color_line_edit_);
    vertical_layout->addWidget(new QLabel("Бренд автомобиля:"));
    vertical_layout->addWidget(brand_line_edit_);

    QPushButton *add_button_ = new QPushButton("Добавить машину!");
    QPushButton *return_button_ = new QPushButton("Назад.");
    QObject::connect(add_button_, SIGNAL(clicked()), this, SLOT(addCar()));
    QObject::connect(return_button_, SIGNAL(clicked()), this, SLOT(hideRootWindow()));
    vertical_layout->addWidget(add_button_);
    vertical_layout->addWidget(return_button_);

    name_line_edit_->setStyleSheet("background-color : rgb(238, 227, 203); color : black; border : none;");
    price_line_edit_->setStyleSheet("background-color : rgb(238, 227, 203); color : black; border : none;");
    consumption_line_edit_->setStyleSheet("background-color : rgb(238, 227, 203); color : black; border : none;");
    capacity_line_edit_->setStyleSheet("background-color : rgb(238, 227, 203); color : black; border : none;");
    fuel_line_edit_->setStyleSheet("background-color : rgb(238, 227, 203); color : black; border : none;");
    color_line_edit_->setStyleSheet("background-color : rgb(238, 227, 203); color : black; border : none;");
    brand_line_edit_->setStyleSheet("background-color : rgb(238, 227, 203); color : black; border : none;");
    town_combo_box_->setStyleSheet("background-color: rgb(215, 192, 174); color: black;");
    picture_path_button_->setStyleSheet("color : black; background-color: rgb(215, 192, 174);");
    add_button_->setStyleSheet("color : black; background-color: rgb(215, 192, 174);");
    return_button_->setStyleSheet("color : black; background-color: rgb(215, 192, 174);");

    vertical_layout->setAlignment(Qt::AlignHCenter);
    this->setLayout(vertical_layout);
    this->adjustSize();
    this->setFixedWidth(parent->width());
}

void RootWindow::searchPicture() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Images (*.png)"));
    dialog.exec();
    if (dialog.selectedFiles().size() == 0) {
        return;
    }
    std::filesystem::path file = dialog.selectedFiles()[0].toUtf8().data();
    if (file.parent_path() == PROJECT_SOURCE_DIR "/imgs") {
        QMessageBox msgBox;
        msgBox.setText("ОШИБКА: нельзя использовать эту директорию, выберите другую.");
        msgBox.exec();
        return;
    }
    if (std::filesystem::exists(std::string{PROJECT_SOURCE_DIR} + "/imgs/" + file.filename().string())) {
        QMessageBox msgBox;
        msgBox.setText("ОШИБКА: данный файл уже существует, пожалуйста, выберите другой.");
        msgBox.exec();
        return;
    }
    picture_path_button_->setText(file.string().c_str());

}

void RootWindow::addCar() {
    std::filesystem::path file = picture_path_button_->text().toUtf8().data();
    if (!std::filesystem::exists(file)) {
        QMessageBox msgBox;
        msgBox.setText("ОШИБКА: файл отсутствует.");
        msgBox.exec();
        return;
    }
    if (name_line_edit_->text().isEmpty() ||
        price_line_edit_->text().isEmpty() ||
        consumption_line_edit_->text().isEmpty() ||
        capacity_line_edit_->text().isEmpty() ||
        fuel_line_edit_->text().isEmpty() ||
        picture_path_button_->text().isEmpty() ||
        (town_combo_box_->currentIndex() == 0) ||
        color_line_edit_->text().isEmpty() ||
        brand_line_edit_->text().isEmpty()) {
        QMessageBox msgBox;
        msgBox.setText("ОШИБКА: необходимо заполнить все поля!");
        msgBox.exec();
        return;
    }
    try {
        Car new_car(
            0,
            name_line_edit_->text().toUtf8().data(),
            std::stoull(price_line_edit_->text().toUtf8().data()),
            std::stod(consumption_line_edit_->text().toUtf8().data()),
            std::stoull(capacity_line_edit_->text().toUtf8().data()),
            fuel_line_edit_->text().toUtf8().data(),
            file.filename().string().c_str(),
            town_combo_box_->currentText().toUtf8().data(),
            color_line_edit_->text().toUtf8().data(),
            brand_line_edit_->text().toUtf8().data()
        );
        new_car.car_id = GeneralDB::insert_car(new_car);
        std::filesystem::copy_file(file, std::string{PROJECT_SOURCE_DIR} + "/imgs/" + file.filename().string());
        emit addCarToUserWindow(new_car);
        name_line_edit_->clear();
        price_line_edit_->clear();
        consumption_line_edit_->clear();
        capacity_line_edit_->clear();
        fuel_line_edit_->clear();
        picture_path_button_->setText("ВЫБЕРИТЕ ПУТЬ");
        town_combo_box_->setCurrentIndex(0);
        color_line_edit_->clear();
        brand_line_edit_->clear();
        QMessageBox msgBox;
        msgBox.setText("Машина добавлена!");
        msgBox.exec();
    } catch (...) {
        QMessageBox msgBox;
        msgBox.setText(
            "ОШИБКА: при добавлении машины произошла ошибка, убедитесь, что все поля заполнены верно и попробуйте еще раз.");
        msgBox.exec();
        return;
    }
}

void RootWindow::hideRootWindow() {
    name_line_edit_->clear();
    price_line_edit_->clear();
    consumption_line_edit_->clear();
    capacity_line_edit_->clear();
    fuel_line_edit_->clear();
    picture_path_button_->setText("ВЫБЕРИТЕ ПУТЬ");
    town_combo_box_->setCurrentIndex(0);
    color_line_edit_->clear();
    brand_line_edit_->clear();
    this->hide();
    emit returnToUserWindow();
}
