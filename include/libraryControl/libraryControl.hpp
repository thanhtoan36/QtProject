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
    Q_PROPERTY(int currentGroupPage READ currentGroupPage WRITE setCurrentGroupPage NOTIFY currentGroupPageChanged)
    Q_PROPERTY(int currentHistoryPage READ currentHistoryPage WRITE setCurrentHistoryPage NOTIFY currentHistoryPageChanged)
    Q_PROPERTY(QString selectedGroupMode READ selectedGroupMode WRITE setSelectedGroupMode NOTIFY selectedGroupModeChanged)
    Q_PROPERTY(QString selectedHistoryMode READ selectedHistoryMode WRITE setSelectedHistoryMode NOTIFY selectedHistoryModeChanged)

public:
    struct LibraryButton
    {
        QString mode;
        QSharedPointer<TitleSelectButton> widget;
    };

    explicit LibraryControl(QWidget * parent = nullptr);
    virtual void SetDispParamData(LIBRARY_DISP_PARAM *param);

    int currentGroupPage() const;
    void setCurrentGroupPage(int newCurrentGroupPage);

    int currentHistoryPage() const;
    void setCurrentHistoryPage(int newCurrentHistoryPage);

    QString selectedGroupMode() const;
    void setSelectedGroupMode(const QString &newSelectedGroupMode);

    QString selectedHistoryMode() const;
    void setSelectedHistoryMode(const QString &newSelectedHistoryMode);

signals:
    void currentGroupPageChanged();
    void currentHistoryPageChanged();
    void selectedGroupModeChanged();
    void selectedHistoryModeChanged();

protected:
    QPoint libStartPoint() const;
    void setLibStartPoint(QPoint newLibStartPoint);

    QPoint modeStartPoint() const;
    void setModeStartPoint(QPoint newModeStartPoint);

    int maxGroupPages() const;
    int maxHistoryPages() const;

    int modeButtonsPerPage() const;
    int libraryButtonsPerPage() const;

    void refilterGroupButtonsByMode();
    void refilterHistoryButtonsByMode();

    static QVector<LibraryButton> filter(const QVector<LibraryButton> &buttons, const QString &mode = QString());
    static QVector<QSharedPointer<TitleSelectButton>> widgetList(const QVector<LibraryButton> &buttons);

    void updateGroupTab();
    void updateHistoryTab();

protected:
    virtual void addButtonToHistory(const LibraryButton &button);

    void onButtonTitleClicked();
    void onButtonRegisterClicked();
    void onButtonDeleteClicked();

protected slots:
    void onGroupModeButtonClicked();
    void onHistoryModeButtonClicked();
    void onGroupLibButtonClicked();
    void onHistoryLibButtonClicked();

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

    QVector<QSharedPointer<SelectButton>> m_group_mode_buttons;
    QVector<QSharedPointer<SelectButton>> m_history_mode_buttons;
    QVector<LibraryButton> m_group_lib_buttons;
    QVector<LibraryButton> m_history_lib_buttons;
    QVector<QSharedPointer<TitleSelectButton>> m_current_group_lib_buttons;
    QVector<QSharedPointer<TitleSelectButton>> m_current_history_lib_buttons;

    QPoint m_libStartPoint;
    QPoint m_modeStartPoint;

    QSize m_mode_buttons_grid_size;
    QSize m_lib_buttons_grid_size;

private:
    int m_currentGroupPage;
    int m_currentHistoryPage;
    QString m_selectedGroupMode;
    QString m_selectedHistoryMode;
};

#endif // LIBRARYCONTROL_HPP
