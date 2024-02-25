#ifndef ALLREFERENCE_H
#define ALLREFERENCE_H

#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QMainWindow>
#include <QMap>
#include <QMenu>
#include <QObject>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QTimeEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QComboBox>

#include "QtWidgets/qpushbutton.h"

inline bool validateTime(int minute, int hour, int dayOfMonth, int month, int dayOfWeek) {
    if (minute < 0 || minute > 59) {
        qDebug() << "ERROR: MINUTE TIME IS NOT VALID";
        return false;
    }
    if (hour < 0 || hour > 23) {
        qDebug() << "ERROR: HOUR TIME IS NOT VALID";
        return false;
    }
    if (dayOfMonth < 1 || dayOfMonth > 31) {
        qDebug() << "ERROR: DAY OF THE MONTH IS NOT VALID";
        return false;
    }
    if (month < 1 || month > 12) {
        qDebug() << "ERROR: MONTH IS NOT VALID";
        return false;
    }
    if (dayOfWeek < 0 || dayOfWeek > 9) {
        qDebug() << "ERROR: DAY OF THE WEEK IS NOT VALID";
        return false;
    }
    return true;
}
#endif // ALLREFERENCE_H
