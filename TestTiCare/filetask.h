#ifndef FILETASK_H
#define FILETASK_H

#include "task.h"

class FileTask : public Task{
    Q_OBJECT
private:
    QString filePath; //Path to check

public:
    FileTask(QObject *parent = nullptr);
    //Override functions of the class Task
    void setPeriod(int seconds) override;
    void setSchedule(const QString & schedule) override;
    void execute() override;
};

#endif // FILETASK_H
