gcc -c "./geometry/geometry2D.c" -o "./geometry2D.o"
gcc -c "./geometry/geometry4D.c" -o "./geometry4D.o"
gcc -c "./physic/physic2D.c" -o "./physic2D.o"

ar rcs "./cphysic.a" "geometry4D.o" "./geometry2D.o" "./physic2D.o" 

rm "./geometry4D.o" "./geometry2D.o" "./physic2D.o"
