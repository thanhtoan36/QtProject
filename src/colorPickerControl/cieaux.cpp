//--------------------------------------------------------------------------
// [ ファイル名 ] : cieaux.cpp
// [ 概      要 ] : CIE data type
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "colorPickerControl/cieaux.h"
#include <cmath>

//--------------------------------------------------------------------------
//  [ 関数名 ] : GetInterpPoint
//  [ 機　能 ] : Get the interpolation point
//  [ 引　数 ] : const CPointF &p1: The 1st point
//              const CPointF &p2: The 2nd point
//              double pos: The position to check
//  [ 戻り値 ] : CPointF : Interpolation point
//--------------------------------------------------------------------------
CPointF CPointF::GetInterpPoint( const CPointF &p1, const CPointF &p2, double pos )
{
    float x, y, r, g, b;
    x = p1.m_x * ( 1 - pos ) + p2.m_x * pos;
    y = p1.m_y * ( 1 - pos ) + p2.m_y * pos;
    r = p1.m_c.r * ( 1 - pos ) + p2.m_c.r * pos;
    g = p1.m_c.g * ( 1 - pos ) + p2.m_c.g * pos;
    b = p1.m_c.b * ( 1 - pos ) + p2.m_c.b * pos;
    return CPointF{x, y, {r, g, b}};
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetInterpColor
//  [ 機　能 ] : Set the interpolation color
//  [ 引　数 ] : const CPointF &p1: The 1st point
//              const CPointF &p2: The 2nd point
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void CPointF::SetInterpColor( const CPointF &p1, const CPointF &p2 )
{
    double dist1 = p1.GetPointDist( p2 );
    double dist2 = GetPointDist( p1 );
    double pos = dist2 / dist1;
    float r, g, b;
    r = p1.m_c.r * ( 1 - pos ) + p2.m_c.r * pos;
    g = p1.m_c.g * ( 1 - pos ) + p2.m_c.g * pos;
    b = p1.m_c.b * ( 1 - pos ) + p2.m_c.b * pos;
    SetColor( {r, g, b} );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : GetPointDist
//  [ 機　能 ] : Set point distance
//  [ 引　数 ] : const CPointF &p : the point to calculate
//  [ 戻り値 ] : double: distance
//--------------------------------------------------------------------------
double CPointF::GetPointDist( const CPointF &p ) const
{
    return pow( ( p.m_x - m_x ) * ( p.m_x - m_x ) + ( p.m_y - m_y ) * ( p.m_y - m_y ), 0.5 );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : CLineF
//  [ 機　能 ] : Constructor for CLineF
//  [ 引　数 ] : const CPointF &p1: The 1st point
//              const CPointF &p2: The 2nd point
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
CLineF::CLineF( const CPointF &p1, const CPointF &p2 )
{
    m_start_point = p1;
    m_end_point = p2;
    m_k = ( p1.m_y - p2.m_y ) / ( p1.m_x - p2.m_x + 0.000001 );
    m_b = p1.m_y - m_k * p1.m_x;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : P
//  [ 機　能 ] : Helper function for calculation
//  [ 引　数 ] : double pos : position
//  [ 戻り値 ] : CPointF : point
//--------------------------------------------------------------------------
CPointF CLineF::P( double pos ) const
{
    pos = cBound( -1.0, pos, 1.0 );
    float x = m_start_point.X() + pos * std::abs( m_end_point.X() - m_start_point.X() );
    return {x, m_k *x + m_b};
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : GetInterColor
//  [ 機　能 ] : Get color at a point
//  [ 引　数 ] : const CPointF &p : position
//  [ 戻り値 ] : rgb_t : RGB color
//--------------------------------------------------------------------------
rgb_t CLineF::GetInterColor( const CPointF &p ) const
{
    CPointF tmp = p;
    tmp.SetInterpColor( m_start_point, m_end_point );
    return tmp.C();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : AddSegment
//  [ 機　能 ] : Add segment to a line
//  [ 引　数 ] : const CLineF &l : the line
//              std::vector<CPointF> &points : list of points
//              const CLineF &colorLine : the line with color
//              int n : number of steps
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void CLineF::AddSegment( const CLineF &l, std::vector<CPointF> &points, const CLineF &colorLine, int n )
{
    if( n <= 0 )
    {
        n = 1;
    }

    double direction = 1.0;

    if( l.m_start_point.X() > l.m_end_point.X() )
    {
        direction = -1.0;
    }

    double stepX = direction / n;

    for( int i = 0; i < n; i++ )
    {
        CPointF p = l.P( stepX * i );
        p.SetColor( colorLine.GetInterColor( p ) );
        points.push_back( p );
    }
}
