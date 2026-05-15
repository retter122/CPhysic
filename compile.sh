echo "Compile CPhysic"

cd "./CPhysic"
bash "./compile.sh"
cd "../"

echo "Compile main.c"

gcc "./main.c" -o "./build/CPhysic.out" -lm -L./CPhysic/bin -lcphysic -lglfw3
