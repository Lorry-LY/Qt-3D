QT += core gui sql quickwidgets 3dextras 3dcore 3drender 3dinput 3dquick 3dlogic qml quick 3dquickextras 3danimation network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

CONFIG += resources_big

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_FILE += Icon.rc

SOURCES += \
    attributewidget.cpp \
    doctor/order.cpp \
    imagebutton.cpp \
    lockerbutton.cpp \
    lockerwidget.cpp \
    main.cpp \
    mainwidget.cpp \
    mainwindow.cpp \
    medicalhistory.cpp \
    newpatient.cpp \
    orbittransroracontroller.cpp \
    patient/teethwidget.cpp \
    patientwidget.cpp \
    scene.cpp \
    scenemodifier.cpp \
    searchpatient.cpp

HEADERS += \
    attributewidget.h \
    doctor/order.h \
    imagebutton.h \
    lockerbutton.h \
    lockerwidget.h \
    mainwidget.h \
    mainwindow.h \
    medicalhistory.h \
    newpatient.h \
    orbittransroracontroller.h \
    patient/teethwidget.h \
    patientwidget.h \
    scene.h \
    scenemodifier.h \
    searchpatient.h

FORMS += \
    attributewidget.ui \
    doctor/order.ui \
    lockerwidget.ui \
    mainwidget.ui \
    mainwindow.ui \
    medicalhistory.ui \
    newpatient.ui \
    patient/teethwidget.ui \
    patientwidget.ui \
    scene.ui \
    searchpatient.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc \
    resources.qrc

DISTFILES += \
    AnimatedEntity.qml \
    MyEntity.qml \
    main.qml \

