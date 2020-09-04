#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

int main(int argc, char* argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);
    // set style sheet
    QFile file(":/qss/qss/main.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    qApp->setStyleSheet(stylesheet);
    file.close();

    MainWindow w;
    w.show();

    return a.exec();
}
