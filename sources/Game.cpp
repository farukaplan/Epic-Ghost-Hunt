#include "headers/Game.h"
#include "headers/Ghost.h"

#include <QApplication>
#include <QFont>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QImage>
#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include <QStyle>
#include <QTimer>

Game::Game()
{
    main_scene = new QGraphicsScene(this);
    main_scene->setSceneRect(0, 0, 800, 600);
    main_scene->setBackgroundBrush(Qt::lightGray);
    QMovie *movie = new QMovie(":/images/initialGround.gif");
    if (movie->isValid())
    {
        QGraphicsProxyWidget *proxy = main_scene->addWidget(new QLabel());
        proxy->setPos(0, 0);
        proxy->show();
        QLabel *label = qobject_cast<QLabel *>(proxy->widget());
        if (label)
        {
            label->setMovie(movie);
            movie->start();
        }
    }

    setScene(main_scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);
    // Start Game
    QPushButton *button1 = new QPushButton("Start The Game");
    button1->setFixedSize(150, 50);

    button1->setStyleSheet("background-color: brown; color: white;");
    QGraphicsProxyWidget *proxy1 = main_scene->addWidget(button1);
    proxy1->setPos(50, 200);
    connect(button1, &QPushButton::clicked, this, &Game::onButton1Clicked);

    // About
    QPushButton *button2 = new QPushButton("Learn About");
    button2->setFixedSize(150, 50);
    button2->setStyleSheet("background-color: brown; color: white;");
    QGraphicsProxyWidget *proxy2 = main_scene->addWidget(button2);
    proxy2->setPos(50, 350);
    connect(button2, &QPushButton::clicked, this, &Game::onButton2Clicked);

    // HowToPlay
    QPushButton *button3 = new QPushButton("How to Play");
    button3->setFixedSize(150, 50);
    button3->setStyleSheet("background-color: brown; color: white;");
    QGraphicsProxyWidget *proxy3 = main_scene->addWidget(button3);
    proxy3->setPos(50, 275);
    connect(button3, &QPushButton::clicked, this, &Game::onButton3Clicked);

    setWindowTitle("Epic Ghost Hunt");
    setWindowIcon(QIcon(":/images/icon.png"));
    show();
}

void Game::onButton1Clicked()
{
    setBackgroundBrush(QBrush(QImage(":/images/ground.jpg")));
    // Start the Game
    inside_game = new QGraphicsScene(); // Explicit heap dynamic variable
    setScene(inside_game);
    inside_game->setSceneRect(0, 0, 800, 600);
    inside_game->setBackgroundBrush(Qt::white);
    player = new Player();   // Explicit heap dynamic variable
    player2 = new Player2(); // Explicit heap dynamic variable
    inside_game->addItem(player);
    inside_game->addItem(player2);
    score = new Score(); // Explicit heap dynamic variable
    inside_game->addItem(score);
    for (int i = 0; i < 11; i++)
    { // 11 ghost
        Ghost *ghost = new Ghost();
        inside_game->addItem(ghost);
    }
}
void Game::onButton2Clicked()
{
    // Create the about_scene
    setBackgroundBrush(QBrush(QImage(":/images/ground2.png")));
    about_scene = new QGraphicsScene();
    setScene(about_scene);
    about_scene->setSceneRect(0, 0, 800, 600);
    about_scene->setBackgroundBrush(Qt::white);

    // Create labels
    QGraphicsTextItem *label1 = new QGraphicsTextItem("About This Game");
    label1->setPos(220, 25);
    label1->setFont(QFont("Arial", 32));
    label1->setDefaultTextColor(Qt::white);
    about_scene->addItem(label1);

    QGraphicsTextItem *label2 = new QGraphicsTextItem("------------------------");
    label2->setPos(220, 50);
    label2->setFont(QFont("Arial", 32));
    label2->setDefaultTextColor(Qt::white);
    about_scene->addItem(label2);

    QGraphicsTextItem *label4 = new QGraphicsTextItem("Contributors :");
    label4->setPos(280, 115);
    label4->setFont(QFont("Arial", 26));
    label4->setDefaultTextColor(Qt::white);
    about_scene->addItem(label4);

    QGraphicsTextItem *label5 = new QGraphicsTextItem("-> Ali Emre PAMUK\n\n"
                                                      "-> Eren ALYÖRÜK\n\n"
                                                      "-> Faruk KAPLAN\n\n"
                                                      "-> Mert ALTEKİN\n\n"
                                                      "-> Şeyma SARCAN");
    label5->setPos(250, 175);
    label5->setFont(QFont("Arial", 22));
    label5->setDefaultTextColor(Qt::white);
    about_scene->addItem(label5);

    // Create the back button
    QPushButton *backButton = new QPushButton("Back");
    backButton->setFixedSize(100, 30);
    backButton->setStyleSheet("background-color: black; color: white;");
    QGraphicsProxyWidget *backButtonProxy = about_scene->addWidget(backButton);
    backButtonProxy->setPos(50, 500);
    connect(backButton, &QPushButton::clicked, this, &Game::returnToMainMenu);

    show();
}

void Game::onButton3Clicked()
{
    // Create the about_scene
    setBackgroundBrush(QBrush(QImage(":/images/ground3.png")));
    about_scene = new QGraphicsScene();
    setScene(about_scene);
    about_scene->setSceneRect(0, 0, 800, 600);
    about_scene->setBackgroundBrush(Qt::white);

    // Create labels
    QGraphicsTextItem *label1 = new QGraphicsTextItem("How To Play");
    label1->setPos(260, 25);
    label1->setFont(QFont("Arial", 32));
    label1->setDefaultTextColor(Qt::white);
    about_scene->addItem(label1);

    QGraphicsTextItem *label2 = new QGraphicsTextItem("-----------------");
    label2->setPos(260, 50);
    label2->setFont(QFont("Arial", 32));
    label2->setDefaultTextColor(Qt::white);
    about_scene->addItem(label2);

    QGraphicsTextItem *label5 =
        new QGraphicsTextItem("-> Press 'Start The Game'.\n\n"
                              "-> First player plays with d-pad.\n\n"
                              "-> Second player plays with 'WASD'.\n\n"
                              "-> First player who eats 6 ghosts\n\n              WINS THE GAME.");
    label5->setPos(175, 200);
    label5->setFont(QFont("Arial", 20));
    label5->setDefaultTextColor(Qt::white);
    about_scene->addItem(label5);

    // Create the back button
    QPushButton *backButton = new QPushButton("Back");
    backButton->setFixedSize(100, 30);
    backButton->setStyleSheet("background-color: black; color: white;");
    QGraphicsProxyWidget *backButtonProxy = about_scene->addWidget(backButton);
    backButtonProxy->setPos(50, 500);
    connect(backButton, &QPushButton::clicked, this, &Game::returnToMainMenu);

    show();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    // Handle key events
    if (player)
    {
        player->keyPressEvent(event);
    }
    if (player2)
    {
        player2->keyPressEvent(event);
    }
}
void Game::returnToMainMenu()
{
    // Delete the about_scene
    QGraphicsScene currentScene = scene();
    setScene(nullptr);

    // Switch back to the main menu scene
    setScene(main_scene);
}
