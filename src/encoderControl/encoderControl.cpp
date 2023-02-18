#include "encoderControl/encoderControl.hpp"
#include "encoderControl/encoderControl_define.hpp"
#include "utility.h"

#include <QDebug>
#include <cmath>
#include <algorithm>

#define EC_FLOAT_TO_INT_SCALE 10.0

static const char *g_encoder_label_format = "%1\n%2";

EncoderControl::EncoderControl(QWidget *parent)
    : PanelControlBase(parent),
      m_encoder_background(this),
      m_button_background(this),
      m_label_title(this),
      m_button_mode_percent(this),
      m_button_mode_255(this),
      m_button_mode_angle(this),
      m_button_previous_page(this),
      m_button_next_page(this),
      m_params(),
      m_encoder_labels(),
      m_encoders(),
      m_currentEncoderPage(0),
      m_mode()
{
    setFixedSize(EC_SCREENSIZE);
    m_encoders_per_page = 4;

    m_encoder_background.setCellSize(EC_ENCODER_LABEL_SIZE + QSize(0, EC_CUSTOM_ENCODER_SIZE.height()));
    m_encoder_background.move(EC_ENCODER_LABELS_TOPLEFT);
    m_encoder_background.setBackgroundColor(Qt::black);
    m_encoder_background.setGridLineColor(Qt::transparent);

    m_button_background.setGridSize(QSize(4, 1));
    m_button_background.setCellSize(EC_BUTTON_NEXT_GEOMETRY.size());
    m_button_background.move(EC_BUTTON_PERCENT_GEOMETRY.topLeft());

    m_label_title.setGeometry(EC_LABEL_TITLE_GEOMETRY);
    m_label_title.setObjectName("title_label");
    m_label_title.setText("エンコーダー　ホイール");

    m_button_mode_percent.setGeometry(EC_BUTTON_PERCENT_GEOMETRY);
    m_button_mode_percent.setText("%");
    m_button_mode_255.setGeometry(EC_BUTTON_255_GEOMETRY);
    m_button_mode_255.setText("255");
    m_button_mode_angle.setGeometry(EC_BUTTON_ANGLE_GEOMETRY);
    m_button_mode_angle.setText("°角度");
    m_button_mode_angle.setEnabled(false);

    m_button_previous_page.setGeometry(EC_BUTTON_PREVIOUS_GEOMETRY);
    m_button_previous_page.setText("◀");
    m_button_previous_page.setVisible(false);

    m_button_next_page.setGeometry(EC_BUTTON_NEXT_GEOMETRY);
    m_button_next_page.setText("▶");
    m_button_next_page.setVisible(false);

    onModeChanged();
    onTypeChanged();

    connect(&m_button_previous_page, &QPushButton::clicked, this, [&](){
        setCurrentEncoderPage(currentEncoderPage() - 1);
    });
    connect(&m_button_next_page, &QPushButton::clicked, this, [&](){
        setCurrentEncoderPage(currentEncoderPage() + 1);
    });
    connect(&m_button_mode_percent, &QPushButton::clicked, this, [&](){
        setMode(ENCODER_MODE_PERCENT);
    });
    connect(&m_button_mode_255, &QPushButton::clicked, this, [&](){
        setMode(ENCODER_MODE_255);
    });
    connect(this, &EncoderControl::currentEncoderPageChanged, this, [&](){
        setupEncoderPages();
        m_button_previous_page.setEnabled(currentEncoderPage() > 0);
        m_button_next_page.setEnabled(currentEncoderPage() < maxEncoderPages() - 1);
    });
    connect(this, &EncoderControl::modeChanged, this, &EncoderControl::onModeChanged);
    connect(this, &EncoderControl::typeChanged, this, &EncoderControl::onTypeChanged);
}

void EncoderControl::SetDispParamData(ENCODER_DISP_PARAM *param)
{
    Q_ASSERT(param);

    setMode(param->mode);
    setType(param->type);

    m_params.clear();
    m_encoder_labels.clear();
    m_encoders.clear();

    for (int i = 0; i < param->count; ++i) {
        m_params.append(param->param[i]);

        auto label = MakeSharedQObject<QLabel>(this);
        label->setObjectName("encoder_label");
        label->setVisible(false);
        label->setFixedSize(EC_ENCODER_LABEL_SIZE - QSize(EC_ENCODER_WIDTH_PADDING * 2, 0));

        m_encoder_labels.append(label);

        auto encoder = MakeSharedQObject<CustomEncoder>(this);
        encoder->setVisible(false);
        encoder->setFixedSize(EC_CUSTOM_ENCODER_SIZE);

        encoder->setRange(0, (param->mode == ENCODER_MODE_255 ? 255 : 100) * EC_FLOAT_TO_INT_SCALE);
        encoder->setSingleStep(10);
        encoder->setValue(param->param[i].level * EC_FLOAT_TO_INT_SCALE);
        encoder->setUpperRestrictValue(param->param[i].maxLevel * EC_FLOAT_TO_INT_SCALE);

        connect(encoder.get(), &CustomEncoder::sliderMoved, this, [&](int value){
            auto encoder = std::find(m_encoders.begin(), m_encoders.end(), (CustomEncoder*)sender());
            if (!encoder) return;
            int index = std::distance(m_encoders.begin(), encoder);
            onEncoderValueChanged(index, value);
        });

        m_encoders.append(encoder);
        onEncoderValueChanged(i, param->param[i].level * EC_FLOAT_TO_INT_SCALE);
    }

    placeChildrenIntoPanel(m_encoder_labels, EC_ENCODER_LABEL_SIZE, EC_ENCODER_LABELS_TOPLEFT + QPoint(EC_ENCODER_WIDTH_PADDING, 0), m_encoders_per_page);
    placeChildrenIntoPanel(m_encoders, EC_CUSTOM_ENCODER_SIZE, EC_ENCODER_TOPLEFT, m_encoders_per_page);

    setCurrentEncoderPage(0);
    setupEncoderPages();

    m_button_next_page.setVisible(maxEncoderPages() > 1);
    m_button_previous_page.setVisible(maxEncoderPages() > 1);
}

void EncoderControl::setupEncoderPages()
{
    updateChildrenVisibility(m_encoders, currentEncoderPage(), m_encoders_per_page);
    updateChildrenVisibility(m_encoder_labels, currentEncoderPage(), m_encoders_per_page);

    int visibleChildCount = calculateNumberOfVisibleItems(m_encoders.length(), m_encoders_per_page, currentEncoderPage());
    m_encoder_background.setGridSize(QSize(visibleChildCount, 1));
}

void EncoderControl::onModeChanged()
{
    m_button_mode_percent.setChecked(mode() == ENCODER_MODE_PERCENT);
    m_button_mode_255.setChecked(mode() == ENCODER_MODE_255);

    Q_ASSERT(m_params.length() == m_encoders.length());
    Q_ASSERT(m_params.length() == m_encoder_labels.length());

    if (mode() == ENCODER_MODE_255) {
        for (int i = 0; i < m_params.length(); ++i) {

            m_params[i].level *= (255.0 / 100.0);
            m_params[i].maxLevel *= (255.0 / 100.0);

            m_encoders[i]->setMaximum(255 * EC_FLOAT_TO_INT_SCALE);
            m_encoders[i]->setUpperRestrictValue(m_params[i].maxLevel * EC_FLOAT_TO_INT_SCALE);
            m_encoders[i]->setValue(m_params[i].level * EC_FLOAT_TO_INT_SCALE);

            updateEncoderLabelValue(i);
        }
    }
    if (mode() == ENCODER_MODE_PERCENT) {
        for (int i = 0; i < m_params.length(); ++i) {

            m_params[i].level *= (100.0 / 255.0);
            m_params[i].maxLevel *= (100.0 / 255.0);

            m_encoders[i]->setMaximum(100 * EC_FLOAT_TO_INT_SCALE);
            m_encoders[i]->setUpperRestrictValue(m_params[i].maxLevel * EC_FLOAT_TO_INT_SCALE);
            m_encoders[i]->setValue(m_params[i].level * EC_FLOAT_TO_INT_SCALE);

            updateEncoderLabelValue(i);
        }
    }
}

void EncoderControl::onTypeChanged()
{
    m_button_mode_angle.setVisible(type() == ENCODER_TYPE_POSITION);
}

void EncoderControl::updateEncoderLabelValue(int index)
{
    auto &label = m_encoder_labels[index];
    auto &param = m_params[index];
    label->setText(QString(g_encoder_label_format).arg(param.name).arg((int)param.level));
}

void EncoderControl::onEncoderValueChanged(int index, int value)
{
    auto &param = m_params[index];
    param.level = value / EC_FLOAT_TO_INT_SCALE;
    updateEncoderLabelValue(index);
    emit encoderValueChanged(index, param.name, value);
}

int EncoderControl::currentEncoderPage() const
{
    return m_currentEncoderPage;
}

void EncoderControl::setCurrentEncoderPage(int newCurrentEncoderPage)
{
    newCurrentEncoderPage = bounded(newCurrentEncoderPage, 0, maxEncoderPages() - 1);
    if (m_currentEncoderPage == newCurrentEncoderPage)
        return;
    m_currentEncoderPage = newCurrentEncoderPage;
    emit currentEncoderPageChanged();
}

int EncoderControl::maxEncoderPages() const
{
    return calulateNumberOfPages(m_encoders.length(), m_encoders_per_page);
}

EncoderMode EncoderControl::mode() const
{
    return m_mode;
}

void EncoderControl::setMode(EncoderMode newMode)
{
    if (m_mode == newMode)
        return;
    m_mode = newMode;
    emit modeChanged();
}

EncoderType EncoderControl::type() const
{
    return m_type;
}

void EncoderControl::setType(EncoderType newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}
