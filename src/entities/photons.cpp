#include <cmath>
#include "photons.hpp"

/* distance between samples */
const double MAX_SAMPLE_STEP = 10;
/* thickness of the lines */
const float LINE_THICKNESS = 4;
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

    double incr = 1/relativeK * 0.1; //about 60 sample per wavelength
    if (MAX_SAMPLE_STEP < incr){ //hard upper limit to the size of sample step
        incr = MAX_SAMPLE_STEP;
    }

    double current = - incr + observer.x - screenSize.x * 0.5;
    double end = screenSize.x * 0.5 + observer.x + incr;
    double first = true;

    sf::Vector2f offset(- observer.x + screenSize.x * 0.5 , screenSize.y - m_altitude);
    sf::Vector2f a,b;
    while (current < end){
        this->sample(current, observer.t, a, b, relativeOmega, relativeK);
        a += offset;
        b += offset;
        
        target->append(sf::Vertex(a, SIGNAL_COLOR));
        target->append(sf::Vertex(b, SIGNAL_COLOR));
        //if not the first time, points have to be added twice for the quads
        if (!first){
            //the order is reversed to have parallel edges
            target->append(sf::Vertex(b, SIGNAL_COLOR));
            target->append(sf::Vertex(a, SIGNAL_COLOR));
        }else {first = false;}
        current += incr;
    }
    //closing the last quad on itself
    target->append(sf::Vertex(a, SIGNAL_COLOR));
    target->append(sf::Vertex(b, SIGNAL_COLOR));
}

void EMWave::sample(double x, double t, sf::Vector2f& a, sf::Vector2f& b, double romega, double rk){
    double value = m_amplitude * (1 + cos(rk * x - romega * t));
    double derivative = - m_amplitude * rk * sin(rk * x - romega * t);
    a.x = x;
    //sfml reverses the y axis
    a.y = - value;
    //the second point is offsetted in the normal direction of derivation to ensure equal linewidth
    //remember that SFML reverses the y axis but not the x axis
    sf::Vector2f second_offset(-derivative, -1);
    second_offset /= (float) sqrt(1 + derivative * derivative);
    second_offset *= LINE_THICKNESS;
    /*sf::Vector2f second_offset(0, LINE_THICKNESS);*/
    b = a + second_offset;
}
