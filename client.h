#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QAndroidJniEnvironment>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

protected:
    static void callbackWithoutArguments(JNIEnv *env, jobject obj);
    static void callbackWithBool(JNIEnv *env, jobject obj, bool b);
    static void callbackWithInt(JNIEnv *env, jobject obj, int i);
    static void callbackWithString(JNIEnv *env, jobject obj, jstring s);
    static void callbackWithStringArray(JNIEnv *env, jobject obj, jobjectArray a);

signals:
    void signalFromJava();
    void boolFromJava(bool b);
    void intFromJava(int i);
    void stringFromJava(QString s);
    void stringArrayFromJava(QStringList sl);

public slots:
    void test();

    void callJavaFunctionWithoutArguments();
    void callJavaFunctionWithBool(bool b);
    void callJavaFunctionWithInt(int i);
    void callJavaFunctionWithString(QString s);

    bool getBoolFromJava();
    int getIntFromJava();
    QString getStringFromJava();

    QString intToString(int i);

    void askCallbacks();



};

#endif // CLIENT_H
