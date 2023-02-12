#ifndef LIBRARYCONTROLHORIZON_H
#define LIBRARYCONTROLHORIZON_H

#include "libraryControl.hpp"


class LibraryControlHorizon : public LibraryControl
{
public:
    explicit LibraryControlHorizon(QWidget* parent = nullptr);
protected:
    virtual void SetupUiComponents() override;
};

#endif // LIBRARYCONTROLHORIZON_H
