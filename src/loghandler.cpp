#include <QRegularExpression>
#include <QDebug>
#include <QMap>
#include <QTime>
#include <stdio.h>
#include <cstring>
#include <iostream>

#include "loghandler.h"
#define TIME_FORMAT "HH:mm:ss.zzz"

const char *GetFileName(const char *path) {
    if (!path) return "";

    const auto last_slash_unix = strrchr(path, '/');
    const auto last_slash_dos = strrchr(path, '\\');

    if (last_slash_unix)
        return last_slash_unix + 1;

    if (last_slash_dos)
        return last_slash_dos + 1;

    return path;
}

QString TrimFunctionName(const QString &longName) {
    // keep class name and function name
    // static auto regex = QRegularExpression("(\\w+::\\w+(?=\\()|(?<= )\\w+.*(?=\\())");
    static auto regex = QRegularExpression(R"(\w+(?=\())");
    const auto matches = regex.match(longName);
    if (!matches.hasMatch())
        return longName;
    return matches.captured(0);
}

void LogHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    const char *file = GetFileName(context.file);
    const QString qfunc = TrimFunctionName(context.function ? context.function : "");

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
    fprintf(stream, "\x1b[36m%s [%c] \x1b[0m%s \x1b[36m(%s, %s:%u)\x1b[0m\n", timeStr, level, qUtf8Printable(msg), qUtf8Printable(qfunc), file, context.line);
    fflush(stream);
}

void InitLog() {
    qInstallMessageHandler(&LogHandler);
    qDebug("init");
}
