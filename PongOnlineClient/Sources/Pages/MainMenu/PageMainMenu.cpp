#include "PageMainMenu.hpp"

PageMainMenu::PageMainMenu ( QWidget* parent ):
    QWidget(parent),
    uiPtr(nullptr)
{
    this->initializeUi();
}

PageMainMenu::~PageMainMenu ( void )
{
    this->uninitializeUi();
}

void PageMainMenu::initializeUi ( void )
{
    this->uiPtr = new Ui::PageMainMenu();
    this->uiPtr->setupUi(this);
    QObject::connect(this->uiPtr->playButton,SIGNAL(clicked()),this,SIGNAL(startGame()));
}

void PageMainMenu::uninitializeUi ( void )
{
    delete this->uiPtr;
    this->uiPtr = nullptr;
}
