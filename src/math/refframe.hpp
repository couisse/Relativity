#ifndef REFFRAME_HPP_INCLUDED
#define REFFRAME_HPP_INCLUDED

/** The celerity of light, expressed in px/s
 *  It is purposefully low to observe relativity effects
 */
extern const double C;

/** This class is meant to represent a
 * Galilean frame of reference
 *
 */
class ReferenceFrame;

/** A position is defined by a position in space and in time,
 * relative to a frame of reference
 */
struct Position{
    double x, t;
    ReferenceFrame* frame;
    Position(double x_, double t_, ReferenceFrame* f) : x(x_), t(t_), frame(f) {}
};

/** A simple pair of position and time value, not relative to a specific frame **/
struct Coords{
    double x, t;
    Coords(double x_ = 0, double t_ = 0) : x(x_), t(t_) {}
};

/** All frames of referenced are defined
 * by their speed (constant, since they are Galilean)
 * relative to the ground. It is a double, since this
 * program only deals with one dimensional movement.
 * they all start at the same point at the origin of time
 */
class ReferenceFrame{
///public methods
public:
    ReferenceFrame(double groundSpeed);
    ~ReferenceFrame();

    /*transforms the given position to be relative
      to this frame of reference*/
    Position transfer(const Position pos);

    /*given a space position in another frame and a time position in this frame,
      return the time position in the other frame and the space position in this
      frame such that the two positions correspond. The format is the same than
      regular Position: space then time
      This is useful when observing an entity: we know the wanted observation time
      (in this frame) and the spatial position of the entity (in its frame), but not
      its relative time or its apparent position [hence the name] */
    Coords observe(const ReferenceFrame& other, Coords pos);


    /*returns lorentz coefficient */
    static double lorentz(double speed);
    double lorentz(const ReferenceFrame& other);

    /*tests if two reference frames are the same (have the same speed)*/
    const bool operator==(const ReferenceFrame& other) const;

    /*calculates the relative speed of the given reference frame
     in this one */
    const double relative_speed(const ReferenceFrame& other) const;

    /*accessor to the ground speed*/
    const double ground_speed() const {return m_groundSpeed;}

protected:
    double m_groundSpeed;
};

#endif // REFFRAME_HPP_INCLUDED
