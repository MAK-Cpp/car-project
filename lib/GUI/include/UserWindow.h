#ifndef CARPROJECT_LIB_GUI_INCLUDE_USERWINDOW_H_
#define CARPROJECT_LIB_GUI_INCLUDE_USERWINDOW_H_

#include "QT-config.h"
#include "CarCardWindow.h"
#include <vector>

class UserWindow : public QWidget {
Q_OBJECT
public:
    explicit UserWindow(QMainWindow *parent, const std::vector<Car> &cars);
private:
    QGridLayout *grid_layout_;
    QVBoxLayout *vertical_layout_;
    QHBoxLayout *horisontal_layout_;
    QScrollArea scroll_area_;
    QWidget buttons_container_;
    QWidget search_container_;
};

#endif //CARPROJECT_LIB_GUI_INCLUDE_USERWINDOW_H_
