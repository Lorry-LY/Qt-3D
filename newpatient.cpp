#include "newpatient.h"
#include "ui_newpatient.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>

NewPatient::NewPatient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewPatient)
{
    ui->setupUi(this);

    db = QSqlDatabase::database();

    connect(ui->comboBox_threeGenerations,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int index){
        if(index == 1){
            ui->lineEdit_threeGenerations->clear();
            ui->lineEdit_threeGenerations->show();
        }else{
            ui->lineEdit_threeGenerations->hide();
        }
    });
    ui->lineEdit_threeGenerations->hide();

    QGridLayout *layout_pastMedical = new QGridLayout(ui->widget_pastMedical);
    layout_pastMedical->setSpacing(0);
    layout_pastMedical->setObjectName("layout_pastMedical");

    QGridLayout *layout_pharmaco = new QGridLayout(ui->widget_pharmaco);
    layout_pharmaco->setSpacing(0);
    layout_pharmaco->setObjectName("layout_pharmaco");

    QGridLayout *layout_allergic = new QGridLayout(ui->widget_allergic);
    layout_allergic->setSpacing(0);
    layout_allergic->setObjectName("layout_allergic");

    QGridLayout *layout_badHabits = new QGridLayout(ui->widget_badHabits);
    layout_badHabits->setSpacing(0);
    layout_badHabits->setObjectName("layout_badHabits");

    QHBoxLayout* layout_orthodontics = new QHBoxLayout(ui->widget_orthodontics);
    layout_orthodontics->setObjectName("layout_Orthodontics");
    QRadioButton *radio_orthodontics_yes = new QRadioButton(ui->widget_orthodontics);
    radio_orthodontics_yes->setObjectName("radio_orthodontics_yes");
    radio_orthodontics_yes->setText("是");
    radio_orthodontics_yes->setChecked(false);
    radio_orthodontics_yes->setMaximumSize(QSize(50,21));
    radio_orthodontics_yes->setMinimumSize(QSize(50,21));
    layout_orthodontics->addWidget(radio_orthodontics_yes);
    QRadioButton *radio_orthodontics_no = new QRadioButton(ui->widget_orthodontics);
    radio_orthodontics_no->setObjectName("radio_orthodontics_no");
    radio_orthodontics_no->setText("否");
    radio_orthodontics_no->setChecked(true);
    radio_orthodontics_no->setMaximumSize(QSize(50,21));
    radio_orthodontics_no->setMinimumSize(QSize(50,21));
    layout_orthodontics->addWidget(radio_orthodontics_no);

    QHBoxLayout* layout_NSCLP = new QHBoxLayout(ui->widget_NSCLP);
    layout_NSCLP->setObjectName("layout_NSCLP");
    QRadioButton *radio_NSCLP_yes = new QRadioButton(ui->widget_NSCLP);
    radio_NSCLP_yes->setObjectName("radio_NSCLP_yes");
    radio_NSCLP_yes->setText("是");
    radio_NSCLP_yes->setChecked(false);
    radio_NSCLP_yes->setMaximumSize(QSize(50,21));
    radio_NSCLP_yes->setMinimumSize(QSize(50,21));
    layout_NSCLP->addWidget(radio_NSCLP_yes);
    QRadioButton *radio_NSCLP_no = new QRadioButton(ui->widget_NSCLP);
    radio_NSCLP_no->setObjectName("radio_NSCLP_no");
    radio_NSCLP_no->setText("否");
    radio_NSCLP_no->setChecked(true);
    radio_NSCLP_no->setMaximumSize(QSize(50,21));
    radio_NSCLP_no->setMinimumSize(QSize(50,21));
    layout_NSCLP->addWidget(radio_NSCLP_no);


    QHBoxLayout* layout_trauma = new QHBoxLayout(ui->widget_trauma);
    layout_trauma->setObjectName("layout_trauma");
    QRadioButton *radio_trauma_yes = new QRadioButton(ui->widget_trauma);
    radio_trauma_yes->setObjectName("radio_trauma_yes");
    radio_trauma_yes->setText("有");
    radio_trauma_yes->setChecked(false);
    radio_trauma_yes->setMaximumSize(QSize(50,21));
    radio_trauma_yes->setMinimumSize(QSize(50,21));
    layout_trauma->addWidget(radio_trauma_yes);
    QRadioButton *radio_trauma_no = new QRadioButton(ui->widget_trauma);
    radio_trauma_no->setObjectName("radio_trauma_no");
    radio_trauma_no->setText("无");
    radio_trauma_no->setChecked(true);
    radio_trauma_no->setMaximumSize(QSize(50,21));
    radio_trauma_no->setMinimumSize(QSize(50,21));
    layout_trauma->addWidget(radio_trauma_no);

    QHBoxLayout* layout_babyTeeth = new QHBoxLayout(ui->widget_babyTeeth);
    layout_babyTeeth->setObjectName("layout_babyTeeth");

    ui->spinBox_height->setMaximum(300);
    ui->doubleSpinBox_weight->setMaximum(250.00);

}

NewPatient::~NewPatient()
{
    delete ui;
}

void NewPatient::init()
{
        ui->lineEdit_name->clear();
        ui->lineEdit_address->clear();
        ui->lineEdit_password->clear();
        ui->lineEdit_telephone->clear();
        ui->lineEdit_profession->clear();
        ui->lineEdit_mailing_address->clear();
        ui->lineEdit_IDCard->clear();
        ui->dateEdit_birthday->setDate(QDate::currentDate());

    QGridLayout* layout_pastMedical = ui->widget_pastMedical->findChild<QGridLayout*>("layout_pastMedical");
    while (!layout_pastMedical->isEmpty()) {
        QLayoutItem* child=layout_pastMedical->takeAt(0);
        if(child->widget()){
            child->widget()->setParent(NULL);
        }
        delete child;
    }
    QSqlQuery query = QSqlQuery(db);
    query.exec("select ID,name from PastMedicalHistory order by ID desc");
    int i=0;
    while (query.next()) {
        QCheckBox* check = new QCheckBox(ui->widget_pastMedical);
        check->setObjectName(QString("%1").arg(query.value(1).toString()));
        check->setChecked(false);
        check->setMaximumSize(QSize(111,21));
        check->setMinimumSize(QSize(111,21));
        check->setText(query.value(1).toString());
        layout_pastMedical->addWidget(check,i/6,i%6);
        i++;
    }
    QLineEdit* lineEdit_pastMedical=new QLineEdit(ui->widget_pastMedical);
    lineEdit_pastMedical->setObjectName("lineEdit_pastMedical");
    lineEdit_pastMedical->hide();
    lineEdit_pastMedical->setMaxLength(100);
    layout_pastMedical->addWidget(lineEdit_pastMedical,i/6,i%6);
    connect(ui->widget_pastMedical->findChild<QCheckBox*>("其他"),&QCheckBox::stateChanged,
            [=](){
        if(ui->widget_pastMedical->findChild<QCheckBox*>("其他")->isChecked()){
            lineEdit_pastMedical->clear();
            lineEdit_pastMedical->show();
        }else{
            lineEdit_pastMedical->hide();
        }
    });

    QGridLayout* layout_allergic = ui->widget_allergic->findChild<QGridLayout*>("layout_allergic");
    while (!layout_allergic->isEmpty()) {
        QLayoutItem* child=layout_allergic->takeAt(0);
        if(child->widget()){
            child->widget()->setParent(NULL);
        }
        delete child;
    }
    query = QSqlQuery(db);
    query.exec("select ID,name from allergicHistory order by ID desc");
    i=0;
    while (query.next()) {
        QCheckBox* check = new QCheckBox(ui->widget_allergic);
        check->setObjectName(QString("%1").arg(query.value(1).toString()));
        check->setChecked(false);
        check->setMaximumSize(QSize(111,21));
        check->setMinimumSize(QSize(111,21));
        check->setText(query.value(1).toString());
        layout_allergic->addWidget(check,i/6,i%6);
        i++;
    }
    QLineEdit* lineEdit_allergic=new QLineEdit(ui->widget_allergic);
    lineEdit_allergic->setObjectName("lineEdit_allergic");
    lineEdit_allergic->hide();
    lineEdit_allergic->setMaxLength(100);
    layout_allergic->addWidget(lineEdit_allergic,i/6,i%6);
    connect(ui->widget_allergic->findChild<QCheckBox*>("其他"),&QCheckBox::stateChanged,
            [=](){
        if(ui->widget_allergic->findChild<QCheckBox*>("其他")->isChecked()){
            lineEdit_allergic->clear();
            lineEdit_allergic->show();
        }else{
            lineEdit_allergic->hide();
        }
    });

    QGridLayout* layout_pharmaco = ui->widget_pharmaco->findChild<QGridLayout*>("layout_pharmaco");
    while (!layout_pharmaco->isEmpty()) {
        QLayoutItem* child=layout_pharmaco->takeAt(0);
        if(child->widget()){
            child->widget()->setParent(NULL);
        }
        delete child;
    }
    query = QSqlQuery(db);
    query.exec("select ID,name from pharmacoHistory order by ID desc");
    i=0;
    while (query.next()) {
        QCheckBox* check = new QCheckBox(ui->widget_pharmaco);
        check->setObjectName(QString("%1").arg(query.value(1).toString()));
        check->setChecked(false);
        check->setMaximumSize(QSize(111,21));
        check->setMinimumSize(QSize(111,21));
        check->setText(query.value(1).toString());
        layout_pharmaco->addWidget(check,i/6,i%6);
        i++;
    }
    QLineEdit* lineEdit_pharmaco=new QLineEdit(ui->widget_pharmaco);
    lineEdit_pharmaco->setObjectName("lineEdit_pharmaco");
    lineEdit_pharmaco->hide();
    lineEdit_pharmaco->setMaxLength(100);
    layout_pharmaco->addWidget(lineEdit_pharmaco,i/6,i%6);
    connect(ui->widget_pharmaco->findChild<QCheckBox*>("其他"),&QCheckBox::stateChanged,
            [=](){
        if(ui->widget_pharmaco->findChild<QCheckBox*>("其他")->isChecked()){
            lineEdit_pharmaco->clear();
            lineEdit_pharmaco->show();
        }else{
            lineEdit_pharmaco->hide();
        }
    });

    QGridLayout* layout_badHabits = ui->widget_badHabits->findChild<QGridLayout*>("layout_badHabits");
    while (!layout_badHabits->isEmpty()) {
        QLayoutItem* child=layout_badHabits->takeAt(0);
        if(child->widget()){
            child->widget()->setParent(NULL);
        }
        delete child;
    }
    query = QSqlQuery(db);
    query.exec("select ID,name from BadOralHabits order by ID desc");
    i=0;
    while (query.next()) {
        QCheckBox* check = new QCheckBox(ui->widget_badHabits);
        check->setObjectName(QString("%1").arg(query.value(1).toString()));
        check->setChecked(false);
        check->setMaximumSize(QSize(111,21));
        check->setMinimumSize(QSize(111,21));
        check->setText(query.value(1).toString());
        layout_badHabits->addWidget(check,i/6,i%6);
        i++;
    }
    QLineEdit* lineEdit_badHabits=new QLineEdit(ui->widget_badHabits);
    lineEdit_badHabits->setObjectName("lineEdit_badHabits");
    lineEdit_badHabits->hide();
    lineEdit_badHabits->setMaxLength(100);
    layout_badHabits->addWidget(lineEdit_badHabits,i/6,i%6);
    connect(ui->widget_badHabits->findChild<QCheckBox*>("其他"),&QCheckBox::stateChanged,
            [=](){
        if(ui->widget_badHabits->findChild<QCheckBox*>("其他")->isChecked()){
            lineEdit_badHabits->clear();
            lineEdit_badHabits->show();
        }else{
            lineEdit_badHabits->hide();
        }
    });

    QHBoxLayout* layout_babyTeeth=ui->widget_babyTeeth->findChild<QHBoxLayout*>("layout_babyTeeth");
    while (!layout_babyTeeth->isEmpty()) {
        QLayoutItem* child=layout_babyTeeth->takeAt(0);
        if(child->widget()){
            child->widget()->setParent(NULL);
        }
        delete child;
    }
    QComboBox* babyTeeth = new QComboBox(ui->widget_babyTeeth);
    babyTeeth->setObjectName("babyTeeth");
    QLineEdit* lineEdit_babyTeeth = new QLineEdit(ui->widget_babyTeeth);
    lineEdit_babyTeeth->setObjectName("lineEdit_babyTeeth");
    lineEdit_babyTeeth->hide();
    lineEdit_babyTeeth->setMaxLength(100);
    query.exec("select ID,name from BabyReplace order by ID desc");
    while(query.next()){
        babyTeeth->addItem(query.value(1).toString());
    }
    connect(babyTeeth,&QComboBox::currentTextChanged,
            [=](QString name){
        if(name == "其他"){
            lineEdit_babyTeeth->clear();
            lineEdit_babyTeeth->show();
        }else{
            lineEdit_babyTeeth->hide();
        }
    });
    babyTeeth->setCurrentText("不清楚");
    layout_babyTeeth->addWidget(babyTeeth);
    layout_babyTeeth->addWidget(lineEdit_babyTeeth);


    ui->comboBox_grade->setCurrentIndex(0);
    ui->comboBox_pride->setCurrentIndex(0);
    ui->comboBox_adaptation->setCurrentIndex(0);
    ui->comboBox_normalDrug->setCurrentIndex(0);
    ui->comboBox_healthOnbirth->setCurrentIndex(0);
    ui->comboBox_selfEvaluation->setCurrentIndex(0);
    ui->comboBox_threeGenerations->setCurrentIndex(0);

    ui->comboBox_frenum->setCurrentIndex(0);
    ui->comboBox_tonsil->setCurrentIndex(0);
    ui->comboBox_gingiva->setCurrentIndex(0);
    ui->comboBox_required->setCurrentIndex(0);
    ui->comboBox_teethAge->setCurrentIndex(0);
    ui->comboBox_mentality->setCurrentIndex(0);
    ui->comboBox_sexuality->setCurrentIndex(0);
    ui->comboBox_growPeriod->setCurrentIndex(0);
    ui->comboBox_softPalate->setCurrentIndex(0);
    ui->comboBox_oralHygiene->setCurrentIndex(0);
    ui->spinBox_height->setValue(170);
    ui->doubleSpinBox_weight->setValue(65.00);

    ui->comboBox_chew->setCurrentIndex(0);
    ui->comboBox_side->setCurrentIndex(0);
    ui->comboBox_front->setCurrentIndex(0);
    ui->comboBox_ICP_RCP->setCurrentIndex(0);
    ui->comboBox_breathe->setCurrentIndex(0);
    ui->comboBox_swallow->setCurrentIndex(0);
    ui->comboBox_pronounce->setCurrentIndex(0);
    ui->comboBox_side_Chin->setCurrentIndex(0);
    ui->comboBox_side_lips->setCurrentIndex(0);
    ui->comboBox_front_Chin->setCurrentIndex(0);
    ui->comboBox_front_lips->setCurrentIndex(0);
    ui->comboBox_front_smile->setCurrentIndex(0);
    ui->comboBox_side_groove->setCurrentIndex(0);
    ui->comboBox_front_Ans_Me->setCurrentIndex(0);
    ui->comboBox_openingModel->setCurrentIndex(0);
    ui->comboBox_openingDegree->setCurrentIndex(0);
    ui->comboBox_side_mandible->setCurrentIndex(0);
    ui->comboBox_front_symmetry->setCurrentIndex(0);
    ui->comboBox_side_nasolabial->setCurrentIndex(0);



}

void NewPatient::on_pushButton_accept_released()
{
    QString name = ui->lineEdit_name->text();
    QString password = ui->lineEdit_password->text();
    QString address = ui->lineEdit_address->text();
    QString IDCard = ui->lineEdit_IDCard->text();
    QString telephone = ui->lineEdit_telephone->text();
    QString profession = ui->lineEdit_profession->text();
    QString email = ui->lineEdit_mailing_address->text();
    QString birthday = ui->dateEdit_birthday->date().toString("yyyy-MM-dd");
    QString sex = ui->comboBox_sex->currentText();

    //QString str = QString("select count(*) from Patient where IDCard = '%1'").arg(IDCard);
    QSqlQuery query=QSqlQuery(db);
    query.prepare("select count(*) from Patient where IDCard=:IDCard");
    query.bindValue(":IDCard",IDCard);
    query.exec();
    query.next();
    if(query.value(0)==0)
    {
        db.transaction();
        query.exec(QString("insert into Patient(name,IDCard,password,sex,birthday,address,profession,mailing_address,telephone) values('%1','%2','%3','%4','%5','%6','%7','%8','%9')").arg(name).arg(IDCard).arg(password).arg(sex).arg(birthday).arg(address).arg(profession).arg(email).arg(telephone));
        query.prepare("select ID from Patient where IDCard=:IDCard");
        query.bindValue(":IDCard",IDCard);
        query.exec();
        query.next();
        QString ID = query.value(0).toString();

        QList<QCheckBox*> pastMedical= ui->widget_pastMedical->findChildren<QCheckBox*>();
        while(!pastMedical.empty())
        {
            if(pastMedical.front()->isChecked()){
                QString str = QString("insert into Patient_PastMedical(patientID,diseaseID,remark) "
                                      "values(%1,(select ID from PastMedicalHistory where name='%2'),'%3')"
                                      "").arg(ID).arg(pastMedical.front()->text()).arg(pastMedical.front()->text() == "其他" ? ui->widget_pastMedical->findChild<QLineEdit*>("lineEdit_pastMedical")->text() : "");
                query.exec(str);
            }
            pastMedical.pop_front();
        }

        QList<QCheckBox*> pharmaco= ui->widget_pharmaco->findChildren<QCheckBox*>();
        while(!pharmaco.empty())
        {
            if(pharmaco.front()->isChecked()){
                QString str = QString("insert into Patient_Pharmaco(patientID,diseaseID,remark) "
                                      "values(%1,(select ID from PharmacoHistory where name='%2'),'%3')"
                                      "").arg(ID).arg(pharmaco.front()->text()).arg(pharmaco.front()->text() == "其他" ? ui->widget_pharmaco->findChild<QLineEdit*>("lineEdit_pharmaco")->text() : "");
                query.exec(str);
            }
            pharmaco.pop_front();
        }

        QList<QCheckBox*> allergic= ui->widget_allergic->findChildren<QCheckBox*>();
        while(!allergic.empty())
        {
            if(allergic.front()->isChecked()){
                QString str = QString("insert into Patient_Allergic(patientID,diseaseID,remark) "
                                      "values(%1,(select ID from AllergicHistory where name='%2'),'%3')"
                                      "").arg(ID).arg(allergic.front()->text()).arg(allergic.front()->text() == "其他" ? ui->widget_allergic->findChild<QLineEdit*>("lineEdit_allergic")->text() : "");
                query.exec(str);
            }
            allergic.pop_front();
        }

        QString orthodontics = ui->widget_orthodontics->findChild<QRadioButton*>("radio_orthodontics_yes")->isChecked() ? "是" : "否";
        QString NSCLP = ui->widget_NSCLP->findChild<QRadioButton*>("radio_NSCLP_yes")->isChecked() ? "是" : "否";
        query.exec(QString("select ID from BabyReplace where name='%1'").arg(ui->widget_babyTeeth->findChild<QComboBox*>("babyTeeth")->currentText()));
        query.next();
        QString babyTeeth = query.value(0).toString();
        QString trauma = ui->widget_trauma->findChild<QRadioButton*>("radio_trauma_yes")->isChecked() ? "是" : "否";
        query.exec(QString("insert into OralHistory(ID,orthodontics,NSCLP,babyTeethID,trauma) values(%1,'%2','%3',%4,'%5')")
                   .arg(ID).arg(orthodontics).arg(NSCLP).arg(babyTeeth).arg(trauma));
        QList<QCheckBox*> badHabits= ui->widget_badHabits->findChildren<QCheckBox*>();
        while(!badHabits.empty())
        {
            if(badHabits.front()->isChecked()){
                QString str = QString("insert into Patient_badHabits(patientID,habitID,remark) "
                                      "values(%1,(select ID from BadOralHabits where name='%2'),'%3')"
                                      "").arg(ID).arg(badHabits.front()->text()).arg(badHabits.front()->text() == "其他" ? ui->widget_badHabits->findChild<QLineEdit*>("lineEdit_badHabits")->text() : "");
                 query.exec(str);
            }
            badHabits.pop_front();
        }

        QString healOnbirth = ui->comboBox_healthOnbirth->currentText();
        QString normalOnDrug = ui->comboBox_normalDrug->currentText();
        QString threeGenerations = ui->comboBox_threeGenerations->currentText() == "有类似畸形" ? ui->comboBox_threeGenerations->currentText()+":"+ui->lineEdit_threeGenerations->text() : ui->comboBox_threeGenerations->currentText();
        QString grade = ui->comboBox_grade->currentText();
        QString adaptation = ui->comboBox_adaptation->currentText();
        QString selfEvaluation = ui->comboBox_selfEvaluation->currentText();
        QString pride = ui->comboBox_grade->currentText();
        query.exec(QString("insert into Relation(ID,healthOnbirth,normalOnDrug,threeGenerations,grade,adaptation,selfEvaluation,pride) "
                           "values(%1,'%2','%3','%4','%5','%6','%7','%8')")
             .arg(ID).arg(healOnbirth).arg(normalOnDrug).arg(threeGenerations).arg(grade).arg(adaptation).arg(selfEvaluation).arg(pride));

        int height = ui->spinBox_height->value();
        double weight = ui->doubleSpinBox_weight->value();
        QString teethAge = ui->comboBox_teethAge->currentText();
        QString sexuality = ui->comboBox_sexuality->currentText();
        QString growPeriod = ui->comboBox_growPeriod->currentText();
        QString mentality = ui->comboBox_mentality->currentText();
        QString required = ui->comboBox_required->currentText();
        QString oralHygiene = ui->comboBox_oralHygiene->currentText();
        QString gingiva = ui->comboBox_gingiva->currentText();
        QString tonsil = ui->comboBox_tonsil->currentText();
        QString frenum = ui->comboBox_frenum->currentText();
        QString softPalate = ui->comboBox_softPalate->currentText();
        query.exec(QString("insert into PhysicalCondition(ID,height,weight,teethAge,sexuality,growPeriod,mentality,required,oralHygiene,gingiva,tonsil,frenum,softPalate) "
                           "values(%1,%2,%3,'%4','%5','%6','%7','%8','%9','%10','%11','%12','%13')")
                   .arg(ID).arg(height).arg(weight).arg(teethAge).arg(sexuality).arg(growPeriod).arg(mentality)
                   .arg(required).arg(oralHygiene).arg(gingiva).arg(tonsil).arg(frenum).arg(softPalate));

        QString front = ui->comboBox_front->currentText();
        QString front_symmetry = ui->comboBox_front_symmetry->currentText();
        QString front_Ans_Me = ui->comboBox_front_Ans_Me->currentText();
        QString front_lips = ui->comboBox_front_lips->currentText();
        QString front_Chin = ui->comboBox_front_Chin->currentText();
        QString front_smile = ui->comboBox_front_smile->currentText();
        QString side = ui->comboBox_side->currentText();
        QString side_nasolabial = ui->comboBox_side_nasolabial->currentText();
        QString side_lips = ui->comboBox_side_lips->currentText();
        QString side_groove = ui->comboBox_side_groove->currentText();
        QString side_Chin = ui->comboBox_side_Chin->currentText();
        QString side_mandible = ui->comboBox_side_mandible->currentText();
        query.exec(QString("insert into FaceExamine(ID,front,front_symmetry,front_Ans_Me,front_lips,front_Chin,front_smile,"
                           "side,side_nasolabial,side_lips,side_groove,side_Chin,side_mandible) values"
                           "(%1,'%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13')")
                   .arg(ID).arg(front).arg(front_symmetry).arg(front_Ans_Me).arg(front_lips).arg(front_Chin).arg(front_smile)
                   .arg(side).arg(side_nasolabial).arg(side_lips).arg(side_groove).arg(side_Chin).arg(side_mandible));

        QString pronounce = ui->comboBox_pronounce->currentText();
        QString breathe = ui->comboBox_breathe->currentText();
        QString chew = ui->comboBox_chew->currentText();
        QString swallow = ui->comboBox_swallow->currentText();
        QString openingDegree = ui->comboBox_openingDegree->currentText();
        QString openingModel = ui->comboBox_openingDegree->currentText();
        QString ICP_RCP = ui->comboBox_ICP_RCP->currentText();
        query.exec(QString("insert into FunctionExamine(ID,pronounce,breathe,chew,swallow,openingDegree,openingModel,ICP_RCP) "
                           "values(%1,'%2','%3','%4','%5','%6','%7','%8')")
                   .arg(ID).arg(pronounce).arg(breathe).arg(chew).arg(swallow).arg(openingDegree).arg(openingModel).arg(ICP_RCP));
        if(db.commit())
        {
            QMessageBox::warning(this,"成功","患者信息创建成功。");
            emit createFinished(QString("%1 (%2)").arg(name).arg(ID));
            return;
        }
    }
    else
    {
        QMessageBox::warning(this,"错误","该患者信息已存在。");
        return;
    }
    QMessageBox::warning(this,"错误","创建患者信息失败。");
}

void NewPatient::on_pushButton_back_released()
{
    close();
}
