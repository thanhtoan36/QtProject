//--------------------------------------------------------------------------
// [ ファイル名 ] : cieaux.cpp
// [ 概      要 ] : CIE data type
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "colorPickerControl/cieaux.h"
#include <cmath>
// ***************************** CPointF *****************************

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

double CPointF::GetPointDist( const CPointF &p ) const
{
    return pow( ( p.m_x - m_x ) * ( p.m_x - m_x ) + ( p.m_y - m_y ) * ( p.m_y - m_y ), 0.5 );
}

// ***************************** CLineF *****************************
CLineF::CLineF( const CPointF &p1, const CPointF &p2 )
{
    m_start_point = p1;
    m_end_point = p2;
    m_k = ( p1.m_y - p2.m_y ) / ( p1.m_x - p2.m_x + 0.000001 );
    m_b = p1.m_y - m_k * p1.m_x;
}

CPointF CLineF::P( double pos ) const
{
    pos = cBound( -1.0, pos, 1.0 );
    float x = m_start_point.X() + pos * std::abs( m_end_point.X() - m_start_point.X() );
    return {x, m_k *x + m_b};
}

rgb_t CLineF::GetInterColor( const CPointF &p ) const
{
    CPointF tmp = p;
    tmp.SetInterpColor( m_start_point, m_end_point );
    return tmp.C();
}

rgb_t CLineF::GetInterColor( double pos ) const
{
    pos = cBound( 0.0, pos, 1.0 );

    return CPointF::GetInterpPoint( m_start_point, m_end_point, pos ).C();
}

CPointF CLineF::GetCrossPoint( const CLineF &l )
{
    if( l.K() == m_k )
    {
        return CPointF();
    }

    double x = ( l.B() - m_b ) / ( m_k - l.K() );
    double y = m_k * x + m_b;
    CPointF p( x, y );

    return p;
}

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
