#include "Loading.hpp"
#include "ui_Loading.h"

Loading::Loading ( QWidget* parentPtr ) :
    QWidget(parentPtr),
    uiPtr(new Ui::Loading)
{
    uiPtr->setupUi(this);
}

Loading::~Loading ( void )
{
    delete uiPtr;
}

void Loading::setText ( const QString& text )
{
    this->uiPtr->Label->setText(text);
}
