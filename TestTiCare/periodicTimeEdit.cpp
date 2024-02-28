#include "periodicTimeEdit.h"

PeriodicTimeEdit::PeriodicTimeEdit(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    QGroupBox *groupBox = new QGroupBox("Periodic Days", this);
    QVBoxLayout *groupBoxLayout = new QVBoxLayout(groupBox);

    // Add a box for each day of the week
    QStringList daysOfWeek = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    foreach (const QString &day, daysOfWeek) {
        QCheckBox *checkBox = new QCheckBox(day, groupBox);
        groupBoxLayout->addWidget(checkBox);
    }
    //periodic times
    periodicitySpinBox = new QSpinBox(this);
    periodicitySpinBox->setSuffix(" secondi");
    periodicitySpinBox->setMinimum(0);
    periodicitySpinBox->setMaximum(86400); // max value 24 hours
    periodicitySpinBox->setValue(10); // Default 10 seconds
    layout->addWidget(periodicitySpinBox);
    layout->addWidget(groupBox);
    dayOfWeekComboBox = groupBox;
}

QTime PeriodicTimeEdit::getTime() const {
    return timeEdit->time();
}


QStringList PeriodicTimeEdit::getSelectedDaysOfWeek() const{
    QStringList selectedDays;
    QList<QCheckBox *> dayCheckBox = this->findChildren<QCheckBox *>();
    foreach(QCheckBox * checkBox, dayCheckBox){
        if(checkBox->isChecked()){
            selectedDays.append(checkBox->text());
        }
    }
    return selectedDays;
}

int PeriodicTimeEdit::getPeriodicity() const {
    return periodicitySpinBox->value();
}

void PeriodicTimeEdit::setTime(const QTime &time) {
    timeEdit->setTime(time);
}

void PeriodicTimeEdit::resetPeriodicityDay(){
    QList<QCheckBox *> dayCheckBox = this->findChildren<QCheckBox *>();
    foreach(QCheckBox * checkBox, dayCheckBox){
        if(checkBox->isChecked()){
            checkBox->setChecked(false);
        }
    }
}

void PeriodicTimeEdit::resetTime(){
    this->periodicitySpinBox->setValue(10);
}
