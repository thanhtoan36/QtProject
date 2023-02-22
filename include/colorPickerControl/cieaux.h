//--------------------------------------------------------------------------
// [ ファイル名 ] : cieaux.h
// [ 概      要 ] : CIE data type
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef CIEAUX_H
#define CIEAUX_H

#include <vector>

template <typename T>
constexpr inline const T &cMin( const T &a, const T &b ) { return ( a < b ) ? a : b; }
template <typename T>
constexpr inline const T &cMax( const T &a, const T &b ) { return ( a < b ) ? b : a; }
template <typename T>
constexpr inline const T &cBound( const T &min, const T &val, const T &max )
{ return cMax( min, cMin( max, val ) ); }

// color
typedef struct
{
    float r;
    float g;
    float b;
} rgb_t;

// point
class CPointF
{
    friend class CLineF;
public:
    CPointF() : CPointF( 0, 0, 0, 0, 0 ) {};
    CPointF( float x, float y ) : CPointF( x, y, 0, 0, 0 ) {};
    CPointF( float x, float y, float r, float g, float b ) : CPointF( x, y, {r, g, b} ) {};
    CPointF( float x, float y, rgb_t c ) : m_x( x ), m_y( y ), m_c( c ) {};

    float X() const {return m_x;};
    float Y() const {return m_y;};
    rgb_t C() const {return m_c;};

    void SetColor( rgb_t c ) { m_c = c; };
    void SetX( float x ) { m_x = x; };
    void SetY( float y ) { m_y = y; };

    static CPointF GetInterpPoint( const CPointF &p1, const CPointF &p2, double pos );
    void SetInterpColor( const CPointF &p1, const CPointF &p2 );
    double GetPointDist( const CPointF & ) const;

private:
    float m_x, m_y;
    rgb_t m_c;
};

// line
class CLineF
{
public:
    CLineF() : m_k( 0.0 ), m_b( 0.0 ) {};
    CLineF( const CPointF &p1, const CPointF &p2 );

    double K() const { return m_k; };
    double B() const { return m_b; };
    CPointF SP() const { return m_start_point; };
    CPointF EP() const { return m_end_point; };
    double Y( double x ) const { return m_k * x + m_b; };
    CPointF P( double pos ) const;

    rgb_t GetInterColor( const CPointF &p ) const;
    rgb_t GetInterColor( double p ) const;
    CPointF GetCrossPoint( const CLineF &l );
    static void AddSegment( const CLineF &l, std::vector<CPointF> &points, const CLineF &colorLine, int n );

private:
    CPointF m_start_point;
    CPointF m_end_point;
    float m_k, m_b;
};



#endif // CIEAUX_H
