#include "texttask.h"
#include "task.cpp"
TextTask::TextTask(QObject *parent) : Task(parent) {
}

void TextTask::setText(const QString &text) {
    this->text = text;
}

QString TextTask::getText() const {
    return text;
}

void TextTask::execute(){
    //show the content of the text
    qDebug() << this->text;
    //emit a signal when the task is completed
    emit taskCompleted();
}
