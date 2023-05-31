#ifndef CARPROJECT_LIB_GUI_INCLUDE_USERACCOUNT_H_
#define CARPROJECT_LIB_GUI_INCLUDE_USERACCOUNT_H_

#include "QT-config.h"

class UserAccount: public QWidget {
Q_OBJECT
public:
    explicit UserAccount(QMainWindow* parent);
public slots:
    void showUserAccount(uint64_t);
};

#endif //CARPROJECT_LIB_GUI_INCLUDE_USERACCOUNT_H_
