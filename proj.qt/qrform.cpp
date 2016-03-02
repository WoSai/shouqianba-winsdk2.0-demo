#include "qrform.h"
#include "ui_qrform.h"

QRForm::QRForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QRForm)
{
    ui->setupUi(this);
}

QRForm::~QRForm()
{
    delete ui;
}

QLabel* QRForm::getQRLabel()
{
    return ui->label;
}
