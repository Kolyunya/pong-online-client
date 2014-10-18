#ifndef SCOREVIEW_HPP
#define SCOREVIEW_HPP

#include <QObject>

class QLabel;

class GameScore;

class ScoreView :
    public QObject
{
    Q_OBJECT
    public:
        explicit ScoreView(QObject *parent = 0);
        void setModel ( GameScore* modelPtr );
        void setLabel ( QLabel* labelPtr );
    private:
        GameScore* modelPtr;
        QLabel* labelPtr;
    public slots:
        void update ( void );
};

#endif // SCOREVIEW_HPP
