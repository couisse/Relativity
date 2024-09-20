#ifndef PERIODICSHIP_HPP_INCLUDED
#define PERIODICSHIP_HPP_INCLUDED

#include "drawable.hpp"

/** This entity is designed to look like an infinite line of spaceships,
 *  to help visualize the effects of relativity
 */

class PeriodicShip : public DrawableEntity {

public:
    /*the ships are attached to a reference frame, fly at a given altitude, have a size and a space period*/
    PeriodicShip(ReferenceFrame* frame, double altitude, double size, double period);
    virtual ~PeriodicShip() {}

    /*override from DrawableEntity */
    virtual void get_vertices(Position observer, sf::Vector2u screenSize, sf::VertexArray* target);

///Attributes
protected:
    double m_altitude, m_size, m_period;

///Internal methods
protected:
    /*adds vertices in the target Array for one ship in position x in viewing frame and t in the attached frame
      y_offset and x_offset are controlling the origin of the window. gamma is precalculated Lorentz factor
    */
    void addShip(Coords settings, double gamma, sf::VertexArray* target, double y_offset, double x_offset);
};


#endif // PERIODICSHIP_HPP_INCLUDED
