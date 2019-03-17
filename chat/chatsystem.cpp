#include "chatbutton.h"

ChatButton::ChatButton(QWidget *parent)
    : QPushButton(parent)
{
    initUI();
}

ChatButton::~ChatButton()
{
}

void ChatButton::initUI()
{
    // Configure the button display
    QPalette buttonPalette = this->palette();
    buttonPalette.setColor(QPalette::Button, QColor("#22313a"));
    this->setAutoFillBackground(true);
    this->setPalette(buttonPalette);
    this->setStyleSheet("QPushButton { text-align: left; padding-left: 65px; background-color: #22313a; border: 1px solid #394e5b;}"
                        "QPushButton:hover { background-color: #1e2a31; }"
                        "QPushButton:pressed { background-color: #141c21; }");
    this->setMinimumHeight(60);
    this->setMaximumHeight(60);

    // Configure the label printed inside the circular icon
    QLabel *label = new QLabel(this);
    label->setText("N");
    label->setGeometry(20, 20, 20, 20);
    label->setAlignment(Qt::AlignCenter);
    QFont font("Arial", 15, QFont::Bold);
    label->setFont(font);
    label->setStyleSheet("QLabel { color: #1e2a31; } ");
}

void ChatButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    // Draw the circular icon to the left of the button
    const QString &color = "#edeff0";
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(color)));
    painter.setPen(QPen(QColor(color)));
    painter.drawEllipse(QPointF(30,30), 20, 20);
}
