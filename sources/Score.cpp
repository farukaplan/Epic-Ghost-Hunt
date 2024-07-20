#include "headers/Score.h"
#include "headers/Game.h"

#include <QDebug>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QMessageBox>
#include <QString>

extern Game *game;
Score::Score(int numPlayers, QGraphicsItem *parent) : QGraphicsTextItem(parent), totalPlayers(numPlayers)
{
    scores.resize(numPlayers, 0); // Initialize scores vector with 0 for all players

    // Update the displayed scores here
    QString htmlText;
    for (int i = 0; i < totalPlayers; i++)
    {
        QString playerText = "Player " + QString::number(i + 1) + ": " + QString::number(scores[i]);
        if (i == 0)
        {
            htmlText += "<font color='blue'>" + playerText + "</font><br>";
        }
        else
        {
            htmlText += "<font color='orange'>" + playerText + "</font><br>";
        }
    }
    setHtml(htmlText);
    setFont(QFont("times", 16));
}

void Score::increase(int player, int points)
{ //??
    if (player < 1 || player > totalPlayers)
    {
        throw std::out_of_range("Invalid player index");
    }

    scores[player - 1] += points;

    // Check if the player has reached 6 Ghosts and display a message
    if (scores[player - 1] >= 6)
    {
        QString playerName = "Player " + QString::number(player);
        QString message = "Congratulations " + playerName + " Reached 6 Ghosts and Won.\nClick OK for the next game";
        QMessageBox::information(nullptr, "Information", message);
        game->setScene(game->main_scene);
    }

    // Update the displayed scores here
    QString htmlText;
    for (int i = 0; i < totalPlayers; i++)
    {
        QString playerText = "Player " + QString::number(i + 1) + ": " + QString::number(scores[i]);
        if (i == 0)
        {
            htmlText += "<font color='blue'>" + playerText + "</font><br>";
        }
        else
        {
            htmlText += "<font color='orange'>" + playerText + "</font><br>";
        }
    }
    setHtml(htmlText);
}
