#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "task.h"

class Schedule : public QObject{
    Q_OBJECT
private:
    QMap<Task*, QString> taskScheduleMap; //Map that associates each task to the respective schedule
    QList<QTimer*> timers; //list of timers to execute tasks

private slots:
    void executeTask(Task *task);//slot to execute a task when finishe the timer

public:
    Schedule(QObject *parent = nullptr);
    virtual ~Schedule();

    //Functions
    void addTask(Task *task, const QString & schedule); //add a task to the schedule
    int convertScheduleToMillisecond(const QString &schedule);//convert to millisecond a schedule
    void start(); //start the schedule
    void stop(); //stop the schedule
};
#endif
