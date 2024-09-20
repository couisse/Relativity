#include <cmath>
#include "refframe.hpp"

const double C = 200;
const double C_2 = C * C;


ReferenceFrame::~ReferenceFrame() {}

ReferenceFrame::ReferenceFrame(double groundSpeed) : m_groundSpeed(groundSpeed) {}

const bool ReferenceFrame::operator==(const ReferenceFrame& other) const {
    return other.m_groundSpeed == m_groundSpeed;
}

double ReferenceFrame::lorentz(double speed){
    double beta = speed / C;
    return 1/sqrt(1 - beta * beta);
}

double ReferenceFrame::lorentz(const ReferenceFrame& other){
    return lorentz(this->relative_speed(other));
}

const double ReferenceFrame::relative_speed(const ReferenceFrame& other) const {
    //the speed of the ground relative to this frame is -this->m_groundSpeed
    double sum = other.m_groundSpeed - m_groundSpeed;
    double prod = - other.m_groundSpeed * m_groundSpeed;
    return sum / (1 + prod / C_2);
}


Position ReferenceFrame::transfer(const Position pos) {
    if ( (*pos.frame) == (*this)){ //no transformation if the frames are the sames
        return Position(pos.x, pos.t, this);
    }
    //the speed of the given reference frame relative to this one
    double v = this->relative_speed(*pos.frame);
    //the coefficient
    double gamma = this->lorentz(v);
    //special lorentz transformation
    double x = gamma * (pos.x + v * pos.t);
    double t = gamma * (pos.t + v * pos.x / C_2);
    return Position(x, t, this);
}

Coords ReferenceFrame::observe(const ReferenceFrame& other, Coords pos){
    //the speed of the given reference frame relative to this one
    double v = this->relative_speed(other);
    //the coefficient
    double gamma = this->lorentz(v);
    //getting space position in this frame
    double x = pos.x / gamma + v * pos.t;
    //getting time position in the other frame
    double t = gamma * (pos.t - v / C_2 * x);

    return Coords(x,t);
}
