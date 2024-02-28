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

void Schedule::addTask(Task *task) {
    // Add a new task in the tasklist
    taskList.append(task);
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
        //get the next days to execute
        QString periodicityDay = currentTask->getPeriodicityDays();
        //Obtain a list of day to execute the task
        QStringList selectedDays = periodicityDay.split(",");
        // get the periodicity time in seconds
        int periodicitySecond = currentTask->getPeriodicitySeconds();
        //execute the task depending on the specific periodicity
        QTimer * timer = new QTimer(this);
        connect(timer, &QTimer::timeout, [=](){
            //Reset the current time
            QDateTime currentTime = QDateTime::currentDateTime();
            //If statement to check if the current task is nullptr, otherwise the program will crashed
            if(currentTask != nullptr){
                if(selectedDays[0] == ""){
                    //execute indipendently from the time, because we wait until the start of the task
                    currentTask->execute();
                } else {
                    //wait until the correct day of the week
                    //If i have different days, like friday and monday, I should check if my string selectedDays contains the current day
                    bool foundNextDays = false;
                    while(!foundNextDays){
                        int valueOfWeek = currentTime.date().dayOfWeek();
                        if(selectedDays.contains(dayOfWeekToString(valueOfWeek))){
                            foundNextDays = true;
                        } else {
                            //sleep the Thread for a specific time and reset the currentTime
                            QThread::msleep(10000);
                            currentTime = QDateTime::currentDateTime();
                        }
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
    //Stop the current task and set up the currentTask to nullptr
    if (currentTask != nullptr) {
        currentTask = nullptr;
    }
}

//Method to check if the tasklist doesn't have any other task
bool Schedule::hasPendingTask(){
    return taskList.isEmpty();
}

//Obtain the string of the day in a week, used for the periodicity day
QString Schedule::dayOfWeekToString(int dayOfWeek) {
    switch (dayOfWeek) {
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thursday";
        case 5: return "Friday";
        case 6: return "Saturday";
        case 7: return "Sunday";
        default: return "Invalid Day";// Not valid value
    }
}

void Schedule::removeLastTask(){
    this->taskList.removeLast();
}

int Schedule::getTaskCount(){
    return this->taskList.count();
}
