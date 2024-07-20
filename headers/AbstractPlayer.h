#ifndef ABSTRACTPLAYER_H
#define ABSTRACTPLAYER_H

#include <QKeyEvent>
#include <QObject>

class AbstractPlayer : public QObject
{
    Q_OBJECT
  public:
    AbstractPlayer();
    virtual void keyPressEvent(QKeyEvent *event) = 0; // Pure virtual function
    virtual void update() = 0;
};

#endif // ABSTRACTPLAYER_H
