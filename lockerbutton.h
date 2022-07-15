/*
* @file                 LockerButton.h
* @brief                抽屉式Widget控件显隐按钮
* @auther               Tree
* @version              0.0
* @date                 2019.12.31
* @copyright
*/

#ifndef LOCKER_BUTTON_H
#define LOCKER_BUTTON_H

#include <QWidget>
#include <QPushButton>

class QLabel;

class LockerButton : public QPushButton
{
    Q_OBJECT
public:
    /// @brief 构造方法
    explicit LockerButton(QWidget* parent = nullptr);

    /// @brief SetImageLabel
    /// 设置按钮图标
    void SetImageLabel(const QPixmap &pixmap);

    /// @brief SetTextLabel
    /// 设置按钮文字
    void SetTextLabel(QString text);

    /// @brief GetImageHandle
    /// 返回m_imageLabel
    QLabel* GetImageHandle();

    /// @brief GetImageHandle
    /// 返回m_textLabel
    QLabel* GetTextHandle();

private:
    // 按钮图标
    QLabel* m_imageLabel;
    // 按钮文字
    QLabel* m_textLabel;
};

#endif // LOCKER_BUTTON_H
