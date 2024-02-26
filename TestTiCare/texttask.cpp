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
    qDebug() << this->text;
    emit taskCompleted();
}
