#include "encoderControl/encoderControl.hpp"
#include "encoderControl/encoderControl_define.hpp"
#include "utility.h"

#include <QDebug>
#include <cmath>

EncoderPanelControl::EncoderPanelControl(QWidget *parent)
    : PanelControlBase(parent),
      m_label_title(this),

      m_button_mode_percent(this),
      m_button_mode_255(this),
      m_button_empty1(this),
      m_button_previous_tab(this),
      m_button_next_tab(this),
      m_encoders(),
      m_currentEncoderPage(0),
      m_mode()
{
    setFixedSize(EC_SCREENSIZE);
}

void EncoderPanelControl::SetDispParamData(ENCODER_DISP_PARAM *param)
{
    Q_ASSERT(param);

    setMode(param->mode);
    onModeChanged();

    m_encoders.clear();
    for (int i = 0; i < param->count; ++i) {
        auto slider = MakeSharedQObject<EncoderSlider>(this);
        slider->setVisible(false);
        slider->setFixedSize(EC_ENCODER_SIZE);

        slider->setRange(0, 255);
        slider->setSingleStep(1);
        slider->setEncoderName(QString::fromLocal8Bit(param->param[i].name));
        slider->setValue(param->param[i].level);
        slider->setUpperRestrictValue(param->param[i].maxLevel);

        connect(slider.get(), &EncoderSlider::sliderMoved, this, [&](int value){
           qDebug() <<  ((EncoderSlider*)sender())->encoderName() << value;
        });

        m_encoders.append(slider);
    }

    setEncoderMatrixSize(QSize(EC_MAX_ENCODER_ITEMS, 1));
    setCurrentEncoderPage(0);

    setupEncoderPages();
}

void EncoderPanelControl::SetupUiComponents()
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
    m_button_previous_tab.setVisible(true);

    m_button_next_tab.setGeometry(EC_BUTTON_NEXT_GEOMETRY);
    m_button_next_tab.setText("▶");
    m_button_next_tab.setVisible(true);
}

void EncoderPanelControl::SetupUiEvents()
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
    connect(this, &EncoderPanelControl::encoderMatrixSizeChanged, this, [&](){
        setCurrentEncoderPage(0);
        setupEncoderPages();
    });
    connect(this, &EncoderPanelControl::encoderMatrixSizeChanged, this, [&](){ setupEncoderPages(); });
    connect(this, &EncoderPanelControl::currentEncoderPageChanged, this, [&](){ setupEncoderPages(); });
    connect(this, &EncoderPanelControl::modeChanged, this, &EncoderPanelControl::onModeChanged);
}

void EncoderPanelControl::setupEncoderPages()
{
    const auto encodersPerPage = encoderMatrixSize().width() * encoderMatrixSize().height();
    updateChildrenVisibility(m_encoders, currentEncoderPage(), encodersPerPage);
    placeChildrenIntoPanel(m_encoders, EC_ENCODER_SIZE, EC_ENCODER_PLACEMENT_START, encodersPerPage);

    m_button_previous_tab.setEnabled(currentEncoderPage() > 0);
    m_button_next_tab.setEnabled(currentEncoderPage() < maxEncoderPages() - 1);
}

void EncoderPanelControl::onModeChanged()
{
    m_button_mode_percent.setChecked(mode() == ENCODER_MODE_PERCENT);
    m_button_mode_255.setChecked(mode() == ENCODER_MODE_255);
}

int EncoderPanelControl::currentEncoderPage() const
{
    return m_currentEncoderPage;
}

void EncoderPanelControl::setCurrentEncoderPage(int newCurrentEncoderPage)
{
    newCurrentEncoderPage = bounded(newCurrentEncoderPage, 0, maxEncoderPages() - 1);
    if (m_currentEncoderPage == newCurrentEncoderPage)
        return;
    m_currentEncoderPage = newCurrentEncoderPage;
    emit currentEncoderPageChanged();
}

int EncoderPanelControl::maxEncoderPages() const
{
    return calulateNumberOfPages(m_encoders.length(), encoderMatrixSize().width() * encoderMatrixSize().height());
}

EncoderMode EncoderPanelControl::mode() const
{
    return m_mode;
}

void EncoderPanelControl::setMode(EncoderMode newMode)
{
    if (m_mode == newMode)
        return;
    m_mode = newMode;
    emit modeChanged();
}

QSize EncoderPanelControl::encoderMatrixSize() const
{
    return m_encoderMatrixSize;
}

void EncoderPanelControl::setEncoderMatrixSize(const QSize &newEncoderMatrixSize)
{
    if (m_encoderMatrixSize == newEncoderMatrixSize)
        return;
    m_encoderMatrixSize = newEncoderMatrixSize;
    emit encoderMatrixSizeChanged();
}
