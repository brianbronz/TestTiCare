#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filetask.h"
#include "texttask.h"
#include "periodicTimeEdit.h"

//Constructor
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    // Initialize UI elements
    setUpUiElements();
    //set up the connections
    setUpActionsConnections();
    //Initialize the schedule
    this->schedule = new Schedule(this);
}

//Deconstructor
MainWindow::~MainWindow(){
    delete ui;
}

//Set up the actions
void MainWindow::setUpActionsConnections(){
    //Connection of actions to the slots
    connect(startButton, &QPushButton::clicked, this, &MainWindow::switchSchedule);
    connect(addTask, &QPushButton::clicked, this, &MainWindow::addSingleTask);
    connect(checkBox, &QCheckBox::stateChanged, this, &MainWindow::handleCheckBoxStateChanged);
    connect(removeTask, &QPushButton::clicked, this, &MainWindow::removeLastTask);
}

//Set up the interfaces
void MainWindow::setUpUiElements() {
    QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
    addButtons(layout);
    addRemoveLastTaskButtonAndCount(layout);
    addTextEdit(layout);
    addCheckBox(layout);
    addTimeControls(layout);
    addPeriodicTimeEdit(layout);
}

void MainWindow::addButtons(QVBoxLayout *layout) {
    //Adds two buttons, one to start a task and the other add a new task
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    this->addTask = new QPushButton("Add Task", this);
    this->startButton = new QPushButton("Start Task", this);
    buttonLayout->addWidget(addTask);
    buttonLayout->addWidget(startButton);
    this->startButton->setEnabled(false);
    layout->addLayout(buttonLayout);
}

void MainWindow::addTextEdit(QVBoxLayout *layout) {
    //add the text plane
    textEdit = new QTextEdit(this);
    layout->addWidget(textEdit);
}

void MainWindow::addCheckBox(QVBoxLayout *layout) {
    //add the check box to (dis)able the text plane
    checkBox = new QCheckBox("Disable the text", this);
    layout->addWidget(checkBox);
}

void MainWindow::addTimeControls(QVBoxLayout *layout) {
    // Create and configure the QLabel for date and time
    QLabel *dateTimeLabel = new QLabel("Date (DD/MM/YYYY) Time (HH:MM:SS):", this);

    // Create and configure the QDateTimeEdit
    QDateTimeEdit *dateTimeEdit = new QDateTimeEdit(this);
    dateTimeEdit->setDisplayFormat("dd/MM/yyyy HH:mm:ss"); // Format of date and time
    dateTimeEdit->setDateTime(QDateTime::currentDateTime()); // set up the initial date and time

    // Add the horizontal layout to the main layout
    layout->addWidget(dateTimeLabel);
    // Add the dateTimeEdit layout
    layout->addWidget(dateTimeEdit);
    // Assign the QDateTimeEdit to clockEdit
    this->clockEdit = dateTimeEdit;
}

void MainWindow::addPeriodicTimeEdit(QVBoxLayout *layout) {
    //Add the object of the periodicTimeEdit to select specific periodic days
    this->periodicTimeEdit = new PeriodicTimeEdit(this);
    layout->addWidget(this->periodicTimeEdit);

}

void MainWindow::addRemoveLastTaskButtonAndCount(QVBoxLayout *layout) {
    QHBoxLayout *buttonAndCountLayout = new QHBoxLayout();
    this->removeTask = new QPushButton("Remove the last task", this);
    this->removeTask->setEnabled(false);
    //Show the number of task in the schedule
    numTask = new QLabel(this);
    numTask->setText(QString("Number of tasks in the schedule: %1").arg(0));

    buttonAndCountLayout->addWidget(numTask);
    buttonAndCountLayout->addWidget(this->removeTask);
    layout->addLayout(buttonAndCountLayout);
}

void MainWindow::addSingleTask(){
    //Get the parameters from the GUI
    /*
     * - when the task starts/is planned
     * - periodic time in seconds
     * - periodic time for days
     */
    QDateTime startDateTime = this->clockEdit->dateTime();
    int periodicityTime = periodicTimeEdit->getPeriodicity();
    QStringList dayOfWeek = periodicTimeEdit->getSelectedDaysOfWeek();

    QString selectedPeriodicity = dayOfWeek.join(",");

    //Create a Task object (is the super class of texttask and filetask)
    Task *newTask = nullptr;
    if(this->checkBox->isChecked()){
        //case filetask
        newTask = new FileTask(this);
    } else{
        //case text edit
        newTask = new TextTask(this);
        QString text = textEdit->toPlainText();
        if(text != ""){
            static_cast<TextTask*>(newTask)->setText(text);
        }
    }
    //Initialize the periodic days, seconds and when the task is planned to do
    newTask->setPeriodicityDays(selectedPeriodicity);
    newTask->setPeriodicitySeconds(periodicityTime);
    newTask->setStartDateTime(startDateTime);
    //add the task to the schedule
    this->schedule->addTask(newTask);
    updateTaskCountLabel();

    if(this->startButton->isEnabled()){
        this->startButton->setEnabled(true);
    }

    //reset the periodic day
    this->periodicTimeEdit->resetPeriodicityDay();
    this->periodicTimeEdit->resetTime();
    //Reset the text edit, respectively set up for a text
    if(!this->checkBox->isChecked()){
        this->textEdit->clear();
    } else {
        textEdit->setEnabled(true);
        this->checkBox->setChecked(false);
    }
}

void MainWindow::handleCheckBoxStateChanged(int state) {
    // Check the value of the checkbox
    if(state == Qt::Checked){
        // if true disable the text Edit and reset it to empty
        textEdit->setEnabled(false);
        textEdit->clear();
    } else {
        //else able the text edit
        textEdit->setEnabled(true);
    }
}

void MainWindow::switchSchedule(){
    //Change the text of the button to start/stop a task
    if (startButton->text() == "Start Task") {
        this->startButton->setText("Stop Task");
        this->schedule->start();
    } else {
        this->startButton->setText("Start Task");
        this->schedule->stop();
        updateTaskCountLabel();
        //Check if inside the schedule there is a task, in case execute it automatically
        if(!this->schedule->hasPendingTask()){
            this->startButton->setText("Stop Task");
            this->schedule->start();
        }
    }
};

//Remove the last Task you added
void MainWindow::removeLastTask(){
    schedule->removeLastTask();
    updateTaskCountLabel();
}

//Update the number of task in the schedule
void MainWindow::updateTaskCountLabel(){
    int taskCount = schedule->getTaskCount();
    numTask->setText(QString("Number of tasks in the schedule: %1").arg(taskCount));
    //(dis)able the start and remove task button
    if(taskCount != 0){
        this->removeTask->setEnabled(true);
        this->startButton->setEnabled(true);
    } else {
        this->removeTask->setEnabled(false);
        this->startButton->setEnabled(false);
    }
}
