#include <QRegularExpression>
#include <QDebug>
#include <QMap>
#include <QTime>
#include <stdio.h>
#include <cstring>

#include "loghandler.h"
#define TIME_FORMAT "HH:mm:ss.zzz"

const char *getFileName(const char *path) {
    if (!path) return "";

    const auto lastSlashUnix = strrchr(path, '/');
    const auto lastSlashWindows = strrchr(path, '\\');

    if (lastSlashUnix)
        return lastSlashUnix + 1;

    if (lastSlashWindows)
        return lastSlashWindows + 1;

    return path;
}

QString trimFunctionName(const QString &longName) {
    // keep class name and function name
    // static auto regex = QRegularExpression("(\\w+::\\w+(?=\\()|(?<= )\\w+.*(?=\\())");
    static auto regex = QRegularExpression(R"(\w+(?=\())");
    const auto matches = regex.match(longName);
    if (!matches.hasMatch())
        return longName;
    return matches.captured(0);
}

void logHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    const QByteArray localMsg = msg.toLocal8Bit();
    const char *file = getFileName(context.file);
    const QString qfunc = trimFunctionName(context.function ? context.function : "");
    const QByteArray bfunc = qfunc.toLocal8Bit();

    const auto time = QTime::currentTime().toString(TIME_FORMAT).toStdString();
    const auto timeStr = time.c_str();

    char level = 'D';
    auto stream = stdout;

    switch (type) {
        case QtDebugMsg:
            level = 'D'; stream = stdout; break;
        case QtInfoMsg:
            level = 'I'; stream = stdout; break;
        case QtWarningMsg:
            level = 'W'; stream = stdout; break;
        case QtCriticalMsg:
        case QtFatalMsg:
            level = 'E'; stream = stderr; break;
        default:
            return;
    }
    fprintf(stream, "\x1b[36m%s [%c] \x1b[0m%s \x1b[36m(%s, %s:%u)\x1b[0m\n", timeStr, level, localMsg.constData(), bfunc.constData(), file, context.line);
    fflush(stream);
}

void initLog() {
    qInstallMessageHandler(&logHandler);
    qDebug("init");
}
