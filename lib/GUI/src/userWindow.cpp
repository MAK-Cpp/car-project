#include "userWindow.h"


userWindow::userWindow(QWidget* parent): QWidget(parent) {
    this->setFixedSize(parent->width(), parent->height());
}
