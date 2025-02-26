#pragma once

#include <QWidget>
#include <QtPlugin>
#include <QTimer>
#include <nmea.h>

#ifdef BASENAVIWIDGET_LIBRARY
#define BASENAVIWIDGET_EXPORT Q_DECL_EXPORT
#else
#define BASENAVIWIDGET_EXPORT Q_DECL_IMPORT
#endif

class BASENAVIWIDGET_EXPORT BaseNaviWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseNaviWidget(QWidget *parent = nullptr);
    explicit BaseNaviWidget(int timerInterval = 1000,QWidget *parent = nullptr);
    ~BaseNaviWidget();
public:
    bool isActive();
    /// @brief Запуск отправки данных
    void startSend();
    /// @brief Остановка оправки данных
    void stopSend();
    /// @brief Иконка плагина
    /// @return QIcon 
    virtual QIcon icon() const = 0;
    /// @brief Название плагина
    /// @return QString 
    virtual QString name() const = 0;
    /// @brief Описание плагина 
    /// @return QString 
    virtual QString description() const = 0;
signals:
    void sendData(QStringList data);
protected slots:
    virtual QStringList getNavigationData() = 0;
private slots:
    void onTimeout();
protected:  
    int tickInterval = 1000;
private:
    QTimer *timer = nullptr;
};

// Объявляем интерфейс для плагинов
Q_DECLARE_INTERFACE(BaseNaviWidget, "com.example.BaseNaviWidget/1.0")
