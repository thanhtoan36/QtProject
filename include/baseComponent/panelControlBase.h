#ifndef PANELCONTROLBASE_H
#define PANELCONTROLBASE_H

#include <QWidget>

class PanelControlBase : public QWidget
{
    Q_OBJECT
public:
    enum VerticalDirections
    {
        TopToBottom,
        BottomToTop,
    };

    explicit PanelControlBase(QWidget *parent = nullptr);

    static int calulateNumberOfPages(int itemCount, int itemsPerPage);
    static int calculateNumberOfVisibleItems(int itemsCount, int itemsPerPage, int pageIndex);

    template <class T>
    static void placeChildrenIntoPanel(const QVector<QSharedPointer<T>> &children, QSize childSize, QPoint firstCellTopLeft, QSize gridSize, VerticalDirections vdirection = TopToBottom) {
        if (gridSize.width() == 0 || gridSize.height() == 0)
            return;

        for (int i  = 0; i < children.length(); ++i) {
            const int visualIndex = i % (gridSize.width() * gridSize.height());
            const int row = visualIndex / gridSize.width();
            const int col = visualIndex % gridSize.width();

            auto &child = children[i];
            if (vdirection == TopToBottom) {
                child->move(firstCellTopLeft + QPoint(col * childSize.width(), row * childSize.height()));
            } else  {
                child->move(firstCellTopLeft + QPoint(col * childSize.width(), -row * childSize.height()));
            }
        }
    }

    template <class T>
    static void updateChildrenVisibility(const QVector<QSharedPointer<T>> &children, int currentPage, int itemsPerPage) {
        int pageBeginIndex = currentPage * itemsPerPage;
        int pageEndIndex = (currentPage + 1) * itemsPerPage;

        for (int i  = 0; i < children.length(); ++i) {
            auto &child = children[i];
            child->setVisible(i >= pageBeginIndex && i < pageEndIndex);
        }
    }
};

#endif // PANELCONTROLBASE_H
