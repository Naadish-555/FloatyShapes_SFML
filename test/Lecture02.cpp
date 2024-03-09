#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<vector>
#include<fstream>



class Student
{
    std::string m_first = "first";
    std::string m_last = "last";
    int m_id = 0;
    float m_avg = 0;

public:
    Student() { }
    
    Student(std::string first, std::string last, int id, float avg)
        : m_first(first)
        , m_last(last)
        , m_id(id)
        , m_avg(avg)
    {
    }

    int getAvg() const
    {
        return m_avg;
    }

    int getID() const
    {
        return m_id;
    }

    std::string getFirst() const
    {
        return m_first;
    }

    std::string getLast() const
    {
        return m_last;
    }

    void print() const
    {
        std::cout << m_first << "  " << m_last << "  ";
        std::cout << m_id << "  " << m_avg<<std::endl;
    }
    
};

class Course
{
    std::string m_name = "Course";
    std::vector<Student> m_students;

public:
    Course() {}

    Course(const std::string& name)
        : m_name(name)
    {
    }

    void addStudent(const Student& s)
    {
        m_students.emplace_back(s);
    }

    const std::vector<Student>& getStudents() const
    {
        return m_students;
    }

    void loadFromFile(const std::string& filename)
    {
        std::ifstream fin(filename);
        std::string first;
        std::string last;
        int id;
        float avg;
        while (fin >> first)
        {
            fin >> last >> id >> avg;
            addStudent(Student(first, last, id, avg));
            /*fin >> id;
            fin >> avg;*/
        }
    }

    void print() const
    {
        for (const auto& s : m_students)
        {
            s.print();
        }
    }
};

int A2main()
{
    /*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
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

    return 0;*/

   

   /* Student s1;
    Student s2("Nandish", "Mittal", 1, 35);
    Student s3("Divy", "Puranik", 1002, 69);

    Course comp4300("COMP 4300");
    comp4300.addStudent(s2);
    comp4300.addStudent(s3);

    comp4300.print();*/
    
    Course c("Comp 4300");
    c.loadFromFile("students.txt");
    c.print();
    return 0;
}