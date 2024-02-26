#include "task.h"

Task::Task(QObject *parent) : QObject(parent) {}

Task::~Task() {}

void Task::setStartDateTime(const QDateTime &startDateTime) {
    this->startDateTime = startDateTime;
}

QDateTime Task::getStartDateTime(){
    return this->startDateTime;
}

void Task::setPeriodicitySeconds(int periodicitySeconds) {
    this->periodicitySeconds = periodicitySeconds;
}

int Task::getPeriodicitySeconds(){
    return this->periodicitySeconds;
}

void Task::setPeriodicityDays(QString periodicityDays) {
    this->periodicityDays = periodicityDays;
}

QString Task::getPeriodicityDays(){
    return this->periodicityDays;
}
