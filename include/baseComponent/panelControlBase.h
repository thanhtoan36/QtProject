#ifndef PANELCONTROLBASE_H
#define PANELCONTROLBASE_H

#include <QWidget>

class PanelControlBase : public QWidget
{
    Q_OBJECT
public:
    explicit PanelControlBase(QWidget *parent = nullptr);

    void PrepareUi();

protected:
    // Place UI components into this panel
    virtual void SetupUiComponents() {};
    // Connect signals / slots to the UI components
    virtual void SetupUiEvents() {};

signals:

private:
    bool m_ui_initialized;
};

#endif // PANELCONTROLBASE_H
