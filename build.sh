export obj=obj
echo Creating working directory
mkdir $obj
echo Building object files...
g++ -Wall -DSFML_STATIC -O2 -std=gnu++14 -c main.cpp -o $obj/main.o
g++ -Wall -DSFML_STATIC -O2 -std=gnu++14 -c src/app/app.cpp -o $obj/app.o
g++ -Wall -DSFML_STATIC -O2 -std=gnu++14 -c src/entities/periodicship.cpp -o $obj/periodicship.o
g++ -Wall -DSFML_STATIC -O2 -std=gnu++14 -c src/entities/photons.cpp -o $obj/photons.o
g++ -Wall -DSFML_STATIC -O2 -std=gnu++14 -c src/math/refframe.cpp -o $obj/refframe.o
echo Creating executable...
g++ $obj/main.o $obj/app.o $obj/periodicship.o $obj/photons.o $obj/refframe.o  -o relativity -lsfml-graphics -lsfml-window -lsfml-system
echo Suppressing objects..
rm -r $obj
echo Done!