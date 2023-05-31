#include "UserWindow.h"

#include <iostream>
#include <Qpair>

void clearLayout(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while ((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void UserWindow::addNewCarButton(const Car &car, int i, int j) {
    CarCardWindow *another_car = new CarCardWindow(this, car);
    QObject::connect(another_car, SIGNAL(showFullScreen()), this, SLOT(freeScreenForFullScreen()));
    QObject::connect(another_car, SIGNAL(hideFullScreen()), this, SLOT(returScreenFromFullScreen()));
    QObject::connect(another_car, SIGNAL(makeRent(uint64_t, uint64_t)), this, SLOT(Rent(uint64_t, uint64_t)));
    grid_layout_->addWidget(another_car, i, j);
}

UserWindow::UserWindow(QMainWindow *parent, const std::vector<Car> &&cars)
    : QWidget(parent),
      scroll_area_(this),
      buttons_container_(&scroll_area_),
      start_calendar_widget_(this),
      end_calendar_widget_(this),
      exit_("Выйти"),
      start_calendar_button_("С: "),
      end_calendar_button_("По: "),
      cars_buttons_(cars){

    start_calendar_button_.setStyleSheet("color : white; background-color: gray;");
    end_calendar_button_.setStyleSheet("color : white; background-color: gray;");

    vertical_layout_ = new QVBoxLayout();
    horisontal_layout_ = new QHBoxLayout();
    grid_layout_ = new QGridLayout();

    vertical_layout_->setContentsMargins(0, 0, 0, 0);
    vertical_layout_->setSpacing(0);

    horisontal_layout_->setContentsMargins(0, 0, 0, 0);
    horisontal_layout_->setSpacing(0);

    this->setFixedSize(parent->size());
    this->setLayout(vertical_layout_);

    vertical_layout_->addWidget(&search_container_);
    vertical_layout_->addWidget(&scroll_area_);

    search_container_.setLayout(horisontal_layout_);
    search_container_.setContentsMargins(this->width() / 30, 0, this->width() / 30, 0);
    search_container_.setFixedSize(this->width(), this->height() * 0.1);
    search_container_.setPalette(QPalette(QPalette::Window, Qt::black));
    search_container_.setAutoFillBackground(true);
    exit_.setFixedSize(search_container_.height() * 0.8, search_container_.height() * 0.8);

    horisontal_layout_->setAlignment(Qt::AlignVCenter);

    towns_ = new QComboBox();
    towns_->insertItem(0, "ВЫБЕРИТЕ ГОРОД");
    int id = 1;
    for (auto x : price_coefficient) {
        towns_->insertItem(id, x.first.c_str());
        id++;
    }
    towns_->setFixedWidth(search_container_.width() * 0.2);
    towns_->setFixedHeight(search_container_.height() * 0.8);
    towns_->setStyleSheet("background-color: gray; color: red");
    towns_->setAutoFillBackground(true);

    search_bar_ = new QLineEdit();
    search_bar_->setFixedHeight(search_container_.height() * 0.4);
    search_bar_->setFixedWidth(search_container_.width() * 0.15);
    search_bar_->setPalette(QPalette(QPalette::Window, Qt::gray));
    search_bar_->setAutoFillBackground(true);

    QPushButton *search_button_ = new QPushButton("Поиск!");
    search_button_->setFixedSize(exit_.size());

    start_calendar_button_.setFixedHeight(search_container_.height() * 0.8);
    start_calendar_button_.setFixedWidth(search_container_.width() / 6);
    end_calendar_button_.setFixedHeight(search_container_.height() * 0.8);
    end_calendar_button_.setFixedWidth(search_container_.width() / 6);
    start_calendar_widget_.setFixedSize(this->size() / 2);
    start_calendar_widget_.setMinimumDate(QDate::currentDate());
    start_calendar_widget_.hide();
    end_calendar_widget_.setFixedSize(this->size() / 2);
    end_calendar_widget_.setMinimumDate(QDate::currentDate());
    end_calendar_widget_.hide();

    QObject::connect(&start_calendar_widget_, SIGNAL(clicked(QDate)), this, SLOT(SetStartData(QDate)));
    QObject::connect(&end_calendar_widget_, SIGNAL(clicked(QDate)), this, SLOT(SetEndData(QDate)));

    QObject::connect(&start_calendar_button_, SIGNAL(clicked()), this, SLOT(StartCalendarVisibility()));
    QObject::connect(&end_calendar_button_, SIGNAL(clicked()), this, SLOT(EndCalendarVisibility()));

    horisontal_layout_->addWidget(&exit_);
    horisontal_layout_->addWidget(towns_);
    horisontal_layout_->addWidget(&start_calendar_button_);
    horisontal_layout_->addWidget(&end_calendar_button_);
    horisontal_layout_->addWidget(search_bar_);
    horisontal_layout_->addWidget(search_button_);
    horisontal_layout_->setSpacing(this->width() / 40);

    scroll_area_.setFixedWidth(this->width());
    scroll_area_.setFixedHeight(this->height() - search_container_.height());
    buttons_container_.setFixedWidth(this->width());

    for (int i = 0; i < cars_buttons_.size(); ++i) {
        addNewCarButton(cars_buttons_[i], (i >> 1), (i & 1));
    }

    grid_layout_->setVerticalSpacing(this->height() / 20);

    buttons_container_.setLayout(grid_layout_);
    buttons_container_.setStyleSheet("border-style: solid; border-width: 3px; border-color: pink;");

    scroll_area_.setWidget(&buttons_container_);
    scroll_area_.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QObject::connect(&exit_, SIGNAL(clicked()), this, SLOT(returToLoginWindow()));
    QObject::connect(search_bar_, SIGNAL(returnPressed()), this, SLOT(MakeRequest()));
    QObject::connect(search_button_, SIGNAL(clicked()), this, SLOT(MakeRequest()));

    start_calendar_widget_.raise();
    start_calendar_widget_.move((this->width() - start_calendar_widget_.width()) / 2, search_container_.height());
    end_calendar_widget_.raise();
    end_calendar_widget_.move((this->width() - end_calendar_widget_.width()) / 2, search_container_.height());
}
void UserWindow::freeScreenForFullScreen() {
    this->hide();
    start_calendar_widget_.hide();
    end_calendar_widget_.hide();
}
void UserWindow::returScreenFromFullScreen() {
    this->show();
}
void UserWindow::returToLoginWindow() {
    this->hide();

    clearLayout(grid_layout_);
    delete grid_layout_;
    grid_layout_ = new QGridLayout();
    for (int i = 0, pos = 0; i < cars_buttons_.size(); ++i) {
            addNewCarButton(cars_buttons_[i], (pos >> 1), (pos & 1));
            ++pos;
    }
    grid_layout_->setContentsMargins(0, 0, 0, 0);
    grid_layout_->setSpacing(0);
    grid_layout_->setVerticalSpacing(this->height() / 20);
    buttons_container_.setLayout(grid_layout_);
    grid_layout_->update();
    buttons_container_.setFixedHeight(
        (this->height() * 0.4  + (this->height() / 20))
            * (cars_buttons_.size() + 1) / 2 - (this->height() / 20));
//    buttons_container_.adjustSize();
    buttons_container_.setContentsMargins(0, 0, 0, 0);
    buttons_container_.setStyleSheet("border-style: solid; border-width: 3px; border-color: pink;");
    scroll_area_.update();

    user_id_ = 0;
    towns_->setCurrentIndex(0);
    start_calendar_widget_.hide();
    end_calendar_widget_.hide();
    start_date_ = std::move(*new QDate());
    end_date_ = std::move(*new QDate());
    start_calendar_button_.setText("С: ");
    end_calendar_button_.setText("По: ");
    search_bar_->clear();
    emit changeToLoginWindow();
}

void UserWindow::StartCalendarVisibility() {
    end_calendar_widget_.hide();
    if (start_calendar_widget_.isHidden()) {
        start_calendar_widget_.show();
    } else {
        start_calendar_widget_.hide();
    }
}

void UserWindow::EndCalendarVisibility() {
    start_calendar_widget_.hide();
    if (end_calendar_widget_.isHidden()) {
        end_calendar_widget_.show();
    } else {
        end_calendar_widget_.hide();
    }
}

void UserWindow::SetStartData(QDate start_date) {
    start_date_ = start_date;
    if (start_date > end_date_) {
        end_date_ = start_date;
        end_calendar_button_.setText("По: " + start_date.toString(date_format_));
    }
    start_calendar_button_.setText("С: " + start_date.toString(date_format_));
    end_calendar_widget_.setMinimumDate(start_date);
}

void UserWindow::SetEndData(QDate end_date) {
    end_date_ = end_date;
    end_calendar_button_.setText("По: " + end_date.toString(date_format_));
}

void UserWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->setFocus();
        start_calendar_widget_.hide();
        end_calendar_widget_.hide();
    }
}


void UserWindow::MakeRequest() {
    QMessageBox msgBox;
    if (start_date_.isNull() || end_date_.isNull()) {
        msgBox.setText("ОШИБКА: необходимо выбрать дату!");
        msgBox.exec();
        return;
    } else if (towns_->currentIndex() == 0) {
        msgBox.setText("ОШИБКА: необходимо выбрать город!");
        msgBox.exec();
        return;
    }
    std::set<uint64_t>
        car_ids = GeneralDB::select_cars(search_bar_->text(), start_date_, end_date_, towns_->currentText());

    clearLayout(grid_layout_);
    delete grid_layout_;
    grid_layout_ = new QGridLayout();
    for (int i = 0, pos = 0; i < cars_buttons_.size(); ++i) {
        if (car_ids.find(cars_buttons_[i].car_id) != car_ids.end()) {
            addNewCarButton(cars_buttons_[i], (pos >> 1), (pos & 1));
            ++pos;
        }
    }
    grid_layout_->setContentsMargins(0, 0, 0, 0);
    grid_layout_->setSpacing(0);
    grid_layout_->setVerticalSpacing(this->height() / 20);
    buttons_container_.setLayout(grid_layout_);
    grid_layout_->update();
    buttons_container_.setFixedHeight(
        (this->height() * 0.4  + (this->height() / 20))
        * (car_ids.size() + 1) / 2 - (this->height() / 20));
//    buttons_container_.adjustSize();
    buttons_container_.setContentsMargins(0, 0, 0, 0);
    buttons_container_.setStyleSheet("border-style: solid; border-width: 3px; border-color: pink;");
    scroll_area_.update();

}

void UserWindow::showWithUserID(uint64_t id) {
    user_id_ = id;
    this->show();
}

void UserWindow::Rent(uint64_t car_id, uint64_t price) {
    QMessageBox msgBox;
    if (start_date_.isNull() || end_date_.isNull()) {
        msgBox.setText("ОШИБКА: необходимо выбрать дату!");
        msgBox.exec();
        return;
    }
    bool is_done = GeneralDB::insert_sell(user_id_, car_id, start_date_, end_date_, price * (start_date_.daysTo(end_date_)  + 1));
    if (is_done) {
        msgBox.setText("Поздравляем, вы арендовали машину! Можете посмотреть свои машины в личном кабинете.");
    } else {
        msgBox.setText("ОШИБКА: на эту дату машина уже забронирована, пожалуйста, выберите другую.");
    }
    msgBox.exec();
}

