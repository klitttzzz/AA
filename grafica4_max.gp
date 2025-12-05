set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'grafica4_max_OB_Bin_vs_Auto.png'

set title "OB Máximo (Peor Caso): Binaria vs Auto-organizada"
set xlabel "Tamaño del Diccionario (N)"
set ylabel "Máximo de Operaciones Básicas"
set grid
set key left top box

# En esta gráfica NO usamos logscale para evidenciar que el peor caso
# de la auto-organizada crece linealmente (diagonal), mientras que
# la binaria se mantiene plana en el suelo.

plot "binaria_potencial.dat" using 1:4 with lines lw 3 lc rgb "black" title "Binaria (Log N)", \
     "auto_1.dat" using 1:4 with linespoints pt 7 ps 0.5 lc rgb "red" title "Auto (n=1)", \
     "auto_100.dat" using 1:4 with linespoints pt 5 ps 0.5 lc rgb "orange" title "Auto (n=100)", \
     "auto_10000.dat" using 1:4 with linespoints pt 9 ps 0.5 lc rgb "green" title "Auto (n=10000)"