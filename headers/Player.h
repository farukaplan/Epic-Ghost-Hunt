#ifndef PLAYER_H
#define PLAYER_H

#include "AbstractPlayer.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QObject>

class Player : public AbstractPlayer, public QGraphicsPixmapItem
{
    Q_OBJECT
  public:
    Player();
    void keyPressEvent(QKeyEvent *event) override;
    void update();
    int visionRadius;
};

#endif // PLAYER_H
