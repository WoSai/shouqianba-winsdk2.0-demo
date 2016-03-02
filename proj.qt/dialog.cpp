#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
#include <QKeyEvent>
#include "dialog.h"
#include "ui_dialog.h"
#include <string>
#include <Windows.h>
#include <iostream>
#include "InfoString.h"
#include "qrform.h"

using namespace std;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("CashBar_V2_Demo");

    ui->load_btn->setEnabled(true);
    ui->create_sign_btn->setEnabled(false);
    ui->refund_sign_btn->setEnabled(false);
    ui->refund_sign_btn_2->setEnabled(false);
    ui->qrcode_sign_btn->setEnabled(false);
    ui->query_sign_btn->setEnabled(false);
    ui->check_sdk_version_btn->setEnabled(false);
    ui->terminal_sn_btn->setEnabled(false);
    ui->update_app_key_btn->setEnabled(false);
    ui->activate_sdk_btn->setEnabled(false);
    ui->set_res_btn->setEnabled(false);
    ui->res_path_edit->setReadOnly(true);

    ui->pay_method_combo->addItem(ALIPAY_STR);
    ui->pay_method_combo->addItem(WECHAT_STR);
    ui->pay_method_combo->addItem(UNIONPAY_STR);
    ui->pay_method_combo->addItem(BAIDU_STR);
    ui->pay_method_combo->addItem(JDPAY_STR);
    ui->pay_method_combo->addItem(UNDEFINE_STR);

    ui->pay_method_combo->setCurrentIndex(5);

    ui->subject_edit->setPlaceholderText(SUBJECT);
    ui->description_edit->setPlaceholderText(DESCRIPTION);
    ui->operator_edit->setPlaceholderText(OPERATOR);
    ui->own_order_id_edit->setPlaceholderText(OWN_ORDER_ID);
    ui->total_fee_edit->setPlaceholderText(TOTAL_FEE);
    ui->card_id_edit->setPlaceholderText(CARD_ID);
    ui->wosai_order_id_edit->setPlaceholderText(WOSAI_ORDER_ID);
    ui->auth_code_edit->setPlaceholderText(AUTH_CODE_INPUT);

    ui->subject_edit->setText(SUBJECT_SAMPLE);
    ui->description_edit->setText(DESCRIPTION_SAMPLE);
    ui->operator_edit->setText(OPERATOR_SAMPLE);
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString time_str = current_date_time.toString("yyyyMMddhhmmss");
    ui->own_order_id_edit->setText(time_str);
    ui->total_fee_edit->setText("1");
    ui->auth_code_edit->setText("");
    ui->res_path_edit->setText("");
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::event(QEvent *e)
{
   if ( e->type() == QEvent::KeyPress )
  {
     QKeyEvent * ke = (QKeyEvent*) e;
      if ( ke->key() == Qt::Key_Escape )
      {
          return true;
      }
   }

  return QWidget::event(e);

}

static HINSTANCE hDll = NULL;
typedef const char* (__stdcall *str_void)(void);
typedef int (__stdcall *int_int)(int b);
typedef const char* (__stdcall *str_str)(const char* str);
typedef int (__stdcall *int_str)(const char* str);

void Dialog::on_load_btn_clicked()
{
    if (hDll == NULL){
        hDll = ::LoadLibrary(L"./CashBarV2.dll");
        //hDll = ::LoadLibrary(L"./CashBarV2_RTM.dll");
    } else {
        FreeLibrary(hDll);
        hDll = NULL;
        ui->load_btn->setText(LOAD_SDK_STR);
        ui->check_sdk_version_btn->setEnabled(false);
        ui->terminal_sn_btn->setEnabled(false);
        ui->update_app_key_btn->setEnabled(false);
        ui->activate_sdk_btn->setEnabled(false);
        ui->set_res_btn->setEnabled(false);
        ui->create_sign_btn->setEnabled(false);
        ui->refund_sign_btn->setEnabled(false);
        ui->refund_sign_btn_2->setEnabled(false);
        ui->qrcode_sign_btn->setEnabled(false);
        ui->query_sign_btn->setEnabled(false);
        ui->set_res_btn->setEnabled(false);
        return;
    }
    cout<<"Library Load To: "<<hDll<<endl;
    if (hDll == NULL)
        QMessageBox::warning(this,"Warn",LOAD_SDK_FAIL);
    else {
        ui->load_btn->setText(UNLOAD_SDK_STR);
        ui->check_sdk_version_btn->setEnabled(true);
        ui->terminal_sn_btn->setEnabled(true);
        ui->update_app_key_btn->setEnabled(true);
        ui->activate_sdk_btn->setEnabled(true);
        ui->set_res_btn->setEnabled(true);
        ui->create_sign_btn->setEnabled(true);
        ui->refund_sign_btn->setEnabled(true);
        ui->refund_sign_btn_2->setEnabled(true);
        ui->qrcode_sign_btn->setEnabled(true);
        ui->query_sign_btn->setEnabled(true);
        ui->set_res_btn->setEnabled(true);
    }
}

void Dialog::on_create_sign_btn_clicked()
{
    QString subject = ui->subject_edit->text();
    if (subject.size() == 0) {
        QMessageBox::warning(this,"Warn",SUBJECT_EMPTY);
        return;
    }
    QString description = ui->description_edit->text();
    QString operator_str = ui->operator_edit->text();
    if (operator_str.size() == 0) {
        QMessageBox::warning(this,"Warn",OPERATOR_EMPTY);
        return;
    }
    QString order_id = ui->own_order_id_edit->text();
    if (order_id.size() == 0) {
        QMessageBox::warning(this,"Warn",OWN_ORDER_ID_EMPTY);
        return;
    }
    QString total_fee = ui->total_fee_edit->text();
    if (total_fee.size() == 0) {
        QMessageBox::warning(this,"Warn",TOTAL_FEE_EMPTY);
        return;
    }
    QString pay_method = "";
    switch (ui->pay_method_combo->currentIndex()) {
    case 0:
        pay_method = "1";
        break;
    case 1:
        pay_method = "3";
        break;
    case 2:
        pay_method = "2";
        break;
    case 3:
        pay_method = "4";
        break;
    case 4:
        pay_method = "5";
        break;
    case 5:
    default:
        break;
    }
    QString card_id = ui->card_id_edit->text();
    QString reflect = ui->reflect_edit->text();
    QString extended = ui->extended_edit->text();

    QString cmd = "";
    cmd.append(order_id+"&");
    cmd.append(subject+"&");
    cmd.append(operator_str+"&");
    cmd.append(description+"&");
    cmd.append(pay_method+"&");
    cmd.append(total_fee+"&");
    cmd.append(card_id+"&");
    cmd.append(reflect+"&");
    cmd.append(extended);

    str_str pf = NULL;
    if (ui->ui_check->isChecked())
        pf = (str_str)GetProcAddress(hDll,"_payUI@4");
    else
        pf = (str_str)GetProcAddress(hDll,"_pay@4");
    if (pf == NULL)
        return;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString time_str = current_date_time.toString("hh:mm:ss");
    ui->log_edit->append(time_str+REQUEST_CALL+"pay:"+cmd+"\n");
    ui->log_edit->repaint();
    app->processEvents();
    string str = cmd.toUtf8().toStdString();
    string ret = (*pf)(str.c_str());

    current_date_time = QDateTime::currentDateTime();
    time_str = current_date_time.toString("hh-mm-ss");
    ui->log_edit->append(time_str+REQUEST_RESULT+QString::fromStdString(ret)+"\n");

    QString result = QString::fromStdString(ret);
    if (result.startsWith("Pay Success.") || result.startsWith("Pay Failure."))
    {
        QString order_str = result.right(result.size()-12);
        QStringList order_list = order_str.split("&");
        if (order_list.size() >= 2)
            ui->wosai_order_id_edit->setText(order_list.at(0));
    }
    ui->card_id_edit->clear();
}

void Dialog::on_refund_sign_btn_clicked()
{
    QString wosai_order_id = ui->wosai_order_id_edit->text();
    QString total_fee = ui->total_fee_edit->text();
    QString operator_id = ui->operator_edit->text();
    QString refund_serial = ui->refund_serial_edit->text();
    QString reflect = ui->reflect_edit->text();

    QString cmd = "";

    str_str pf = NULL;
    if (ui->ui_check->isChecked()) {
        cmd.append(wosai_order_id+"&");
        cmd.append(refund_serial+"&");
        cmd.append(operator_id+"&");
        cmd.append(total_fee+"&");
        cmd.append(reflect);
        pf = (str_str)GetProcAddress(hDll,"_refundUIWithSN@4");
    } else {
        cmd.append(wosai_order_id+"&&");
        cmd.append(refund_serial+"&");
        cmd.append(operator_id+"&");
        cmd.append(total_fee+"&");
        cmd.append(reflect);
        pf = (str_str)GetProcAddress(hDll,"_refund@4");
    }
    if (pf == NULL)
        return;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString time_str = current_date_time.toString("hh:mm:ss");
    ui->log_edit->append(time_str+REQUEST_CALL+"refund:"+cmd+"\n");
    ui->log_edit->repaint();
    app->processEvents();
    string str = cmd.toUtf8().toStdString();
    string ret = (*pf)(str.c_str());

    current_date_time = QDateTime::currentDateTime();
    time_str = current_date_time.toString("hh-mm-ss");
    ui->log_edit->append(time_str+REQUEST_RESULT+QString::fromStdString(ret)+"\n");
    ui->card_id_edit->clear();
}

void Dialog::on_qrcode_sign_btn_clicked()
{
    QString subject = ui->subject_edit->text();
    if (subject.size() == 0) {
        QMessageBox::warning(this,"Warn",SUBJECT_EMPTY);
        return;
    }
    QString description = ui->description_edit->text();
    QString operator_str = ui->operator_edit->text();
    if (operator_str.size() == 0) {
        QMessageBox::warning(this,"Warn",OPERATOR_EMPTY);
        return;
    }
    QString order_id = ui->own_order_id_edit->text();
    if (order_id.size() == 0) {
        QMessageBox::warning(this,"Warn",OWN_ORDER_ID_EMPTY);
        return;
    }
    QString total_fee = ui->total_fee_edit->text();
    if (total_fee.size() == 0) {
        QMessageBox::warning(this,"Warn",TOTAL_FEE_EMPTY);
        return;
    }
    QString pay_method = "";
    switch (ui->pay_method_combo->currentIndex()) {
    case 0:
        pay_method = "1";
        break;
    case 1:
        pay_method = "3";
        break;
    case 2:
        pay_method = "2";
        break;
    case 3:
        pay_method = "4";
        break;
    case 4:
        pay_method = "5";
        break;
    case 5:
    default:
        break;
    }

    QString save_path = "";
    if (!ui->ui_check->isChecked()) {
        QFileDialog *fileDialog = new QFileDialog(this);
        fileDialog->setWindowTitle(SELECT_QRCODE_PATH);
        QString cur_path = QApplication::applicationDirPath();
        fileDialog->setDirectory(cur_path);
        fileDialog->setFileMode(QFileDialog::DirectoryOnly);
        //fileDialog->setNameFilter("LeafScanner Data Files(*.lsd)");
        if(fileDialog->exec() == QDialog::Accepted) {
            save_path = fileDialog->selectedFiles()[0]+"/";
        } else {
            delete fileDialog;
            return;
        }
        delete fileDialog;
    }
    QString reflect = ui->reflect_edit->text();
    QString extended = ui->extended_edit->text();

    QString cmd = "";

    str_str pf = NULL;
    if (ui->ui_check->isChecked()) {
        cmd.append(order_id+"&");
        cmd.append(subject+"&");
        cmd.append(operator_str+"&");
        cmd.append(description+"&");
        cmd.append(pay_method+"&");
        cmd.append(total_fee+"&");
        cmd.append(reflect+"&");
        cmd.append(extended);
        pf = (str_str)GetProcAddress(hDll,"_preCreateUI@4");
    } else {
        cmd.append(order_id+"&");
        cmd.append(subject+"&");
        cmd.append(operator_str+"&");
        cmd.append(description+"&");
        cmd.append(pay_method+"&");
        cmd.append(total_fee+"&");
        cmd.append(save_path+"&");
        cmd.append(reflect+"&");
        cmd.append(extended);
        pf = (str_str)GetProcAddress(hDll,"_preCreate@4");
    }
    if (pf == NULL)
        return;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString time_str = current_date_time.toString("hh:mm:ss");
    ui->log_edit->append(time_str+REQUEST_CALL+"preCreate:"+cmd+"\n");
    ui->log_edit->repaint();
    app->processEvents();
    string str = cmd.toUtf8().toStdString();
    string ret = (*pf)(str.c_str());

    current_date_time = QDateTime::currentDateTime();
    time_str = current_date_time.toString("hh-mm-ss");
    ui->log_edit->append(time_str+REQUEST_RESULT+QString::fromStdString(ret)+"\n");
    QString result = QString::fromStdString(ret);
    if (result.startsWith("PreCreate Success."))
    {
        QString order_str = result.right(result.size()-18);
        QStringList order_list = order_str.split("&");
        if (order_list.size() >= 3) {
            ui->wosai_order_id_edit->setText(order_list.at(0));
            QString pic_path = order_list.at(2);
            cout<<pic_path.toStdString()<<endl;
            QImage* img=new QImage;
            if(! ( img->load(pic_path) ) ) //加载图像
            {
                QMessageBox::information(this, tr("失败"), tr("打开二维码文件失败!"));
                delete img;
                return;
            }
            qr_form.getQRLabel()->setPixmap(QPixmap::fromImage(*img));
            qr_form.setWindowModality(Qt::ApplicationModal);
            qr_form.show();
        }
        str_void sv=(str_void)GetProcAddress(hDll,"_qrcode@0");
        if (sv != NULL){
            string ret = (*sv)();
            current_date_time = QDateTime::currentDateTime();
            time_str = current_date_time.toString("hh-mm-ss");
            ui->log_edit->append(time_str+REQUEST_RESULT+QString::fromStdString(ret)+"\n");
        }
    }
    if (result.startsWith("Pay Success."))
    {
        QString order_str = result.right(result.size()-12);
        QStringList order_list = order_str.split("&");
        if (order_list.size() >= 2)
            ui->wosai_order_id_edit->setText(order_list.at(0));
    }
    ui->card_id_edit->clear();
}

void Dialog::on_query_sign_btn_clicked()
{
    QString wosai_order_id = ui->wosai_order_id_edit->text();
    QString own_order_id = ui->own_order_id_edit->text();
    if (own_order_id.size() == 0 && wosai_order_id.size() == 0) {
        QMessageBox::warning(this,"Warn",OWN_AND_WOSAI_ORDER_ID_EMPTY);
        return;
    }

    QString cmd = "";
    cmd.append(wosai_order_id+"&");
    cmd.append(own_order_id);

    str_str pf=(str_str)GetProcAddress(hDll,"_query@4");
    if (pf == NULL)
        return;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString time_str = current_date_time.toString("hh:mm:ss");
    ui->log_edit->append(time_str+REQUEST_CALL+"query:"+cmd+"\n");
    ui->log_edit->repaint();
    app->processEvents();
    string str = cmd.toUtf8().toStdString();
    string ret = (*pf)(str.c_str());

    current_date_time = QDateTime::currentDateTime();
    time_str = current_date_time.toString("hh-mm-ss");
    ui->log_edit->append(time_str+REQUEST_RESULT+QString::fromStdString(ret)+"\n");
    ui->card_id_edit->clear();
}

void Dialog::on_clear_log_btn_clicked()
{
    ui->log_edit->clear();
}

void Dialog::on_check_sdk_version_btn_clicked()
{
    if (hDll == NULL)
        return;
    str_void pf=(str_void)GetProcAddress(hDll,"_version@0");
    if (pf == NULL)
        return;
    string version = (*pf)();
    QString ver = QString::fromStdString(version);
    QMessageBox::information(this,tr("SDK Version"),ver);
}

void Dialog::on_update_app_key_btn_clicked()
{
    if (hDll == NULL)
        return;
    str_void pf=(str_void)GetProcAddress(hDll,"_signIn@0");
    if (pf == NULL)
        return;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString time_str = current_date_time.toString("hh:mm:ss");
    ui->log_edit->append(time_str+REQUEST_CALL+"signin."+"\n");
    ui->log_edit->repaint();
    app->processEvents();
    string result = (*pf)();
    QString ret = QString::fromStdString(result);
    current_date_time = QDateTime::currentDateTime();
    time_str = current_date_time.toString("hh-mm-ss");
    ui->log_edit->append(time_str+REQUEST_RESULT+ret+"\n");
    QString suc = "SignIn Success.";
    if (ret.startsWith(suc)) {
        QString k = ret.right(ret.length()-suc.length());
        QMessageBox::information(this,tr("更新成功"),"已自动修改参数内容为"+k);
    } else {
        QMessageBox::information(this,tr("更新失败"),ret);
    }
}

void Dialog::on_activate_sdk_btn_clicked()
{
    QString vendor_id = ui->auth_vendor_edit->text();
    if (vendor_id.size() == 0) {
        QMessageBox::warning(this,"Warn",AUTH_VENDOR_INPUT);
        return;
    }
    QString vendor_key = ui->auth_key_edit->text();
    if (vendor_key.size() == 0) {
        QMessageBox::warning(this,"Warn",AUTH_KEY_INPUT);
        return;
    }
    QString auth_code = ui->auth_code_edit->text();
    if (auth_code.size() == 0 && !ui->ui_check->isChecked()) {
        QMessageBox::warning(this,"Warn",AUTH_CODE_INPUT);
        return;
    }
    if (hDll == NULL)
        return;

    string ret = "";
    QString cmd = "";
    if (ui->ui_check->isChecked()) {
        str_str pf = (str_str)GetProcAddress(hDll,"_activateUI@4");
        if (pf == NULL)
            return;
        cmd = vendor_id+"&"+vendor_key;
        ret = (*pf)(cmd.toUtf8().toStdString().c_str());
    } else {
        str_str pf = (str_str)GetProcAddress(hDll,"_activate@4");
        if (pf == NULL)
            return;
        cmd = vendor_id+"&"+vendor_key+"&"+auth_code;
        ret = (*pf)(cmd.toUtf8().toStdString().c_str());
    }

    QString qret = QString::fromUtf8(ret.c_str());
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString time_str = current_date_time.toString("hh:mm:ss");
    ui->log_edit->append(time_str+REQUEST_CALL+"activate:"+cmd+"\n");
    ui->log_edit->repaint();
    app->processEvents();

    current_date_time = QDateTime::currentDateTime();
    time_str = current_date_time.toString("hh-mm-ss");
    ui->log_edit->append(time_str+REQUEST_RESULT+QString::fromStdString(ret)+"\n");
    QMessageBox::information(this,tr("Activate SDK:"),qret);
}

void Dialog::on_set_res_btn_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(SELECT_SDK_PATH);
    QString cur_path = QApplication::applicationDirPath();
    fileDialog->setDirectory(cur_path);
    fileDialog->setFileMode(QFileDialog::DirectoryOnly);
    QString save_path;
    if(fileDialog->exec() == QDialog::Accepted) {
        save_path = fileDialog->selectedFiles()[0];
    } else {
        delete fileDialog;
        return;
    }
    delete fileDialog;

    if (hDll == NULL)
        return;
    int_str pf=(int_str)GetProcAddress(hDll,"_setSDKPath@4");
    if (pf == NULL)
        return;
    if (save_path.at(save_path.size()-1) != '/')
        save_path.append("/");
    int ret = (*pf)(save_path.toUtf8().toStdString().c_str());
    if (ret == 0x1000)
    {
        QMessageBox::warning(this,"Warn",save_path+" Not Ended With \'/\'.");
        return;
    } else if (ret == 0x2000) {
        QMessageBox::warning(this,"Warn",save_path+" Not Exist.");
        return;
    }
    ui->res_path_edit->setText(save_path);
}

void Dialog::on_refund_sign_btn_2_clicked()
{
    QString order_id = ui->own_order_id_edit->text();
    QString total_fee = ui->total_fee_edit->text();
    QString operator_id = ui->operator_edit->text();
    QString refund_serial = ui->refund_serial_edit->text();
    QString reflect = ui->reflect_edit->text();

    QString cmd = "";

    str_str pf = NULL;
    if (ui->ui_check->isChecked()) {
        cmd.append(order_id+"&");
        cmd.append(refund_serial+"&");
        cmd.append(operator_id+"&");
        cmd.append(total_fee+"&");
        cmd.append(reflect);
        pf = (str_str)GetProcAddress(hDll,"_refundUIWithClientSN@4");
    } else {
        cmd.append("&"+order_id+"&");
        cmd.append(refund_serial+"&");
        cmd.append(operator_id+"&");
        cmd.append(total_fee+"&");
        cmd.append(reflect);
        pf = (str_str)GetProcAddress(hDll,"_refund@4");
    }
    if (pf == NULL)
        return;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString time_str = current_date_time.toString("hh:mm:ss");
    ui->log_edit->append(time_str+REQUEST_CALL+"refund:"+cmd+"\n");
    ui->log_edit->repaint();
    app->processEvents();
    string str = cmd.toUtf8().toStdString();
    string ret = (*pf)(str.c_str());

    current_date_time = QDateTime::currentDateTime();
    time_str = current_date_time.toString("hh-mm-ss");
    ui->log_edit->append(time_str+REQUEST_RESULT+QString::fromStdString(ret)+"\n");
    ui->card_id_edit->clear();
}

void Dialog::on_terminal_sn_btn_clicked()
{
    if (hDll == NULL)
        return;
    str_void pf=(str_void)GetProcAddress(hDll,"_terminalSN@0");
    if (pf == NULL)
        return;
    string sn = (*pf)();
    QString qsn = QString::fromStdString(sn);
    QMessageBox::information(this,tr("Terminal SN"),qsn);
}

void Dialog::on_revoke_sign_btn_clicked()
{
    QString wosai_order_id = ui->wosai_order_id_edit->text();
    QString reflect = ui->reflect_edit->text();

    QString cmd = "";

    str_str pf = NULL;
    if (ui->ui_check->isChecked()) {
        cmd.append(wosai_order_id+"&"+reflect);
        pf = (str_str)GetProcAddress(hDll,"_revokeUIWithSN@4");
    } else {
        cmd.append(wosai_order_id+"&&"+reflect);
        pf = (str_str)GetProcAddress(hDll,"_revoke@4");
    }
    if (pf == NULL)
        return;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString time_str = current_date_time.toString("hh:mm:ss");
    ui->log_edit->append(time_str+REQUEST_CALL+"revoke:"+cmd+"\n");
    ui->log_edit->repaint();
    app->processEvents();
    string str = cmd.toUtf8().toStdString();
    string ret = (*pf)(str.c_str());

    current_date_time = QDateTime::currentDateTime();
    time_str = current_date_time.toString("hh-mm-ss");
    ui->log_edit->append(time_str+REQUEST_RESULT+QString::fromStdString(ret)+"\n");
    ui->card_id_edit->clear();
}

void Dialog::on_revoke_sign_btn_2_clicked()
{
    QString order_id = ui->own_order_id_edit->text();
    QString reflect = ui->reflect_edit->text();

    QString cmd = "";

    str_str pf = NULL;
    if (ui->ui_check->isChecked()) {
        cmd.append(order_id+"&"+reflect);
        pf = (str_str)GetProcAddress(hDll,"_revokeUIWithClientSN@4");
    } else {
        cmd.append("&"+order_id+"&"+reflect);
        pf = (str_str)GetProcAddress(hDll,"_revoke@4");
    }
    if (pf == NULL)
        return;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString time_str = current_date_time.toString("hh:mm:ss");
    ui->log_edit->append(time_str+REQUEST_CALL+"revoke:"+cmd+"\n");
    ui->log_edit->repaint();
    app->processEvents();
    string str = cmd.toUtf8().toStdString();
    string ret = (*pf)(str.c_str());

    current_date_time = QDateTime::currentDateTime();
    time_str = current_date_time.toString("hh-mm-ss");
    ui->log_edit->append(time_str+REQUEST_RESULT+QString::fromStdString(ret)+"\n");
    ui->card_id_edit->clear();
}
