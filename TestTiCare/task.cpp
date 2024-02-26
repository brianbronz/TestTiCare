#include "task.h"

//constructor
Task::Task(QObject *parent) : QObject(parent) {}

//decinstructor
Task::~Task() {}

//Set functions
void Task::setStartDateTime(const QDateTime &startDateTime) {
    this->startDateTime = startDateTime;
}

void Task::setPeriodicityDays(QString periodicityDays) {
    this->periodicityDays = periodicityDays;
}
void Task::setPeriodicitySeconds(int periodicitySeconds) {
    this->periodicitySeconds = periodicitySeconds;
}

//Get functions
QDateTime Task::getStartDateTime(){
    return this->startDateTime;
}

QString Task::getPeriodicityDays(){
    return this->periodicityDays;
}

int Task::getPeriodicitySeconds(){
    return this->periodicitySeconds;
}

