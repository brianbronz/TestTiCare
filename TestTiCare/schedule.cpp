#include "schedule.h"

Schedule::Schedule(QObject * parent) : QObject(parent) {}

Schedule::~Schedule(){}

void Schedule::addTask(Task *task, const QString & schedule){
    this->taskScheduleMap.insert(task, schedule);
}

int Schedule::convertScheduleToMillisecond(const QString &schedule){
    //Parsing of the string
    QStringList parts = schedule.split(" ");
    if(parts.size() != 5){
        qDebug() << "ERROR IN THE FORMAT OF THE SCHEDULE";
        return -1;
    }
    int minute, hour, dayOfMonth, month, dayOfWeek;
    minute = parts[0].toInt();
    hour = parts[1].toInt();
    dayOfMonth = parts[2].toInt();
    month = parts[3].toInt();
    dayOfWeek = parts[4].toInt();
    if (!validateTime(minute, hour, dayOfMonth, month, dayOfWeek)) {
        return -1;
    }
    int ms = (minute * 60 + hour * 3600 + dayOfMonth * 86400 + month * 2592000 + dayOfWeek * 604800) * 1000;
    return ms;
}

void Schedule::start(){
    qDebug() << "10";
    for(auto it = taskScheduleMap.begin(); it != taskScheduleMap.end(); ++it){
        Task * task = it.key();
        const QString schedule = it.value();
        //create the timer for the task
        QTimer *timer = new QTimer(this);

        //connection
        connect(timer, &QTimer::timeout, [=](){
            executeTask(task);
        });

        //Setting
        int interval = convertScheduleToMillisecond(schedule);//conert the schedule in millisecond
        timer->start(interval);
    }
}

void Schedule::stop(){
    for(QTimer *timer : timers){
        timer->stop();
        delete timer;
    }
    timers.clear();
}

void Schedule::executeTask(Task *task){
    if(!task->isRunning()){
        task->execute();
    } else {
        QTimer::singleShot(0, [=](){
            executeTask(task);
        });
    }
}
