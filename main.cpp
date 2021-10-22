#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

Font font;

class Game
{
public:
            Game();
    void    run();
private:
    void    processEvents();
    void    update(Time);
    void    render();
    void    handlePlayerInput(Keyboard::Key, bool);
private:

    RenderWindow    Window;
    Time            timePerFrame;
    int c;
    bool IsNextRed;
    bool IsPress;
    vector<vector<int>> Field;

    bool IsMovingRight;
    bool IsMovingLeft;

    int framesSinceUpdate;
    int WaitFrames;

    Text text;

    vector<vector<CircleShape>> Circles;

    int PlayerWin;
};

Game::Game()
:Window(VideoMode(800,600),"TIC-TAC-TOE")
{
    timePerFrame = seconds(1.f / 60.f);

    c = 3;
    IsNextRed = 1;
    IsPress = 0;

    Field.resize(7);
    for (int i=0; i<7; i++) Field[i].resize(6);

     for (int i=0; i<7; i++)
     for (int j=0; j<6; j++)
       {
           Field[i][j] = 0;
       }

    Circles.resize(7);
    for (int i=0; i<7; i++) Circles[i].resize(6);

    for (int i=0; i<7; i++)
        for (int j=0; j<6; j++)
        {
            Circles[i][j].setRadius(37.5);
            //Подправить позиции
            Circles[i][j].setPosition(Vector2f(107.5 + 85*i, 85 + 85 *j));
            Circles[i][j].setFillColor(Color::Black);
        }

     framesSinceUpdate = 0;
     WaitFrames = 5;

     PlayerWin = 0;
     text.setFont(font);
     text.setFillColor(Color::White);
     text.setString("");
}

void Game::run()
{
    Clock clock;
    Time timeSinceLastUpdate = Time::Zero;

    while (Window.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            processEvents();
            update(timePerFrame);
        }
        render();
    }
}

void Game::processEvents()
{
    Event event;
    while (Window.pollEvent(event))

        switch (event.type) {
            case Event::Closed: {
                Window.close();
                break;
            }
            case Event::KeyPressed: {
                handlePlayerInput(event.key.code, 1);
                break;
            }
            case Event::KeyReleased: {
                handlePlayerInput(event.key.code, 0);
                break;
            }
    }
}

void Game::update(Time timePerFrame)
{
    for (int i=0; i<7; i++)
        for (int j=0; j<6; j++)
        {
            Circles[i][j].setFillColor(Color::Black);
        }

    framesSinceUpdate++;
    if (framesSinceUpdate > WaitFrames) {
    if (IsMovingLeft  && c > 0) {c--;}
    if (IsMovingRight && c < 6) {c++;}
    framesSinceUpdate = 0;
    }

    if (IsPress && PlayerWin == 0)
    {
        if (Field[c][0] == 0 && IsNextRed == 1) {
            // Ставим кружок
            for (int i = 5; i > -1; i--)
                if (Field[c][i] == 0) {
                    Field[c][i] = 1;
                    break;
                }
            IsNextRed = 0; }
        else {
        if (Field[c][0] == 0 && IsNextRed == 0) {
            // Ставим кружок
            for (int i = 5; i > -1; i--) {
                if (Field[c][i] == 0) {
                    Field[c][i] = 2;
                    break;
                }
            }
            IsNextRed = 1;}
        }
        IsPress = 0;
    }

    if (PlayerWin == 0) {
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 3; j++) {

                bool w1 = 0;
                for (int l = 0; l < 4; l++)
                    if (Field[i][j+l] != 1) { w1 = 1; }
                if (w1 == 0) {PlayerWin = 1;}

                bool w2 = 0;
                for (int l = 0; l < 4; l++)
                    if (Field[i][j+l] != 2) { w2 = 1; }
                if (w2 == 0) {PlayerWin = 2;}
            }

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 7; j++) {

                bool w1 = 0;
                for (int l = 0; l < 4; l++)
                    if (Field[i+l][j] != 1) { w1 = 1; }
                if (w1 == 0) {PlayerWin = 1;}

                bool w2 = 0;
                for (int l = 0; l < 4; l++)
                    if (Field[i+l][j] != 2) { w2 = 1; }
                if (w2 == 0) {PlayerWin = 2;}
            }

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++) {

                bool w1 = 0;
                for (int l = 0; l < 4; l++)
                    if (Field[i+l][j+l] != 1) { w1 = 1; }
                if (w1 == 0) {PlayerWin = 1;}

                bool w2 = 0;
                for (int l = 0; l < 4; l++)
                    if (Field[i+l][j+l] != 2) { w2 = 1; }
                if (w2 == 0) {PlayerWin = 2;}
            }

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++) {

                bool w1 = 0;
                for (int l = 0; l < 4; l++)
                    if (Field[5 - (i+l)][(j+l)] != 1) { w1 = 1; }
                if (w1 == 0) {PlayerWin = 1;}

                bool w2 = 0;
                for (int l = 0; l < 4; l++)
                    if (Field[5 - (i+l)][(j+l)] != 2) { w2 = 1; }
                if (w2 == 0) {PlayerWin = 2;}
            }
    }

    for (int i=0; i<7; i++)
        for (int j=0; j<6; j++)
        {
            if (Field[i][j] == 1) Circles[i][j].setFillColor(Color::Red);
            if (Field[i][j] == 2) Circles[i][j].setFillColor(Color::Yellow);
        }

    //Проверка на 4 в ряд
}

void Game::render()
{
    Window.clear();
    //Рисуем поле и т.п.
    RectangleShape rectangle;
    rectangle.setPosition(102.5,80);
    rectangle.setSize(Vector2f(85.f*7.f , 600.f - 80.f));
    rectangle.setFillColor({63,63,63,255});
    Window.draw(rectangle);

    RectangleShape rectangle1;
    rectangle1.setPosition(102.5 + c * 85 ,80);
    rectangle1.setSize(Vector2f(85 , 600.f - 80.f));
    rectangle1.setFillColor({95,95,95,255});
    Window.draw(rectangle1);

    for (int i=0; i<7; i++)
        for (int j=0; j<6; j++)
        {
            Window.draw(Circles[i][j]);
        }
    //Выводим то, выирграл ли какой-то игрок
    if (PlayerWin != 0)
    {
        RectangleShape Shade;
        Shade.setSize(Vector2f(800 , 600));
        Shade.setPosition(0,0);
        Shade.setFillColor({0, 0, 0, 127});
        Window.draw(Shade);
    }

    if (PlayerWin == 1)
    {
        text.setFillColor({255, 63, 63, 255});
        text.setString("RED WON!");
        text.setPosition(400 - text.getLocalBounds().width/2, 300 - text.getLocalBounds().height/2);
        Window.draw(text);
    }

    if (PlayerWin == 2)
    {
        text.setFillColor({255, 255, 63, 255});
        text.setString("YELLOW WON!");
        text.setPosition(400 - text.getLocalBounds().width/2, 300 - text.getLocalBounds().height/2);
        Window.draw(text);
    }

    Window.display();
}

void Game::handlePlayerInput(Keyboard::Key key, bool IsPressed)
{
    switch (key)
    {
        case Keyboard::Key::Left: {
            IsMovingLeft = IsPressed;
            break;
        }
        case Keyboard::Key::Right: {
            IsMovingRight = IsPressed;
            break;
        }
        case Keyboard::Key::Enter: {
            IsPress = IsPressed;
            break;
        }
    }
}

int main()
{
    if (!font.loadFromFile("../ArialBlack.ttf")) {cout << "Can't load font.\n";}
    Game game;
    game.run();
    return 0;
}