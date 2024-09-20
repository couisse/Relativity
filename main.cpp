#include "src/app/app.hpp"

int main()
{
    std::cout << "Greetings!\n" << std::endl;
    //looping the menu until the user is done
    while(menu()){}
    return 0;

    sf::RenderWindow window(sf::VideoMode(800, 500), "Relativity Illustrated");

    ReferenceFrame frames[3] = {ReferenceFrame(0), ReferenceFrame(0.6 * C), ReferenceFrame(-0.6 * C)};
    PeriodicShip ships[3] = {
        PeriodicShip(&frames[0], 50, 50, 175),
        PeriodicShip(&frames[1], 150, 50, 175),
        PeriodicShip(&frames[2], 250, 50, 175)
    };
    EMWave wave(true, 350, 100, 50);

    sf::Clock clock;

    sf::VertexArray vertices(sf::Quads);

    Position observer(0, 0, frames);

    unsigned short selected = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }else if (event.type == sf::Event::MouseButtonPressed){
                selected++;
                if (selected > 2){selected = 0;}
                observer = frames[selected].transfer(observer);
            }
        }

        for (int i = 0; i < 3; ++i){
            ships[i].get_vertices(observer, window.getSize(), &vertices);
        }
        wave.get_vertices(observer, window.getSize(), &vertices);

        window.clear(sf::Color::Blue);
        window.draw(vertices);
        window.display();

        vertices.clear();

        observer.t += clock.restart().asSeconds();
    }

    return 0;
}
