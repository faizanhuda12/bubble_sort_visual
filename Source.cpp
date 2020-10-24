#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Field
{
public:
    // fill 'm_points'
    void fill(const std::size_t number_of_points)
    {
        m_sorted = false;
        //Creating the points
        for (std::size_t i = 0; i < number_of_points; ++i)
        {
            m_points.push_back(i);
        }
        //Shuffling it
        std::random_shuffle(m_points.begin(), m_points.end());
    }

    //bubble sort
    bool sort()
    {
        bool exit = false;
        for (std::size_t o = this->m_points.size() - 1; o > 0; --o)
        {
            for (std::size_t pos = 0; pos < o; ++pos)
            {
                if (this->m_points[pos] < this->m_points[pos + 1])
                {
                    int tmp_pos = this->m_points[pos];
                    this->m_points[pos] = this->m_points[pos + 1];
                    this->m_points[pos + 1] = tmp_pos;
                    exit = true;
                }
            }
            if (exit)
            {
                return m_sorted;
            }
        }
        m_sorted = true;
        return m_sorted;
    }

    //bubble sort
    void show_points(sf::RenderWindow& App)
    {
        sf::CircleShape point;
        point.setRadius(1);
        point.setFillColor(sf::Color::Green);
        for (std::size_t i = 0; i < this->m_points.size(); i++)
        {
            point.setPosition(i, m_points[i]);
            App.draw(point);
        }
    }

private:
    std::vector<int> m_points;
    bool m_sorted;
};

int main()
{
    sf::RenderWindow App;
    sf::Event Event;
    Field fieldContext;
    bool sorting = false;

    App.create(sf::VideoMode(1500, 1500), "Bubble sort");

    //Filling the field
    std::cout << "Filling..." << std::endl;
    fieldContext.fill(1500);

    //Let's start the app
    while (App.isOpen())
    {
        //Verifying events
        while (App.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed)
            {
                App.close();
            }
            //Key pressed
            if (Event.type == sf::Event::KeyPressed)
            {
                switch (Event.key.code)
                {
                case sf::Keyboard::Escape:;
                    App.close();
                    break;;
                case sf::Keyboard::S:;
                    if (!sorting)
                    {
                        std::cout << "Sorting..." << std::endl;
                        sorting = true;
                    }
                    break;
                default:
                    break;
                }
            }
        }

        //Update objects
        if (sorting)
        {
            sorting = !fieldContext.sort();
            if (sorting == false)
            {
                std::cout << "Sorted !" << std::endl;
            }
        }

        //Clearing screen
        App.clear();

        //Dessin du test
        fieldContext.show_points(App);

        //Displaying result
        App.display();
    }

    return EXIT_SUCCESS;
}
