#include "BaseNaviWidget.h"
#include <QEvent>
#include <qapplication.h>
BaseNaviWidget::BaseNaviWidget(QWidget *parent) : QWidget(parent),timer(new QTimer(this)),
translator(new QTranslator(this)){
    connect(timer, &QTimer::timeout, this, &BaseNaviWidget::onTimeout);
}
BaseNaviWidget::BaseNaviWidget(int timerInterval ,QWidget *parent ) : BaseNaviWidget(parent){
    if(timerInterval > 10 ) tickInterval = timerInterval;
}
BaseNaviWidget::~BaseNaviWidget(){

}

void BaseNaviWidget::startSend(){
    if(!timer->isActive())
        timer->start(tickInterval);
}

void BaseNaviWidget::stopSend(){
    if(timer->isActive())
        timer->stop();
}
bool BaseNaviWidget::isActive(){
    return timer->isActive();
}

void BaseNaviWidget::onTimeout(){
    QStringList data = getNavigationData();
    if(!data.empty()) sendData(data);
}
void BaseNaviWidget::setPos(double lat, double lon){}

void BaseNaviWidget::setRetranslate(QString retranslateName){
    // Удаляем текущий перевод
    if (qApp->removeTranslator(translator)) {
        qDebug() << "Removed previous translator";
    }
    QString name = getRetranslateName(retranslateName);
    // Загружаем новый перевод
    if (translator->load(name)) {
        if (qApp->installTranslator(translator)) {
            qDebug() << "Installed translator for" << objectName() <<name;
            retranslate();
        } else {
            qDebug() << "Failed to install translator for" << name;
        }
    } else {
        qDebug() << "Failed to load translation file for" << name;
    }
}
QString BaseNaviWidget::getRetranslateName(QString retranslateName){ return QString();}
void BaseNaviWidget::retranslate(){}