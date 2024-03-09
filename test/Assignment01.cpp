#include<SFML\Window.hpp>
#include<SFMl\Graphics.hpp>
#include<iostream>
#include<fstream>

class Shapez
{
public:
	std::string m_name = "shape";
	std::string m_text = "text";
	float m_posX = 0;
	float m_posY = 0;
	float m_speedX = 0;
	float m_speedY = 0;
	int R = 0;
	int G = 0;
	int B = 0;
	float m_sizeW = 0;
	float m_sizeH = 0;
	float m_sizeR = 0;
	float m_top, m_bottom, m_left, m_right;
	std::shared_ptr<sf::Shape> shape;
	sf::Text m_label;

	Shapez()
	{}

	Shapez(const std::string &name,const std::string &text, float posX, float posY, float speedX, float speedY, int r, int g, int b, float sizeW, float sizeH)
		: m_name(name)
		, m_posX(posX)
		, m_posY(posY)
		, m_speedX(speedX)
		, m_speedY(speedY)
		, R(r)
		, G(g)
		, B(b)
		, m_sizeW(sizeW)
		, m_sizeH(sizeH)
	{
		shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(m_sizeH, m_sizeW));
		shape->setFillColor(sf::Color(R, G, B));
		shape->setPosition(m_posX, m_posY);
		m_top = shape->getGlobalBounds().width * 0.5f;
		m_left = shape->getGlobalBounds().height * 0.5f;
		
	}


	Shapez(const std::string& name, const std::string& text, float posX, float posY, float speedX, float speedY, int r, int g, int b, float sizeR)
		: m_name(name)
		, m_posX(posX)
		, m_posY(posY)
		, m_speedX(speedX)
		, m_speedY(speedY)
		, R(r)
		, G(g)
		, B(b)
		, m_sizeR(sizeR)
	{
		shape = std::make_shared<sf::CircleShape>(m_sizeR);
		shape->setFillColor(sf::Color(R, G, B));
		shape->setPosition(m_posX, m_posY);
	}
	
};


int main()
{
	std::vector<Shapez> shapeVec;
	std::ifstream fin("configuration.txt");
	std::string input , sText, fFile;
	int fSize;
	int fR, fG, fB;
	unsigned int windowH,windowW;
	float posX,posY;
	float speedX,speedY;
	int r,g,b;
	float sizeW, sizeH, sizeR;
	sf::Font myFont;
	while (fin >> input)
	{
		if (input == "Rectangle" || input == "rectangle")
		{
			fin >> sText >> posX >> posY >> speedX >> speedY >> r >> g >> b >> sizeW >> sizeH;
			Shapez rect(input,sText, posX, posY, speedX, speedY, r, g, b, sizeW, sizeH);
			shapeVec.emplace_back(rect);
		}
		else if (input == "Circle" || input == "circle")
		{
			fin >> sText >> posX >> posY >> speedX >> speedY >> r >> g >> b >> sizeR;
			Shapez circle(input,sText, posX, posY, speedX, speedY, r, g, b, sizeR);
			shapeVec.emplace_back(circle);
		}
		else if (input == "Window" || input == "window")
		{
			fin >> windowH >> windowW;

		}
		else if (input == "font" || input == "Font")
		{
			fin >> fFile >> fSize >> fR >> fG >> fB;
			if (!myFont.loadFromFile(fFile))
			{
				//some error handling
				std::cout << "failed to load tech font from file";
				exit(-1);
			}
		}

		else
		{
			std::cout << "invalid input :" << input << std::endl;
		}
	}

//	std::vector<std::shared_ptr<sf::Shape>> shapes;
	sf::RenderWindow window(sf::VideoMode(windowH, windowW), "Assignment 01");
	window.setFramerateLimit(60);
	std::string lstr = "Rect1";
	sf::RectangleShape rect1(sf::Vector2f(200, 200));
	rect1.setPosition(200, 200);
	rect1.setSize(sf::Vector2f(100, 100));
	rect1.setFillColor(sf::Color::Red);
	
	std::cout << "A :  " << rect1.getGlobalBounds().top << "," << rect1.getGlobalBounds().left << std::endl;
	std::cout << "B : " << rect1.getGlobalBounds().top << "," << rect1.getGlobalBounds().height + rect1.getGlobalBounds().left << std::endl;
	std::cout << "C : " << rect1.getGlobalBounds().top + rect1.getGlobalBounds().width << "," << rect1.getGlobalBounds().height + rect1.getGlobalBounds().left << std::endl;
	std::cout << "D : " << rect1.getGlobalBounds().top + rect1.getGlobalBounds().width << "," << rect1.getGlobalBounds().left << std::endl;


	/*for (auto& shape : shapeVec)
	{
		std::cout << shape.m_name << std::endl;
		if (shape.m_name == "rectangle" || shape.m_name == "Rectangle")
		{
			std::shared_ptr<sf::Shape> rectangle = std::make_shared<sf::RectangleShape>(sf::Vector2f(shape.m_sizeH, shape.m_sizeW));
			rectangle->setFillColor(sf::Color(shape.R, shape.G, shape.B));
			rectangle->setPosition(shape.m_posX, shape.m_posY);
			shapes.emplace_back(rectangle);
		}
		else if (shape.m_name == "circle" || shape.m_name == "Circle")
		{
			std::shared_ptr<sf::Shape> circle = std::make_shared<sf::CircleShape>(shape.m_sizeR);
			circle->setFillColor(sf::Color(shape.R, shape.G, shape.B));
			circle->setPosition(shape.m_posX, shape.m_posY);
			shapes.emplace_back(circle);
		}
	}*/
	/*sf::RectangleShape rect1(sf::Vector2f(Rect1.m_sizeH, Rect1.m_sizeW));
	rect1.setFillColor(sf::Color(Rect1.R, Rect1.G, Rect1.B));
	rect1.setPosition(Rect1.m_posX, Rect1.m_posY);*/

		
	
	while (window.isOpen())
	{
		sf::Event event;
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				std::cout << "Window closed";
				window.close();
			}
		
			if (event.type == sf::Event::KeyPressed)
			{
				std::cout << "Key pressed code = " << event.key.code<<std::endl;
			}
		}

		window.clear();
		rect1.setPosition(rect1.getPosition().x - 0.1f, rect1.getPosition().y - 0.2f);
		
		window.draw(rect1);
		for (auto& s : shapeVec)
		{
			s.shape->setPosition(s.shape->getPosition().x - s.m_speedX, s.shape->getPosition().y - s.m_speedY);
			s.m_label = sf::Text(s.m_text, myFont, fSize);
			s.m_label.setFillColor(sf::Color(fR, fG, fB));
			s.m_label.setPosition(s.shape->getPosition());
			window.draw(*s.shape);
			window.draw(s.m_label);
		}
		//window.draw(rect2);
		window.display();
		//rect1.setPosition(rect1.getPosition().x - Rect1.m_speedX, rect1.getPosition().y - Rect1.m_speedY);
		
	}

	return 0;
}