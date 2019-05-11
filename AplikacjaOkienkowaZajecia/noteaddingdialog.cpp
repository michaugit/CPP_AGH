#include "noteaddingdialog.h"
#include "ui_noteaddingdialog.h"

NoteAddingDialog::NoteAddingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoteAddingDialog)
{
    ui->setupUi(this);
}

NoteAddingDialog::~NoteAddingDialog()
{
    delete ui;
}

void NoteAddingDialog::accept()
{
   const auto note= ui->textEdit->toPlainText();
   if(!note.isEmpty()){
       emit noteAdded(note);
       QDialog::accept();
   }
}
