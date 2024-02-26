#ifndef PERIODICTIMEEDIT_H
#define PERIODICTIMEEDIT_H
#include "allReference.h"

class PeriodicTimeEdit : public QWidget {
    Q_OBJECT

private:
    QTimeEdit *timeEdit;
    QGroupBox *dayOfWeekComboBox;
    QSpinBox *periodicitySpinBox;

public:
    PeriodicTimeEdit(QWidget *parent = nullptr);

    QTime getTime() const;
    QStringList getSelectedDaysOfWeek() const;
    int getPeriodicity() const;
    void setTime(const QTime &time);
};

#endif // PERIODICTIMEEDIT_H
