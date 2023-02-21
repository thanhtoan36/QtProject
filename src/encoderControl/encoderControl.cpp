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
      m_current_encoder_page(0),
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

    OnModeChanged();
    OnTypeChanged();

    connect(&m_button_previous_page, &QPushButton::clicked, this, [&](){
        SetCurrentEncoderPage(CurrentEncoderPage() - 1);
    });
    connect(&m_button_next_page, &QPushButton::clicked, this, [&](){
        SetCurrentEncoderPage(CurrentEncoderPage() + 1);
    });
    connect(&m_button_mode_percent, &QPushButton::clicked, this, [&](){
        SetMode(ENCODER_MODE_PERCENT);
    });
    connect(&m_button_mode_255, &QPushButton::clicked, this, [&](){
        SetMode(ENCODER_MODE_255);
    });
    connect(&m_button_mode_angle, &QPushButton::clicked, this, [&](){
        SetMode(ENCODER_MODE_ANGLE);
    });
    connect(this, &EncoderControl::CurrentEncoderPageChanged, this, [&](){
        SetupEncoderPages();
        m_button_previous_page.setEnabled(CurrentEncoderPage() > 0);
        m_button_next_page.setEnabled(CurrentEncoderPage() < MaxEncoderPages() - 1);
    });
    connect(this, &EncoderControl::ModeChanged, this, &EncoderControl::OnModeChanged);
    connect(this, &EncoderControl::TypeChanged, this, &EncoderControl::OnTypeChanged);
}

void EncoderControl::SetDispParamData(ENCODER_DISP_PARAM *param)
{
    Q_ASSERT(param);

    SetMode(param->mode);
    SetType(param->type);

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
        encoder->setSingleStep(EC_FLOAT_TO_INT_SCALE);
        encoder->setValue(param->param[i].level * EC_FLOAT_TO_INT_SCALE);
        encoder->SetUpperRestrictValue(param->param[i].maxLevel * EC_FLOAT_TO_INT_SCALE);

        connect(encoder.get(), &CustomEncoder::sliderMoved, this, [&](int value){
            auto encoder = std::find(m_encoders.begin(), m_encoders.end(), (CustomEncoder*)sender());
            if (!encoder) return;
            int index = std::distance(m_encoders.begin(), encoder);
            OnEncoderValueChanged(index, value);
        });

        m_encoders.append(encoder);
        OnEncoderValueChanged(i, param->param[i].level * EC_FLOAT_TO_INT_SCALE);
    }

    placeChildrenIntoPanel(m_encoder_labels, EC_ENCODER_LABEL_SIZE, EC_ENCODER_LABELS_TOPLEFT + QPoint(EC_ENCODER_WIDTH_PADDING, 0), QSize(m_encoders_per_page, 1));
    placeChildrenIntoPanel(m_encoders, EC_CUSTOM_ENCODER_SIZE, EC_ENCODER_TOPLEFT, QSize(m_encoders_per_page, 1));

    SetCurrentEncoderPage(0);
    SetupEncoderPages();

    m_button_next_page.setVisible(MaxEncoderPages() > 1);
    m_button_previous_page.setVisible(MaxEncoderPages() > 1);
}

void EncoderControl::SetupEncoderPages()
{
    UpdateChildrenVisibility(m_encoders, CurrentEncoderPage(), m_encoders_per_page);
    UpdateChildrenVisibility(m_encoder_labels, CurrentEncoderPage(), m_encoders_per_page);

    int visible_items = calculateNumberOfVisibleItems(m_encoders.length(), m_encoders_per_page, CurrentEncoderPage());
    m_encoder_background.setGridSize(QSize(visible_items, 1));
}

void EncoderControl::OnModeChanged()
{
    m_button_mode_percent.setChecked(Mode() == ENCODER_MODE_PERCENT);
    m_button_mode_255.setChecked(Mode() == ENCODER_MODE_255);

    Q_ASSERT(m_params.length() == m_encoders.length());
    Q_ASSERT(m_params.length() == m_encoder_labels.length());

    if (Mode() == ENCODER_MODE_255) {
        for (int i = 0; i < m_params.length(); ++i) {

            m_params[i].level *= (255.0 / 100.0);
            m_params[i].max_level *= (255.0 / 100.0);

            m_encoders[i]->setMaximum(255 * EC_FLOAT_TO_INT_SCALE);
            m_encoders[i]->SetUpperRestrictValue(m_params[i].max_level * EC_FLOAT_TO_INT_SCALE);
            m_encoders[i]->setValue(m_params[i].level * EC_FLOAT_TO_INT_SCALE);

            UpdateEncoderLabelValue(i);
        }
    }
    if (Mode() == ENCODER_MODE_PERCENT) {
        for (int i = 0; i < m_params.length(); ++i) {

            m_params[i].level *= (100.0 / 255.0);
            m_params[i].max_level *= (100.0 / 255.0);

            m_encoders[i]->setMaximum(100 * EC_FLOAT_TO_INT_SCALE);
            m_encoders[i]->SetUpperRestrictValue(m_params[i].max_level * EC_FLOAT_TO_INT_SCALE);
            m_encoders[i]->setValue(m_params[i].level * EC_FLOAT_TO_INT_SCALE);

            UpdateEncoderLabelValue(i);
        }
    }
}

void EncoderControl::OnTypeChanged()
{
    m_button_mode_angle.setVisible(Type() == ENCODER_TYPE_POSITION);
}

void EncoderControl::UpdateEncoderLabelValue(int index)
{
    auto &label = m_encoder_labels[index];
    auto &param = m_params[index];
    label->setText(QString(g_encoder_label_format).arg(param.name).arg((int)param.level));
}

void EncoderControl::OnEncoderValueChanged(int index, int value)
{
    auto &param = m_params[index];
    param.level = value / EC_FLOAT_TO_INT_SCALE;
    UpdateEncoderLabelValue(index);
    emit EncoderValueChanged(index, param.name, value);
}

int EncoderControl::CurrentEncoderPage() const
{
    return m_current_encoder_page;
}

void EncoderControl::SetCurrentEncoderPage(int value)
{
    value = qBound(value, 0, MaxEncoderPages() - 1);
    if (m_current_encoder_page == value)
        return;
    m_current_encoder_page = value;
    emit CurrentEncoderPageChanged();
}

int EncoderControl::MaxEncoderPages() const
{
    return calulateNumberOfPages(m_encoders.length(), m_encoders_per_page);
}

EncoderMode EncoderControl::Mode() const
{
    return m_mode;
}

void EncoderControl::SetMode(EncoderMode value)
{
    if (m_mode == value)
        return;
    m_mode = value;
    emit ModeChanged();
}

EncoderType EncoderControl::Type() const
{
    return m_type;
}

void EncoderControl::SetType(EncoderType value)
{
    if (m_type == value)
        return;
    m_type = value;
    emit TypeChanged();
}
