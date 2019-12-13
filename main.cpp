#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    
	a.setStyle("fusion");
    
	MainWindow w;
    
	w.setWindowTitle("Archylex CALC 2018 \"Практика\"");
    w.setWindowIcon(QIcon(":/calc.png"));
    w.setFixedSize(w.width(), w.height());
    w.show();

    return a.exec();
}
