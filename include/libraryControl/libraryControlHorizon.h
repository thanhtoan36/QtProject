//--------------------------------------------------------------------------
// [ ファイル名 ] : libraryControlHorizon.h
// [ 概      要 ] : ライブラリコントロール水平ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef LIBRARYCONTROLHORIZON_H
#define LIBRARYCONTROLHORIZON_H

#include "libraryControl.h"


class LibraryControlHorizon : public LibraryControl
{
    Q_OBJECT
public:
    explicit LibraryControlHorizon( QWidget *parent = nullptr );
};

#endif // LIBRARYCONTROLHORIZON_H
