#ifndef PLAYER2_H
#define PLAYER2_H

#include "AbstractPlayer.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QObject>

class Player2 : public AbstractPlayer, public QGraphicsPixmapItem
{
    Q_OBJECT
  public:
    Player2();
    void keyPressEvent(QKeyEvent *event) override;
    void update();
    int visionRadius;
};

#endif // PLAYER2_H
