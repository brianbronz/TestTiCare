#ifndef TEXTTASK_H
#define TEXTTASK_H

#include "task.h"

class TextTask : public Task {
    Q_OBJECT
private:
    QString text; // Text to print

public:
    TextTask(QObject *parent = nullptr);
    virtual void execute() override;
    void setText(const QString &text); // Set up the text
    QString getText() const; // Get the text
};

#endif // TEXTTASK_H
