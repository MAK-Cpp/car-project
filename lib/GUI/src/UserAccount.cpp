#include "UserAccount.h"

#include <iostream>

UserAccount::UserAccount(QMainWindow *parent): QWidget(parent) {
    this->setFixedSize(parent->size());
    this->setPalette(parent->palette());

    QPushButton* return_button_ = new QPushButton("Назад", this);
    return_button_->setFixedWidth(this->width());
    return_button_->setFixedHeight(this->height() * 0.1);
    return_button_->move(0, this->height() - return_button_->height());

    QObject::connect(return_button_, SIGNAL(clicked()), this, SLOT(hideUserAccount()));

}
void UserAccount::showUserAccount(uint64_t user_id) {
    std::cout << user_id << " is in his account!\n";
    auto user_cars = GeneralDB::get_rented_car(user_id);
    std::cout << user_cars.size() << '\n';
    user_story_table_ = new QTableWidget(user_cars.size() + 1, 4, this);
    user_story_table_->setItem(0, 0, new QTableWidgetItem("Машина"));
    user_story_table_->setItem(0, 1, new QTableWidgetItem("Начало брони"));
    user_story_table_->setItem(0, 2, new QTableWidgetItem("Конец брони"));
    user_story_table_->setItem(0, 3, new QTableWidgetItem("Итоговая стоимость (в местной валюте)"));
    user_story_table_->setColumnWidth(0, this->width() / 4);
    user_story_table_->setColumnWidth(1, this->width() / 4);
    user_story_table_->setColumnWidth(2, this->width() / 4);
    user_story_table_->setColumnWidth(3, this->width() / 4);

    for (std::size_t i = 0; i < user_cars.size(); ++i) {
        user_story_table_->setItem(i + 1, 0, new QTableWidgetItem(std::get<0>(user_cars[i]).c_str()));
        user_story_table_->setItem(i + 1, 1, new QTableWidgetItem(std::get<1>(user_cars[i]).toString()));
        user_story_table_->setItem(i + 1, 2, new QTableWidgetItem(std::get<2>(user_cars[i]).toString()));
        user_story_table_->setItem(i + 1, 3,
                                   new QTableWidgetItem(
                                       (std::to_string(static_cast<int>(std::get<3>(user_cars[i]) * price_coefficient.at(std::get<4>(user_cars[i])).first)) + " " + price_coefficient.at(std::get<4>(user_cars[i])).second).c_str()));

    }
    user_story_table_->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    user_story_table_->horizontalHeader()->setVisible(false);
    user_story_table_->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    user_story_table_->verticalHeader()->setVisible(false);
    user_story_table_->setPalette(this->palette());
    user_story_table_->setEditTriggers(QAbstractItemView::NoEditTriggers);

    user_story_table_->setFixedWidth(this->width());
    user_story_table_->setFixedHeight(this->height() * 0.9);


    this->show();
}

void UserAccount::hideUserAccount() {
    delete user_story_table_;
    this->hide();
    emit returnToUserWindow();
}