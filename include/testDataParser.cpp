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
            strncpy(g.color_filter[i].name, qUtf8Printable(name), sizeof(g.color_filter[i].name));
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
        strncpy(p.param[i].name, qUtf8Printable(name), sizeof(p.param[i].name));
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

INPUT_NUM_DISP_PARAM INC_ParseInput(const QString &raw)
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
        strncpy(p.param[i].name, qUtf8Printable(name), sizeof(p.param[i].name));
    }

    return p;
}

PLAYBACK_DISP_PARAM PLC_ParseInput(const QString &raw)
{
    QJsonDocument doc = QJsonDocument::fromJson(raw.toLocal8Bit());
    const auto array = doc.array();

    PLAYBACK_DISP_PARAM p;

    p.count = array.count();
    // NOTE: leak
    p.param = new PLAYBACK_PARAM[p.count];
    for (int i = 0; i < p.count; ++i) {
        p.param[i].select = array[i].toObject()["select"].toBool();
        p.param[i].marking.color = QColor(array[i].toObject()["marking"].toObject()["color"].toString());

        const auto marking = array[i].toObject()["marking"].toObject()["marking"].toString();
        const auto queue = array[i].toObject()["queue"].toString();
        const auto fade = array[i].toObject()["fade"].toString();
        const auto delay = array[i].toObject()["delay"].toString();
        const auto weight = array[i].toObject()["weight"].toString();
        const auto link = array[i].toObject()["link"].toString();
        const auto title = array[i].toObject()["title"].toString();

        // qDebug() << strlen(qUtf8Printable(marking)) << marking.length() << (marking == "★");
        strncpy(p.param[i].marking.marking, qUtf8Printable(marking), sizeof(p.param[i].marking.marking));
        strncpy(p.param[i].queue, qUtf8Printable(queue), sizeof(p.param[i].queue));
        strncpy(p.param[i].fade, qUtf8Printable(fade), sizeof(p.param[i].fade));
        strncpy(p.param[i].delay, qUtf8Printable(delay), sizeof(p.param[i].delay));
        strncpy(p.param[i].weight, qUtf8Printable(weight), sizeof(p.param[i].weight));
        strncpy(p.param[i].link, qUtf8Printable(link), sizeof(p.param[i].link));
        strncpy(p.param[i].title, qUtf8Printable(title), sizeof(p.param[i].title));
    }

    return p;
}

GROUP_DISP_PARAM GC_ParseInput(const QString &raw)
{
    QJsonDocument doc = QJsonDocument::fromJson(raw.toLocal8Bit());
    const auto object = doc.object();

    GROUP_DISP_PARAM p;

    const auto parseGroup = [](QJsonArray array) -> GROUP_PARAM_GROUP {
        GROUP_PARAM_GROUP g;

        g.count = array.count();

        // NOTE: leak
        g.group_param = new GROUP_PARAM[g.count];
        for (int i = 0; i < g.count; ++i) {
            QString title = array[i].toObject()["title"].toString();
            QString group_no = array[i].toObject()["group_no"].toString();
            bool select = array[i].toObject()["select"].toBool(false);

            g.group_param[i].select = select;
            strncpy(g.group_param[i].title, qUtf8Printable(title), sizeof(g.group_param[i].title));
            strncpy(g.group_param[i].group_no, qUtf8Printable(group_no), sizeof(g.group_param[i].group_no));
        }

        return g;
    };

    p.group = parseGroup(object["group"].toArray());
    p.history = parseGroup(object["history"].toArray());

    return p;
}

LIBRARY_DISP_PARAM LC_ParseInput(const QString &raw)
{
    QJsonDocument doc = QJsonDocument::fromJson(raw.toLocal8Bit());
    const auto object = doc.object();

    LIBRARY_DISP_PARAM p;

    const auto parseGroup = [](QJsonArray array) -> LIBRARY_PARAM_GROUP {
        LIBRARY_PARAM_GROUP g;

        g.count = array.count();

        // NOTE: leak
        g.library_param = new LIBRARY_PARAM[g.count];
        for (int i = 0; i < g.count; ++i) {
            QString mode = array[i].toObject()["mode"].toString();
            QString title = array[i].toObject()["title"].toString();
            QString library_no = array[i].toObject()["library_no"].toString();
            bool select = array[i].toObject()["select"].toBool(false);

            g.library_param[i].select = select;
            strncpy(g.library_param[i].title, qUtf8Printable(title), sizeof(g.library_param[i].title));
            strncpy(g.library_param[i].mode, qUtf8Printable(mode), sizeof(g.library_param[i].mode));
            strncpy(g.library_param[i].library_no, qUtf8Printable(library_no), sizeof(g.library_param[i].library_no));
        }

        return g;
    };

    p.group = parseGroup(object["group"].toArray());
    p.history = parseGroup(object["history"].toArray());

    return p;
}

PALETTE_DISP_PARAM PD_ParseInput(const QString &raw)
{
    QJsonDocument doc = QJsonDocument::fromJson(raw.toLocal8Bit());
    const auto array = doc.array();

    PALETTE_DISP_PARAM p;

    p.count = array.count();
    // NOTE: leak
    p.data = new PALETTE_PARAM_GROUP[p.count];
    for (int groupIndex = 0; groupIndex < p.count; ++groupIndex) {
        const auto self = array[groupIndex].toObject();
        auto &selfData = p.data[groupIndex];

        selfData.select = self["select"].toBool();
        const auto imageName = self["image"].toString();
        if (!imageName.isEmpty()) {
            const auto imagePath = QString(":/resources/%1.png").arg(imageName);
            qDebug() << "palette image: " << imagePath;
            selfData.image = QImage(imagePath);
        }

        const auto name = self["name"].toString();
        strncpy(selfData.name, qUtf8Printable(name), sizeof(selfData.name));

        const auto children = self["buttons"].toArray();

        selfData.count = children.count();
        selfData.palette = new PALETTE_PARAM[selfData.count];
        for (int childIndex = 0; childIndex < selfData.count; ++childIndex) {
            const auto childObject = children[childIndex].toObject();
            const auto name = childObject["name"].toString();
            const auto imageName = childObject["image"].toString();

            if (!imageName.isEmpty()) {
                const auto imagePath = QString(":/resources/%1.png").arg(imageName);
                qDebug() << "button image: " << imagePath;
                selfData.palette[childIndex].image = QImage(imagePath);
            }

            selfData.palette[childIndex].select = childObject["select"].toBool();
            strncpy(selfData.palette[childIndex].name, qUtf8Printable(name), sizeof(selfData.palette[childIndex].name));
        }
    }

    return p;
}
