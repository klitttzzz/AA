set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'grafica5_min_OB_Bin_vs_Auto.png'

set title "OB Mínimo (Mejor Caso): Binaria vs Auto-organizada"
set xlabel "Tamaño del Diccionario (N)"
set ylabel "Mínimo de Operaciones Básicas"
set grid
set key right center box

# Fijamos el rango Y de 0 a 5 porque el mínimo siempre será 1
set yrange [0:5]

plot "binaria_potencial.dat" using 1:5 with lines lw 3 lc rgb "black" title "Binaria", \
     "auto_1.dat" using 1:5 with linespoints pt 7 ps 0.5 lc rgb "red" title "Auto (n=1)", \
     "auto_100.dat" using 1:5 with linespoints pt 5 ps 0.5 lc rgb "orange" title "Auto (n=100)", \
     "auto_10000.dat" using 1:5 with linespoints pt 9 ps 0.5 lc rgb "green" title "Auto (n=10000)"