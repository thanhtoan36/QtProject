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

public:
    explicit PaletteControl(QWidget * parent = nullptr);
    void SetDispParamData(PALETTE_DISP_PARAM *param);


protected:
    uint16_t menuColumn() const;
    void setMenuColumn(uint16_t newMenuColumn);

    uint16_t buttonColumn() const;
    void setButtonColumn(uint16_t newColumn);

    uint16_t buttonRow() const;
    void setButtonRow(uint16_t newButtonRow);

    uint16_t menuRow() const;
    void setMenuRow(uint16_t newMenuRow);

    uint16_t menuPageSize() const;
    uint16_t buttonPageSize() const;

    QPoint buttonStartPoint() const;
    void setButtonStartPoint(QPoint newButtonStartPoint);

    QPoint menuStartPoint() const;
    void setMenuStartPoint(QPoint newMenuStartPoint);

protected:
    virtual void SetupUiComponents() override;
    virtual void SetupUiEvents() override;

protected slots:
    virtual void onButtonMenuClicked(const int index, QObject* sender);
    virtual void onPaletteButtonClicked(const int index, QObject* sender);
    virtual void scrollUp();
    virtual void scrollDown();
    virtual void scrollNext();
    virtual void scrollPrev();

protected:
    GridBackground m_grid;
    QLabel m_title_label;
    CustomPushButton m_prev_button;
    CustomPushButton m_next_button;
    CustomPushButton m_up_button;
    CustomPushButton m_down_button;
    CustomPushButton m_return_button;

    uint16_t m_buttonColumn;
    uint16_t m_menuColumn;
    uint16_t m_buttonRow;
    uint16_t m_menuRow;

    QPoint m_buttonStartPoint;
    QPoint m_menuStartPoint;

    QVector<QSharedPointer<SelectButton>> m_menu_buttons;
    QVector<QVector<QSharedPointer<SelectButton>>> m_palette_buttons_list;

    uint32_t m_current_menu;
    uint32_t m_current_menu_page;
    QVector<uint32_t> m_current_palette_page;

};

#endif // PALETTECONTROL_H
