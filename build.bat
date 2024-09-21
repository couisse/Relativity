@echo off
set sfmlpath=""
set obj="obj"
echo Creating working directory
mkdir %obj%
echo Building object files...
g++ -Wall -DSFML_STATIC -O2 -std=gnu++14 -I %sfmlpath%\include -c main.cpp -o %obj%\main.o
g++ -Wall -DSFML_STATIC -O2 -std=gnu++14 -I %sfmlpath%\include -c src\app\app.cpp -o %obj%\app.o
g++ -Wall -DSFML_STATIC -O2 -std=gnu++14 -I %sfmlpath%\include -c src\entities\periodicship.cpp -o %obj%\periodicship.o
g++ -Wall -DSFML_STATIC -O2 -std=gnu++14 -I %sfmlpath%\include -c src\entities\photons.cpp -o %obj%\photons.o
g++ -Wall -DSFML_STATIC -O2 -std=gnu++14 -I %sfmlpath%\include -c src\math\refframe.cpp -o %obj%\refframe.o
echo Creating executable...
g++ -L%sfmlpath%\lib -o Relativity.exe %obj%\main.o %obj%\app.o %obj%\periodicship.o %obj%\photons.o %obj%\refframe.o  -s  -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lgdi32 -lfreetype -lwinmm
echo Suppressing objects..
rmdir %obj% /s /q
echo Done!
pause