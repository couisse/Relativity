#include "photons.hpp"

/* distance between samples */
const double SAMPLE_STEP = 10;
/* thickness of the lines */
const double LINE_THICKNESS = 4;
/* color of the wave */
const sf::Color SIGNAL_COLOR(0xfa, 0xbd, 0x2f);

const double C_2 = C * C;

//photons have no frame of reference
EMWave::EMWave(bool orientation, double altitude, double lambda, double amplitude) :
        DrawableEntity(nullptr), m_orientation(orientation), m_altitude(altitude), m_omega(2 * 3.14159 * C / lambda),
        m_k(3.14159 * 2 / lambda * (orientation ? 1 : -1) ), m_amplitude(amplitude) {}

void EMWave::get_vertices(Position observer, sf::Vector2u screenSize, sf::VertexArray* target){
    //speed and coefficient
    double v = observer.frame->ground_speed();
    double gamma = ReferenceFrame::lorentz(v);
    //the new wave components
    double relativeOmega = gamma * (m_omega - v * m_k);
    double relativeK = gamma * (m_k - v * m_omega / C_2);

    double current = - SAMPLE_STEP + observer.x - screenSize.x * 0.5;
    double end = screenSize.x * 0.5 + observer.x + SAMPLE_STEP;
    double value;
    double first = true;
    double x(0), y(0);
    while (current < end){
        value = m_amplitude * (1 + cos(relativeK * current - relativeOmega * observer.t));
        y = screenSize.y - m_altitude - value; //SFML Reverses the y axis
        x = current - observer.x + screenSize.x * 0.5;
        target->append(sf::Vertex(sf::Vector2f(x, y), SIGNAL_COLOR));
        target->append(sf::Vertex(sf::Vector2f(x, y - SAMPLE_STEP), SIGNAL_COLOR));
        //if not the first time, points have to be added twice for the quads
        if (!first){
            target->append(sf::Vertex(sf::Vector2f(x, y), SIGNAL_COLOR));
            target->append(sf::Vertex(sf::Vector2f(x, y - SAMPLE_STEP), SIGNAL_COLOR));
        }else {first = false;}
        current += SAMPLE_STEP;
    }
    //closing the last quad on itself
    target->append(sf::Vertex(sf::Vector2f(x, y), SIGNAL_COLOR));
    target->append(sf::Vertex(sf::Vector2f(x, y - SAMPLE_STEP), SIGNAL_COLOR));
}
