#include "task.h"

//Constructor
Task::Task(QObject * parent): QObject(parent){
    this->timer = new QTimer(this);
    this->periodInSeconds = 0;
    connect(this->timer, &QTimer::timeout, this, &Task::execute);
}

Task::~Task(){
    delete this->timer;
}

bool Task::isRunning() const{
    return this->timer->isActive();
}

void Task::setPeriod(int seconds){
    this->periodInSeconds = seconds;
    timer->setInterval(seconds * 1000); //convert to milliseconds
}

//To check
void Task::setSchedule(const QString & schedule){
    this->schedule = schedule;
    //parsing of the schedule
    QStringList parts = this->schedule.split(" ");
    if(parts.size() == 5){
        int minute, hour, dayOfMonth, month, dayOfWeek;
        minute = parts[0].toInt();
        hour = parts[1].toInt();
        dayOfMonth = parts[2].toInt();
        month = parts[3].toInt();
        dayOfWeek = parts[4].toInt();
        if (!validateTime(minute, hour, dayOfMonth, month, dayOfWeek)) {
            return;
        }
    } else {
        qDebug() << "ERROR IN THE FORMAT";
    }
}

void Task::execute(){
    emit taskCompleted();
}
