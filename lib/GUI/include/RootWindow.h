#ifndef CARPROJECT_LIB_GUI_INCLUDE_ROOTWINDOW_H_
#define CARPROJECT_LIB_GUI_INCLUDE_ROOTWINDOW_H_

#include "QT-config.h"
#include "GeneralDB.h"

class RootWindow : public QWidget{
Q_OBJECT
public:
    explicit RootWindow(QMainWindow* parent);
private:
    QLineEdit* name_line_edit_;
    QLineEdit* price_line_edit_;
    QLineEdit* consumption_line_edit_;
    QLineEdit* capacity_line_edit_;
    QLineEdit* fuel_line_edit_;
    QPushButton* picture_path_button_;
    QComboBox* town_combo_box_;
    QLineEdit* color_line_edit_;
    QLineEdit* brand_line_edit_;
public slots:
    void searchPicture();
    void addCar();
    void hideRootWindow();
signals:
    void addCarToUserWindow(Car);
    void returnToUserWindow();
};

#endif //CARPROJECT_LIB_GUI_INCLUDE_ROOTWINDOW_H_
