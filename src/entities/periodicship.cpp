#ifndef PERIODICSHIP_CPP_INCLUDED
#define PERIODICSHIP_CPP_INCLUDED

#include <cmath>
#include <iostream>
#include "periodicship.hpp"

PeriodicShip::PeriodicShip(ReferenceFrame *frame, double altitude, double size, double period)
    : DrawableEntity(frame), m_altitude(altitude), m_size(size), m_period(period) {
}

void PeriodicShip::get_vertices(Position observer, sf::Vector2u screenSize, sf::VertexArray* target){

    //the position of the observer in entity's frame (is used to determinate an origin to the drawings)
    Position relative_observer = m_frame->transfer(observer);
    //relative speed and coefficient for all length contractions
    double v = observer.frame->relative_speed(*m_frame);
    double gamma = ReferenceFrame::lorentz(v);

    //the number of the closest spaceship to the observer in the entity's frame
    int n = relative_observer.x / m_period;

    //now generating visible ships
    //calculating the number of ships to draw to the right, adjusted to the worst case to cover the borders
    int count = screenSize.x * 0.5 * gamma / m_period + 2;
    Coords observed;
    for (int i = 0; i < count; ++i){
        //right ships
        observed = observer.frame->observe(*m_frame, Coords((n + i) * m_period, observer.t));
        this->addShip(observed, gamma, target, screenSize.y, 0.5 * screenSize.x - observer.x);
        //left ships
        observed = observer.frame->observe(*m_frame, Coords((n - i - 1) * m_period, observer.t));
        this->addShip(observed, gamma, target, screenSize.y, 0.5 * screenSize.x - observer.x);
    }

}

void PeriodicShip::addShip(Coords settings, double gamma, sf::VertexArray* target, double y_offset, double x_offset){
    //the origin of the ship
    double origin = settings.x + x_offset;
    //getting the positions of the two edges of the ship
    double lx = origin - 0.5 * m_size / gamma;
    double rx = origin + 0.5 * m_size / gamma;
    //SFML reverses the y scale
    double y = y_offset - m_altitude;
    //the color factor for the blinking
    double color_factor = 0.5 * (1 + sin(settings.t * 2 * 3.14159)); //pulsating at 1Hz
    sf::Color color(255 * color_factor, 0, 0);
    //adding the ship
    //first the frame
    target->append(sf::Vertex(sf::Vector2f(lx, y), sf::Color::Black));
    target->append(sf::Vertex(sf::Vector2f(lx, y - m_size), sf::Color::Black));
    target->append(sf::Vertex(sf::Vector2f(rx, y - m_size), sf::Color::Black));
    target->append(sf::Vertex(sf::Vector2f(rx, y), sf::Color::Black));
    //then the light diamond
    target->append(sf::Vertex(sf::Vector2f(origin, y - 0.25 * m_size)               , color));
    target->append(sf::Vertex(sf::Vector2f(0.5 * (lx + origin), y - 0.5 * m_size)   , color));
    target->append(sf::Vertex(sf::Vector2f(origin, y - 0.75 * m_size)               , color));
    target->append(sf::Vertex(sf::Vector2f(0.5 * (rx + origin), y - 0.5 * m_size)   , color));
}

#endif // PERIODICSHIP_CPP_INCLUDED
