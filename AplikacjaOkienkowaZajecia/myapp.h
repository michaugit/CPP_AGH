#ifndef MYAPP_H
#define MYAPP_H

#include <QMainWindow>

namespace Ui {
class MyApp;
}

class MyApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyApp(QWidget *parent = nullptr);
    ~MyApp();

public slots:
    void onCalendarClicked(const QDate &date);
    void onButtonClicked();
    void onNoteAdded(QString note);

private:
    Ui::MyApp *ui;
};

#endif // MYAPP_H
