#include "dialog.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    w.app = &a;

    return a.exec();
}
