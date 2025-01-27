#include "BaseNaviWidget.h"

BaseNaviWidget::BaseNaviWidget(QWidget *parent) : QWidget(parent),timer(new QTimer(this)){
    connect(timer, &QTimer::timeout, this, &BaseNaviWidget::onTimeout);
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

void BaseNaviWidget::onTimeout(){
    QStringList data = getNavigationData();
    if(!data.empty()) sendData(data);
}