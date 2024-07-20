#ifndef SCORE_H
#define SCORE_H

#include <QFont>
#include <QGraphicsTextItem>

#include <vector>

class Score : public QGraphicsTextItem
{
  public:
    Score(int numPlayers = 2, QGraphicsItem *parent = nullptr);
    void increase(int player, int points = 1);
    inline int getScore(int player)
    {
        if (player < 1 || player > totalPlayers)
        {
            throw std::out_of_range("Invalid player index");
        }

        return scores[player - 1];
    }

  private:
    std::vector<int> scores;
    int totalPlayers;
};

#endif // SCORE_H
