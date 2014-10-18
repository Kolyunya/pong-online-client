#ifndef LOADING_HPP
#define LOADING_HPP

#include <QWidget>

namespace Ui
{
    class Loading;
}

class Loading :
    public QWidget
{
    Q_OBJECT
    public:
        explicit Loading ( QWidget* parent = nullptr );
        ~Loading();
        void setText ( const QString& text );
    private:
        Ui::Loading* uiPtr;
};

#endif // LOADING_HPP
