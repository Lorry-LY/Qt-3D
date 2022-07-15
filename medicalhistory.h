#ifndef MEDICALHISTORY_H
#define MEDICALHISTORY_H

#include <QWidget>

namespace Ui {
class MedicalHistory;
}

class MedicalHistory : public QWidget
{
    Q_OBJECT

public:
    explicit MedicalHistory(QWidget *parent = nullptr);
    ~MedicalHistory();

private:
    Ui::MedicalHistory *ui;
};

#endif // MEDICALHISTORY_H
