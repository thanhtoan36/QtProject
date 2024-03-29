//--------------------------------------------------------------------------
// [ ファイル名 ] : inputNumControl.h
// [ 概      要 ] : 数値入力コントロール垂直ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef INPUTNUMCONTROL_H
#define INPUTNUMCONTROL_H

#include "baseComponent/panelControlBase.h"
#include "baseComponent/customPushButton.h"
#include "baseComponent/selectButton.h"
#include "inputNumControl_datatypes.h"
#include "baseComponent/gridBackground.h"
#include <QLabel>

enum InputNumValueMode
{
    INPUT_NUM_MODE_RELATIVE,
    INPUT_NUM_MODE_ABSOLUTE,
};

class InputNumControl : public PanelControlBase
{
    Q_OBJECT
    Q_PROPERTY( InputNumMode Mode READ Mode WRITE SetMode NOTIFY ModeChanged )
    Q_PROPERTY( InputNumValueMode ValueMode READ ValueMode WRITE SetValueMode NOTIFY ValueModeChanged )
    Q_PROPERTY( InputNumType Type READ Type WRITE SetType NOTIFY TypeChanged )
    Q_PROPERTY( int CurrentGroupButtonsPage READ CurrentGroupButtonsPage WRITE SetCurrentGroupButtonsPage NOTIFY CurrentGroupButtonsPageChanged )
    Q_PROPERTY( QString SelectedModeButton READ SelectedModeButton WRITE SetSelectedModeButton NOTIFY SelectedModeButtonChanged )

public:
    explicit InputNumControl( QWidget *parent = nullptr );
    virtual void SetDispParamData( INPUT_NUM_DISP_PARAM *param );

    InputNumMode Mode() const;
    InputNumType Type() const;
    InputNumValueMode ValueMode() const;
    int CurrentGroupButtonsPage() const;
    const QString &SelectedModeButton() const;

signals:
    void ModeChanged();
    void TypeChanged();
    void ValueModeChanged();
    void CurrentGroupButtonsPageChanged();
    void InputNumButtonClicked( const QString &text );
    void SelectedModeButtonChanged();
    void ReturnClicked();

protected:
    int MaxGroupButtonPages() const;
    virtual int GroupButtonsPerPage() const;
    virtual void SetupGroupButtonPages();
    void OnGroupButtonClicked();

    void SetMode( InputNumMode newMode );
    void SetType( InputNumType newType );
    void SetValueMode( const InputNumValueMode &mode );
    void SetCurrentGroupButtonsPage( int page );
    void SetSelectedModeButton( const QString &mode );

protected slots:
    void OnModeChanged();
    void OnValueModeChanged();
    virtual void OnTypeChanged();

protected:
    GridBackground m_grid;
    QLabel m_label_title;
    SelectButton m_button_mode_percent;
    SelectButton m_button_mode_255;
    SelectButton m_button_mode_angle;
    SelectButton m_button_relative;
    SelectButton m_button_absolute;

    CustomPushButton m_button_previous_tab;
    CustomPushButton m_button_next_tab;

    QVector<QSharedPointer<SelectButton>> m_group_buttons;
    QVector<QSharedPointer<CustomPushButton>> m_input_num_buttons;
    CustomPushButton m_return_button;

    InputNumMode m_mode;
    InputNumValueMode m_valueMode;
    InputNumType m_type;
    int m_current_group_buttons_page;
    int m_group_buttons_per_page;

    QString m_selected_mode_button;
};


#endif // INPUTNUMCONTROL_H
