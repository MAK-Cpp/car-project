#ifndef CARPROJECT_LIB_GUI_INCLUDE_USERWINDOW_H_
#define CARPROJECT_LIB_GUI_INCLUDE_USERWINDOW_H_

#include <QWidget>


class userWindow : public QWidget{
Q_OBJECT
public:
    explicit userWindow(int w = 800, int h = 600, QWidget* parent = nullptr);
};

#endif //CARPROJECT_LIB_GUI_INCLUDE_USERWINDOW_H_
