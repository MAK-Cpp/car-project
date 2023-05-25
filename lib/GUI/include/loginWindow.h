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

#include <string>


class loginWindow : public QWidget {
    Q_OBJECT

public:
    explicit loginWindow(QWidget* parent = nullptr, int w = 800, int h = 600);
    void mousePressEvent ( QMouseEvent * event ) override;
public slots:
    void showUserWindow();
signals:
    void changeWindow();
private:
    QVBoxLayout layout_;
    QLineEdit login_input_;
    QLineEdit password_input_;
    QPushButton login_button_;
};

#endif //CARPROJECT_LIB_GUI_INCLUDE_LOGINWINDOW_H_
