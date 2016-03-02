#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "qrform.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_load_btn_clicked();

    void on_create_sign_btn_clicked();

    void on_refund_sign_btn_clicked();

    void on_qrcode_sign_btn_clicked();

    void on_query_sign_btn_clicked();

    virtual bool event(QEvent *e);
    void on_clear_log_btn_clicked();

    void on_check_sdk_version_btn_clicked();

    void on_update_app_key_btn_clicked();

    void on_activate_sdk_btn_clicked();

    void on_set_res_btn_clicked();

    void on_refund_sign_btn_2_clicked();

    void on_terminal_sn_btn_clicked();

    void on_revoke_sign_btn_clicked();

    void on_revoke_sign_btn_2_clicked();

private:
    Ui::Dialog *ui;
    QRForm qr_form;
public:
    QApplication* app;
};

#endif // DIALOG_H
