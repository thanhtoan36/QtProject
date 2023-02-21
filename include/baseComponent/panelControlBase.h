#ifndef PANELCONTROLBASE_H
#define PANELCONTROLBASE_H

#include <QWidget>
#include "baseComponent/gridBackground.h"

class PanelControlBase : public QWidget
{
    Q_OBJECT
public:
    enum VerticalDirections
    {
        TOP_TO_BOTTOM,
        BOTTOM_TO_TOP,
    };

    explicit PanelControlBase(QWidget *parent = nullptr);

    static int CalulateNumberOfPages(int itemCount, int itemsPerPage);
    static int CalculateNumberOfVisibleItems(int itemsCount, int itemsPerPage, int pageIndex);

    template <class T>
    static void PlaceChildrenIntoPanel(const QVector<QSharedPointer<T>> &children, QSize child_size, QPoint first_cell_top_left, QSize grid_size, VerticalDirections vdirection = TOP_TO_BOTTOM) {
        if (grid_size.width() == 0 || grid_size.height() == 0)
            return;

        for (int i  = 0; i < children.length(); ++i) {
            const int visual_index = i % (grid_size.width() * grid_size.height());
            const int row = visual_index / grid_size.width();
            const int col = visual_index % grid_size.width();

            auto &child = children[i];
            if (vdirection == TOP_TO_BOTTOM) {
                child->move(first_cell_top_left + QPoint(col * child_size.width(), row * child_size.height()));
            } else  {
                child->move(first_cell_top_left + QPoint(col * child_size.width(), -row * child_size.height()));
            }
        }
    }

    template <class T>
    static void UpdateChildrenVisibility(const QVector<QSharedPointer<T>> &children, int page_index, int items_per_page) {
        int begin_index = page_index * items_per_page;
        int end_index = (page_index + 1) * items_per_page;

        for (int i  = 0; i < children.length(); ++i)
        {
            auto &child = children[i];
            child->setVisible(i >= begin_index && i < end_index);
        }
    }

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

protected:
    GridBackground m_background;
};

#endif // PANELCONTROLBASE_H
