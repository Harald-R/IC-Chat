#include "widget.h"
#include "ui_widget.h"
#include <string.h>
#include <QString>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_sendButton_clicked()
{
    QString textBoxValue;
    static QString chatHist;

    textBoxValue = ui->enterMessageText->toPlainText();
    chatHist += textBoxValue + "\n";
    ui->chatHistory->setText(chatHist);

//    ui->enterMessageText->setText(textBoxValue);
    ui->enterMessageText->clear();
}
