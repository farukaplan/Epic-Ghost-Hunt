#include "headers/Ghost.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QTimer>

Ghost::Ghost(QGraphicsRectItem *parent) : QGraphicsPixmapItem(parent)
{
    // Set the ghost's initial position and size
    setPixmap(QPixmap(":/images/Ghost.png"));
    setPos(QRandomGenerator::global()->bounded(0, 500), QRandomGenerator::global()->bounded(0, 500));
    qreal new_ax = 0.5;
    qreal new_ay = 0.5;
    QTransform transform;
    transform.translate(-pixmap().width() * new_ax, -pixmap().height() * new_ay);
    setTransform(transform);
    // Create a timer to update the ghost's position every 100 ms
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Ghost::move);
    timer->start(100);
    isVisible = false;
}

Ghost::~Ghost()
{ // F
    if (scene() != nullptr)
    {
        scene()->removeItem(this);
    }
}

void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Set the transparency level
    if (isVisible)
    {
        painter->setOpacity(0.5); // Adjust the value to change the transparency
        painter->drawPixmap(boundingRect().toRect(), pixmap());
    }
}

void Ghost::move()
{

    // Move the ghost in a random direction
    qreal dx = QRandomGenerator::global()->bounded(-10, 11);
    qreal dy = QRandomGenerator::global()->bounded(-10, 11);
    // Calculate the new position
    QPointF newPos = pos() + QPointF(dx, dy);

    // Check if the new position is within the scene boundaries
    if (scene() && scene()->sceneRect().contains(newPos))
    {
        // Set the new position if it's within the scene
        for (QGraphicsItem *item : scene()->items())
        {
            if (Ghost *otherGhost = dynamic_cast<Ghost *>(item))
            {
                if (*this == *otherGhost && this != otherGhost) //!
                {
                    // Ghosts have the same position, so generate a new random position
                    move();
                    return;
                }
            }
        }
        // Set the new position if it's within the scene
        setPos(newPos);
    }
    else
    {
        move();
    }
}

bool Ghost::operator==(const Ghost &other) const
{ // operator overloading
    // Compare the positions of two Ghost objects
    return (this->pos() == other.pos());
}
