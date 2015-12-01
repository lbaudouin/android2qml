#include "client.h"

#include <QDebug>

#include <callback.h>
//JNI types : http://doc.qt.io/qt-5/qandroidjniobject.html#jni-types

static Callback *callback = NULL;

Client::Client(QObject *parent) : QObject(parent)
{
    if(!callback){
        callback = new Callback;
    }

    connect(callback,SIGNAL(signalFromJava()),this,SIGNAL(signalFromJava()));
    connect(callback,SIGNAL(boolFromJava(bool)),this,SIGNAL(boolFromJava(bool)));
    connect(callback,SIGNAL(intFromJava(int)),this,SIGNAL(intFromJava(int)));
    connect(callback,SIGNAL(stringFromJava(QString)),this,SIGNAL(stringFromJava(QString)));
    connect(callback,SIGNAL(stringArrayFromJava(QStringList)),this,SIGNAL(stringArrayFromJava(QStringList)));

    JNINativeMethod methods[] {
        {"callbackWithoutArguments", "()V", reinterpret_cast<void *>(Client::callbackWithoutArguments)},
        {"callbackWithBool", "(Z)V", reinterpret_cast<void *>(Client::callbackWithBool)},
        {"callbackWithInt", "(I)V", reinterpret_cast<void *>(Client::callbackWithInt)},
        {"callbackWithString", "(Ljava/lang/String;)V", reinterpret_cast<void *>(Client::callbackWithString)},
        {"callbackWithStringArray", "([Ljava/lang/String;)V", reinterpret_cast<void *>(Client::callbackWithStringArray)}
    };

    QAndroidJniObject javaClass("org/qtproject/test/MyJavaNatives");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
}

void Client::test()
{
    callJavaFunctionWithoutArguments();
    callJavaFunctionWithBool(true);
    callJavaFunctionWithBool(false);
    callJavaFunctionWithInt(-1);
    callJavaFunctionWithInt(5);
    callJavaFunctionWithString("test");
    callJavaFunctionWithString("");

    getBoolFromJava();
    getIntFromJava();
    getStringFromJava();

    intToString(9);

    askCallbacks();
}

void Client::callJavaFunctionWithoutArguments()
{
    QAndroidJniObject::callStaticMethod<void> ("org/qtproject/test/Test","functionWithoutArguments");
}

void Client::callJavaFunctionWithBool(bool b)
{
    QAndroidJniObject::callStaticMethod<void> ("org/qtproject/test/Test","functionWithBool","(Z)V", b);
}

void Client::callJavaFunctionWithInt(int i)
{
    QAndroidJniObject::callStaticMethod<void> ("org/qtproject/test/Test","functionWithInt","(I)V", i);
}

void Client::callJavaFunctionWithString(QString s)
{
    QAndroidJniObject string = QAndroidJniObject::fromString(s);
    QAndroidJniObject::callStaticMethod<void> ("org/qtproject/test/Test","functionWithString","(Ljava/lang/String;)V", string.object<jstring>());
}

bool Client::getBoolFromJava()
{
    bool b = QAndroidJniObject::callStaticMethod<jboolean>("org/qtproject/test/Test","getBool");
    qDebug() << "getBoolFromJava" << b;
    return b;
}

int Client::getIntFromJava()
{
    int i = QAndroidJniObject::callStaticMethod<jint>("org/qtproject/test/Test","getInt");
    qDebug() << "getIntFromJava" << i;
    return i;
}

QString Client::getStringFromJava()
{
    QAndroidJniObject string = QAndroidJniObject::callStaticObjectMethod<jstring>("org/qtproject/test/Test","getString");
    QString s = string.toString();
    qDebug() << "getStringFromJava" << s;
    return s;
}

QString Client::intToString(int i)
{
    QAndroidJniObject string = QAndroidJniObject::callStaticObjectMethod("org/qtproject/test/Test","intToString","(I)Ljava/lang/String;", i);
    QString s = string.toString();
    qDebug() << i << s;
    return s;
}

void Client::askCallbacks()
{
    QAndroidJniObject::callStaticMethod<void> ("org/qtproject/test/Test","callbacks");
}

void Client::callbackWithoutArguments(JNIEnv *env, jobject obj)
{
    Q_UNUSED(env);
    Q_UNUSED(obj);
    qDebug() << "callbackWithoutArguments";

    callback->sendSignalFromJava();
    //emit signalFromJava();
}

void Client::callbackWithBool(JNIEnv *env, jobject obj, bool b)
{
    Q_UNUSED(env);
    Q_UNUSED(obj);
    qDebug() << "callbackWithBool" << b;

    callback->sendBoolFromJava(b);
    //emit boolFromJava(b);
}

void Client::callbackWithInt(JNIEnv *env, jobject obj, int i)
{
    Q_UNUSED(env);
    Q_UNUSED(obj);
    qDebug() << "callbackWithInt" << i;

    callback->sendIntFromJava(i);
    //emit intFromJava(i);
}

void Client::callbackWithString(JNIEnv *env, jobject obj, jstring s)
{
    QString qstring;
#if 1
    const char *nativeString = env->GetStringUTFChars(s, 0);
    Q_UNUSED(obj)
    qstring = QString::fromUtf8(nativeString);
    qstring.detach();
    env->ReleaseStringUTFChars(s, nativeString);
#else
    Q_UNUSED(env);
    Q_UNUSED(obj);
    QAndroidJniObject myNewJavaString("java/lang/String", "(Ljava/lang/String;)V", s);
    qstring = myNewJavaString.toString();
#endif

    qDebug() << "callbackWithString" << qstring;

    callback->sendStringFromJava(qstring);
    //emit stringFromJava(qstring);
}

void Client::callbackWithStringArray(JNIEnv *env, jobject obj, jobjectArray stringArray)
{
    Q_UNUSED(obj)
    QStringList list;

    int stringCount = env->GetArrayLength(stringArray);

    for (int i=0; i<stringCount; i++) {
        jstring string = (jstring) env->GetObjectArrayElement(stringArray, i);
        const char *nativeString = env->GetStringUTFChars(string, 0);
        QString qstring = QString::fromUtf8(nativeString);
        qstring.detach();
        list << qstring;
        env->ReleaseStringUTFChars(string, nativeString);
    }

    qDebug() << "callbackWithStringArray" << list;
    callback->sendStringArrayFromJava(list);
    //emit stringFromJava(qstring);
}
