//--------------------------------------------------------------------------
// [ ファイル名 ] : utility.h
// [ 概      要 ] : ユーティリティ関数を含める
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef UTILITY_H
#define UTILITY_H

#include <QSharedPointer>
#include <QPoint>
#include <QSize>
#include <QDebug>

// Same as std::make_shared(), but use QObject::deleteLater() to delete
template <class T, class ...Args>
QSharedPointer<T> MakeSharedQObject( Args &&... args )
{
    auto raw_pointer = new T( std::forward<Args>( args )... );
    return QSharedPointer<T>( raw_pointer, &QObject::deleteLater );
}

float Map( float x, float in_min, float in_max, float out_min, float out_max );

#endif // UTILITY_H
