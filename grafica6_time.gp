set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'grafica6_time_Bin_vs_Auto.png'

set title "Tiempo Medio: Binaria vs Auto-organizada (Potencial)"
set xlabel "Tamaño del Diccionario (N)"
set ylabel "Tiempo (segundos)"
set grid
set key left top box

# Usamos formato científico porque los tiempos de la Binaria son cercanos a 0
set format y "%.1e"

plot "binaria_potencial.dat" using 1:2 with lines lw 2 lc rgb "black" title "Binaria (~0s)", \
     "auto_1.dat" using 1:2 with linespoints pt 7 ps 0.5 lc rgb "red" title "Auto (n=1)", \
     "auto_100.dat" using 1:2 with linespoints pt 5 ps 0.5 lc rgb "orange" title "Auto (n=100)", \
     "auto_10000.dat" using 1:2 with linespoints pt 9 ps 0.5 lc rgb "green" title "Auto (n=10000)"