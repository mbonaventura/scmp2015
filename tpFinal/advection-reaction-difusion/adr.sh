cwd=$(pwd)
cd /home/simulations/qss-solver/build/adr/
make -f /home/simulations/qss-solver/build/adr/adr.makefile clean
make -f /home/simulations/qss-solver/build/adr/adr.makefile
./adr
cd $cwd
