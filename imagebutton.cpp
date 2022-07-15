#include "imagebutton.h"
#include <QtWidgets>

ImageButton::ImageButton(QWidget *parent)
    : QPushButton(parent)
    , curStatus_(ST_INIT)
{
    this->setStyleSheet("#ImageButton{background-color:transparent}"
        "ImageButton{border: none}");
}

void ImageButton::setImages(QString &normalName, QString &horverName, QString &pressName)
{
    curStatus_ = ST_NORMAL;
    imageName_[ST_NORMAL] = normalName;
    imageName_[ST_HOVER] = horverName;
    imageName_[ST_PRESS] = pressName;
}

void ImageButton::enterEvent(QEvent *)
{
    if (curStatus_ == ST_INIT) {
        return;
    }

    curStatus_ = ST_HOVER;
    update();
}

void ImageButton::leaveEvent(QEvent *)
{
    if (curStatus_ == ST_INIT) {
        return;
    }

    curStatus_ = ST_NORMAL;
    update();
}

void ImageButton::mousePressEvent(QMouseEvent *event)
{
    if (curStatus_ == ST_INIT) {
        return;
    }

    if (event->button() == Qt::LeftButton) {
        curStatus_ = ST_PRESS;
        update();
    }
}

void ImageButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (curStatus_ != ST_INIT) {
            curStatus_ = ST_HOVER;
            update();
        }
        // 鼠标在弹起的时候光标在按钮上才激发clicked信号
        if (rect().contains(event->pos())) {
            emit released();
        }
    }
}

void ImageButton::paintEvent(QPaintEvent *event)
{
    if (curStatus_ == ST_INIT) {
        QPushButton::paintEvent(event);
        return;
    }

    QPainter painter(this);
    QPixmap pixmap(imageName_[curStatus_]);
    painter.drawPixmap(rect(), pixmap);
}
