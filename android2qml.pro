TEMPLATE = app

QT += qml quick androidextras
CONFIG += c++11

SOURCES += main.cpp \
    client.cpp \
    callback.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    android-sources/AndroidManifest.xml \
    android-sources/gradle/wrapper/gradle-wrapper.jar \
    android-sources/gradlew \
    android-sources/res/values/libs.xml \
    android-sources/build.gradle \
    android-sources/gradle/wrapper/gradle-wrapper.properties \
    android-sources/gradlew.bat \
    android-sources/src/org/qtproject/test/Test.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

HEADERS += \
    client.h \
    callback.h

