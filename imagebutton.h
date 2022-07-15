#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QPushButton>

class ImageButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ImageButton(QWidget *parent = 0);
    void setImages(QString &normalName, QString &horverName, QString &pressName);

protected:
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *);

private:
    typedef enum {
        ST_INIT, ST_NORMAL, ST_HOVER, ST_PRESS, ST_COUNT
    } Status;
    Status curStatus_;
    QString imageName_[ST_COUNT];
};

#endif // IMAGEBUTTON_H
