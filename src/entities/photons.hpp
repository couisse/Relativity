#ifndef PHOTONS_H_INCLUDED
#define PHOTONS_H_INCLUDED

#include "drawable.hpp"

/** The frame of reference objects can't handle lightspeed velocity
 *  Thus, we have to create a special entity that can travel at such speed
 *  This one is EMWave of wavelength lambda (in ground referential)
 */

class EMWave: public DrawableEntity{

public:
    /* The photon is defined by its orientation (true = +x)
     * its altitude, its wavelength and amplitude
     * /!\ wavelength is not the true wavelength, but the spatial
     * period of the wave in pixel in the ground frame.
     * Thus a value like 100 would be appropriated
     */
    EMWave(bool orientation, double altitude, double lambda, double amplitude);

    /*override from DrawableEntity */
    virtual void get_vertices(Position observer, sf::Vector2u screenSize, sf::VertexArray* target);

protected:
    bool m_orientation;
    double m_altitude;
    double m_omega;
    double m_k;
    double m_amplitude;

///internal methods
protected:
    void sample(double x, double t, sf::Vector2f& a, sf::Vector2f& b, double romega, double rk);
};

#endif // PHOTONS_H_INCLUDED
