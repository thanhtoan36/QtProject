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
      m_button_empty1(this),
      m_button_previous_tab(this),
      m_button_next_tab(this),
      m_params(),
      m_encoder_labels(),
      m_encoders(),
      m_currentEncoderPage(0),
      m_mode()
{
    setFixedSize(EC_SCREENSIZE);
    setEncoderMatrixSize(QSize(EC_MAX_ENCODER_ITEMS, 1));

    onModeChanged();
    onTypeChanged();

    m_encoder_background.setCellSize(EC_ENCODER_LABEL_SIZE + QSize(0, EC_CUSTOM_ENCODER_SIZE.height()));
    m_encoder_background.move(EC_ENCODER_LABELS_TOPLEFT);
    m_encoder_background.setBackgroundColor(Qt::black);
    m_encoder_background.setGridLineColor(Qt::transparent);

    m_button_background.setGridSize(QSize(4, 1));
    m_button_background.setCellSize(EC_BUTTON_NEXT_GEOMETRY.size());
    m_button_background.move(EC_BUTTON_PERCENT_GEOMETRY.topLeft());
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
        // slider->setEncoderName(QString::fromLocal8Bit(param->param[i].name));
        encoder->setValue(param->param[i].level * EC_FLOAT_TO_INT_SCALE);
        encoder->setUpperRestrictValue(param->param[i].maxLevel * EC_FLOAT_TO_INT_SCALE);

        connect(encoder.get(), &CustomEncoder::sliderMoved, this, [&](int value){
           // qDebug() <<  ((CncoderEncoder*)sender())->encoderName() << value;
            auto encoder = std::find(m_encoders.begin(), m_encoders.end(), (CustomEncoder*)sender());
            if (!encoder) return;
            int index = std::distance(m_encoders.begin(), encoder);
            onEncoderValueChanged(index, value);
        });

        m_encoders.append(encoder);
        onEncoderValueChanged(i, param->param[i].level * EC_FLOAT_TO_INT_SCALE);
    }

    const auto encodersPerPage = encoderMatrixSize().width() * encoderMatrixSize().height();
    placeChildrenIntoPanel(m_encoder_labels, EC_ENCODER_LABEL_SIZE, EC_ENCODER_LABELS_TOPLEFT + QPoint(EC_ENCODER_WIDTH_PADDING, 0), encodersPerPage);
    placeChildrenIntoPanel(m_encoders, EC_CUSTOM_ENCODER_SIZE, EC_ENCODER_TOPLEFT, encodersPerPage);

    setCurrentEncoderPage(0);
    setupEncoderPages();

    qDebug() << m_encoders.length() << maxEncoderPages();
    m_button_next_tab.setVisible(maxEncoderPages() > 1);
    m_button_previous_tab.setVisible(maxEncoderPages() > 1);
}

void EncoderControl::SetupUiComponents()
{
    m_label_title.setGeometry(EC_LABEL_TITLE_GEOMETRY);
    m_label_title.setObjectName("title_label");
    m_label_title.setText("エンコーダ");

    m_button_mode_percent.setGeometry(EC_BUTTON_PERCENT_GEOMETRY);
    m_button_mode_percent.setText("%");
    m_button_mode_255.setGeometry(EC_BUTTON_255_GEOMETRY);
    m_button_mode_255.setText("255");
    m_button_empty1.setGeometry(EC_BUTTON_EMPTY_1_GEOMETRY);
    m_button_empty1.setEnabled(false);

    m_button_previous_tab.setGeometry(EC_BUTTON_PREVIOUS_GEOMETRY);
    m_button_previous_tab.setText("◀");

    m_button_next_tab.setGeometry(EC_BUTTON_NEXT_GEOMETRY);
    m_button_next_tab.setText("▶");
}

void EncoderControl::SetupUiEvents()
{
    connect(&m_button_previous_tab, &QPushButton::clicked, this, [&](){
        qDebug("previous");
        setCurrentEncoderPage(currentEncoderPage() - 1);
    });
    connect(&m_button_next_tab, &QPushButton::clicked, this, [&](){
        qDebug("next");
        setCurrentEncoderPage(currentEncoderPage() + 1);
    });
    connect(&m_button_mode_percent, &QPushButton::clicked, this, [&](){
        setMode(ENCODER_MODE_PERCENT);
    });
    connect(&m_button_mode_255, &QPushButton::clicked, this, [&](){
        setMode(ENCODER_MODE_255);
    });
    connect(this, &EncoderControl::encoderMatrixSizeChanged, this, [&](){
        setCurrentEncoderPage(0);
        setupEncoderPages();
    });
    connect(this, &EncoderControl::encoderMatrixSizeChanged, this, [&](){
        setupEncoderPages();
    });
    connect(this, &EncoderControl::currentEncoderPageChanged, this, [&](){
        setupEncoderPages();
        m_button_previous_tab.setEnabled(currentEncoderPage() > 0);
        m_button_next_tab.setEnabled(currentEncoderPage() < maxEncoderPages() - 1);
    });
    connect(this, &EncoderControl::modeChanged, this, &EncoderControl::onModeChanged);
    connect(this, &EncoderControl::typeChanged, this, &EncoderControl::onTypeChanged);
}

void EncoderControl::setupEncoderPages()
{
    const auto encodersPerPage = encoderMatrixSize().width() * encoderMatrixSize().height();
    updateChildrenVisibility(m_encoders, currentEncoderPage(), encodersPerPage);
    updateChildrenVisibility(m_encoder_labels, currentEncoderPage(), encodersPerPage);

    int visibleChildCount = calculateNumberOfVisibleItems(m_encoders.length(), encodersPerPage, currentEncoderPage());
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
    return calulateNumberOfPages(m_encoders.length(), encoderMatrixSize().width() * encoderMatrixSize().height());
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

QSize EncoderControl::encoderMatrixSize() const
{
    return m_encoderMatrixSize;
}

void EncoderControl::setEncoderMatrixSize(const QSize &newEncoderMatrixSize)
{
    if (m_encoderMatrixSize == newEncoderMatrixSize)
        return;
    m_encoderMatrixSize = newEncoderMatrixSize;
    emit encoderMatrixSizeChanged();
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
