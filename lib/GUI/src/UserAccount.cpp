#include "UserAccount.h"

#include <iostream>

UserAccount::UserAccount(QMainWindow *parent): QWidget(parent) {

}
void UserAccount::showUserAccount(uint64_t user_id) {
    std::cout << user_id << " is in his account!\n";
}
