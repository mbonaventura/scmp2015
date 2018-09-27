## this assumes qss-solver is installed in default directories (~)
## execute in this same directory

# generate
~/qss-solver/bin/mmoc.sh -o ~/qss-solver/build/adr/adr ./adr.mo 

# compile and run
~/qss-solver/build/adr/adr.sh 

# copy locally
cp ~/qss-solver/build/adr/adr .
cp ~/qss-solver/build/adr/adr.ini .
