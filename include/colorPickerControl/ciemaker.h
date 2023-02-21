#ifndef CIEMAKER_H
#define CIEMAKER_H

#include "cieaux.h"
#include <QColor>
#include <QPointF>
#include <QImage>

std::vector<CPointF>&  GetCieCurve();

class CIEMaker
{
private:
    enum PointFlag { BLUE, CYAN, GREEN, YELLOW, RED, BOTTOM, LEFT, TOP, RIGHT };
    enum AreaFlag { LEFT_A, RIGHT_A, BOTTOM_A };
public:
    CIEMaker(int interpNum = 20, double brightness = 1.0);

    QImage DrawCIEDiagram(int picSize = 500);
    std::vector<CPointF> GetCieCurvePoints() const { return m_cie_curve_points; };
    bool IsPointInsideBound(const CPointF &p) const;
    QColor GetColor(QPointF xy) const;

private:
    void InitData();

    AreaFlag CrossArea(const CPointF &p) const;
    CPointF GetCrossPoint(const CLineF &l, int start, int end) const;

    bool IsPointInsideBound(const CPointF &p, int start, int end) const;

private:
    int m_interp_num;
    double m_brightness;

    std::vector<CPointF> m_cie_curve_points;
    CPointF m_white_point{0.3333,0.3333};

    int m_color_point_idx[9]{0};
    CPointF m_color_points[9]{};
    CLineF m_color_lines[5]{};
    CLineF m_white_lines[3]{};
};

#endif // CIEMAKER_H
