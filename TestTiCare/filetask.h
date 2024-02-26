#ifndef FILETASK_H
#define FILETASK_H

#include "task.h"

class FileTask : public Task{
    Q_OBJECT
private:
    QString filePath; //Path to check

public:
    FileTask(QObject *parent = nullptr);
    virtual void execute() override;
    void setFileName(const QString &fileName); // Imposta il nome del file
    QString getFileName() const; // Ottiene il nome del file
};

#endif // FILETASK_H
