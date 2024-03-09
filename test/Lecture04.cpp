#include<iostream>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<memory>//for smart pointers

//can make class for storing all shapes from the file;
//class Ashape
//{
//public:
//    sf::CircleShape circle;
//    sf::RectangleShape rects;
//    float speedx;
//    float speedy;
//};



int L4main()
{
     //creating a new window of size w*h pixels
     // top left of the window is(0,0) and bottom right is (w,h)
    const int wWidth = 480;
    const int wHeight = 720;
    sf::RenderWindow window(sf::VideoMode(wHeight,wWidth), "Lecture 04");
    window.setFramerateLimit(60); //limits the fps

    int r = 0;
    int g = 255;
    int b = 255;
    //lets make a shape that will draw to the screen
    sf::CircleShape circle(50); //create a circle shape with radius 50
    circle.setFillColor(sf::Color(r, g, b));
    circle.setPosition(300.0f, 300.0f);
    float circleMoveSpeed = 0.4f;

    float rx = 300;
    float ry = 200;
    sf::Vector2f rSize(rx, ry);
    sf::RectangleShape rectangle(rSize);
    rectangle.setPosition(100, 5);
    rectangle.setFillColor(sf::Color::Yellow);
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(20);



    sf::RectangleShape rectangle2(rSize);
    rectangle2.setPosition(200, 250);
    rectangle2.setFillColor(sf::Color::Red);


    //lets load a font so we can display a font
    sf::Font myFont;


    //attempt to load font from file
    if (!myFont.loadFromFile("tech.ttf"))
    {
        //some error handling
        std::cout << "failed to load tech font from file";
        exit(-1);
    }

    //set up text object that will be drawn to the screen
    sf::Text text("Sample text", myFont, 24);
    text.setPosition(0,wWidth - (float)text.getCharacterSize());
    text.setFillColor(sf::Color::Red);


    //for rendering multiple shapes by taking input from the notepad file 

    //first way
    std::vector<sf::CircleShape> circles;
    circles.emplace_back(circle);    
    std::vector<sf::RectangleShape> rectangles;
    rectangles.emplace_back(rectangle);
    rectangles.emplace_back(rectangle2);

    std::vector<std::shared_ptr<sf::Shape>> shapes;
    std::shared_ptr<sf::Shape> circlez = std::make_shared<sf::CircleShape>(20);
    shapes.emplace_back(circlez);

    std::shared_ptr<sf::Shape> rectz = std::make_shared<sf::RectangleShape>(sf::Vector2f(40,40));
    rectz->setPosition(300, 400);
    shapes.emplace_back(rectz);




   while (window.isOpen())
   {
      
       sf::Event event;
       if (window.pollEvent(event))
       {
           if (event.type == sf::Event::Closed)
           {
               std::cout << "window closed";
               window.close();
           }

           //if event is triggered when a key is pressed
           if (event.type == sf::Event::KeyPressed)
           {

               //print the key that was pressed to the console
               std::cout << "key pressed with the code = " << event.key.code << std::endl;

               if (event.key.code == sf::Keyboard::X)
               {
                   //reverses the direction of the circle on the screen
                   circleMoveSpeed *= -1.0f;
               }

           }
       }



       //basic rendering calls
       //basic animation - move each frame if it's still in the frame
       circle.setPosition(circle.getPosition().x - circleMoveSpeed, circle.getPosition().y - 
circleMoveSpeed);
       window.clear();
   /*    window.draw(circle);
       window.draw(rectangle);*/
      

       //for drawing multiplle shapes with 2 different vectors
      /* for (auto& c : circles)
       {
           window.draw(c);
       }
       for (auto& r : rectangles)
       {
           window.draw(r);
       }*/


      //for matrix shaped color rendering
      for (int i = 0; i < 25; i++)
       {
           for (int j = 0; j < 15; j++)
           {
               sf::Vector2f rSizes(15, 15);
               sf::RectangleShape rectanglez(rSizes);
               rectanglez.setPosition(i*20, j*20);
               rectanglez.setFillColor(sf::Color(i*10,j*10,0));
               window.draw(rectanglez);
              
           }
       }

       /*for (auto& shape : shapes)
       {
           window.draw(*shape);
       }*/
       //window.draw(circle);
       window.draw(text);
       window.display();
     
   }
   
}