#ifndef TEXTTASK_H
#define TEXTTASK_H
#include "task.h"

class TextTask : public Task{
    Q_OBJECT
private:
    QString text; //text to print

public:
    TextTask(QObject *parent = nullptr);
    //Override functions of the class Task
    void setPeriod(int seconds) override;
    QString getSchedule();
    void setText(QString & text);
    QString getText();
    void setSchedule(const QString & schedule) override;
    void execute() override;
};

#endif // TEXTTASK_H
