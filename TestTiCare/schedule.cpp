#include "schedule.h"

QMap<QString, int> dayOfWeekMap = {
    {"Monday", Qt::Monday},
    {"Tuesday", Qt::Tuesday},
    {"Wednesday", Qt::Wednesday},
    {"Thursday", Qt::Thursday},
    {"Friday", Qt::Friday},
    {"Saturday", Qt::Saturday},
    {"Sunday", Qt::Sunday}
};

Schedule::Schedule(QObject *parent) : QObject(parent), currentTask(nullptr){}

Schedule::~Schedule() {}

void Schedule::addTask(Task *task, const QString &executionTime) {
    // Add a new task in the tasklist
    taskList.append(task);

    // Calcola il tempo rimanente fino all'esecuzione del task
    /*QDateTime currentTime = QDateTime::currentDateTime();
    QDateTime executionDateTime = QDateTime::fromString(executionTime, "yyyy-MM-dd hh:mm:ss");
    int millisecondsToExecute = currentTime.msecsTo(executionDateTime);

    // Se il tempo rimanente è negativo, imposta un timeout di 0 millisecondi
    if (millisecondsToExecute < 0) {
        millisecondsToExecute = 0;
    }

    // Crea un timer per eseguire il task al momento specificato
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        qDebug() << "Esecuzione task programmato per" << executionTime;
        task->execute();
        taskList.removeOne(task);
        if (!taskList.isEmpty()) {
            // Prende il prossimo task dalla coda e lo esegue
            currentTask = taskList.takeFirst();
            currentTask->execute();
        } else {
            // Se non ci sono altri task in coda, imposta il task corrente a nullptr
            currentTask = nullptr;
        }
    });
    timer->setSingleShot(true); // Imposta il timer per un'unica esecuzione
    timer->start(millisecondsToExecute); // Avvia il timer*/
}

void Schedule::start() {
    //start a task and complete
    if (!taskList.isEmpty() && currentTask == nullptr) {

        currentTask = taskList.takeFirst();
        QDateTime currentTime = QDateTime::currentDateTime();
        QDateTime dateStartTask = currentTask->getStartDateTime();
        int timeToWait = currentTime.msecsTo(dateStartTask);
        if(timeToWait < 0){
            timeToWait = 0;
        }
        //Wait until the start of the task
        QThread::msleep(timeToWait);
        //get the next day to execute
        QString periodicityDay = currentTask->getPeriodicityDays();
        int periodicitySecond = currentTask->getPeriodicitySeconds();
        QStringList parts = periodicityDay.split(" ");
        QString nextDay = "";
        //take the nextDay
        if(parts[0] !="No"){
            if(parts[1] == "Day"){
                nextDay = "Every";
            } else {
                nextDay = parts[1];
            }
        }

        //execute the task depending on the specific periodicity
        QTimer * timer = new QTimer(this);
        connect(timer, &QTimer::timeout, [=](){
            //If statement to check if the current task is nullptr, otherwise the program will crashed
            if(currentTask != nullptr){
                if(nextDay.isEmpty() || nextDay == "Every"){
                    //execute indipendently from the time, because we wait until the start of the task
                    currentTask->execute();
                } else {
                    //wait until the correct day of the week
                    while (QDateTime::currentDateTime().date().dayOfWeek() != dayOfWeekFromString(nextDay)){
                        QThread::msleep(10000);
                    }
                    currentTask->execute();
                }
            }
        });

        if(periodicitySecond != 0){
            timer->start(periodicitySecond * 1000);
        }
    }
}

void Schedule::stop() {
    //Stop the current task
    if (currentTask != nullptr) {
        currentTask = nullptr;
    }
}

bool Schedule::hasPendingTask(){
    return taskList.isEmpty();
}

int Schedule::dayOfWeekFromString(const QString &dayString) {
    if (dayString == "Monday") return 1;
    else if (dayString == "Tuesday") return 2;
    else if (dayString == "Wednesday") return 3;
    else if (dayString == "Thursday") return 4;
    else if (dayString == "Friday") return 5;
    else if (dayString == "Saturday") return 6;
    else if (dayString == "Sunday") return 7;
    else return -1; // Valore non valido
}
