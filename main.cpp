#include "mainwidget.h"
#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("project.db");
    if(!db.open())
    {
        qDebug()<<"数据库没有打开。";
        return -1;
    }
    MainWindow w;
    w.show();
    return a.exec();
}
