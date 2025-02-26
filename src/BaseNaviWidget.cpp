#include "BaseNaviWidget.h"

BaseNaviWidget::BaseNaviWidget(QWidget *parent) : QWidget(parent),timer(new QTimer(this)){
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