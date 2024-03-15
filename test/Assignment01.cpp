#include<SFML\Window.hpp>
#include<SFMl\Graphics.hpp>
#include<iostream>
#include<fstream>
#include<cmath>

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
		, m_text(text)
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
		, m_text(text)
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

void CheckCollision(Shapez &s, unsigned int wW , unsigned int wH)
{
	if (s.shape->getGlobalBounds().top <= 0 || s.shape->getGlobalBounds().top + s.shape->getGlobalBounds().height >= wW)
	{
		s.m_speedY = -(s.m_speedY);
		//std::cout << s.m_name << ":" << s.m_speedX << "," << s.m_speedY;
	}
	if (s.shape->getGlobalBounds().left <= 0 || s.shape->getGlobalBounds().left + s.shape->getGlobalBounds().width >= wH)
	{
		s.m_speedX = -(s.m_speedX);
		//std::cout << s.m_name<<":" << s.m_speedX << "," << s.m_speedY;
	}
}

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
	if (fin.is_open()) 
	{
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
		sf::RenderWindow window(sf::VideoMode(windowW, windowH), "Assignment 01");
		window.setFramerateLimit(60);
		std::string lstr = "Rect1";
		/*sf::RectangleShape rect1(sf::Vector2f(200, 200));
		rect1.setPosition(200, 200);
		rect1.setSize(sf::Vector2f(100, 100));
		rect1.setFillColor(sf::Color::Red);
	
		std::cout << "A :  " << rect1.getGlobalBounds().top << "," << rect1.getGlobalBounds().left << std::endl;
		std::cout << "B : " << rect1.getGlobalBounds().top << "," << rect1.getGlobalBounds().height + rect1.getGlobalBounds().left << std::endl;
		std::cout << "C : " << rect1.getGlobalBounds().top + rect1.getGlobalBounds().width << "," << rect1.getGlobalBounds().height + rect1.getGlobalBounds().left << std::endl;
		std::cout << "D : " << rect1.getGlobalBounds().top + rect1.getGlobalBounds().width << "," << rect1.getGlobalBounds().left << std::endl;*/

	
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
			//rect1.setPosition(rect1.getPosition().x - 0.1f, rect1.getPosition().y - 0.2f);
			//window.draw(rect1);
		
			for (auto& s : shapeVec)
			{
				CheckCollision(s,windowH, windowW);
				s.shape->setPosition(s.shape->getPosition().x - s.m_speedX, s.shape->getPosition().y - s.m_speedY);
				s.m_label = sf::Text(s.m_text, myFont, fSize);
				s.m_label.setFillColor(sf::Color(fR, fG, fB));

				//for centralized text
				auto center = s.m_label.getGlobalBounds().getSize() / 2.f;
				auto localBounds = center + s.m_label.getLocalBounds().getPosition();
				s.m_label.setOrigin(localBounds);
				s.shape->setOrigin(s.shape->getGlobalBounds().getSize() / 2.f);
				s.m_label.setPosition(s.shape->getPosition());
				

				window.draw(*s.shape);
				window.draw(s.m_label);
			}
			window.display();
		
		}
		return 0;

	}
	else
	{
		std::cout << "File not opened";
		std::cin.get();
		return -1;
	}
}