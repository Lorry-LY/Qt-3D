#include "medicalhistory.h"
#include "ui_medicalhistory.h"

MedicalHistory::MedicalHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MedicalHistory)
{
    ui->setupUi(this);
}

MedicalHistory::~MedicalHistory()
{
    delete ui;
}
