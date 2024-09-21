# Relativity
A small visualization of the effects of relativity on objects.

## Install
### Windows
There are two solutions: you can either use the precompiled release (all-in-one exe file [here](https://github.com/couisse/Relativity/releases)) or install SFML [here](https://www.sfml-dev.org/download-fr.php) before executing `build.bat`. It will generate the executable, letting you use the app \
NOTE: you have to specify the SFML install path in the batch, in the variable `sfmlpath`

### Linux
You have to install SFML. On Ubuntu, that can simply be done using `sudo apt-get install libsfml-dev`. If you're using another distribution, you should be able to install it [there](https://www.sfml-dev.org/download-fr.php). Then simply run `build.sh` to generate the executable.

## Usage 
The program will let you create multiple galilean frames of reference you'll be able to cycle through, to see the effects of Lorentz's transformation, including:
* Time dilation
* Length contraction
* Loss of synchronization
* constancy of EM waves travel speed
<!-- End of list -->
To do so, each frame of reference will include an infinite line of regularly spaced squares with synchronized (in their reference frame) pulsating light at 1Hz, and a travelling EM on top of screen.\
NOTE: be careful to read all the text in the console, even if another window pops up.\
NOTE: the program still has a lot of bugs. In case a problem arises, don't hesitate to kill the window/process, it won't cause any harm to your device.

## Future
Other functionalities may one day be added, like a more general relativistic mechanics engines
