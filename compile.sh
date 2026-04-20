echo "Compile CPhysic"

cd "./CPhysic"
bash "./compile.sh"
cd "../"
mv "./CPhysic/cphysic.a" "./bin"

echo "Compile main.c"

gcc "./main.c" "bin/libglfw3.a" "bin/cphysic.a" -o "./build/CPhysic.out"  -lm
