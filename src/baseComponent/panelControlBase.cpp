#include "include/baseComponent/panelControlBase.h"
#include <QFont>

PanelControlBase::PanelControlBase(QWidget *parent)
    : QWidget{parent}
{
    SetDefaultFont(QFont("MS PGothic", 12, QFont::Bold));
}

void PanelControlBase::PrepareUi()
{
    if (m_ui_initialized)
        return;
    m_ui_initialized = true;

    SetupUiComponents();
    SetupUiEvents();
}

void PanelControlBase::SetDefaultFont(const QFont &font)
{
    setFont(font);
}

QFont PanelControlBase::GetDefaultFont() const
{
    return font();
}
