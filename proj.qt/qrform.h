#ifndef QRFORM_H
#define QRFORM_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class QRForm;
}

class QRForm : public QWidget
{
    Q_OBJECT

public:
    explicit QRForm(QWidget *parent = 0);
    ~QRForm();

public:
    QLabel* getQRLabel();
private:
    Ui::QRForm *ui;
};

#endif // QRFORM_H
