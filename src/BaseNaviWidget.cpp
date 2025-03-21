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

QString getRetranslatePref(QString retranslatepr){
    return QString();
}

void BaseNaviWidget::setRetranslate(QString retranslateName){
    if (qApp->removeTranslator(translator)) {
        qDebug() << "Removed previous translator";
    }
    QString name = getRetranslatePref(retranslateName);
    // Загружаем новый перевод
    if (translator->load(retranslateName)) {
        if (qApp->installTranslator(translator)) {
            qDebug() << "Installed translator for" << retranslateName;
            retranslate();
        } else {
            qDebug() << "Failed to install translator for" << retranslateName;
        }
    } else {
        qDebug() << "Failed to load translation file for" << retranslateName;
    }
}

void BaseNaviWidget::retranslate(){}