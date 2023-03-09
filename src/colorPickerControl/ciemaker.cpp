//--------------------------------------------------------------------------
// [ ファイル名 ] : ciemaker.cpp
// [ 概      要 ] : CIE helper class to generate CIE diagram
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#include "colorPickerControl/ciemaker.h"
#include <cmath>
#include <QDebug>
#include <QImage>

std::vector<CPointF> g_cie_curve{{0.172787, 0.004800}, {0.170806, 0.005472}, {0.170085, 0.005976}, {0.160343, 0.014496}, {0.146958, 0.026643}, {0.139149, 0.035211}, {0.133536, 0.042704},
    {0.126688, 0.053441/*blue*/}, {0.115830, 0.073601}, {0.109616, 0.086866}, {0.099146, 0.112037}, {0.091310, 0.132737}, {0.078130, 0.170464}, {0.068717, 0.200773},
    {0.054675, 0.254155}, {0.040763, 0.317049}, {0.027497, 0.387997/*cyan*/}, {0.016270, 0.463035}, {0.008169, 0.538504}, {0.004876, 0.587196}, {0.003983, 0.610526},
    {0.003859, 0.654897}, {0.004646, 0.675970}, {0.007988, 0.715407}, {0.013870, 0.750246}, {0.022244, 0.779682}, {0.027273, 0.792153}, {0.032820, 0.802971},
    {0.038851, 0.812059}, {0.045327, 0.819430}, {0.052175, 0.825200}, {0.059323, 0.829460}, {0.066713, 0.832306}, {0.074299, 0.833833/*green*/}, {0.089937, 0.833316},
    {0.114155, 0.826231}, {0.138695, 0.814796}, {0.154714, 0.805884}, {0.192865, 0.781648}, {0.229607, 0.754347}, {0.265760, 0.724342}, {0.301588, 0.692326},
    {0.337346, 0.658867}, {0.373083, 0.624470}, {0.408717, 0.589626}, {0.444043, 0.554734}, {0.478755, 0.520222}, {0.512467, 0.486611/*yellow*/}, {0.544767, 0.454454},
    {0.575132, 0.424252}, {0.602914, 0.396516}, {0.627018, 0.372510}, {0.648215, 0.351413}, {0.665746, 0.334028}, {0.680061, 0.319765}, {0.691487, 0.308359},
    {0.700589, 0.299317}, {0.707901, 0.292044}, {0.714015, 0.285945}, {0.719017, 0.280951}, {0.723016, 0.276964}, {0.734674, 0.265326/*red*/}};

//--------------------------------------------------------------------------
//  [ 関数名 ] : GetCieCurve
//  [ 機　能 ] : Get CIE curve
//  [ 引　数 ] : void
//  [ 戻り値 ] : std::vector<CPointF> : The curve
//--------------------------------------------------------------------------
std::vector<CPointF> &GetCieCurve()
{
    return g_cie_curve;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : CIEMaker
//  [ 機　能 ] : Constructor for CIEMaker
//  [ 引　数 ] : Qint interp_num : number of interpolations
//              double brightness : brightness
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
CIEMaker::CIEMaker( int interp_num, double brightness ):
    m_interp_num( interp_num ),
    m_brightness( brightness )
{
    InitData();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : InitData
//  [ 機　能 ] : Init CIE data
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void CIEMaker::InitData()
{
    static size_t color_idx[9] {7, 16, 33, 47, 61, 0, 21, 33, 61};
    int n = m_interp_num;
    float color_val = m_brightness;
    m_white_point.SetColor( {color_val, color_val, color_val} );
    rgb_t key_color[]
    {
        {0, 0, color_val},
        {0, color_val, color_val},
        {0, color_val, 0},
        {color_val, color_val, 0},
        {color_val, 0, 0}
    };

    for( size_t i = 0; i < 5; i++ )
    {
        g_cie_curve[color_idx[i]].SetColor( key_color[i] );
    }

    for( size_t i = 0; i < sizeof( color_idx ) / sizeof( color_idx[0] ); i++ )
    {
        m_color_points[i] = g_cie_curve[color_idx[i]];
        m_color_point_idx[i] = color_idx[i] * n;
    }

    for( int i = 0; i < 5; i++ )
    {
        m_color_lines[i] = CLineF( m_color_points[i], m_color_points[( i + 1 ) % 5] );
    }

    m_white_lines[0] = CLineF( m_white_point, m_color_points[BOTTOM] );
    m_white_lines[1] = CLineF( m_white_point, m_color_points[TOP] );
    m_white_lines[2] = CLineF( m_white_point, m_color_points[RIGHT] );

    m_cie_curve_points.clear();

    for( size_t i = 0; i < g_cie_curve.size() - 1; i++ )
    {
        CLineF tmpLine( g_cie_curve[i], g_cie_curve[i + 1] );

        if( i < color_idx[BLUE] )
        {
            CLineF::AddSegment( tmpLine, m_cie_curve_points, m_color_lines[4], n );
        }
        else if( i < color_idx[CYAN] )
        {
            CLineF::AddSegment( tmpLine, m_cie_curve_points, m_color_lines[0], n );
        }
        else if( i < color_idx[GREEN] )
        {
            CLineF::AddSegment( tmpLine, m_cie_curve_points, m_color_lines[1], n );
        }
        else if( i < color_idx[YELLOW] )
        {
            CLineF::AddSegment( tmpLine, m_cie_curve_points, m_color_lines[2], n );
        }
        else
        {
            CLineF::AddSegment( tmpLine, m_cie_curve_points, m_color_lines[3], n );
        }
    }

    int bottom_point_num = n * 5 > 20 ? n * 5 : 20;
    CLineF::AddSegment( CLineF( g_cie_curve.back(), g_cie_curve.front() ), m_cie_curve_points, m_color_lines[4], bottom_point_num );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : GetColor
//  [ 機　能 ] : Get color at a point
//  [ 引　数 ] : QPointF xy : The point to get color
//  [ 戻り値 ] : QColor : color
//--------------------------------------------------------------------------
QColor CIEMaker::GetColor( QPointF xy ) const
{
    QColor out;
    CPointF cur_p( xy.x(), xy.y() );

    if( IsPointInsideBound( cur_p ) )
    {
        CLineF white_p( m_white_point, cur_p );
        CPointF cross_point;
        AreaFlag areaflag = CrossArea( cur_p );

        switch( areaflag )
        {
            case LEFT_A:
            {
                cross_point = GetCrossPoint( white_p, m_color_point_idx[BOTTOM], m_color_point_idx[TOP] );
                break;
            }

            case RIGHT_A:
            {
                cross_point = GetCrossPoint( white_p, m_color_point_idx[TOP], m_color_point_idx[RIGHT] );
                break;
            }

            default:
            {
                cross_point = GetCrossPoint( white_p, m_color_point_idx[RIGHT], m_cie_curve_points.size() );
                break;
            }
        }

        CLineF white_to_bound_line( m_white_point, cross_point );
        rgb_t c = white_to_bound_line.GetInterColor( cur_p );
        out = QColor::fromRgb( cBound( 0, int( c.r * 255 ), 255 ),
                               cBound( 0, int( c.g * 255 ), 255 ),
                               cBound( 0, int( c.b * 255 ), 255 ), 255 );
    }
    else
    {
        out = QColor::fromRgb( 255, 255, 255, 0 );
    }

    return out;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : DrawCIEDiagram
//  [ 機　能 ] : Draw CIE into an image
//  [ 引　数 ] : int pic_size : image size
//  [ 戻り値 ] : QImage : result
//--------------------------------------------------------------------------
QImage CIEMaker::DrawCIEDiagram( int pic_size )
{
    QImage image( QSize( pic_size, pic_size ), QImage::Format_ARGB32 );

    for( int y = 0; y < pic_size; y++ )
    {
        for( int x = 0; x < pic_size; x++ )
        {
            QPointF xy = QPointF( 1.0 * x / pic_size, 1.0 - 1.0 * y / pic_size );
            auto color = GetColor( xy );
            image.setPixel( x, y, color.rgba() );
        }
    }

    return image;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : GetCrossPoint
//  [ 機　能 ] : Get cross point
//  [ 引　数 ] : const CLineF &l : line
//              int start : start index
//              int end : end index
//  [ 戻り値 ] : CPointF : the cross point
//--------------------------------------------------------------------------
CPointF CIEMaker::GetCrossPoint( const CLineF &l, int start, int end ) const
{
    double min_dist = INT_MAX;
    int min_idx = 0;

    for( int i = start; i < end; i++ )
    {
        const CPointF &p = m_cie_curve_points[i];
        double tmpDist = std::abs( p.Y() - l.K() * p.X() - l.B() );

        if( tmpDist < min_dist )
        {
            min_dist = tmpDist;
            min_idx = i;
        }
    }

    return m_cie_curve_points[min_idx];
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : CrossArea
//  [ 機　能 ] : Get cross area
//  [ 引　数 ] : const CPointF &p: the point to calculate
//  [ 戻り値 ] : AreaFlag : which area is being returned
//--------------------------------------------------------------------------
CIEMaker::AreaFlag CIEMaker::CrossArea( const CPointF &p ) const
{
    if( p.Y() >= m_white_lines[0].Y( p.X() ) &&
        p.Y() <= m_white_lines[1].Y( p.X() ) )
    {
        return LEFT_A;
    }
    else if( p.Y() >= m_white_lines[1].Y( p.X() ) &&
             p.Y() >= m_white_lines[2].Y( p.X() ) )
    {
        return RIGHT_A;
    }
    else
    {
        return BOTTOM_A;
    }
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : IsPointInsideBound
//  [ 機　能 ] : Check if a point is inside the boundary
//  [ 引　数 ] : const CPointF &p: the point to check
//  [ 戻り値 ] : bool : True if the point is inside bound, otherwise False
//--------------------------------------------------------------------------
bool CIEMaker::IsPointInsideBound( const CPointF &p ) const
{
    bool rect_condition = p.Y() < m_color_points[TOP].Y() &&
                          p.X() > m_color_points[LEFT].X() &&
                          p.X() < m_color_points[RIGHT].X();

    if( !rect_condition )
    {
        return rect_condition;
    }

    CLineF bottom_line( m_color_points[RIGHT], m_color_points[BOTTOM] );
    bool is_bottom = p.Y() < m_white_lines[0].Y( p.X() ) && p.Y() < m_white_lines[2].Y( p.X() );

    if( is_bottom )
    {
        return rect_condition && p.Y() > bottom_line.K() * p.X() + bottom_line.B();
    }
    else
    {
        return rect_condition && IsPointInsideBound( p, m_color_point_idx[BOTTOM], m_color_point_idx[RIGHT] );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : IsPointInsideBound
//  [ 機　能 ] : Check if a point is inside the boundary
//  [ 引　数 ] : const CPointF &p: the point to check
//              int start : start index
//              int end : end index
//  [ 戻り値 ] : bool : True if the point is inside bound, otherwise False
//--------------------------------------------------------------------------
bool CIEMaker::IsPointInsideBound( const CPointF &p, int start, int end ) const
{
    double min_dist1 = INT_MAX;
    double min_dist2 = INT_MAX;
    int min_idx1 = 0;
    int min_dx2 = 0;
    double tmp_dist = 0;

    for( int i = start; i < end; i++ )
    {
        const CPointF &q = m_cie_curve_points[i];
        tmp_dist = powf( p.Y() - q.Y(), 2 ) + powf( p.X() - q.X(), 2 );

        if( tmp_dist < min_dist1 && q.Y() < p.Y() )
        {
            min_dist1 = tmp_dist;
            min_idx1 = i;
        }

        if( tmp_dist < min_dist2 && q.Y() > p.Y() )
        {
            min_dist2 = tmp_dist;
            min_dx2 = i;
        }
    }

    CLineF dist_line( m_cie_curve_points[min_idx1], m_cie_curve_points[min_dx2] );

    if( min_dx2 <= m_color_point_idx[LEFT] && min_idx1 <= m_color_point_idx[LEFT] )
    {
        return p.Y() > dist_line.Y( p.X() );
    }
    else
    {
        return p.Y() < dist_line.Y( p.X() );
    }
}
