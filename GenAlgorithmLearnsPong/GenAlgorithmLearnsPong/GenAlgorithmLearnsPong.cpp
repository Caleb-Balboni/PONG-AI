#include <iostream>
#include <SFML/graphics.hpp>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <windows.h>
#include <thread>
#include <vector>
bool longbeep = false;
bool shortbeep = false;
int random_num(int start, int end)
{
    int range = (end - start) + 1;
    int random_int = start + (rand() % range);
    return random_int;
}
struct setup
{
    int distance[2];
    int speed[10];
};
struct Node
{
    int fitnessval = 0;
    std::vector<setup> decestions;
    Node()
    {
        for (int y = -200; y < 200; y++)
           {
              for (int x = 0; x < 200; x++)
                {
                  setup Nsetup;
                  Nsetup.distance[0] = x;
                  Nsetup.distance[1] = y;
                  for (int s = 0; s < 10; s++)
                  {
                      Nsetup.speed[s] = random_num(0, 1);
                  }
                  decestions.push_back(Nsetup);
                }
            }
    }
    
};
void makebeep()
{
    while (true)
    {
        if (shortbeep)
        {
            Beep(500, 150);
            shortbeep = false;
        }
        else if (longbeep)
        {
            Beep(300, 300);
            longbeep = false;
        }
    }
}
Node Mate(Node father, Node mother)
{
    Node Child;
    for (int i = 0; i < father.decestions.size() - 1; i++)
    {

            float p = random_num(0, 100);
            p = p / 100;
            if (p < 0.45)
            {
                for (int s = 0; s < 10; s++)
                {
                    Child.decestions[i].speed[s] = mother.decestions[i].speed[s];
                }

            }
            else if (p < 0.95)
            {

                for (int s = 0; s < 10; s++)
                {
                Child.decestions[i].speed[s] = father.decestions[i].speed[s];

                }
            }
            else
            {
                for (int s = 0; s < 10; s++)
                {
                    Child.decestions[i].speed[s] = random_num(0, 1);
                }
            }
        
    }

    return Child;
}
struct rectangle
{
    sf::RectangleShape rec;
    int recypos;
    bool dead = false;
};
int main()
{
    float ballspeed = 1.2;
    int curspeed = 1;
    Node Nodearr[10];
    int generation = 0;
    int highestfitness = 1;
    for (int i = 0; i < 10; i++)
    {
        Node generatednode;
        Nodearr[i] = generatednode;
    }

    std::cout << "pong!\n";
    sf::RenderWindow window(sf::VideoMode(200, 200), "PONG", sf::Style::Close | sf::Style::Resize);
    sf::err().rdbuf(NULL);
    int score = 0;
    window.setFramerateLimit(240);
    std::vector <rectangle> recright;
    for (int i = 0; i < 10; i++)
    {
        rectangle Nrec;
        Nrec.rec.setSize(sf::Vector2f(20, 70));
        switch (i)
        {
        case 0:
            
            Nrec.rec.setFillColor(sf::Color(255, 0, 0));
            break;
        case 1:
        
            Nrec.rec.setFillColor(sf::Color(0, 255, 0));
            break;
        case 2:
        
            Nrec.rec.setFillColor(sf::Color(0, 0, 255));
            break;
        case 3:
        
            Nrec.rec.setFillColor(sf::Color(255, 0, 255));
            break;
        case 4:
        
            Nrec.rec.setFillColor(sf::Color(255, 255, 0));
            break;
        case 5:
        
            Nrec.rec.setFillColor(sf::Color(255, 255, 255));
            break;
        case 6:
        
            Nrec.rec.setFillColor(sf::Color(35, 0, 255));
            break;
        case 7:
        
            Nrec.rec.setFillColor(sf::Color(255, 100, 0));
            break;
        case 8:
        
            Nrec.rec.setFillColor(sf::Color(0, 240, 255));
        break;
        case 9:

            Nrec.rec.setFillColor(sf::Color(170, 0, 255));
            break;
        }
        Nrec.recypos = 100;
        recright.push_back(Nrec);
    }
    sf::CircleShape ball;
    ball.setRadius(10);
    ball.setOrigin(10, 10);
    int ballposX = window.getSize().x / 2.f;
    int ballposY = window.getSize().y / 2.f;
    ball.setPosition(ballposX, ballposY);
    //ball random start posiion
    srand((unsigned)time(0));
    float xoffset = -1;
    float yoffset = 2;
    //create gamename and font
    sf::Font font;
    if (!font.loadFromFile("font.ttf"))
    {
        std::cout << "could not load file!" << std::endl;
        return 0;
    }
    sf::Text gamename;
    gamename.setFont(font);
    gamename.setString("PONG");
    gamename.setScale(.5, .5);
    gamename.setPosition(70, 10);
    // finish section
    //create score
    sf::Text scoreone;
    scoreone.setFont(font);
    scoreone.setPosition(10, 10);
    sf::Text scoretwo;
    scoretwo.setFont(font);
    scoretwo.setPosition(10, 10);
    scoretwo.setScale(.5, .5);
    //speed
    sf::Text ballspeedX;
    ballspeedX.setFont(font);
    ballspeedX.setCharacterSize(7);
    ballspeedX.setPosition(150, 10);
    std::thread dobeep(&makebeep);
    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == evnt.Closed)
            {
                window.close();
            }
        }
            bool hit = false;
            while (true)
            {
                 sf::Event evnt;
            while (window.pollEvent(evnt))
            {
                if (evnt.type == evnt.Closed)
                {
                    window.close();
                }
            }
            window.clear(sf::Color::Black);
                for (int r = 0; r < 10; r++)
                {
                    if (!recright[r].dead)
                    {
                        if (recright[r].recypos >= 0 && recright[r].recypos <= 200)
                        {
                            int size = Nodearr[r].decestions.size();
                            for (int x = 0; x < Nodearr[r].decestions.size(); x++)
                            {
                                int xdistance = 195 - ball.getPosition().x;
                                int ydistance = recright[r].recypos - ball.getPosition().y;
                                int xpredict = Nodearr[r].decestions[x].distance[0];
                                int ypredict = Nodearr[r].decestions[x].distance[1];
                                if ((xpredict == xdistance) && (ypredict == ydistance))
                                {
                                    if (Nodearr[r].decestions[x].speed[curspeed] == 0)
                                        recright[r].recypos += -4;
                                    else
                                        recright[r].recypos += 4;

                                }
                            }
                        }
                        while (recright[r].recypos < 0)
                        {
                            recright[r].recypos++;
                        }
                        while (recright[r].recypos > 200)
                        {
                            recright[r].recypos--;
                        }
                        if (ball.getPosition().x > 190)
                        {
                            if (ball.getGlobalBounds().intersects(recright[r].rec.getGlobalBounds()))
                            {
                                Nodearr[r].fitnessval++;
                                hit = true;
                            }
                            else
                            {
                                recright[r].dead = true;
                            }
                        }
                        recright[r].rec.setPosition(195, recright[r].recypos);
                    }
                }
                if (hit)
                {
                    xoffset = -xoffset;
                    yoffset = -yoffset;
                    if (curspeed < 9)
                    {
                        curspeed ++;
                    }
                    hit = false;
                }
                else if (ball.getPosition().x >= 210)
                    break;
                if (ball.getPosition().x <= 0)
                {
                    //  ball.setPosition(ballposX, ballposY);
                    xoffset = -xoffset;
                }
                if (ball.getPosition().y < 0)
                {
                    yoffset = -yoffset;
                }
                else if (ball.getPosition().y > 200)
                {
                    yoffset = -yoffset;
                }
                scoretwo.setString(std::to_string(score));
                std::string speedball = std::to_string(curspeed);
                std::string newballstring;
                for (int i = 0; i < speedball.size(); i++)
                {
                    if (speedball[i] != '0')
                    {
                        newballstring += speedball[i];
                    }
                }
                std::string speed = "Speed: " + newballstring;
                ballspeedX.setString(speed);
                ball.move(xoffset * curspeed, yoffset * curspeed);
                for (int i = 0; i < 10; i++)
                {
                    if (!recright[i].dead)
                    {
                        window.draw(recright[i].rec);
                    }
                }
                //std::cout << "y pos left: " << reclefty << std::endl;
                //std::cout << "y pos right: " << recrighty << std::endl;
                window.draw(ball);
                window.draw(gamename);
                window.draw(scoreone);
                window.draw(scoretwo);
                window.draw(ballspeedX);
                window.display();
            }
        generation++;
        Node NewNodearr[10];
        int i, j;
        for (i = 0; i < 10 - 1; i++)
        {
            for (j = 0; j < 10 - i - 1; j++)
                if (Nodearr[j].fitnessval <= Nodearr[j + 1].fitnessval)
                {
                    Node save = Nodearr[j];
                    Nodearr[j] = Nodearr[j + 1];
                    Nodearr[j + 1] = save;
                }
        }
        for (int i = 0; i < 3; i++)
        {
            NewNodearr[i] = Nodearr[i];
        }
        for (int i = 3; i < 10; i++)
        {
            int r = random_num(0, 4);
            Node parent1 = Nodearr[r];
            r = random_num(0, 4);
            Node parent2 = Nodearr[r];
            Node offspring = Mate(parent1, parent2);
            NewNodearr[i] = offspring;
        }
        highestfitness = Nodearr[0].fitnessval;
        for (int i = 0; i < 10; i++)
        {
            Nodearr[i] = NewNodearr[i];
            Nodearr[i].fitnessval = 0;
        }
        std::cout << "current generation: " << generation << " greatest fitness: " << highestfitness;
        std::cout << std::endl;
        curspeed = 1;
        for (int i = 0; i < 10; i++)
        {
            recright[i].dead = false;
            recright[i].recypos = 100;
        }
        ball.setPosition(ballposX, ballposY);
        xoffset = -1;
        yoffset = 2;
    }
    /*
    while (window.isOpen())
    {
        //ball movment
        std::cout << "pong has been sucessfully learned! here is the result-" << std::endl;
        curspeed = 1;
        recrighty = 100;
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == evnt.Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        while (true)
        {
            sf::Event evnt;
            while (window.pollEvent(evnt))
            {
                if (evnt.type == evnt.Closed)
                {
                    window.close();
                }
            }
            window.clear(sf::Color::Black);
            if (recrighty >= 0 && recrighty <= 200)
            {
                int size = Nodearr[0].decestions.size();
                for (int x = 0; x < Nodearr[0].decestions.size(); x++)
                {
                    int xdistance = 195 - ball.getPosition().x;
                    int ydistance = recrighty - ball.getPosition().y;
                    int xpredict = Nodearr[0].decestions[x].distance[0];
                    int ypredict = Nodearr[0].decestions[x].distance[1];
                    if ((xpredict == xdistance) && (ypredict == ydistance))
                    {
                        if (Nodearr[0].decestions[x].speed[curspeed] == 0)
                            recrighty += -4;
                        else
                            recrighty += 4;

                    }
                }
            }
            while (recrighty < 0)
            {
                recrighty++;
            }
            while (recrighty > 175)
            {
                recrighty--;
            }

            if (ball.getPosition().x <= -0)
            {
                //  ball.setPosition(ballposX, ballposY);
                xoffset = -xoffset;
            }
            else if (ball.getPosition().x >= 205)
            {
                ball.setPosition(ballposX, ballposY);
                xoffset = -1;
                yoffset = 2;
                recrighty = 100;
                score = 0;
                break;
            }
            if (ball.getPosition().y < 0)
            {
                yoffset = -yoffset;
            }
            else if (ball.getPosition().y > 200)
            {
                yoffset = -yoffset;
            }

            if (ball.getPosition().x > 190 && ball.getPosition().y >= recright.getPosition().y && ball.getPosition().y <= recright.getPosition().y + 55)
            {
                xoffset = -xoffset;
                yoffset = -yoffset;
                score++;
                if (curspeed < 10)
                {
                    curspeed++;
                }
            }
            scoretwo.setString(std::to_string(score));
            std::string speedball = std::to_string(curspeed);
            std::string newballstring;
            for (int i = 0; i < speedball.size(); i++)
            {
                if (speedball[i] != '0')
                {
                    newballstring += speedball[i];
                }
            }
            std::string speed = "Speed: " + newballstring;
            ballspeedX.setString(speed);
            ball.move(xoffset * curspeed, yoffset * curspeed);
            //std::cout << "y pos left: " << reclefty << std::endl;
            //std::cout << "y pos right: " << recrighty << std::endl;
            recright.setPosition(195, recrighty);
            window.draw(recright);
            window.draw(ball);
            window.draw(gamename);
            window.draw(scoreone);
            window.draw(scoretwo);
            window.draw(ballspeedX);
            window.display();
        }
    }
    */
}
