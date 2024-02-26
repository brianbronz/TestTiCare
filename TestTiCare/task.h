#ifndef TASK_H
#define TASK_H

#include "allReference.h"

class Task : public QObject{
    Q_OBJECT //enables Qt signal and slot support
protected:
    QDateTime startDateTime;
    QString periodicityDays;
    int periodicitySeconds;

public:
    Task(QObject *parent = nullptr);//constructor
    virtual ~Task();//deconstructor

    //Functions
    virtual void execute() = 0;

    void setStartDateTime(const QDateTime &startDateTime);
    QDateTime getStartDateTime();
    void setPeriodicitySeconds(int periodicityseconds);
    int getPeriodicitySeconds();
    void setPeriodicityDays(QString periodictyDays);
    QString getPeriodicityDays();

signals:
    void taskCompleted();
};
#endif
