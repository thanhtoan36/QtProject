#ifndef LIBRARYCONTROL_HPP
#define LIBRARYCONTROL_HPP

#include "baseComponent/panelControlBase.h"
#include "libraryControl_datatypes.h"
#include "baseComponent/titleSelectButton.h"
#include "baseComponent/customPushButton.h"
#include "baseComponent/gridBackground.h"
#include <QLabel>

class LibraryControl : public PanelControlBase
{
    Q_OBJECT

public:
    explicit LibraryControl(QWidget * parent = nullptr);
    void SetDispParamData(LIBRARY_DISP_PARAM *param);


protected:
    uint16_t column() const;
    void setColumn(uint16_t newColumn);

    uint16_t libRow() const;
    void setLibRow(uint16_t newLibRow);

    uint16_t modeRow() const;
    void setModeRow(uint16_t newModeRow);

    uint16_t libPageSize() const;
    uint16_t modePageSize() const;

    QPoint libStartPoint() const;
    void setLibStartPoint(QPoint newLibStartPoint);

    QPoint modeStartPoint() const;
    void setModeStartPoint(QPoint newModeStartPoint);


protected:
    virtual void SetupUiComponents() override;
    virtual void SetupUiEvents() override;
    virtual void scrollUpLibraryPages();
    virtual void scrollDownLibraryPages();

protected slots:
    virtual void onButtonModeClicked(const int index, QObject* sender);
    virtual void onButtonLibraryClicked(const int index, QObject* sender);
    virtual void onButtonHistoryLibraryClicked(const int index, QObject* sender);
    virtual void onButtonModeHistoryClicked(const int index, QObject* sender);
    virtual void onButtonHistoryClicked(const bool check);

protected:
    GridBackground m_grid;
    QLabel m_title_label;
    ToggleButton m_history_button;
    CustomPushButton m_up_button;
    CustomButtonBase m_down_button;
    CustomPushButton m_return_button;
    QLabel m_setting_label;
    SelectButton m_title_button;
    CustomPushButton m_empty_button;
    SelectButton m_register_button;
    SelectButton m_delete_button;

    //for library panel
    QVector<QVector<QSharedPointer<TitleSelectButton>>> m_library_buttons_list;
    QVector<QSharedPointer<SelectButton>> m_mode_buttons; //already contain ALL Mode
    QVector<QSharedPointer<TitleSelectButton>> m_all_lib_buttons;
    QVector<uint32_t> m_current_page_indexs;
    uint32_t m_current_mode = 0; //default là ALL

    //for history
    QVector<QVector<QSharedPointer<TitleSelectButton>>> m_history_buttons_list;
    QVector<QSharedPointer<SelectButton>> m_history_mode_buttons; //already contain ALL Mode
    QVector<QSharedPointer<TitleSelectButton>> m_all_historty_buttons;
    QVector<uint32_t> m_current_history_indexs;
    uint32_t m_current_history_mode = 0; //default là ALL

    uint16_t m_column;
    uint16_t m_libRow;
    uint16_t m_modeRow;

    QPoint m_libStartPoint;
    QPoint m_modeStartPoint;
};

#endif // LIBRARYCONTROL_HPP
