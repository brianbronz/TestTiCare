#ifndef TASK_H
#define TASK_H

#include "allReference.h"

class Task : public QObject{
    Q_OBJECT //enables Qt signal and slot support
protected:
    QTimer * timer;//Timer to execute periodically the task
    int periodInSeconds;//Task periodicity in seconds
    QString schedule;//Task's schedule

public:
    Task(QObject *parent = nullptr);//constructor
    virtual ~Task();//deconstructor

    //Functions
    bool isRunning() const;
    virtual void setPeriod(int seconds) = 0;
    virtual void setSchedule(const QString & schedule) = 0;

public slots:
    virtual void execute() = 0;

signals:
    void taskCompleted();
};
#endif
