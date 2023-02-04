#ifndef PANELCONTROLBASE_H
#define PANELCONTROLBASE_H

#include <QWidget>

class PanelControlBase : public QWidget
{
    Q_OBJECT
public:
    explicit PanelControlBase(QWidget *parent = nullptr);

    void PrepareUi();

    void SetDefaultFont(const QFont &font);
    QFont GetDefaultFont() const;

protected:
    // Place UI components into this panel
    virtual void SetupUiComponents() = 0;
    // Connect signals / slots to the UI components
    virtual void SetupUiEvents() {};

signals:

private:
    bool m_ui_initialized {false};
};

#endif // PANELCONTROLBASE_H
