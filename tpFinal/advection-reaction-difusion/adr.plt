set terminal wxt persist
set title "/home/simulations/qss-solver/build/adr/adr"
set ylabel "State Variables"
set xlabel "Time"
set grid
plot "u[100].dat" with lines title "u[100]","u[300].dat" with lines title "u[300]","u[500].dat" with lines title "u[500]","u[700].dat" with lines title "u[700]","u[900].dat" with lines title "u[900]","u[1000].dat" with lines title "u[1000]"
