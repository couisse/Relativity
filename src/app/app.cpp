#include "app.hpp"

#include <vector>

int askInt(int lowest, int highest){
    int respond;
    std::cin >> respond;
    while (lowest > respond || highest < respond){
        std::cout << "Invalid value. Please specify an integer between " << lowest << " and " << highest << " : ";
        std::cin >> respond;
    }
    return respond;
}

double askDouble(double lowest, double highest){
    double respond;
    std::cin >> respond;
    while (lowest > respond || highest < respond){
        std::cout << "Invalid value. Please specify a floating point value between " << lowest << " and " << highest << " : ";
        std::cin >> respond;
    }
    return respond;
}

/* the menu of the application. if returns false, the app should close */
bool menu(){
    std::cout << "\n\nChoose an option\n 1) Frame of reference transfomations\n 2) Exit\n Your choice : ";
    int respond = askInt(1, 2);
    if (respond == 1){
        refEperiment();
        return true;
    }
    return false;
}

/* the frame of reference experiment */
void refEperiment(){
    ///Getting parameters
    std::cout << "In this experiment, you will be able to visualize Lorentz's transformation effects.\n";
    std::cout << "Please specify the number of frame of reference you want to introduce, in addition to the ground one (max 5): ";
    int n = askInt(0, 5);

    std::cout << "Now, for each frame of reference, you will have to specify its speed relative to the ground as a fraction ";
    std::cout << "of c\n(c is intentionally low in this experiment to let you see the effects).\nNegative fraction will result ";
    std::cout << "in the frame to go in the decreasing x way, instead of increasing.\nBoundaries are -0.99 and 0.99\n";
    std::cout << "Note: when done so, the visualization window will pop up. Be careful to continue to read this console";
    std::cout << " important informations might be displayed while performing the experiment\n";

    std::vector<ReferenceFrame> frames;
    std::vector<PeriodicShip> ships;

    //to avoid memory reallocation
    frames.reserve(n + 1);
    ships.reserve(n + 1);

    frames.emplace_back(0);
    ships.emplace_back(&frames[0], 50, 50, 175);

    double speed;
    for (int i = 1; i <= n; ++i){
        std::cout << "Enter speed for the frame " << i << " : ";
        speed = askDouble(-0.99, 0.99);
        frames.emplace_back(speed * C);
        ships.emplace_back(&frames[i], 50 + 100 * i, 50, 175);
    }

    EMWave wave(true, 150 + n * 100 , 100, 50);

    std::cout << "You can now see the frames of reference. Use [left and right click] to cycle ";
    std::cout << "through frames.\nThe sinusoid on top of the screen is a EM wave traveling.";
    std::cout << "You can note that its speed is always, no matter the reference frame\n";
    std::cout << "Press [Escape] to exit" << std::endl;

    sf::Vector2u sizeScreen;
    sizeScreen.x = 800;
    sizeScreen.y = 300  + n * 100;

    sf::RenderWindow window(
        sf::VideoMode(sizeScreen.x, sizeScreen.y, sf::Style::Titlebar | sf::Style::Close),
        "Relativity Illustrated");

    window.setFramerateLimit(60); //limitting the framerate to avoid the window overconsuming

    sf::VertexArray vertices(sf::Quads);

    Position observer(0, 0, &frames[0]);

    int selected = 0;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }else if (event.type == sf::Event::MouseButtonReleased){

                //cycling through frames of reference
                if (event.mouseButton.button == sf::Mouse::Left){
                    selected++;
                    if (selected > n){selected = 0;}
                }else if (event.mouseButton.button == sf::Mouse::Right){
                    if (selected == 0){
                        selected = n;
                    }else {selected--;}
                }

                observer = frames[selected].transfer(observer);
            }else if (event.type == sf::Event::KeyReleased){
                if (event.key.code == sf::Keyboard::Escape){
                    window.close();
                }
            }else if (event.type == sf::Event::Resized){
                window.setSize(sizeScreen); //size is locked
            }
        }

        for (int i = 0; i <= n ; ++i){
            ships[i].get_vertices(observer, sizeScreen, &vertices);
        }
        wave.get_vertices(observer, window.getSize(), &vertices);

        //the ground
        vertices.append(sf::Vertex(sf::Vector2f(0, sizeScreen.y), sf::Color(0x28, 0x28, 0x28)));
        vertices.append(sf::Vertex(sf::Vector2f(sizeScreen.x, sizeScreen.y), sf::Color(0x28, 0x28, 0x28)));
        //top pixels are black to make a little transition
        vertices.append(sf::Vertex(sf::Vector2f(sizeScreen.x, sizeScreen.y - 50), sf::Color::Black));
        vertices.append(sf::Vertex(sf::Vector2f(0, sizeScreen.y - 50), sf::Color::Black));

        window.clear(sf::Color(0x45, 0x85, 0x88));
        window.draw(vertices);
        window.display();

        vertices.clear();

        observer.t += clock.restart().asSeconds();
    }
}
