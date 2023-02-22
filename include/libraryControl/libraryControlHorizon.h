//--------------------------------------------------------------------------
// [ ファイル名 ] : libraryControlHorizon.h
// [ 概      要 ] : LibraryControl horizon widget
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef LIBRARYCONTROLHORIZON_H
#define LIBRARYCONTROLHORIZON_H

#include "libraryControl.hpp"


class LibraryControlHorizon : public LibraryControl
{
public:
    explicit LibraryControlHorizon(QWidget* parent = nullptr);
};

#endif // LIBRARYCONTROLHORIZON_H
