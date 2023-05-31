#ifndef CARPROJECT_LIB_GUI_INCLUDE_USERWINDOW_H_
#define CARPROJECT_LIB_GUI_INCLUDE_USERWINDOW_H_

#include "QT-config.h"
#include "CarCardWindow.h"
#include "UserAccount.h"
#include <vector>
#include <QVector>


class UserWindow : public QWidget {
Q_OBJECT
public:
    explicit UserWindow(QMainWindow *parent, const std::vector<Car> &&cars);
    void mousePressEvent ( QMouseEvent * event ) override;
protected:
    void addNewCarButton(const Car& car, int i, int j);
private:
    uint64_t user_id_;
    QCalendarWidget start_calendar_widget_;
    QCalendarWidget end_calendar_widget_;
    QComboBox *towns_;
    QGridLayout *grid_layout_;
    QVBoxLayout *vertical_layout_;
    QHBoxLayout *horisontal_layout_;
    QScrollArea scroll_area_;
    QLineEdit *search_bar_;
    QWidget buttons_container_;
    QWidget search_container_;
    QDate start_date_;
    QDate end_date_;
    QPushButton exit_;
    QPushButton start_calendar_button_;
    QPushButton end_calendar_button_;
    inline static QString date_format_ = "dd.MM.yyyy";
    std::vector <Car> cars_buttons_;
public slots:
    void freeScreenForFullScreen();
    void returScreenFromFullScreen();
    void returToLoginWindow();
    void showUserAccount();
    void StartCalendarVisibility();
    void EndCalendarVisibility();
    void SetStartData(QDate);
    void SetEndData(QDate);
    void MakeRequest();
    void showWithUserID(uint64_t);
    void Rent(uint64_t, uint64_t);
signals:
    void changeToLoginWindow();
    void changeToUserAccount(uint64_t);
};

#endif //CARPROJECT_LIB_GUI_INCLUDE_USERWINDOW_H_
