#include "texttask.h"
#include "task.cpp"
TextTask::TextTask(QObject * parent) : Task(parent){
    this->text = "Default Text";
}


void TextTask::setPeriod(int seconds){
    this->periodInSeconds = seconds;
}

void TextTask::setSchedule(const QString & schedule){
    this->schedule = schedule;
}

QString TextTask::getSchedule(){
    return this->schedule;
}

void TextTask::setText(QString & text){
    this->text = text;
}

QString TextTask::getText(){
    return this->text;
}

void TextTask::execute(){
    qDebug() << this->text;
    emit taskCompleted();
}
