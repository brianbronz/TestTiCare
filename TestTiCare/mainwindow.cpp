#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filetask.h"
#include "texttask.h"
#include "periodicTimeEdit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize UI elements
    setupUiElements();
    //set up the connections
    setUpActionsConnections();
    //Initialize the schedule
    this->schedule = new Schedule(this);
}

void MainWindow::addPeriodicTimeEdit(QVBoxLayout *layout) {
    this->periodicTimeEdit = new PeriodicTimeEdit(this);
    layout->addWidget(this->periodicTimeEdit);

}

void MainWindow::setupUiElements() {
    QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
    addButtons(layout);
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
    layout->addLayout(buttonLayout);
}

void MainWindow::addTextEdit(QVBoxLayout *layout) {
    //add the text plane
    textEdit = new QTextEdit(this);
    layout->addWidget(textEdit);
}

void MainWindow::addCheckBox(QVBoxLayout *layout) {
    //add the check box to (dis)able the plane text
    checkBox = new QCheckBox("Checkbox", this);
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

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::setUpActionsConnections(){
    //Connection of actions to the slots
    connect(startButton, &QPushButton::clicked, this, &MainWindow::switchSchedule);
    connect(addTask, &QPushButton::clicked, this, &MainWindow::addSingleTask);
    connect(checkBox, &QCheckBox::stateChanged, this, &MainWindow::handleCheckBoxStateChanged);
}


void MainWindow::handleCheckBoxStateChanged(int state) {
    // Check the value of the checkbox
    if(state == Qt::Checked){
        // if true disable the text Edit and reset it to empty
        textEdit->setEnabled(false);
        textEdit->clear();
    } else {
        textEdit->setEnabled(true);
    }
}

void MainWindow::switchSchedule(){
    if (startButton->text() == "Start Task") {
        this->startButton->setText("Stop Task");
        this->schedule->start();
    } else {
        this->startButton->setText("Start Task");
        this->schedule->stop();
        //verificare la presenza di un'altra task all;interno della schedule
        if(!this->schedule->hasPendingTask()){
            this->startButton->setText("Stop Task");
            this->schedule->start();
        }
    }
};

void MainWindow::addSingleTask(){
    QDateTime startDateTime = this->clockEdit->dateTime();
    int periodicityTime = periodicTimeEdit->getPeriodicity();
    int dayOfWeek = periodicTimeEdit->getDayOfWeek();

    QString selectedPeriodicity = periodicTimeEdit->getPeriodicitygetNamePeriodicDay(dayOfWeek);

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
    newTask->setPeriodicityDays(selectedPeriodicity);
    newTask->setPeriodicitySeconds(periodicityTime);
    newTask->setStartDateTime(startDateTime);
    this->schedule->addTask(newTask, startDateTime.toString());
    //Reset the text edit, respectively set up for a text
    if(!this->checkBox->isChecked()){
        this->textEdit->clear();
    } else {
        textEdit->setEnabled(true);
        this->checkBox->setChecked(false);
    }
}
