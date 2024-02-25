#include "filetask.h"

FileTask::FileTask(QObject *parent) : Task(parent){

    this->filePath = "C:/ESEMPIO.txt";
}

void FileTask::setPeriod(int seconds){
    this->periodInSeconds = seconds;
}

void FileTask::setSchedule(const QString & schedule){
    this->schedule = schedule;
}

void FileTask::execute(){
    QFile file(this->filePath);
    file.exists()? qDebug() << "File Exists.": qDebug() << "File doesn't exist.";
    emit taskCompleted();
}
