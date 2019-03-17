#ifndef CHATBUTTON_H
#define CHATBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>

class ChatButton : public QPushButton
{
    Q_OBJECT
public:
    ChatButton(QWidget *parent = nullptr);
    virtual ~ChatButton();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void initUI();
};

#endif // CHATBUTTON_H
