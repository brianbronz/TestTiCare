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
    // Create and configure of QTimeEdit to start at a specific time
    QTimeEdit *timeEdit = new QTimeEdit(this);
    timeEdit->setDisplayFormat("hh:mm:ss"); // Format of the hours
    timeEdit->setTime(QTime(0, 0, 0)); // set up the initial time

    // Adding the QTimeEdit to layout
    layout->addWidget(timeEdit);

    // assign the timeclock
    this->clockEdit = timeEdit;
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
    }
};

void MainWindow::addSingleTask(){
    QTime time = this->clockEdit->time();
    QString timeToStart = time.toString("hh:mm:ss");
    int periodicityTime = periodicTimeEdit->getPeriodicity();
    int dayOfWeek = periodicTimeEdit->getDayOfWeek();

    QString selectedPeriodicity = periodicTimeEdit->getPeriodicitygetNamePeriodicDay(dayOfWeek);
    qDebug() << timeToStart << " l'orario della task";
    qDebug() << "Periodicita: " << periodicityTime << " in secondi";
    qDebug() << this->checkBox->isChecked();
    qDebug() << selectedPeriodicity << " periodicita dei giorni";
    if(this->checkBox->isChecked()){
        //case filetask
        FileTask * ft = new FileTask(this);
        qDebug() << "FileTask created";
        ft->setSchedule(timeToStart);
        this->schedule->addTask(ft, timeToStart);
    } else{
        //case text edit
        TextTask * tt = new TextTask(this);
        QString text = textEdit->toPlainText();
        if(text != ""){
            tt->setText(text);
        }
        qDebug() << "TextTask created";
        qDebug() << tt->getText();
        tt->setSchedule(timeToStart);
        qDebug() << tt->getSchedule();
        this->schedule->addTask(tt, timeToStart);
    }
}
