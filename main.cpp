#include "store.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    store w;
    bool fecha;

    QSplashScreen *tela = new QSplashScreen;
    tela->setPixmap(QPixmap(":/Imgs/UI/splashscreen.png"));


    //w.show();


    fecha = w.verifica_logado();
    if(fecha == false)
    {
        w.close();
    }else{
        tela->show();
        QTimer::singleShot(2000,tela,SLOT(close()));
        QTimer::singleShot(2000,&w,SLOT(show()));
    }
    return a.exec();
    w.close();
    return 0;
}
