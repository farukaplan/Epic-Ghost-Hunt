#include "headers/Player.h"
#include "headers/Game.h"
#include "headers/Ghost.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QLabel>
#include <QList>
#include <QMessageBox>
#include <QRectF>
#include <QTimer>

#include <unordered_set>

extern Game *game;
Player ::Player() : QGraphicsPixmapItem(), AbstractPlayer()
{
    setPixmap(QPixmap(":/images/area.png"));
    setPos(400, 550);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    qreal new_ax = 0.5;
    qreal new_ay = 0.5;
    QTransform transform;
    transform.translate(-pixmap().width() * new_ax, -pixmap().height() * new_ay);
    setTransform(transform);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Player::update);
    timer->start(10);
    visionRadius = 60.00;
}
void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left && x() > 0)
    {
        setPos(x() - 10, y());
    }
    else if (event->key() == Qt::Key_Right && x() < scene()->width())
    {
        setPos(x() + 10, y());
    }
    else if (event->key() == Qt::Key_Up && y() > 0)
    {
        setPos(x(), y() - 10);
    }
    else if (event->key() == Qt::Key_Down && y() < scene()->height())
    {
        setPos(x(), y() + 10);
    }
}
void Player::update()
{
    static qreal rotationAngle = 0.0;

    // Rotate the image without changing the position
    setTransformOriginPoint(pixmap().width() / 2, pixmap().height() / 2);
    setRotation(rotationAngle);

    // Increment the rotation angle
    rotationAngle -= 1.0;
    if (rotationAngle <= -360.0)
    {
        rotationAngle = 0.0;
    }

    // Get a list of all items colliding with the player
    QList<QGraphicsItem *> collisions = collidingItems();

    static std::unordered_set<Ghost *> visibleGhosts;

    for (auto it = visibleGhosts.begin(); it != visibleGhosts.end();)
    {
        Ghost *ghost = *it;
        qreal dx = ghost->x() - x();
        qreal dy = ghost->y() - y();
        qreal distance = std::sqrt(dx * dx + dy * dy);

        if (distance > visionRadius)
        {
            ghost->isVisible = false;
            it = visibleGhosts.erase(it);
        }
        else
        {
            ++it;
        }
    }
    for (QGraphicsItem *item : collisions)
    {
        if (Ghost *ghost = dynamic_cast<Ghost *>(item))
        {
            qreal dx = ghost->x() - x();
            qreal dy = ghost->y() - y();
            qreal distance = std::sqrt(dx * dx + dy * dy);

            if (distance <= visionRadius)
            {
                ghost->isVisible = true;

                // Add the visible ghost to the set
                visibleGhosts.insert(ghost);
            }

            if (distance <= 10)
            {
                game->score->increase(1);
                scene()->removeItem(ghost);
                delete ghost;
                visibleGhosts.erase(ghost);
            }
        }
    }
}
