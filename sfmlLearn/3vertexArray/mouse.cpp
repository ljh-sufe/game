#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "WINDOW_TITLE");
    window.setFramerateLimit(50);
    std::vector<sf::Shape*> shapes;

    sf::RectangleShape *rowcol = new sf::RectangleShape();
    rowcol->setSize(sf::Vector2f(100, 50));
    rowcol->setPosition(0.f, 70.f);
    shapes.push_back(rowcol);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    return 0;
                }
                case sf::Event::MouseButtonPressed:
                {
                    sf::CircleShape *shape = new sf::CircleShape(20);
                    shape->setPosition(event.mouseButton.x,event.mouseButton.y);
                    shape->setFillColor(sf::Color(100, 250, 50));
                    shapes.push_back(shape);
                } 
            }
        }

        window.clear();

        for(auto it=shapes.begin();it!=shapes.end();it++)
        {
            window.draw(**it);
        }
        window.display();
    }

    return 0;
}