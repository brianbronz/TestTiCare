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

    QSystemTrayIcon * trayIcon;
    QPushButton *startButton;
    QPushButton *addTask;
    QCheckBox *checkBox;
    QDateTimeEdit *clockEdit;
    QTextEdit *textEdit;

    PeriodicTimeEdit *periodicTimeEdit;
    Schedule *schedule;

    //Functions
    void setupUiElements();
    void addButtons(QVBoxLayout *layout);
    void addTextEdit(QVBoxLayout *layout);
    void addCheckBox(QVBoxLayout *layout);
    void addTimeControls(QVBoxLayout *layout);
    void addPeriodicTimeEdit(QVBoxLayout *layout);
    void addSingleTask();
    void setUpActionsConnections();

private slots:
    void switchSchedule();
    void handleCheckBoxStateChanged(int state);
};
#endif // MAINWINDOW_H
