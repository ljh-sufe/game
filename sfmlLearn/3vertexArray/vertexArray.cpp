#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

int chessboardLineWidth = 5;
int chessboardSize = 19;
int plaidLength = 70;
int windowSize = plaidLength * chessboardSize;
int pieceRadius = 30;


int main()
{
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "GOBANG");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    std::vector<sf::Shape*> lines;
    std::vector<sf::Shape*> shapes;
    static bool lock_click=false;
    int turn = 0; //0 stands for black and 1 stands for white

    sf::Texture texture;
    texture.loadFromFile("/Users/junhao/git_clone/game/sfmlLearn/3vertexArray/lighttexture.jpg");


    for (int i = 1; i <= 18; i++) {
        float row = plaidLength*i;
        sf::RectangleShape *rowline = new sf::RectangleShape();
        rowline->setSize(sf::Vector2f(windowSize, chessboardLineWidth));
        rowline->setPosition(0.f, row);
        lines.push_back(rowline);

        sf::RectangleShape *colline = new sf::RectangleShape();
        colline->setSize(sf::Vector2f(chessboardLineWidth, windowSize));
        colline->setPosition(row, 0.f);
        lines.push_back(colline);
    }

    // run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                std::cout << "game ended!";
                 window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left && lock_click != true){
                    lock_click = true;
                    // left mouse button is pressed:
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);            
                    sf::CircleShape *shape = new sf::CircleShape(pieceRadius);
                    int pieceLocation_x = round((localPosition.x-pieceRadius)/plaidLength);
                    pieceLocation_x = plaidLength * (pieceLocation_x + 0.6);
                    int pieceLocation_y = round((localPosition.y-pieceRadius)/plaidLength);
                    pieceLocation_y = plaidLength * (pieceLocation_y + 0.6);
                    shape->setPosition(pieceLocation_x, pieceLocation_y);
                    shape->setTexture(&texture);
                    if (turn==0){
                        shape->setFillColor(sf::Color(10, 10, 32, 250));
                    } else {
                        shape->setFillColor(sf::Color(255, 255, 255, 255));
                    }
                    
                    shapes.push_back(shape);
                    turn = 1 - turn;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased){
                    if (event.mouseButton.button == sf::Mouse::Left){
                        lock_click = false; //unlock when the button has been released.
                    }
                } //Released Scope
        }

        // window.clear(sf::Color(0,0,255));
        window.clear(sf::Color(255,165,0));

        for(auto it=lines.begin();it!=lines.end();it++){
            window.draw(**it);
        }
    
        for(auto it=shapes.begin();it!=shapes.end();it++){
            window.draw(**it);
        }
        window.display();
    }

    return 0;
}