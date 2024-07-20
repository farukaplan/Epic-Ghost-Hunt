#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Player2.h"
#include "Score.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMovie>
#include <QTimer>
#include <QWidget>

class Game : public QGraphicsView
{
  public:
    Game();
    QGraphicsScene *main_scene;
    QGraphicsScene *inside_game;
    Player *player;
    Player2 *player2;
    Score *score;
    void resetGame();
    QGraphicsScene *about_scene;
  public slots:
    void onButton1Clicked();
    void onButton2Clicked();
    void onButton3Clicked();
    void returnToMainMenu();

  protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // GAME_H
