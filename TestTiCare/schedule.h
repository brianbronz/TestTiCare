#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "task.h"

class Schedule : public QObject{
    Q_OBJECT
private:
    QList<Task*> taskList; //list of task to execute
    Task * currentTask;
public:
    Schedule(QObject *parent = nullptr);
    virtual ~Schedule();

    //Functions
    void addTask(Task *task, const QString &executionTime); //add a task to the schedule
    void start(); //start a task in the schedule (then for loop and check every time if there is already an active task)
    void stop(); //stop the schedule (stop the task and remove it)
    bool hasPendingTask();
    int dayOfWeekFromString(const QString &dayString);//get the value of the day in the week
};
#endif
