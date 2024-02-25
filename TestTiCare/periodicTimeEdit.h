#ifndef PERIODICTIMEEDIT_H
#define PERIODICTIMEEDIT_H
#include "allReference.h"

class PeriodicTimeEdit : public QWidget {
    Q_OBJECT
public:
    PeriodicTimeEdit(QWidget *parent = nullptr);

    QTime getTime() const;
    void setTime(const QTime &time);
    int getDayOfWeek() const;
    int getPeriodicity() const;
    QString getPeriodicitygetNamePeriodicDay(int dayOfWeek) const;
private:
    QTimeEdit *timeEdit;
    QComboBox *dayOfWeekComboBox;
    QSpinBox *periodicitySpinBox;
};

#endif // PERIODICTIMEEDIT_H
