gcc -c "./geometry/geometry2D.c" -o "./geometry2D.o"
gcc -c "./geometry/geometry4D.c" -o "./geometry4D.o"
gcc -c "./physic/physic2D.c" -o "./physic2D.o"
gcc -c "./graphics/graphics_gl.c" -o "./graphics_gl.o"

ar rcs "./bin/libcphysic.a" "geometry4D.o" "./geometry2D.o" "./physic2D.o" "./graphics_gl.o"

rm "./geometry4D.o" "./geometry2D.o" "./physic2D.o" "./graphics_gl.o"
