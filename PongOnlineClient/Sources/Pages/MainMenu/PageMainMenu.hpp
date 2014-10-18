#ifndef PAGEMAINMENU_HPP
#define PAGEMAINMENU_HPP

#include <ui_PageMainMenu.h>
#include <QtWidgets/QWidget>

class PageMainMenu:
    public QWidget
{
    Q_OBJECT
    public:
        explicit PageMainMenu ( QWidget* parent = nullptr );
        virtual ~PageMainMenu ( void );
    private:
        void initializeUi ( void );
        void uninitializeUi ( void );
        Ui::PageMainMenu* uiPtr;
    signals:
        void startGame ( void );
};

#endif // PAGEMAINMENU_HPP
