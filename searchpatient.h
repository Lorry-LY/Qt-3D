#ifndef SEARCHPATIENT_H
#define SEARCHPATIENT_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

namespace Ui {
class SearchPatient;
}

class SearchPatient : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPatient(QWidget *parent = nullptr);
    ~SearchPatient();

    void init();

signals:
    void newPatient();
    void changeToPatientWidget(QString ID);

private slots:
    void on_pushButton_search_released();

    void on_pushButton_newPatient_released();

    void dealDoubleClicked(const QModelIndex &index);

private:
    Ui::SearchPatient *ui;

    QSqlDatabase db;

};

#endif // SEARCHPATIENT_H
