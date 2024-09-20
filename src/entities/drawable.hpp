#ifndef DRAWABLE_HPP_INCLUDED
#define DRAWABLE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "../math/refframe.hpp"

/** an entity that is attached to a referenced frame and can be drawn
*/

class DrawableEntity{

public:
    DrawableEntity(ReferenceFrame* frame) : m_frame(frame) {}
    virtual ~DrawableEntity() {}

    /* dumps vertices in target that can be drawn on the screen to simulate
     * what the observer would see from the entity, the observer being at the given
     * position (in space-time). Observer is considered to be at the center of the screen.
     * target is considered to be a Quads Array
     */
    virtual void get_vertices(Position observer, sf::Vector2u screenSize, sf::VertexArray* target) = 0;

protected:
    ReferenceFrame* m_frame;

};

#endif // DRAWABLE_HPP_INCLUDED
