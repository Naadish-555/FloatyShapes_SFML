#include <fstream>
#include <SFML/Graphics.hpp>
int tmain()
{
    //std::ofstream{ "Hello.txt" };
    //return 0;
    //// Hello.txt has been created here


    

   
    {
        sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
        }

        return 0;
    }
}