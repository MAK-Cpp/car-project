#include <iostream>
#include <filesystem>
#include <string>

// for SQL
#include "sqlite3.h"

#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>

#include "loginWindow.h"
#include "userWindow.h"
#include "GeneralDB.h"

int main(int argc, char *argv[]) {
    GeneralDB::init();
    std::vector<Car> ans;
    ans = GeneralDB::select_cars("sh", "20-04-2023", "27-05-2023");
    std::cout << ans.size();
    return 0;
}


