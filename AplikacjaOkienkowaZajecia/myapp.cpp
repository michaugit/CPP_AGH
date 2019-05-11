#include "noteaddingdialog.h"
#include "myapp.h"
#include "ui_myapp.h"
#include <QDebug>

MyApp::MyApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyApp)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());


    connect(ui->Calendar, &QCalendarWidget::clicked, this, &MyApp::onCalendarClicked  );
    connect(ui->pushButton, &QPushButton::clicked, this, &MyApp::onButtonClicked );
}

MyApp::~MyApp()
{
    delete ui;
}

void MyApp::onCalendarClicked(const QDate &date)
{

    //qDebug()<<date;
    ui->dateTimeEdit->setDate(date);
}
void MyApp::onButtonClicked()
{
    //ui->listWidget->addItem("Nowe wydarzenie!");
    //qDebug()<<"KLIKNIETO!";
    auto note=new NoteAddingDialog(this);
    connect(note, &NoteAddingDialog::noteAdded, this, &MyApp::onNoteAdded);
    note->show();
}

void MyApp::onNoteAdded(QString note)
{
    ui->listWidget->addItem(ui->dateTimeEdit->dateTime().toString()+" "+note);
}
