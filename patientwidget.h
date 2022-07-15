#ifndef PATIENTWIDGET_H
#define PATIENTWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

namespace Ui {
class PatientWidget;
}

class PatientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PatientWidget(QWidget *parent = nullptr);
    ~PatientWidget();

    void init(QString ID);

signals:

private:
    Ui::PatientWidget *ui;
    QSqlDatabase db;

};

#endif // PATIENTWIDGET_H
