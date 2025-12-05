set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'grafica3_avg_OB_Bin_vs_Auto.png'

set title "OB Promedio: Binaria vs Auto-organizada (Potencial)"
set xlabel "Tamaño del Diccionario (N)"
set ylabel "Número Medio de OBs (Escala Log)"
set grid
set key right top box

# --- ESCALA LOGARÍTMICA ---
# Fundamental para ver datos grandes (5000) y pequeños (10) a la vez
set logscale y

# Graficamos los 4 archivos
plot "binaria_potencial.dat" using 1:3 with lines lw 3 lc rgb "black" title "Binaria (Referencia)", \
     "auto_1.dat" using 1:3 with linespoints pt 7 ps 0.5 lc rgb "red" title "Auto (n_times=1)", \
     "auto_100.dat" using 1:3 with linespoints pt 5 ps 0.5 lc rgb "orange" title "Auto (n_times=100)", \
     "auto_10000.dat" using 1:3 with linespoints pt 9 ps 0.5 lc rgb "green" title "Auto (n_times=10000)"