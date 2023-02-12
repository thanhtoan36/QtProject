#include "testDataParser.h"

#include <QDebug>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#define STR(a) #a

COLOR_PICKER_DISP_PARAM CPC_ParseInput(const QString &raw)
{
    QJsonDocument doc = QJsonDocument::fromJson(raw.toLocal8Bit());
    const auto object = doc.object();

    COLOR_PICKER_DISP_PARAM p;

    p.type = object["type"].toString() == STR(COLOR_PICKER_TYPE_XY) ? COLOR_PICKER_TYPE_XY : COLOR_PICKER_TYPE_RGB;
    p.color = QColor(object["color"].toString());

    return p;
}

COLOR_FILTER_DISP_PARAM CFC_ParseInput(const QString &raw)
{
    QJsonDocument doc = QJsonDocument::fromJson(raw.toLocal8Bit());
    const auto object = doc.object();

    COLOR_FILTER_DISP_PARAM p;

    const auto parseGroup = [](QJsonObject o) -> COLOR_FILTER_PARAM_GROUP {
        COLOR_FILTER_PARAM_GROUP g;

        g.select = o["select"].toBool(false);
        auto array = o["buttons"].toArray();
        g.count = array.count();

        // NOTE: leak
        g.color_filter = new COLOR_FILTER_PARAM[g.count];
        for (int i = 0; i < g.count; ++i) {
            QString name = array[i].toObject()["name"].toString();
            QColor color = QColor(array[i].toObject()["color"].toString());
            bool select = array[i].toObject()["select"].toBool(false);

            g.color_filter[i].select = select;
            g.color_filter[i].color = color;
            strncpy(g.color_filter[i].name, qPrintable(name), sizeof(g.color_filter[i].name));
        }

        return g;
    };

    p.tb = parseGroup(object["tb"].toObject());
    p.custom = parseGroup(object["custom"].toObject());
    p.history = parseGroup(object["history"].toObject());

    return p;
}

ENCODER_DISP_PARAM EC_ParseInput(const QString &raw)
{
    QJsonDocument doc = QJsonDocument::fromJson(raw.toLocal8Bit());
    const auto object = doc.object();

    ENCODER_DISP_PARAM p;

    QStringList types = {
        "ENCODER_TYPE_COLOR",
        "ENCODER_TYPE_POSITION",
        "ENCODER_TYPE_GOBO",
        "ENCODER_TYPE_BEAM_SHUTTER",
        "ENCODER_TYPE_CONTROL"
    };

    QStringList modes = {
        "ENCODER_MODE_PERCENT",
        "ENCODER_MODE_255",
        "ENCODER_MODE_ANGLE"
    };

    p.type = (EncoderType)types.indexOf(object["type"].toString());
    p.mode = (EncoderMode)modes.indexOf(object["mode"].toString());

    auto array = object["encoders"].toArray();
    p.count = array.count();

    // NOTE: leak
    p.param = new ENCODER_PARAM[p.count];
    for (int i = 0; i < p.count; ++i) {
        QString name = array[i].toObject()["name"].toString();
        int level = array[i].toObject()["level"].toInt();
        int maxLevel = array[i].toObject()["maxLevel"].toInt();

        p.param[i].level = level;
        p.param[i].maxLevel = maxLevel;
        strncpy(p.param[i].name, qPrintable(name), sizeof(p.param[i].name));
    }

    return p;
}

TRACK_DISP_PARAM TC_ParseInput(const QString &raw)
{
    QJsonDocument doc = QJsonDocument::fromJson(raw.toLocal8Bit());
    const auto object = doc.object();

    TRACK_DISP_PARAM p;

    QStringList modes = {
        "TRACK_MODE_PERCENT",
        "TRACK_MODE_255",
        "TRACK_MODE_ANGLE"
    };

    QStringList valueModes = {
        "TRACK_MODE_RELATIVE",
        "TRACK_MODE_ABSOLUTE"
    };

    p.mode = (TrackMode)modes.indexOf(object["mode"].toString());
    p.valueMode = (TrackValueMode)valueModes.indexOf(object["valueMode"].toString());

    auto array = object["points"].toArray();
    p.count = array.count();

    // NOTE: leak
    p.data = new TRACK_PARAM_GROUP[p.count];
    for (int i = 0; i < p.count; ++i) {
        p.data[i].pan.current = array[i].toObject()["pan"].toObject()["current"].toInt();
        p.data[i].pan.min = array[i].toObject()["pan"].toObject()["min"].toInt();
        p.data[i].pan.max = array[i].toObject()["pan"].toObject()["max"].toInt();

        p.data[i].tilt.current = array[i].toObject()["tilt"].toObject()["current"].toInt();
        p.data[i].tilt.min = array[i].toObject()["tilt"].toObject()["min"].toInt();
        p.data[i].tilt.max = array[i].toObject()["tilt"].toObject()["max"].toInt();
    }

    return p;
}

INPUT_NUM_DISP_PARAM IN_ParseInput(const QString &raw)
{
    QJsonDocument doc = QJsonDocument::fromJson(raw.toLocal8Bit());
    const auto object = doc.object();

    INPUT_NUM_DISP_PARAM p;

    QStringList types = {
        "INPUT_NUM_TYPE_COLOR",
        "INPUT_NUM_TYPE_POSITION",
        "INPUT_NUM_TYPE_GOBO",
        "INPUT_NUM_TYPE_BEAM_SHUTTER",
        "INPUT_NUM_TYPE_CONTROL"
    };

    QStringList modes = {
        "INPUT_NUM_MODE_PERCENT",
        "INPUT_NUM_MODE_255",
        "INPUT_NUM_MODE_ANGLE"
    };

    p.type = (InputNumType)types.indexOf(object["type"].toString());
    p.mode = (InputNumMode)modes.indexOf(object["mode"].toString());

    auto array = object["buttons"].toArray();
    p.count = array.count();

    // NOTE: leak
    p.param = new INPUT_NUM_PARAM[p.count];
    for (int i = 0; i < p.count; ++i) {
        p.param[i].select = array[i].toObject()["select"].toBool();
        const auto name = array[i].toObject()["name"].toString();
        strncpy(p.param[i].name, qPrintable(name), sizeof(p.param[i].name));
    }

    return p;
}
