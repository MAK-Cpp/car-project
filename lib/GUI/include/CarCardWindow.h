#ifndef CARPROJECT_LIB_GUI_INCLUDE_CARCARDWINDOW_H_
#define CARPROJECT_LIB_GUI_INCLUDE_CARCARDWINDOW_H_

#include "QT-config.h"
#include "GeneralDB.h"
//
//class QPushButtonNoAnimation : public QPushButton {
//    Q_OBJECT
//public:
//    explicit QPushButtonNoAnimation(QWidget *parent);
//    void animateClick() override;
//};

class CarCardWindow : public QWidget{
Q_OBJECT
public:
    explicit CarCardWindow(QWidget *parent, const Car& car);
private:
    QLabel full_screen_;
    QPushButton rent_button_;
    QPushButton close_full_screen_;
    QPushButton car_image_button_;
    QVBoxLayout vertical_layout_;
    QGridLayout grid_layout_;
    QLabel car_name_;
    QPixmap car_image_pixmap_;
public slots:
    void openFullScreen();
    void closeFullScreen();
signals:
    void showFullScreen();
    void hideFullScreen();
};

#endif //CARPROJECT_LIB_GUI_INCLUDE_CARCARDWINDOW_H_
