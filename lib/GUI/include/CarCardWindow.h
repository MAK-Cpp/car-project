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
    explicit CarCardWindow(const QWidget *parent, const Car& car);
    [[nodiscard]] uint64_t car_id() const;
private:
    QLabel full_screen_;
    QPushButton rent_button_;
    QPushButton close_full_screen_;
    QPushButton car_image_button_;
    QVBoxLayout vertical_layout_;
    QGridLayout grid_layout_;
    QLabel car_name_;
    QPixmap car_image_pixmap_;
    uint64_t car_id_;
    uint64_t car_price_;
    QLabel *full_description_;
public slots:
    void openFullScreen();
    void closeFullScreen();
    void callRent();
signals:
    void showFullScreen();
    void hideFullScreen();
    void makeRent(uint64_t, uint64_t);
};

#endif //CARPROJECT_LIB_GUI_INCLUDE_CARCARDWINDOW_H_
