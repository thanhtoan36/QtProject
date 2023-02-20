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

    Q_PROPERTY(int currentModePage READ currentModePage WRITE setCurrentModePage NOTIFY currentModePageChanged)
    Q_PROPERTY(int currentPalettePage READ currentPalettePage WRITE setCurrentPalettePage NOTIFY currentPalettePageChanged)
    Q_PROPERTY(PaletteType type READ type WRITE setType NOTIFY typeChanged)

    Q_PROPERTY(QString selectedPalette READ selectedPalette WRITE setSelectedPalette NOTIFY selectedPaletteChanged)
    Q_PROPERTY(QString selectMode READ selectMode WRITE setSelectMode NOTIFY selectModeChanged)

public:
    explicit PaletteControl(QWidget * parent = nullptr);
    virtual void SetDispParamData(PALETTE_DISP_PARAM *param);

    PaletteType type() const;

    QString selectedPalette() const;
    void setSelectedPalette(const QString &newSelectedPalette);

    QString selectMode() const;
    void setSelectMode(const QString &newSelectMode);

signals:
    void currentModePageChanged();
    void currentPalettePageChanged();
    void typeChanged();

    void NextModePageClicked();
    void PrevModePageClicked();
    void NextPalettePageClicked();
    void PrevPalettePageClicked();

    void selectedPaletteChanged();
    void selectModeChanged();

protected:
    uint16_t menuPageSize() const;
    uint16_t buttonPageSize() const;

    QPoint buttonStartPoint() const;
    void setButtonStartPoint(QPoint newButtonStartPoint);

    QPoint modeStartPoint() const;
    void setMenuStartPoint(QPoint newMenuStartPoint);

    int currentModePage() const;
    void setCurrentModePage(int newCurrentModePage);

    int currentPalettePage() const;
    void setCurrentPalettePage(int newCurrentPalettePage);

    void setType(PaletteType newType);

protected:
    int maxModePages() const;
    int maxPalettePages() const;
    int modeButtonsPerPage() const;
    int paletteButtonsPerPage() const;
    int selectedModeIndex() const;

protected slots:
    virtual void onModeButtonClicked();
    virtual void onPaletteButtonClicked();

    virtual void updateModePages();
    virtual void updatePalettePages();

    virtual void onTypeChanged();

protected:
    GridBackground m_grid;
    QLabel m_title_label;

    CustomPushButton m_button_previous_mode_page;
    CustomPushButton m_button_next_mode_page;
    CustomPushButton m_button_previous_palette_page;
    CustomPushButton m_button_next_palette_page;
    CustomPushButton m_return_button;

    QPoint m_buttonStartPoint;
    QPoint m_menuStartPoint;

    QVector<QSharedPointer<SelectButton>> m_mode_buttons;
    QVector<QVector<QSharedPointer<SelectButton>>> m_palette_buttons;

    QSize m_mode_button_grid_size;
    QSize m_palette_button_grid_size;

private:
    int m_currentModePage;
    int m_currentPalettePage;
    PaletteType m_type;
    QString m_selectedPalette;
    QString m_selectMode;
};

#endif // PALETTECONTROL_H
