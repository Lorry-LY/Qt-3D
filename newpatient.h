#ifndef NEWPATIENT_H
#define NEWPATIENT_H

#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QRadioButton>
#include <QComboBox>
#include <QVector>
#include <QPair>

namespace Ui {
class NewPatient;
}

class NewPatient : public QWidget
{
    Q_OBJECT

public:
    explicit NewPatient(QWidget *parent = nullptr);
    ~NewPatient();

    void init();

signals:
    void createFinished(QString str);

private slots:
    void on_pushButton_accept_released();

    void on_pushButton_back_released();

private:
    Ui::NewPatient *ui;

    QSqlDatabase db;

};

#endif // NEWPATIENT_H
