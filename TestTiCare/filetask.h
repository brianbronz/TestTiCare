#ifndef FILETASK_H
#define FILETASK_H

#include "task.h"

class FileTask : public Task{
    Q_OBJECT
private:
    QString filePath; //Path/name of the file to check

public:
    FileTask(QObject *parent = nullptr);//constructor
    virtual void execute() override;//deconstructor
    void setFileName(const QString &fileName); // Set the name of the file
    QString getFileName() const; // Get the name of the file
};

#endif // FILETASK_H
