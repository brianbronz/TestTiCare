#include "filetask.h"

FileTask::FileTask(QObject *parent) : Task(parent){
    //Default name of the file
    this->filePath = "C:/ESEMPIO.txt";
}

void FileTask::setFileName(const QString &fileName) {
    this->filePath = fileName;
}

QString FileTask::getFileName() const {
    return filePath;
}


void FileTask::execute(){
    QFile file(this->filePath);
    //check if the file exists
    //Only in case the file doesn't exist
    if (!file.exists()) {
        qDebug() << "File doesn't exist.";
    }
    //emit a signal when the task is completed
    emit taskCompleted();
}
