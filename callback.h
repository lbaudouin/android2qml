#ifndef MYCALLBACK_H
#define MYCALLBACK_H

#include <QObject>

class Callback : public QObject
{
    Q_OBJECT
public:
    explicit Callback(QObject *parent = 0);

    inline void sendSignalFromJava() { emit signalFromJava(); }
    inline void sendBoolFromJava(bool b) { emit boolFromJava(b); }
    inline void sendIntFromJava(int i) { emit intFromJava(i); }
    inline void sendStringFromJava(QString s) { emit stringFromJava(s); }
    inline void sendStringArrayFromJava(QStringList sl) { emit stringArrayFromJava(sl); }

signals:
    void signalFromJava();
    void boolFromJava(bool b);
    void intFromJava(int i);
    void stringFromJava(QString s);
    void stringArrayFromJava(QStringList sl);
};

#endif // MYCALLBACK_H
