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
      start_calendar_widget_(this),
      end_calendar_widget_(this),
      exit_("Выйти"),
      start_calendar_button_("С: "),
      end_calendar_button_("По: "){

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
    search_container_.setContentsMargins(0, 0, 0, 0);
    search_container_.setFixedSize(this->width(), this->height() * 0.1);
    search_container_.setPalette(QPalette(QPalette::Window, Qt::darkGray));
    search_container_.setAutoFillBackground(true);
    exit_.setFixedSize(search_container_.height() * 0.8, search_container_.height() * 0.8);

    horisontal_layout_->setAlignment(Qt::AlignVCenter);

    search_bar_ = new QLineEdit();
    search_bar_->setFixedHeight(search_container_.height() * 0.8);
    search_bar_->setFixedWidth(search_container_.width() * 0.3);
    search_bar_->setPalette(QPalette(QPalette::Window, Qt::white));
    search_bar_->setAutoFillBackground(true);

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
    horisontal_layout_->addWidget(search_bar_);
    horisontal_layout_->addWidget(&start_calendar_button_);
    horisontal_layout_->addWidget(&end_calendar_button_);
    horisontal_layout_->setAlignment(&exit_, Qt::AlignLeft);
    horisontal_layout_->setAlignment(search_bar_, Qt::AlignLeft);
    horisontal_layout_->setAlignment(&start_calendar_button_, Qt::AlignRight);
    horisontal_layout_->setAlignment(&end_calendar_button_, Qt::AlignRight);



    scroll_area_.setFixedWidth(this->width());
    scroll_area_.setFixedHeight(this->height() - search_container_.height());
    buttons_container_.setFixedWidth(this->width());

    for (int i = 0; i < cars.size(); ++i) {
        addNewCarButton(cars[i], (i >> 1), (i & 1));
    }
    grid_layout_->setVerticalSpacing(this->height() / 20);

    buttons_container_.setLayout(grid_layout_);

    scroll_area_.setWidget(&buttons_container_);
    scroll_area_.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QObject::connect(&exit_, SIGNAL(clicked()), this, SLOT(returToLoginWindow()));

    start_calendar_widget_.raise();
    start_calendar_widget_.move((this->width() - start_calendar_widget_.width()) / 2, search_container_.height());
    end_calendar_widget_.raise();
    end_calendar_widget_.move((this->width() - end_calendar_widget_.width()) / 2, search_container_.height());
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
    }
}


