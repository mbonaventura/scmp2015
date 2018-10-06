set terminal wxt persist
set title "/home/simulations/qss-solver/build/adr/adr"
set ylabel "State Variables"
set xlabel "Time"
set grid
plot "u[1].dat" with lines title "u[1]"
