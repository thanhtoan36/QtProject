//--------------------------------------------------------------------------
// [ ファイル名 ] : paletteControl.h
// [ 概      要 ] : PaletteControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef PALETTECONTROL_H
#define PALETTECONTROL_H

#include "paletteControl_datatypes.h"
#include "baseComponent/panelControlBase.h"
#include "baseComponent/selectButton.h"
#include "baseComponent/customPushButton.h"
#include "baseComponent/gridBackground.h"
#include <QLabel>

class PaletteControl : public PanelControlBase
{
    Q_OBJECT

    Q_PROPERTY( int CurrentModePage READ CurrentModePage WRITE SetCurrentModePage NOTIFY CurrentModePageChanged )
    Q_PROPERTY( int CurrentPalettePage READ CurrentPalettePage WRITE SetCurrentPalettePage NOTIFY CurrentPalettePageChanged )
    Q_PROPERTY( PaletteType Type READ Type WRITE SetType NOTIFY TypeChanged )

    Q_PROPERTY( QString SelectedPalette READ SelectedPalette WRITE SetSelectedPalette NOTIFY SelectedPaletteChanged )
    Q_PROPERTY( QString SelectedMode READ SelectedMode WRITE SetSelectedMode NOTIFY SelectedModeChanged )

public:
    explicit PaletteControl( QWidget *parent = nullptr );
    virtual void SetDispParamData( PALETTE_DISP_PARAM *param );

    PaletteType Type() const;
    QString SelectedPalette() const;
    QString SelectedMode() const;

signals:
    void CurrentModePageChanged();
    void CurrentPalettePageChanged();
    void TypeChanged();

    void NextModePageClicked();
    void PrevModePageClicked();
    void NextPalettePageClicked();
    void PrevPalettePageClicked();
    void ReturnButtonClicked();

    void SelectedPaletteChanged();
    void SelectedModeChanged();

protected:
    void SetSelectedPalette( const QString &value );
    void SetSelectedMode( const QString &value );

    uint16_t MenuPageSize() const;
    uint16_t ButtonPageSize() const;

    QPoint PaletteStartPoint() const;
    void SetPaletteStartPoint( QPoint value );

    QPoint ModeStartPoint() const;
    void SetMenuStartPoint( QPoint value );

    int CurrentModePage() const;
    void SetCurrentModePage( int value );

    int CurrentPalettePage() const;
    void SetCurrentPalettePage( int value );

    void SetType( PaletteType value );

protected:
    int MaxModePages() const;
    int MaxPalettePages() const;
    int ModeButtonsPerPage() const;
    int PaletteButtonsPerPage() const;
    int SelectedModeIndex() const;

protected slots:
    virtual void OnModeButtonClicked();
    virtual void OnPaletteButtonClicked();

    virtual void UpdateModePages();
    virtual void UpdatePalettePages();

    virtual void OnTypeChanged();

protected:
    GridBackground m_grid;
    QLabel m_title_label;

    CustomPushButton m_button_previous_mode_page;
    CustomPushButton m_button_next_mode_page;
    CustomPushButton m_button_previous_palette_page;
    CustomPushButton m_button_next_palette_page;
    CustomPushButton m_return_button;

    QPoint m_button_start_point;
    QPoint m_menu_start_point;

    QVector<QSharedPointer<SelectButton>> m_mode_buttons;
    QVector<QVector<QSharedPointer<SelectButton>>> m_palette_buttons;
    QStringList m_mode_names;
    QVector<QStringList> m_palette_names;

    QSize m_mode_button_grid_size;
    QSize m_palette_button_grid_size;

private:
    int m_current_mode_page;
    int m_current_palette_page;
    PaletteType m_type;
    QString m_selected_palette;
    QString m_selected_mode;
};

#endif // PALETTECONTROL_H
