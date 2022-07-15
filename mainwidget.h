#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "newpatient.h"
#include "patientwidget.h"
#include "searchpatient.h"
#include "doctor/order.h"

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_pushButton_newPatient_released();

    void dealOpenPatient(const QModelIndex &index);
    void dealChangeToPatientWidget(QString ID);

    void on_pushButton_searchPatient_released();

    void addPatientItem(QString str);

    void on_pushButton_checkOrder_released();

    void dealNewConnection();
    void dealAcceptError(QAbstractSocket::SocketError socketError);

private:
    Ui::MainWidget *ui;
    NewPatient* newPatient;
    PatientWidget *patientWidget;
    SearchPatient *searchPatient;
    QTcpServer *tcpServer;

    QSqlDatabase db;
};

#endif // MAINWIDGET_H
