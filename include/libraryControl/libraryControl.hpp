#ifndef LIBRARYCONTROL_HPP
#define LIBRARYCONTROL_HPP

#include "baseComponent/panelControlBase.h"
#include "libraryControl_datatypes.h"
#include "libraryControl_define.h"
#include "baseComponent/titleSelectButton.h"
#include "baseComponent/customPushButton.h"
#include "baseComponent/gridBackground.h"
#include <QLabel>

class LibraryControl : public PanelControlBase
{
    Q_OBJECT
//    Q_PROPERTY(int currentLibraryPage READ currentLibraryPage WRITE setCurrentLibraryPage NOTIFY currentLibraryPageChanged)
//    Q_PROPERTY(int currentHistoryPage READ currentHistoryPage WRITE setCurrentHistoryPage NOTIFY currentHistoryPageChanged)

public:
    explicit LibraryControl(QWidget * parent = nullptr);
    void SetDispParamData(LIBRARY_DISP_PARAM *param);

protected:
    virtual void SetupUiComponents() override;
    virtual void SetupUiEvents() override;
    virtual void scrollUpLibraryPages();
    virtual void scrollDownLibraryPages();

protected slots:
    virtual void onButtonModeClicked(const int index, QObject* sender);

    virtual void onButtonHistoryClicked();

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
    QVector<QVector<QSharedPointer<TitleSelectButton>>> m_library_buttons_list;
    QVector<QSharedPointer<TitleSelectButton>> m_history_buttons;
    QVector<QSharedPointer<SelectButton>> m_mode_buttons; //already contain ALL Mode
    QVector<QSharedPointer<TitleSelectButton>> m_all_lib_buttons;
    QVector<uint32_t> m_current_page_indexs;
    uint32_t m_current_mode = 0; //default là ALL
};

#endif // LIBRARYCONTROL_HPP
