#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "schedule.h"
#include "periodicTimeEdit.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //field variables for the interfaces
    QCheckBox *checkBox;
    QDateTimeEdit *clockEdit;
    QSystemTrayIcon *trayIcon;
    QTextEdit *textEdit;
    QPushButton *startButton;
    QPushButton *addTask;

    PeriodicTimeEdit *periodicTimeEdit;
    Schedule *schedule;

    //Set Functions
    void setUpActionsConnections();
    void setUpUiElements();

    //add functions: interfaces
    void addButtons(QVBoxLayout *layout);
    void addTextEdit(QVBoxLayout *layout);
    void addCheckBox(QVBoxLayout *layout);
    void addTimeControls(QVBoxLayout *layout);
    void addPeriodicTimeEdit(QVBoxLayout *layout);

    //add a single task
    void addSingleTask();

private slots:
    //Private methods
    void switchSchedule();//from start to stop task, and viceversa
    void handleCheckBoxStateChanged(int state);//from file to text, and viceversa
};
#endif // MAINWINDOW_H
