#ifndef CARPROJECT_LIB_GUI_INCLUDE_CARCARDWINDOW_H_
#define CARPROJECT_LIB_GUI_INCLUDE_CARCARDWINDOW_H_

#include "QT-config.h"
#include "GeneralDB.h"

class CarCardWindow : public QWidget{
Q_OBJECT
public:
    explicit CarCardWindow(QWidget *parent, const Car& car);
private:
    QWidget full_screen_;
    QPushButton rent_button_;
    QPushButton close_full_screen_;
public slots:
    void openFullScreen();
    void closeFullScreen();
};

#endif //CARPROJECT_LIB_GUI_INCLUDE_CARCARDWINDOW_H_
