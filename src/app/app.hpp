#ifndef APP_HPP_INCLUDED
#define APP_HPP_INCLUDED

#include <iostream>

#include "../entities/periodicship.hpp"
#include "../entities/photons.hpp"

//asks the user for a value in an interval
int askInt(int lowest, int highest);
double askDouble(double lowest, double highest);

/* the menu of the application. if returns false, the app should close */
bool menu();

/* the frame of reference experiment */
void refEperiment();

#endif // APP_HPP_INCLUDED
