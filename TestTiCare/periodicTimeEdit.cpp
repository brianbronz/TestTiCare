#include "periodicTimeEdit.h"
PeriodicTimeEdit::PeriodicTimeEdit(QWidget *parent) : QWidget(parent) {
    QComboBox *periodicityComboBox = new QComboBox(this);
    QHBoxLayout *layout = new QHBoxLayout(this);
    //Periodic days
    periodicityComboBox->addItem("No periodicity Days");
    periodicityComboBox->addItem("Every Day");
    periodicityComboBox->addItem("Every Monday");
    periodicityComboBox->addItem("Every Tuesday");
    periodicityComboBox->addItem("Every Wednesday");
    periodicityComboBox->addItem("Every Thursday");
    periodicityComboBox->addItem("Every Friday");
    periodicityComboBox->addItem("Every Saturday");
    periodicityComboBox->addItem("Every Sunday");

    //periodic times
    periodicitySpinBox = new QSpinBox(this);
    periodicitySpinBox->setSuffix(" secondi");
    periodicitySpinBox->setMinimum(0);
    periodicitySpinBox->setMaximum(86400); // max value 24 hours
    periodicitySpinBox->setValue(10); // Default 10 seconds
    layout->addWidget(periodicitySpinBox);
    layout->addWidget(periodicityComboBox);
    dayOfWeekComboBox = periodicityComboBox;
}
QTime PeriodicTimeEdit::getTime() const {
    return timeEdit->time();
}

void PeriodicTimeEdit::setTime(const QTime &time) {
    timeEdit->setTime(time);
}

int PeriodicTimeEdit::getDayOfWeek() const {
    return dayOfWeekComboBox->currentIndex(); // 0 for no days, 1 every day, 2 every monday, ....
}

int PeriodicTimeEdit::getPeriodicity() const {
    return periodicitySpinBox->value();
}

QString PeriodicTimeEdit::getPeriodicitygetNamePeriodicDay(int dayOfWeek) const{
    switch (dayOfWeek) {
    case 1: return "Every Day"; break;
    case 2: return "Every Monday"; break;
    case 3: return "Every Tuesday"; break;
    case 4: return "Every Wednesday"; break;
    case 5: return "Every Thursday"; break;
    case 6: return "Every Friday"; break;
    case 7: return "Every Saturday"; break;
    case 8 : return "Every Sunday"; break;
    default: return "No periodicity Days"; break;
    }
}
