#include "filetask.h"

FileTask::FileTask(QObject *parent) : Task(parent){

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
    file.exists()? qDebug() << "File Exists.": qDebug() << "File doesn't exist.";
    emit taskCompleted();
}
