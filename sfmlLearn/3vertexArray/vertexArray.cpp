#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

const int chessboardLineWidth = 5;
const int chessboardSize = 19;
const int plaidLength = 70;
const int windowSize = plaidLength * chessboardSize;
const int pieceRadius = 30;
int chessboardStatus[chessboardSize][chessboardSize];

void printChessBoard(int q[chessboardSize][chessboardSize]){
    for (int i = 0; i<chessboardSize; i++){
        for (int j = 0; j<chessboardSize; j++){
            std::cout << q[j][i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "_________________________________________________________" << std::endl;
}

int main()
{
    for(int i=0; i<chessboardSize; i++){
        for(int j=0; j<chessboardSize; j++){
            chessboardStatus[i][j] = -1;
        }
    }
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "GOBANG");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    std::vector<sf::Shape*> lines;
    std::vector<sf::Shape*> shapes;
    sf::RectangleShape *AvailablePiecePos = new sf::RectangleShape();  // 当前鼠标所对应的坐标
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

                    int plaid_x = round((localPosition.x-pieceRadius)/plaidLength);
                    int pieceLocation_x = plaidLength * (plaid_x + 0.6);
                    int plaid_y = round((localPosition.y-pieceRadius)/plaidLength);
                    int pieceLocation_y = plaidLength * (plaid_y + 0.6);
                    shape->setPosition(pieceLocation_x, pieceLocation_y);

                    shape->setTexture(&texture);
                    if (turn==0){
                        shape->setFillColor(sf::Color(10, 10, 32, 250));
                        chessboardStatus[plaid_x][plaid_y] = 0; //黑棋
                    } else {
                        shape->setFillColor(sf::Color(255, 255, 255, 255));
                        chessboardStatus[plaid_x][plaid_y] = 1; //白棋
                    }
                    shapes.push_back(shape);
                    turn = 1 - turn; // 换边
                    printChessBoard(chessboardStatus);
                }
            }
            if (event.type == sf::Event::MouseButtonReleased){
                if (event.mouseButton.button == sf::Mouse::Left){
                    lock_click = false; //unlock when the button has been released.
                }
            } //Released Scope
            if (event.type == sf::Event::MouseMoved){
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);            
                int plaid_x = round((localPosition.x-pieceRadius)/plaidLength);
                int plaid_y = round((localPosition.y-pieceRadius)/plaidLength);

                AvailablePiecePos->setSize(sf::Vector2f(30, 30));
                int pieceLocation_x = plaidLength * (plaid_x + 0.8);
                int pieceLocation_y = plaidLength * (plaid_y + 0.8);
                AvailablePiecePos->setPosition(pieceLocation_x, pieceLocation_y);
            }
            
        }
        
        
        // window.clear(sf::Color(0,0,255));
        window.clear(sf::Color(255,165,0));

        for(auto it=lines.begin();it!=lines.end();it++){
            window.draw(**it);
        }
    
        for(auto it=shapes.begin();it!=shapes.end();it++){
            window.draw(**it);
        }
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);            
        int plaid_x = round((localPosition.x-pieceRadius)/plaidLength);
        int plaid_y = round((localPosition.y-pieceRadius)/plaidLength);
        if (chessboardStatus[plaid_x][plaid_y] == 0 || chessboardStatus[plaid_x][plaid_y] == 1){
            // 当前位置已经落子了，不显示
            sf::RectangleShape *AvailablePiecePos = new sf::RectangleShape();
        } else{
            window.draw(*AvailablePiecePos);
        }
        
        window.display();
    }
    return 0;
}