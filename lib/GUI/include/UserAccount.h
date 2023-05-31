#ifndef CARPROJECT_LIB_GUI_INCLUDE_USERACCOUNT_H_
#define CARPROJECT_LIB_GUI_INCLUDE_USERACCOUNT_H_

#include "QT-config.h"
#include "GeneralDB.h"
#include <tuple>

class UserAccount: public QWidget {
Q_OBJECT
public:
    explicit UserAccount(QMainWindow* parent);
private:
    QTableWidget* user_story_table_;
public slots:
    void showUserAccount(uint64_t);
    void hideUserAccount();
signals:
    void returnToUserWindow();
};

#endif //CARPROJECT_LIB_GUI_INCLUDE_USERACCOUNT_H_
