#ifndef TASK_H
#define TASK_H

#include "allReference.h"

class Task : public QObject{
    Q_OBJECT //enables Qt signal and slot support
protected:
    QDateTime startDateTime;//When the task should be started
    QString periodicityDays;//the periodicity for days
    int periodicitySeconds;//the periodicity for seconds

public:
    Task(QObject *parent = nullptr);//constructor
    virtual ~Task();//deconstructor

    //Functions
    virtual void execute() = 0;

    //Set functions
    void setStartDateTime(const QDateTime &startDateTime);
    void setPeriodicitySeconds(int periodicityseconds);
    void setPeriodicityDays(QString periodictyDays);

    //Get functions
    QDateTime getStartDateTime();
    QString getPeriodicityDays();
    int getPeriodicitySeconds();

signals:
    void taskCompleted();
};
#endif
