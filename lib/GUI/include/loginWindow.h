#ifndef CARPROJECT_LIB_GUI_INCLUDE_LOGINWINDOW_H_
#define CARPROJECT_LIB_GUI_INCLUDE_LOGINWINDOW_H_

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QObject>
#include <QMouseEvent>
#include <QString>
#include <QByteArray>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPalette>

#include <string>


class loginWindow : public QWidget {
    Q_OBJECT
public:
    explicit loginWindow(QWidget* parent = nullptr, int w = 800, int h = 600);
    void mousePressEvent ( QMouseEvent * event ) override;
public slots:
    void showUserWindow();
signals:
    void changeToUserWindow();
    void changeToRegistrationWindow();
private:
    QVBoxLayout vertical_box_layout_;
    QFormLayout form_layout_;
    QLineEdit login_input_;
    QLineEdit password_input_;
    QLabel login_;
    QLabel password_;
    QLabel error_;
    QLabel name_;
    QPushButton login_button_;
    QPushButton register_button_;
};

#endif //CARPROJECT_LIB_GUI_INCLUDE_LOGINWINDOW_H_
