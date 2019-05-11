#ifndef NOTEADDINGDIALOG_H
#define NOTEADDINGDIALOG_H

#include <QDialog>

namespace Ui {
class NoteAddingDialog;
}

class NoteAddingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NoteAddingDialog(QWidget *parent = nullptr);
    ~NoteAddingDialog();

    void accept() override;

signals:
    void noteAdded(const QString note);


private:
    Ui::NoteAddingDialog *ui;
};

#endif // NOTEADDINGDIALOG_H
