#ifndef CARPROJECT_LIB_GUI_INCLUDE_REGISTRATIONWINDOW_H_
#define CARPROJECT_LIB_GUI_INCLUDE_REGISTRATIONWINDOW_H_

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
#include <QFontDatabase>
#include <QFontMetrics>

class registrationWindow : public QWidget {
Q_OBJECT
public:
    explicit registrationWindow(QWidget *parent);
    void mousePressEvent(QMouseEvent *event) override;
public slots:
    void registerUser();
    void showLoginWindow();
signals:
    void changeToLoginWindow();
private:
    QVBoxLayout vertical_box_layout_;
    QFormLayout form_layout_;
    QLineEdit user_name_input_;
    QLineEdit login_input_;
    QLineEdit password_input_;
    QLineEdit again_password_input_;
    QLabel user_name_;
    QLabel login_;
    QLabel password_;
    QLabel again_password_;
    QLabel error_;
    QLabel name_;
    QPushButton login_button_;
    QPushButton register_button_;
};

#endif //CARPROJECT_LIB_GUI_INCLUDE_REGISTRATIONWINDOW_H_
