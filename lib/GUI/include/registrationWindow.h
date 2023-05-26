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

#ifndef QT_COMPILING_QSTRING_COMPAT_CPP
#define QT_COMPILING_QSTRING_COMPAT_CPP
#endif

class registrationWindow : public QWidget{
    Q_OBJECT
public:
    explicit registrationWindow(QWidget* parent = nullptr, int w = 800, int h = 600);
    void mousePressEvent ( QMouseEvent * event ) override;
public slots:
    void registerUser();
signals:
    void changeToLoginWindow();
private:

};

#endif //CARPROJECT_LIB_GUI_INCLUDE_REGISTRATIONWINDOW_H_
