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

    Q_PROPERTY(int currentGroupPage READ currentGroupPage WRITE setCurrentGroupPage NOTIFY currentGroupPageChanged)
    Q_PROPERTY(int currentPalettePage READ currentPalettePage WRITE setCurrentPalettePage NOTIFY currentPalettePageChanged)
    Q_PROPERTY(PaletteType type READ type WRITE setType NOTIFY typeChanged)

public:
    explicit PaletteControl(QWidget * parent = nullptr);
    virtual void SetDispParamData(PALETTE_DISP_PARAM *param);

    int currentGroupPage() const;
    void setCurrentGroupPage(int newCurrentGroupPage);

    int currentPalettePage() const;
    void setCurrentPalettePage(int newCurrentPalettePage);

    PaletteType type() const;
    void setType(PaletteType newType);

signals:
    void currentGroupPageChanged();
    void currentPalettePageChanged();
    void typeChanged();

protected:
    uint16_t menuPageSize() const;
    uint16_t buttonPageSize() const;

    QPoint buttonStartPoint() const;
    void setButtonStartPoint(QPoint newButtonStartPoint);

    QPoint groupStartPoint() const;
    void setMenuStartPoint(QPoint newMenuStartPoint);

protected:
    int maxGroupPages() const;
    int maxPalettePages() const;
    int groupButtonsPerPage() const;
    int paletteButtonsPerPage() const;
    int selectedGroupIndex() const;

protected slots:
    virtual void onGroupButtonClicked();
    virtual void onPaletteButtonClicked();

    virtual void updateGroupPages();
    virtual void updatePalettePages();

    virtual void onTypeChanged();

protected:
    GridBackground m_grid;
    QLabel m_title_label;

    CustomPushButton m_button_previous_group_page;
    CustomPushButton m_button_next_group_page;
    CustomPushButton m_button_previous_palette_page;
    CustomPushButton m_button_next_palette_page;
    CustomPushButton m_return_button;

    QPoint m_buttonStartPoint;
    QPoint m_menuStartPoint;

    QVector<QSharedPointer<SelectButton>> m_group_buttons;
    QVector<QVector<QSharedPointer<SelectButton>>> m_palette_buttons;

    QSize m_group_button_grid_size;
    QSize m_palette_button_grid_size;

private:
    int m_currentGroupPage;
    int m_currentPalettePage;
    PaletteType m_type;
};

#endif // PALETTECONTROL_H
