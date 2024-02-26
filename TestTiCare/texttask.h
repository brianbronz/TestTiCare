#ifndef TEXTTASK_H
#define TEXTTASK_H

#include "task.h"

class TextTask : public Task {
    Q_OBJECT
private:
    QString text; // Testo da stampare

public:
    TextTask(QObject *parent = nullptr);
    virtual void execute() override;
    void setText(const QString &text); // Imposta il testo
    QString getText() const; // Ottiene il testo
};

#endif // TEXTTASK_H
