//--------------------------------------------------------------------------
// [ ファイル名 ] : encoderControl.h
// [ 概      要 ] : EncoderControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef ENCODERCONTROL_H
#define ENCODERCONTROL_H

#include "baseComponent/panelControlBase.h"
#include "encoderControl_datatypes.h"
#include "customEncoder.h"
#include "baseComponent/selectButton.h"
#include "baseComponent/gridBackground.h"

#include <QLabel>
#include <QVector>

class EncoderControl : public PanelControlBase
{
    Q_OBJECT
    Q_PROPERTY( int CurrentEncoderPage READ CurrentEncoderPage WRITE SetCurrentEncoderPage NOTIFY CurrentEncoderPageChanged )
    Q_PROPERTY( EncoderMode Mode READ Mode WRITE SetMode NOTIFY ModeChanged )
    Q_PROPERTY( EncoderType Type READ Type WRITE SetType NOTIFY TypeChanged )

public:
    EncoderControl( QWidget *parent = nullptr );
    virtual void SetDispParamData( ENCODER_DISP_PARAM *param );

    EncoderMode Mode() const;
    EncoderType Type() const;

    QVector<ENCODER_PARAM> Encoders() const;

signals:
    void CurrentEncoderPageChanged();
    void ModeChanged();
    void TypeChanged();
    void EncoderValueChanged( int index, const QString &name, int value );

protected:
    virtual void SetupEncoderPages();
    int CurrentEncoderPage() const;
    void SetCurrentEncoderPage( int value );
    int MaxEncoderPages() const;
    void SetMode( EncoderMode value );
    void SetType( EncoderType value );

protected slots:
    void OnModeChanged();
    virtual void OnTypeChanged();
    void UpdateEncoderLabelValue( int index );
    void OnEncoderValueChanged( int index, int value );

protected:
    struct EncoderParamFloat
    {
        QString name;
        float level, max_level;

        EncoderParamFloat() {}
        EncoderParamFloat( const ENCODER_PARAM &param_int ) : name( param_int.name ), level( param_int.level ), max_level( param_int.maxLevel ) { }
    };

    GridBackground m_encoder_background;
    GridBackground m_button_background;

    QLabel m_label_title;

    SelectButton m_button_mode_percent;
    SelectButton m_button_mode_255;
    SelectButton m_button_mode_angle;

    CustomPushButton m_button_previous_page; // ◀
    CustomPushButton m_button_next_page;     // ▶

    QVector<EncoderParamFloat> m_params;
    QVector<QSharedPointer<QLabel>> m_encoder_labels;
    QVector<QSharedPointer<CustomEncoder>> m_encoders;

    int m_current_encoder_page;
    int m_encoders_per_page;

    EncoderType m_type;
    EncoderMode m_mode;
};

#endif // ENCODERCONTROL_H
